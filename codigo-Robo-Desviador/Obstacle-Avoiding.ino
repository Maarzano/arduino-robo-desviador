// Define os pinos dos motores
#define LEFT_MOTOR_BACKWARD 5
#define LEFT_MOTOR_FORWARD 6
#define RIGHT_MOTOR_BACKWARD 7
#define RIGHT_MOTOR_FORWARD 8

// Define os pinos do sensor ultrassônico
#define ECHO_PIN A4
#define TRIGGER_PIN A5

#define SPEED_INCREMENT 2
#define INITIAL_MOTOR_SPEED 80

int motorSpeed = INITIAL_MOTOR_SPEED; // Variavel para velocidade inicial do motor

const int MIN_DISTANCE = 15; // Distância mínima para desvio em cm

void setup() {
  // Define os pinos do motor como saída
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);

  // Define os pinos do sensor ultrassônico como entrada e sáida
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Inicializa a comunicação serial
  Serial.begin(9600);
}

void loop() {
  long distance = measureDistance(); // Mede a distância do objeto mais próximo

  if (distance < MIN_DISTANCE) {
    motorSpeed = INITIAL_MOTOR_SPEED;
    moveBackward();
    delay(500);
    stopMotors();
    delay(150);
    turnRight();
    delay(600);
    stopMotors();
    delay(150);

  } else {
    moveForwardFull();
  }

  // Imprime a distância medida no monitor serial
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void stopMotors() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void moveForwardFull() {

  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);

  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);

}

void moveForward() {

    // Aumenta gradualmente a velocidade do motor
    if (motorSpeed < 255) {
      motorSpeed = min(motorSpeed + SPEED_INCREMENT, 255); // Garante que a velocidade não exceda 255
    }

  // Define a velocidade do motor
  analogWrite(LEFT_MOTOR_FORWARD, motorSpeed);
  analogWrite(RIGHT_MOTOR_FORWARD, motorSpeed);

  // Move o motor para frente
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);

  
  delay(1);
}

void moveBackward() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
}

void turnLeft() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void turnRight() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
}

long measureDistance() { //metódo de medição de distancia
  delay(50);
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration / 58; // Converte a duração para distância
  return distance;
}
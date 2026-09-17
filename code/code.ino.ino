#include <Servo.h>

#define trigPin 8
#define echoPin 10

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

#define SERVO_PIN 6

long duration;
int distance;

Servo myServo;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(90);   // Center position
}

void loop() {

  distance = getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  // If ultrasonic fails
  if(distance == 0){
    stopMotor();
    return;
  }

  if (distance > 10) {
    moveForward();
  } 
  else {

    stopMotor();
    delay(100);

    myServo.write(150);   // Look left
    delay(300);

    turnLeft();
    delay(300);

    stopMotor();
    myServo.write(90);    // Center again
  }

  delay(100);
}

// ---------- FUNCTIONS ----------

int getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);  // timeout added

  distance = duration * 0.034 / 2;

  return distance;
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
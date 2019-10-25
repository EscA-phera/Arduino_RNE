# include <SoftwareSerial.h>

# define LEFT_A1 4
# define LEFT_B1 5
# define RIGHT_A2 6
# define RIGHT_B2 7
# define UnderLeftMotor_A1 8
# define UnderLeftMotor_B1 9
# define UnderRightMotor_A2 10
# define UnderRightMotor_B2 11

SoftwareSerial mySerial(2, 3);
char value;

void setup () {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(LEFT_A1, OUTPUT);
  pinMode(RIGHT_A2, OUTPUT);
  pinMode(LEFT_B1, OUTPUT);
  pinMode(RIGHT_B2, OUTPUT);
  pinMode(UnderLeftMotor_A1, OUTPUT);
  pinMode(UnderLeftMotor_B1, OUTPUT);
  pinMode(UnderRightMotor_A2, OUTPUT);
  pinMode(UnderRightMotor_B2, OUTPUT);
}

void loop() {
  while (mySerial.available()) {
    value = mySerial.read();
    Serial.print(value);

    if (value == 'l') {
      left();
      delay(1000);
      left_force();
      delay(1000);
      forward();
    }

    else if (value == 'r') {
      right();
      delay(1000);
      right_force();
      delay(1000);
      forward();
    }

    else if (value == 's') {
      stop();
    }

    else {
      forward();
    }
  }
}

void forward() {
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, HIGH);
  digitalWrite(RIGHT_B2, LOW);
  digitalWrite(UnderLeftMotor_A1, HIGH);
  digitalWrite(UnderLeftMotor_B1, LOW);
  digitalWrite(UnderRightMotor_A2, HIGH);
  digitalWrite(UnderRightMotor_B2, LOW);
}

void left() {
  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_B1, HIGH);
  digitalWrite(RIGHT_A2, HIGH);
  digitalWrite(RIGHT_B2, LOW);
  digitalWrite(UnderLeftMotor_A1, HIGH);
  digitalWrite(UnderLeftMotor_B1, LOW);
  digitalWrite(UnderRightMotor_A2, HIGH);
  digitalWrite(UnderRightMotor_B2, LOW);
}

void left_force () {
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B2, HIGH);
  digitalWrite(UnderLeftMotor_A1, LOW);
  digitalWrite(UnderLeftMotor_B1, LOW);
  digitalWrite(UnderRightMotor_A2, LOW);
  digitalWrite(UnderRightMotor_B2, LOW);
}

void right() {
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B2, HIGH);
  digitalWrite(UnderLeftMotor_A1, HIGH);
  digitalWrite(UnderLeftMotor_B1, LOW);
  digitalWrite(UnderRightMotor_A2, HIGH);
  digitalWrite(UnderRightMotor_B2, LOW);
}

void right_force () {
  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_B1, HIGH);
  digitalWrite(RIGHT_A2, HIGH);
  digitalWrite(RIGHT_B2, LOW);
  digitalWrite(UnderLeftMotor_A1, LOW);
  digitalWrite(UnderLeftMotor_B1, LOW);
  digitalWrite(UnderRightMotor_A2, LOW);
  digitalWrite(UnderRightMotor_B2, LOW);
}

void stop() {
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, HIGH);
  digitalWrite(RIGHT_B2, LOW);
  digitalWrite(UnderLeftMotor_A1, LOW);
  digitalWrite(UnderLeftMotor_B1, LOW);
  digitalWrite(UnderRightMotor_A2, LOW);
  digitalWrite(UnderRightMotor_B2, LOW);
}

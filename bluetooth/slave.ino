// https://deneb21.tistory.com/267
// https://deneb21.tistory.com/311
// LEFT, RIGHT가 조향용 모터임

# include <SoftwareSerial.h>

# define LEFT_A1 4
# define LEFT_B1 5
# define RIGHT_A2 6
# define RIGHT_B2 7
# define UnderLeftMotor_A1 8
# define UnderLeftMotor_B1 9
# define UnderRightMotor_A2 10
# define UnderRightMotor_B2 11

SoftwareSerial HM10(2, 3);
String real_value;

void setup () {
  Serial.begin(9600);
  HM10.begin(9600);
  delay(4500);
  HM10.println("AT+ROLE0");

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
  while (HM10.available()) {
    char value = (char)HM10.read();
    real_value += value;
    delay(5);
  }

  if (!real_value.equals("")) {
    Serial.println("" + real_value);

    if (real_value == "l") {
      left();
      delay(1000);
      left_force();
      delay(1000);
      forward();
      delay(60000);
    }

    if (real_value == "r") {
      right();
      delay(1000);
      right_force();
      delay(1000);
      forward();
      delay(60000);
    }

    if (real_value == "s") {
      stop(); 
      delay(60000);
    }

    if (real_value == "f") {
      forward();
      delay(60000);
    }
  }

  if (Serial.available()) {
    HM10.write(Serial.read());
  }
}

/*
 * 아래 구문은 장비 조향 부분
 * HIGH : 모터 속도 255, LOW : 모터 속도 0
 * 모터를 이렇게 사용하는 코딩은 처음해봐서 동작이 이상할 수 있으니
 * 양해해주고 이상하게 동작하는 부분만 HIGH - LOW 바꿔가면서
 * 조져보면 될듯
 * left_force - 조향 왼쪽으로 돌렸을 때 조향키만 원래대로 재조정
 * right_force - 조향 오른쪽으로 돌렸을 때 조향키만 원래대로 재조정
 */

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

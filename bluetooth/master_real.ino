#include <SoftwareSerial.h>

SoftwareSerial HM10(2,3); // TX, RX
int i = 1;

void setup() {
  Serial.begin(9600);
  HM10.begin(9600);

  for (i; i <= 1; i++) {
    HM10.println("AT+CONA**"); // CONA 뒤 '**' 부분에 장비 아두이노의 mac 주소를 ':' 빼고 입력
                               // etc; AT+CONA123456789012
    delay(2000);
    HM10.println("AT+ROLE1"); // master 지정
    delay(2000);
  }

  while (1) {
    HM10.println("l"); // l(left) 무한 반복
  }
}

void loop() {
  if (HM10.available()) {
    Serial.write(HM10.read());
  }
  if (Serial.available()) {
    HM10.write(Serial.read());
  }
}

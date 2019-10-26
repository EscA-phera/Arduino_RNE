// https://deneb21.tistory.com/267

#include <SoftwareSerial.h>

SoftwareSerial HM10(2,3); // TX, RX
int i = 1;

void setup() {
  Serial.begin(9600);
  HM10.begin(9600);

  for (i; i <= 1; i++) {
    HM10.println("AT+CONA**"); // CONA 뒤 '**' 부분에 장비 아두이노의 mac 주소를 ':' 빼고 입력
                               // etc; 가령 mac 주소가 12:34:56:78:90:12 라고 가정할 때,
                               // etc; AT+CONA123456789012 -> HM10.println("AT+CONA123456789012")
                               // 이상하게 우리 HM10만 인터넷에 나오는 HM10 명령어와 다름 주의
                               // 참고로 mac 주소 확인할 때에는 master_test.ino 다운받아서
                               // 시리얼창 열고 AT 쳐서 블루투스 반응 확인한 후
                               // OK 뜨면 AT+LADDR 쳐서 확인 가능.
    delay(2000);
    HM10.println("AT+ROLE1"); // master 지정
    delay(2000);
  }

  while (1) {
    HM10.println("l"); // l(left) 무한 반복, f = 전진, r = 우회전, s = 정지
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

# include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

void setup () {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop () {
  if (mySerial.available()) {
    mySerial.write("l"); /*
                             l = left, r = right, s = stop
                         */
    delay(500);
  }
}

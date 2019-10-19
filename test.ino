/*!
 * Copyright: Copyright (c) 2019, Nalssam
 */
# include <SoftwareSerial.h>
# include <WiFi.h>

/*!
 * third-party library
 * 1. TinyGPS - Copyright: Copyright (c) 2008 - 2013, Mikal Hart
              - Usage: To check the position of the equipment and to make it move autonomously
              
 * 2. ArduinoJson - Copyright: Copyright (c) 2014 - 2019, Benoit BLANCHON
                  - Usage: To POST Data to server from arduino using Json Array
 */
# include <TinyGPS.h>
# include <ArduinoJson.h>

// arduino GPS
# define RXPIN 6
# define TXPIN 5
# define GPSBAUD 9600

// WiFi Setting
char ssid[] = "Daeshin_Public_WiFi";
char pass[] = "12341234";
int status = WL_IDLE_STATUS;
unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 5000L;
String rcvbuf;
boolean getIsConnected = false;

// server host-IP
IPAddress hostIp(18, 191, 157, 204);
int SERVER_PORT = 80;
WiFiClient client;

// GPS setting
TinyGPS gps;
SoftwareSerial uart_gps(RXPIN, TXPIN);
void get_gps(TinyGPS &gps);

void setup() {
  Serial.begin(9600);
  Serial.println();

  uart_gps.begin(GPSBAUD); // gps check
  status = WiFi.begin(ssid, pass); // WiFi check

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi is not connected");

    while(true);
  }
  else {
    Serial.println("WiFi is loading now.");
  }

  Serial.print(F("Firmware version: "));
  Serial.println(WiFi.firmwareVersion());

  if (status != WL_CONNECTED) {
    Serial.println("WiFi Connection is failed.");
    while(true);
  }

  else {
    Serial.println("Successfully Connected");
  }
}

void loop() {
  while(uart_gps.available()) {
    int c = uart_gps.read();

    if(gps.encode(c)) {
      get_gps(gps);
    }
  }
}

void get_gps (TinyGPS &gps) {
  float latitude, longitude;
  gps.f_get_position(&latitude, &longitude);

  // latitude + longitude + client_id to Json Array
  String jsondata = "";

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["client_code"] = "test_bot_1";
  root["latitude"] = latitude;
  root["longitude"] = longitude;
  root["speed_kmph"] = gps.f_speed_kmph();
  root.printTo(jsondata);

  client.print(F("POST /gpsdata")); // POST json data from Arduino WiFi Module to Server using Python Flask
  client.print(F("HTTP/1.1\r\n")); // to HTTP RESTFul-API server
  client.print(F("Cache-Control: no-cache\r\n")); // not using cache
  client.print(F("HOST: esphera.xyz\r\n")); // HOST NAME: esphera.xyz using AWS EC2
  client.print(F("User-Agent: Arduino\r\n")); // U.A: Arduino
  client.print(F("Content-Type: application/json\r\n")); // Content Type - log
  client.print(F("Content-Length: "));
  client.print(jsondata.length());
  client.println();
  client.println(jsondata); // Json Data
  client.print(F("\r\n\r\n"));

  lastConnectionTime = millis();
  getIsConnected = true;

  unsigned long chars;
  unsigned short sentences, failed_checksum;
  gps.stats(&chars, &sentences, &failed_checksum);
  delay(1500);

  int headcount = 0;
  while (client.connected()) {
    
    if (client.available() && status == WL_CONNECTED) {
      char client_test = client.read();
      rcvbuf += client_test;

        if (client_test == '\r') {
          headcount ++ ;

          if (headcount != 13) {
            rcvbuf = "";
          }
        }

          if (headcount == 13) {
            StaticJsonBuffer<200> jsonBuffer;
            JsonObject& root = jsonBuffer.parseObject(rcvbuf);
            String result = root["result"];

            if (result == "left") {
              
            }

            else if (result == "right") {
              
            }
            else if (result == "true") {
              break;
            }
            else if (result == "false") {
              
            }
    }
  }
  }
  client.flush();
  client.stop();
}

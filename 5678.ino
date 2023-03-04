#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>
/**
   NodeMCU v3 (ESP8266)
   RX = GPIO 5 (D1)
   TX = GPIO 4 (D2)
*/
SoftwareSerial arduinocon(D1, D0);


const char* ssid = "LAPTOP-0N2B010N 3481";
const char* pass = "00000000";
#define LINE_TOKEN "Y4nxVsjcnBK1ripNtdP4sgYk9hi4DbFSLtauMVIRnbw"

void setup() {
  Serial.begin(115200);
  arduinocon.begin(57600);
  Serial.printf("WiFi connecting to %s\n",  ssid);
  Serial.println(LINE.getVersion());
  WiFi.begin(ssid, pass);
  LINE.setToken(LINE_TOKEN);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("Wi-Fi connected to "); //แสดงว่าเชื่อมต่อ Wi-Fi ได้แล้ว
  Serial.println(ssid);
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP()); //แสดง IP ของบอร์ดที่ได้รับแจกจาก AP
  Serial.println("Start");

}

void loop() {
  char inByte;

  while (arduinocon.available() > 0) {
    inByte = arduinocon.read();
    Serial.print(inByte);
    //Serial.println("*");
  }

  switch (inByte) {
    case 'A':
      LINE.notify("เปิดระบบแจ้งทางไลน์");
      //Serial.println("เปิดระบบแจ้งทางไลน");
      break;

    case 'a':
      LINE.notify("ปิดระบบแจ้งทางไลน์");
      //Serial.println("ปิดระบบแจ้งทางไลน์");
      break;

    case 'B':
      LINE.notify("อุณหภูมิในน้ำสูงกว่าปกติ");
      //Serial.println("เปิดระบบแจ้งทางไลน");
      break;

    case 'b':
      LINE.notify("อุณหภูมิในน้ำต่ำกว่าปกติ");
      //Serial.println("ปิดระบบแจ้งทางไลน์");
      break;
      
    case '1':
      LINE.notify("อุณหภูมิในน้ำปกติ");
      //Serial.println("ปิดระบบแจ้งทางไลน์");
      break;
  }
}

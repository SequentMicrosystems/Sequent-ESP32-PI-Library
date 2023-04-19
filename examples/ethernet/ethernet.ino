/*
 * This sketch demonstrate the usage of the Ethernet port on the Sequent Microsystems 
 * ESP32 Raspberry Pi Alternative card.
 * Please connect a ethernet cable to the card and 
 * open the Serial Monitor to see the results
 */
#include "SM_ESP32Pi.h"
#include "Ethernet.h"

char server[] = "httpbin.org";

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

#define MYIPADDR 192,168,1,28
#define MYIPMASK 255,255,255,0
#define MYDNS 192,168,1,1
#define MYGW 192,168,1,1

EthernetClient client;
SM_ESP32Pi esp = SM_ESP32Pi(1);// pin header pin number type

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement

void setup() {
  unsigned int i = 0;
  Serial.begin(115200);
  delay(1000);

  esp.begin(1);// debug enable

  Ethernet.init(SM_ESP32PI_ETH_CS);
  nbDelay(1000);
  if (Ethernet.begin(mac)) { // Dynamic IP setup
    Serial.println("DHCP OK!");
  } else {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }

    IPAddress ip(MYIPADDR);
    IPAddress dns(MYDNS);
    IPAddress gw(MYGW);
    IPAddress sn(MYIPMASK);
    Ethernet.begin(mac, ip, dns, gw, sn);
    Serial.println("STATIC OK!");
  }
  nbDelay(5000);


  Serial.print("Local IP : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Gateway IP : ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server : ");
  Serial.println(Ethernet.dnsServerIP());

  Serial.println("Ethernet Successfully Initialized");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("Connected!");
    // Make a HTTP request:
    client.println("GET /get HTTP/1.1");
    client.println("Host: httpbin.org");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  beginMicros = micros();
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  int len = client.available();
  if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    client.read(buffer, len);
    if (printWebData) {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }
    byteCount = byteCount + len;
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    endMicros = micros();
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    Serial.print("Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(", rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();

    // do nothing forevermore:
    while (true) {
      nbDelay(1);
    }
  }

}

#define ON_TIME_MS 50
#define PERIOD_MS 1000

void heartBeat()
{
  static int period = ON_TIME_MS;
  static unsigned long tms = 0;

  if ((millis() > (tms + period)) || (millis() < tms))
  {
    tms = millis();
    if (period == ON_TIME_MS)
    {
      //esp.led(0); //library function
      digitalWrite(SM_ESP32PI_LED, LOW);//builtin function with library definition SM_ESP32PI_LED
      period = PERIOD_MS - ON_TIME_MS;
    }
    else
    {
      //esp.led(1);//library function
      digitalWrite(SM_ESP32PI_LED, HIGH);//builtin function with library definition SM_ESP32PI_LED
      period = ON_TIME_MS;
    }
  }
}

void nbDelay(int milliseconds)
{
  unsigned long time_now = 0;

  time_now = millis();
  while (millis() < time_now + milliseconds)
  {
    heartBeat();
  }
}

/*
 * GPIO usage example for Sequnt Microsystems ESP32 Raspberry Pi Alternative Card
 * Save the example in a different place and switch between test the inputs and 
 * the outputs by commenting the defines below
 * For the OUTPT test you will see 0.5HZ square wave on each available pin
 * For the INPUT test you will get transition on the Serial monitor console
 */
#include "SM_ESP32Pi.h"

//#define TEST_OUTPUT 1
#define TEST_INPUT 1

SM_ESP32Pi esp = SM_ESP32Pi(1);// pin header pin number type one based counting [1..40]

void setup()
{
  unsigned int i = 0;
  Serial.begin(115200);
  delay(1000);
  esp.begin(1);

#ifdef TEST_OUTPUT
  Serial.println("Digital output test begin");
  Serial.println("Togle all pins at 0.5Hz");
  nbDelay(1000);
  for (i = 1; i <= RASP_HEADER_PIN_COUNT; i++)
  {
    Serial.printf("H: %d  ESP: %d\n", i, esp.header2Gpio(i));
    esp.pinDir(i, OUTPUT);
  }
#elif TEST_INPUT
  Serial.println("Digital input test begin");
  nbDelay(1000);
  for (i = 1; i <= RASP_HEADER_PIN_COUNT; i++)
  {
    esp.pinDir(i, INPUT);
  }
#endif
}


void loop()
{
  unsigned int i = 0;
  int val  = 0;
  static int lastPin[RASP_HEADER_PIN_COUNT];

#ifdef TEST_OUTPUT
  for (i = 1; i <= RASP_HEADER_PIN_COUNT; i++)
  {
    esp.pinWrite(i, HIGH);//library digital write function
//    if(esp.header2Gpio(i) > -1) // find ESP GPIO number, avoid power and NC pins
//    {
//      digitalWrite(esp.header2Gpio(i), HIGH);
//    }
  }
  nbDelay(1000);
  for (i = 1; i <= RASP_HEADER_PIN_COUNT; i++)
  {
    esp.pinWrite(i, LOW);
  }
  nbDelay(1000);

#elif TEST_INPUT
  for (i = 1; i <= RASP_HEADER_PIN_COUNT; i++)
  {
    val = esp.pinRead(i);
    if ( lastPin[i] != val)
    {
      Serial.printf("Pin %d goes to %d\n", i + 1, val);
      lastPin[i] = val;
    }
  }
  nbDelay(1000);
#endif
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

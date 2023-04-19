#ifndef SM_ESP32_PI_H__
#define SM_ESP32_PI_H__

#include "Arduino.h"
#include <inttypes.h>

#define RASP_GPIO_COUNT 28
#define RASP_HEADER_PIN_COUNT 40
#define OK 0

#define SM_ESP32PI_LED 2
#define SM_ESP32PI_ETH_CS 4
#define SM_ESP32PI_SDCARD_CS 5
#define SM_ESP32PI_SPI_CS 5
#define SM_ESP32PI_ETH_INT 39

#define SM_ESP32PI_PIN_MODE_RASPBERRY 0
#define SM_ESP32PI_PIN_MODE_HEADER 1

class SM_ESP32Pi
{
	public:
		SM_ESP32Pi(uint8_t pinNoType = 0);//refere to pins as Raspberry GPIO (pinNoType = 0) or as pin number of the 40 pins header (pinNoType = 1)
		void begin(uint8_t debug = 0);
		void pinDir(unsigned int pin, int mode);
		void pinWrite(unsigned int pin, int val);
		int pinRead(unsigned int gpio);
		void led(uint8_t val);
		int header2Gpio(int pin);
		int raspGpio2Gpio(int pin);
	private:
		uint8_t __pinNoType;
		uint8_t __debug;
		int isDebugPin(int pin);
		int isDebugGpio(int gpio);
};


#endif //SM_ESP32_PI_H__
extern "C" {
#include <inttypes.h>
}
#include "Arduino.h"
#include "Wire.h"
#include "SM_ESP32Pi.h"

#define GPIO_DEBUG_TX 1
#define GPIO_DEBUG_RX 3

#define PIN_TYPE_POWER 200
#define PIN_TYPE_GND 201
#define PIN_TYPE_DISCONNECTED 100

//Raspberry GPIO to ESP, zero based
const int gpioMaping[RASP_GPIO_COUNT] =
{
	1, 3, 201, 201, 336, 14, 12, 334, 5, 19, 23, 18, 25, 33, 17, 16, 13, 339, 101, 102,
	15, 104, 26, 335, 32, 103, 27, 104
};

//Raspberry 40 pin connector pin number to ESP GPIO  [0,1..40]
const int pinMaping[RASP_HEADER_PIN_COUNT +1] = {203, 200, 200, 201, 200, 201, 200, 336,
	17, 200, 16, 339, 101, 104, 200, 26, 335, 200, 32, 23, 200, 19, 103, 18, 5,
	200, 334, 1, 3, 14, 200, 12, 25, 33, 200, 102, 13, 27, 15, 200, 104};

SM_ESP32Pi::SM_ESP32Pi(uint8_t pinNoType)
{
	__pinNoType = pinNoType;
	__debug = 0;
}

void SM_ESP32Pi::begin(uint8_t debug)
{
     __debug = debug;
	 pinMode(SM_ESP32PI_LED, OUTPUT);
	 digitalWrite(SM_ESP32PI_LED, LOW);
}

void SM_ESP32Pi::pinDir(unsigned int pin, int mode)
{
	if (__pinNoType == 0)
	{
		if (pin < RASP_GPIO_COUNT && !isDebugGpio(pin))
		{
			if (gpioMaping[pin] < 100)
			{
				pinMode(gpioMaping[pin], mode);
			}
			else if((gpioMaping[pin] > 300) && (mode == INPUT))
			{
				pinMode(gpioMaping[pin]-300, mode);
			}
		}
	}
	else
	{
		if (pin <= RASP_HEADER_PIN_COUNT && !isDebugPin(pin))
		{
			if (pinMaping[pin] < 100)
			{
				pinMode(pinMaping[pin], mode);
			}
			else if((pinMaping[pin] > 300) && (mode == INPUT))
			{
				pinMode(pinMaping[pin]-300, mode);
			}
		}
	}
}

void SM_ESP32Pi::pinWrite(unsigned int pin, int val)
{
	if (__pinNoType == 0)
	{
		if (pin < RASP_GPIO_COUNT && !isDebugGpio(pin))
		{
			if (gpioMaping[pin] < 100)
			{
				digitalWrite(gpioMaping[pin], val);
			}
		}
	}
	else
	{
		if (pin <= RASP_HEADER_PIN_COUNT && !isDebugPin(pin))
		{
			if (pinMaping[pin] < 100)
			{
				digitalWrite(pinMaping[pin], val);
			}
		}
	}
}

int SM_ESP32Pi::pinRead(unsigned int pin)
{
	if (__pinNoType == 0)
	{
		if (pin < RASP_GPIO_COUNT && !isDebugGpio(pin))
		{
			if (gpioMaping[pin] < 100)
			{
				return digitalRead(gpioMaping[pin]);
			}
			else if(gpioMaping[pin] > 300)
			{
				return digitalRead(gpioMaping[pin] - 300);
			}
		}
	}
	else
	{
		if (pin <= RASP_HEADER_PIN_COUNT && !isDebugPin(pin))
		{
			if (pinMaping[pin] < 100)
			{
				return digitalRead(pinMaping[pin]);
			}
			else if(pinMaping[pin] > 300)
			{
				return digitalRead(pinMaping[pin] - 300);
			}
		}
	}
	return 0;
}

int SM_ESP32Pi::header2Gpio(int pin)
{
	if (pin <= RASP_HEADER_PIN_COUNT && !isDebugPin(pin))
	{
		if (pinMaping[pin] < 100)
		{
			return pinMaping[pin];
		}
	}
	return -1; //invalid or power or input only pin.
}

int SM_ESP32Pi::raspGpio2Gpio(int pin)
{
	if (pin < RASP_GPIO_COUNT && !isDebugGpio(pin))
	{
		if (gpioMaping[pin] < 100)
		{
			return gpioMaping[pin];
		}
	}
	return -1; //invalid or power or input only pin.
}

void SM_ESP32Pi::led(uint8_t val)
{
	digitalWrite(SM_ESP32PI_LED, val);
}

int SM_ESP32Pi::isDebugPin(int pin)
{
	if ( (0 != __debug)
		&& ( (pinMaping[pin] == GPIO_DEBUG_TX)
			|| (pinMaping[pin] == GPIO_DEBUG_RX)))
	{
		return 1;
	}
	return 0;
}

int SM_ESP32Pi::isDebugGpio(int gpio)
{
	if ( (0 != __debug)
		&& ( (gpioMaping[gpio] == GPIO_DEBUG_TX)
			|| (gpioMaping[gpio] == GPIO_DEBUG_RX)))
	{
		return 1;
	}
	return 0;
}

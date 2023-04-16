/*
 *	Библиотека для управления моторами проекта Time
 *	v 1.5
 *	Разработчик Хартанен А.В.
 */

#ifndef Motors_h
#define Motors_h
 
#include <Arduino.h>

extern volatile uint8_t* _directionInReg0;
extern volatile uint8_t* _directionInReg1;
extern volatile uint8_t* _directionInReg2;
extern volatile uint8_t* _directionInReg3;

extern uint8_t _directionBitMask0;
extern uint8_t _directionBitMask1;
extern uint8_t _directionBitMask2;
extern uint8_t _directionBitMask3;

extern volatile int16_t nMotorEncoder[4];

class Motors
{
	public:
		Motors(uint8_t pinPWM, uint8_t pinA, uint8_t pinB);
		Motors(uint8_t pinPWM, uint8_t pinA, uint8_t pinB, uint8_t interruptNumber, uint8_t directionPin);
		void set(int16_t pwm);
		void stop();
	private:
		//void _offPWM(uint8_t timer);
		//void _onPWM(uint8_t timer, int16_t val);
		uint8_t _portPWM;
		uint8_t _portA;
		uint8_t _portB;
		uint8_t _bitMaskPWM;
		uint8_t _bitMaskA;
		uint8_t _bitMaskB;
		uint8_t _timerPWM;
		uint8_t _interruptNumber;
		int16_t _oldPwm; 
		volatile uint8_t *_outRegPWM;
		volatile uint8_t *_outRegA;
		volatile uint8_t *_outRegB;
};

/*extern Motors motorA;
extern Motors motorB;
extern Motors motorC;
extern Motors motorD;*/

#endif


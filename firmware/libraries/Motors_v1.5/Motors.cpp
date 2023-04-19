/*
 *	Библиотека для управления моторами проекта Time
 *	v 1.5
 *	Разработчик Хартанен А.В.
 */
 
#include <Motors.h>

volatile uint8_t *_directionInReg0;
volatile uint8_t *_directionInReg1;
volatile uint8_t *_directionInReg2;
volatile uint8_t *_directionInReg3;

uint8_t _directionBitMask0;
uint8_t _directionBitMask1;
uint8_t _directionBitMask2;
uint8_t _directionBitMask3;


volatile int16_t nMotorEncoder[4] = {0, 0, 0, 0};

void _enc0()
{
	if(*_directionInReg0 & _directionBitMask0)
		nMotorEncoder[0]--;
	else
		nMotorEncoder[0]++;
}
void _enc1()
{
	if(*_directionInReg1 & _directionBitMask1)
		nMotorEncoder[1]--;
	else
		nMotorEncoder[1]++;
}
void _enc2()
{
	if(*_directionInReg2 & _directionBitMask2)
		nMotorEncoder[2]--;
	else
		nMotorEncoder[2]++;
}
void _enc3()
{
	if(*_directionInReg3 & _directionBitMask3)
		nMotorEncoder[3]--;
	else
		nMotorEncoder[3]++;
}

Motors::Motors(uint8_t pinPWM, uint8_t pinA, uint8_t pinB)
{
	_portPWM = digitalPinToPort(pinPWM);
	_outRegPWM = portOutputRegister(_portPWM);
	_bitMaskPWM = digitalPinToBitMask(pinPWM);
	_timerPWM = digitalPinToTimer(pinPWM);
	
	_portA = digitalPinToPort(pinA);
	_portB = digitalPinToPort(pinB);
	_outRegA = portOutputRegister(_portA);
	_outRegB = portOutputRegister(_portB);
	_bitMaskA = digitalPinToBitMask(pinA);
	_bitMaskB = digitalPinToBitMask(pinB);
	pinMode(pinPWM, OUTPUT);
	pinMode(pinA, OUTPUT);
	pinMode(pinB, OUTPUT);
}

Motors::Motors(uint8_t pinPWM, uint8_t pinA, uint8_t pinB, uint8_t interruptNumber, uint8_t directionPin)
{
	_portPWM = digitalPinToPort(pinPWM);
	_outRegPWM = portOutputRegister(_portPWM);
	_bitMaskPWM = digitalPinToBitMask(pinPWM);
	_timerPWM = digitalPinToTimer(pinPWM);
	
	_portA = digitalPinToPort(pinA);
	_outRegA = portOutputRegister(_portA);
	_bitMaskA = digitalPinToBitMask(pinA);

	_portB = digitalPinToPort(pinB);
	_outRegB = portOutputRegister(_portB);
	_bitMaskB = digitalPinToBitMask(pinB);
	
	pinMode(pinPWM, OUTPUT);
	pinMode(pinA, OUTPUT);
	pinMode(pinB, OUTPUT);
	pinMode(interruptNumber, INPUT);  //(!)
	pinMode(directionPin, INPUT);
	
	if(interruptNumber == 0){
		attachInterrupt(0, _enc0, FALLING);
		_directionInReg0 = portInputRegister(digitalPinToPort(directionPin));
		_directionBitMask0 = digitalPinToBitMask(directionPin);
	}
	if(interruptNumber == 1){
		attachInterrupt(1, _enc1, FALLING);
		_directionInReg1 = portInputRegister(digitalPinToPort(directionPin));
		_directionBitMask1 = digitalPinToBitMask(directionPin);
	}
	if(interruptNumber == 2){
		attachInterrupt(2, _enc2, FALLING);
		_directionInReg2 = portInputRegister(digitalPinToPort(directionPin));
		_directionBitMask2 = digitalPinToBitMask(directionPin);
	}
	if(interruptNumber == 3){
		attachInterrupt(3, _enc3, FALLING);
		_directionInReg3 = portInputRegister(digitalPinToPort(directionPin));
		_directionBitMask3 = digitalPinToBitMask(directionPin);
	}
}

/*Motors motorA = Motors(12, 11, 0, 50);
Motors motorB = Motors(10, 9, 1, 52);
Motors motorC = Motors(8, 7);
Motors motorD = Motors(6, 5);*/

void _offPWM(uint8_t timer)
{
	switch (timer)
	{
		#if defined(TCCR1A) && defined(COM1A1)
		case TIMER1A:   bitClear(TCCR1A, COM1A1);    break;
		#endif
		#if defined(TCCR1A) && defined(COM1B1)
		case TIMER1B:   bitClear(TCCR1A, COM1B1);    break;
		#endif
		#if defined(TCCR1A) && defined(COM1C1)
		case TIMER1C:   bitClear(TCCR1A, COM1C1);    break;
		#endif
		
		#if defined(TCCR2) && defined(COM21)
		case  TIMER2:   bitClear(TCCR2, COM21);      break;
		#endif
		
		#if defined(TCCR0A) && defined(COM0A1)
		case  TIMER0A:  bitClear(TCCR0A, COM0A1);    break;
		#endif
		
		#if defined(TCCR0A) && defined(COM0B1)
		case  TIMER0B:  bitClear(TCCR0A, COM0B1);    break;
		#endif
		#if defined(TCCR2A) && defined(COM2A1)
		case  TIMER2A:  bitClear(TCCR2A, COM2A1);    break;
		#endif
		#if defined(TCCR2A) && defined(COM2B1)
		case  TIMER2B:  bitClear(TCCR2A, COM2B1);    break;
		#endif
		
		#if defined(TCCR3A) && defined(COM3A1)
		case  TIMER3A:  bitClear(TCCR3A, COM3A1);    break;
		#endif
		#if defined(TCCR3A) && defined(COM3B1)
		case  TIMER3B:  bitClear(TCCR3A, COM3B1);    break;
		#endif
		#if defined(TCCR3A) && defined(COM3C1)
		case  TIMER3C:  bitClear(TCCR3A, COM3C1);    break;
		#endif

		#if defined(TCCR4A) && defined(COM4A1)
		case  TIMER4A:  bitClear(TCCR4A, COM4A1);    break;
		#endif					
		#if defined(TCCR4A) && defined(COM4B1)
		case  TIMER4B:  bitClear(TCCR4A, COM4B1);    break;
		#endif
		#if defined(TCCR4A) && defined(COM4C1)
		case  TIMER4C:  bitClear(TCCR4A, COM4C1);    break;
		#endif			
		#if defined(TCCR4C) && defined(COM4D1)
		case TIMER4D:	bitClear(TCCR4C, COM4D1);	break;
		#endif			
			
		#if defined(TCCR5A)
		case  TIMER5A:  bitClear(TCCR5A, COM5A1);    break;
		case  TIMER5B:  bitClear(TCCR5A, COM5B1);    break;
		case  TIMER5C:  bitClear(TCCR5A, COM5C1);    break;
		#endif
	}
}

void _onPWM(uint8_t timer, int val)
{
	switch(timer)
		{
			// XXX fix needed for atmega8
			#if defined(TCCR0) && defined(COM00) && !defined(__AVR_ATmega8__)
			case TIMER0A:
				// connect pwm to pin on timer 0
				bitSet(TCCR0, COM00);
				OCR0 = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR0A) && defined(COM0A1)
			case TIMER0A:
				// connect pwm to pin on timer 0, channel A
				bitSet(TCCR0A, COM0A1);
				OCR0A = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR0A) && defined(COM0B1)
			case TIMER0B:
				// connect pwm to pin on timer 0, channel B
				bitSet(TCCR0A, COM0B1);
				OCR0B = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR1A) && defined(COM1A1)
			case TIMER1A:
				// connect pwm to pin on timer 1, channel A
				bitSet(TCCR1A, COM1A1);
				OCR1A = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR1A) && defined(COM1B1)
			case TIMER1B:
				// connect pwm to pin on timer 1, channel B
				bitSet(TCCR1A, COM1B1);
				OCR1B = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR1A) && defined(COM1C1)
			case TIMER1C:
				// connect pwm to pin on timer 1, channel C
				bitSet(TCCR1A, COM1C1);
				OCR1C = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR2) && defined(COM21)
			case TIMER2:
				// connect pwm to pin on timer 2
				bitSet(TCCR2, COM21);
				OCR2 = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR2A) && defined(COM2A1)
			case TIMER2A:
				// connect pwm to pin on timer 2, channel A
				bitSet(TCCR2A, COM2A1);
				OCR2A = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR2A) && defined(COM2B1)
			case TIMER2B:
				// connect pwm to pin on timer 2, channel B
				bitSet(TCCR2A, COM2B1);
				OCR2B = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR3A) && defined(COM3A1)
			case TIMER3A:
				// connect pwm to pin on timer 3, channel A
				bitSet(TCCR3A, COM3A1);
				OCR3A = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR3A) && defined(COM3B1)
			case TIMER3B:
				// connect pwm to pin on timer 3, channel B
				bitSet(TCCR3A, COM3B1);
				OCR3B = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR3A) && defined(COM3C1)
			case TIMER3C:
				// connect pwm to pin on timer 3, channel C
				bitSet(TCCR3A, COM3C1);
				OCR3C = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR4A)
			case TIMER4A:
				//connect pwm to pin on timer 4, channel A
				bitSet(TCCR4A, COM4A1);
				#if defined(COM4A0)		// only used on 32U4
				bitClear(TCCR4A, COM4A0);
				#endif
				OCR4A = val;	// set pwm duty
				break;
			#endif
			
			#if defined(TCCR4A) && defined(COM4B1)
			case TIMER4B:
				// connect pwm to pin on timer 4, channel B
				bitSet(TCCR4A, COM4B1);
				OCR4B = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR4A) && defined(COM4C1)
			case TIMER4C:
				// connect pwm to pin on timer 4, channel C
				bitSet(TCCR4A, COM4C1);
				OCR4C = val; // set pwm duty
				break;
			#endif
				
			#if defined(TCCR4C) && defined(COM4D1)
			case TIMER4D:				
				// connect pwm to pin on timer 4, channel D
				bitSet(TCCR4C, COM4D1);
				#if defined(COM4D0)		// only used on 32U4
				bitClear(TCCR4C, COM4D0);
				#endif
				OCR4D = val;	// set pwm duty
				break;
			#endif

							
			#if defined(TCCR5A) && defined(COM5A1)
			case TIMER5A:
				// connect pwm to pin on timer 5, channel A
				bitSet(TCCR5A, COM5A1);
				OCR5A = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR5A) && defined(COM5B1)
			case TIMER5B:
				// connect pwm to pin on timer 5, channel B
				bitSet(TCCR5A, COM5B1);
				OCR5B = val; // set pwm duty
				break;
			#endif

			#if defined(TCCR5A) && defined(COM5C1)
			case TIMER5C:
				// connect pwm to pin on timer 5, channel C
				bitSet(TCCR5A, COM5C1);
				OCR5C = val; // set pwm duty
				break;
			#endif
			
			default: break;
		}
}

void Motors::set(int16_t pwm)
{	
	if(pwm == _oldPwm)	return;
		
	_oldPwm = pwm;
	
	//pwm = constrain(pwm, -255, 255);
	if(pwm <= -255)
	{
		_offPWM(_timerPWM);
		*_outRegPWM |= _bitMaskPWM;	//PWM HIGH
		*_outRegB |= _bitMaskB;	//B HIGH
		*_outRegA &= ~_bitMaskA; //A LOW
	}
	else if(pwm >= 255)
	{
		_offPWM(_timerPWM);
		*_outRegPWM |= _bitMaskPWM;	//PWM HIGH
		*_outRegA |= _bitMaskA;	//A HIGH
		*_outRegB &= ~_bitMaskB; //B LOW
	}
	else if(pwm < 0)
	{
		_onPWM(_timerPWM, pwm *= -1);
		*_outRegB |= _bitMaskB;	//B HIGH
		*_outRegA &= ~_bitMaskA; //A LOW
	}
	else if(pwm > 0)
	{
		_onPWM(_timerPWM, pwm);
		*_outRegA |= _bitMaskA;	//A HIGH
		*_outRegB &= ~_bitMaskB; //B LOW
	}
	else
	{
		_offPWM(_timerPWM);
		*_outRegPWM &= ~_bitMaskPWM; //B LOW
		*_outRegA &= ~_bitMaskA; //A LOW
		*_outRegB &= ~_bitMaskB; //B LOW
	}
}

void Motors::stop()
{
	_offPWM(_timerPWM);
	*_outRegPWM &= ~_bitMaskPWM; //B LOW
	*_outRegA |= _bitMaskA;	//A HIGH
	*_outRegB |= _bitMaskB;	//B HIGH
	_oldPwm = 0;
}
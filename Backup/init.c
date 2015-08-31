#include "init.h"

static void initPorts(void);
static void initLed(void);
static void initPrescaler(void);
static void initADC(void);

static void initPorts(void){
	cli();          	// disable all interrupts
	DDRL = INIT_PORTL_DIR; 
	PORTL = INIT_PORTL; 
	DDRF = INIT_PORTF_DIR; 
	DDRK = INIT_PORTK_DIR;  
	DDRA = INIT_PORTA_DIR;
	DDRC = INIT_PORTC_DIR;
	sei();				// enable all interrupts
}

static void initLed(void){
	helperSetDir(&DDRL, 6, 0); //avoid MS legacy ballpoint drivers  
	helperDigitalWrite(&PORTL, 6, 1); //turn debug LED on  
	_delay_ms(1000);  // these 3 lines delay the uart output when plugged in in the hope of not being recognised as legacy mouse hardware  
	helperDigitalWrite(&PORTL, 6, 0);
}

static void initPrescaler(void){
	helperDigitalWrite(&ADCSRA, ADPS2, 1);
	helperDigitalWrite(&ADCSRA, ADPS1, 1); 
	helperDigitalWrite(&ADCSRA, ADPS0, 0); 	
}

static void initADC(void){
	ADMUX |= 1<<ADLAR;		//8 bit or 10 bit result -> setting ADLAR =1 to allow an 8bit reading frmo ADCH
	ADMUX |= 1<<REFS0;		//reference selection pins -- setting to use AVCC with ext cap @ AREF
}

void initStartup(void){
	//flash LED and wait a second
	initLed();

	// Port initialization
	initPorts();

	// Init the prescaler division factor to 64, a sample rate of 115 KHz
	initPrescaler();

	//setting an 8bit adc with the ref pin set to AVcc with ext cap @ ARef
	initADC();

	// comm setup
	uart0_init(1,0);  // Asyn,NoParity,1StopBit,8Bit,  -- baud rate: 230.4k u2xn = 1 
}
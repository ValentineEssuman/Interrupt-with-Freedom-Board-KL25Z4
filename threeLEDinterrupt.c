#include <MKL25Z4.h>
//#include "threeLEDinterrupt.h"
#include "LEDs.h"

#define RED_LED_SHIFT (18)  //port B
#define GREEN_LED_SHIFT (19) //on port B
#define BLUE_LED_SHIFT (1) // port D
#define SwitchIn (5) // portD

#define MASK(x) (1UL << (x))
void Init_Peripherals(void);
void Delay_millisec(volatile unsigned int t);
void PORTD_IRQHandler(void);
void RGB(void);
volatile unsigned int memcount =0;
volatile unsigned int counter;


void Delay_millisec(volatile unsigned int time_del){
	  //time_del = (1000 * (time_del));
		while(time_del--){
			;
		}
}

void Init_Peripherals(void){
	
				SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTB_MASK;
				SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTD_MASK;
				
				
				
				//Make LEDs  GPIO
				PORTB->PCR[RED_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
				PORTB->PCR[RED_LED_SHIFT] |= PORT_PCR_MUX(1);
				PORTB->PCR[GREEN_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
				PORTB->PCR[GREEN_LED_SHIFT] |= PORT_PCR_MUX(1);
				PORTD->PCR[BLUE_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
				PORTD->PCR[BLUE_LED_SHIFT] |= PORT_PCR_MUX(1);
				
				//Set ports to outputs
				PTB->PDDR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
				PTD->PDDR |= MASK(BLUE_LED_SHIFT);
	
	
				//Make SWITCH GPIO
				PORTD->PCR[SwitchIn] &= ~PORT_PCR_MUX_MASK;
				PORTD->PCR[SwitchIn] |= PORT_PCR_MUX(1)| PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(11);
				
				
				//Make swicth input
				PTA->PDDR &= ~MASK(SwitchIn);
	
	
	
		//setting NVIC
		NVIC_SetPriority(PORTD_IRQn,2);
		NVIC_ClearPendingIRQ(PORTD_IRQn);
		NVIC_EnableIRQ(PORTD_IRQn);
		
		//Optional: Configure PRIMASK
		__enable_irq();

		
		// LEDs on
		PTB->PCOR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
		PTD->PCOR |= MASK(BLUE_LED_SHIFT);
}


void PORTD_IRQHandler(void){
			//LEDs off
		PTB->PCOR &= ~MASK(RED_LED_SHIFT) | ~MASK(GREEN_LED_SHIFT);
		PTD->PCOR &= ~MASK(BLUE_LED_SHIFT);
		
		if((PORTD->ISFR & MASK(SwitchIn))){
				memcount += counter;
				Control_RGB_LEDs(0,0,0);
		}
		  // LEDs on
		PTB->PCOR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
		PTD->PCOR |= MASK(BLUE_LED_SHIFT);
	
		//clear status flags
		PORTD->ISFR = 0xffffffff;
}


void RGB(void){
	if(counter == 0){
		Control_RGB_LEDs(1,1,1);
		Delay_millisec(5000);
	}
	
	if(counter == 2){
		Control_RGB_LEDs(1,0,0);
		Delay_millisec(5000);
		
	}
	
	if(counter == 4){
		Control_RGB_LEDs(0,1,0);
		Delay_millisec(5000);
		
	}
	
		if(counter == 4){
		Control_RGB_LEDs(0,0,1);
		Delay_millisec(5000);
		
	}
}



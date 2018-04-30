#ifndef THREELEDINTERRUPT_H
#define THREELEDINTERRUPT_H

#define RED_LED_SHIFT (18)  //port B
#define GREEN_LED_SHIFT (19) //on port B
#define BLUE_LED_SHIFT (1) // port D
#define SwitchIn (5) // portB

#define MASK(x) (1UL << (x))
void Init_Peripherals(void);
void Delay_millisec(volatile unsigned int t);
void PORTD_IRQHandler(void);
int volatile * counter;

#endif
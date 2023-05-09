// Description----------------------------------------------------------------|
/*
 * Initialises a struct with Name and Age data. Displays results on LEDs and
 * LCD.
 */
// DEFINES AND INCLUDES-------------------------------------------------------|

#include "stm32f0xx.h"

// GLOBAL VARIABLES ----------------------------------------------------------|


// FUNCTION DECLARATIONS -----------------------------------------------------|

void main(void);                                                   
void init_ADC(void);											   
void init_timer_2(void);
void trigger_ADC_conversion(void);
_Bool ADC_busy(void);
uint16_t read_ADC_value(void);


// MAIN FUNCTION -------------------------------------------------------------|

void main(void)
{


	while(1)
	{

	}
}

// OTHER FUNCTIONS -----------------------------------------------------------|

/* Description:
 * This function initialises the ADC setting to allow 10 bit conversions on PA6
 * in single conversion, wait mode.
 */
void init_ADC(void)
{
	//
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	//
	GPIOA->MODER |= GPIO_MODER_MODER6;
	//
	RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
	//
	ADC1->CR |= ADC_CR_ADEN;
	//
	ADC1->CHSELR |= ADC_CHSELR_CHSEL6;
	// Setup in wait mode
	ADC1->CFGR1 |= ADC_CFGR1_WAIT;
	// Setup 10 bit resolution
	ADC1->CFGR1 |= ADC_CFGR1_RES_0;
	//
	while((ADC1->ISR & ADC_ISR_ADRDY) == 0);
}

/* Description:
 * This function starts the conversion sequence of the ADC
 */
void trigger_ADC_conversion(void)
{
	ADC1->CR |= ADC_CR_ADSTART;	
}

/* Description:
 * This function checks whether the ADC conversion sequence is ongoing.
 * It returns true if the conversion is ongoing.
 * It returns false if the conversion is complete and data is ready.
 */
_Bool ADC_busy(void)
{
	return (ADC1->ISR & ADC_ISR_EOC) == 0) ? true : false; // This line uses the ternery operator
}

/* Description:
 * This function reads the numerical result of the ADC conversion.
 * The programmer should ensure that the conversion is complete before reading the result.
 */
uint16_t read_ADC_value(void)
{
	return ADC1->DR;
}

#if 0
void init_timer_2(void)		
{
	// Enable GPIOB clock & pin 10 as alternate function
       RCC->AHBENR |= RCC_AHBENR_GPIOBEN;              
       GPIOB->MODER |= GPIO_MODER_MODER10_1;          
       // Select alternate function: TIM2_CH3
       GPIOB->AFR[1] |= (2 << 2*4);                    
       // Enable TIM2
       RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;             
       // Set clock source to 15 kHz
       TIM2->PSC = 2;                            
       // Setup ARR 
       TIM2->ARR = 1023;                         
       TIM2->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE
       TIM2->CCER |= TIM_CCER_CC3E;                   
       TIM2->CR1 |= TIM_CR1_CEN;                       
       TIM2->CCR3 = 1023 / 4;                           
	
}
#endif

void init_timer_6(void)
{					

}

// INTERRUPT HANDLERS --------------------------------------------------------|

void TIM6_IRQHandler(void)
{				
	TIM6->SR &= ~TIM_SR_UIF;	//acknowledge interrupt
}

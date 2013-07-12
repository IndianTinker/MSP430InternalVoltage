/*Coded by : Rohit Gupta
 *
 * Description: Measures the voltage from internal voltage sensor and turns on LED based on Battery state
 * License- CC-NC-ND
 * Code Log: Started on: 0012hrs 27th June 13
 * Used Internal Ref as battery may die out, so reference has to be generated!
 * Typically driven , Gxx series cant work lesser than 2.1V
 *
 *
 */
#include<msp430g2553.h>
int value=0;
float voltage=0.0;
void adcInit()
{
	ADC10CTL0=SREF_1+REFON+REF2_5V+ADC10ON+ADC10SHT_3; // Using internal reference of 2.5V
	ADC10CTL1=INCH_11+ADC10DIV_3;                      //Inch-11 = (Vcc-Vss)/2
	
}
void main(void)
	{
	  WDTCTL = WDTPW + WDTHOLD;                           //Stop Watchdog!
      adcInit();                                          //Initialise
      P1DIR|=BIT6+BIT0;                                   // Configure GPIO
      P1OUT=0;
      while(1)
      {
     	       __delay_cycles(1000);                   // Wait for ADC Ref to settle
     	       ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
     	       while (ADC10CTL1 & BUSY);             //waiting for conversion to finish
     	       value = ADC10MEM;                    //fetching adc value
               voltage=(value*2*2.5)/1023;           // Converting To Legit Voltage Values in Volts

               if(voltage>3.3)                         // If Voltage is OK! Light Up Green LED
            	   {
            	   P1OUT=0;
            	   P1OUT|=BIT6;
            	   }
               else                                   // Else Turn On RED for Low Voltage
               {
            	   P1OUT=0;
            	   P1OUT|=BIT0;

               }
      }
	}

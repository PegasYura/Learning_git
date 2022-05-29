/**
  ******************************************************************************
  * @file     main progect 
  * @author   Yurii Bohdanovskyi
  * @version  V2.2.0
  * @date     30-04-2022
  * @brief    I am making the ADC measuring the voltage of battery
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "ProjectDefines.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

/**
  * @addtogroup UART1_HyperTerminal_Interrupt
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

unsigned char      Time_1_sec, Time_02_sec;   	// бит мен€ющийс€ раз в 1 с
uint8_t ucFlagDelay1sCurrent = 0;									// флаг задержки превышени€ тока
extern uint32_t ulMiliSeconds;
unsigned char    bProg=0, bReset=0; 


const unsigned char LCD_digits[] =
{
	'0','1','2','3','4','5','6','7',
	'8','9','A','B','C','D','E','F',
};

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
	void vHardwareInit(void);
	void Delay(uint32_t nCount);
	
	void vConvertCurrent(void);
	void vConvertPotenciometr(void);
//=============================================================================================
//=============================================================================================
//=============================================================================================
void vControl(void)
{
  //-------RS485------------------------------------------------
  if (cRsGo) ProcessingCOM();
  //------------ADC-------------------------------------------
  if (bADCflag[cCurrReadCh])
  {
    ;

  }
}
//=============================================================================================

//#include <limits.h>
//#include <stdio.h>

static char *itoa_simple_helper(char *dest, int i) {
  if (i <= -10) {
    dest = itoa_simple_helper(dest, i/10);
  }
  *dest++ = '0' - i%10;
  return dest;
}

char *itoa_simple(char *dest, int i) {
  char *s = dest;
  if (i < 0) {
    *s++ = '-';
  } else {
    i = -i;
  }
  *itoa_simple_helper(s, i) = '\0';
  return dest;
}
/*
int main() {
  char s[100];
  puts(itoa_simple(s, 0));
  puts(itoa_simple(s, 1));
  puts(itoa_simple(s, -1));
  puts(itoa_simple(s, 12345));
  puts(itoa_simple(s, INT_MAX-1));
  puts(itoa_simple(s, INT_MAX));
  puts(itoa_simple(s, INT_MIN+1));
  puts(itoa_simple(s, INT_MIN));
}
*/

//=============================================================================================
//=============================================================================================
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void) {
  
  //initialization
  vHardwareInit();
  vLed1Off();
  vLed2Off();
  vReleOff();
  vLed2Off();
  while (1)
  {
   static char out_str[20];
   uint8_t i;
   uint8_t device_number = 4;
   const char text[] = {" Number V=_"};
   int16_t adc, voltage;
   float k, b; 


   
   if(Time_1_sec > 1)
   {
     Time_1_sec = 0;
     
     if(bADCflag[0])
     {
       bADCflag[0] = 0;
       adc = ADC_[0];
       
       k = 3.189823;
       b = 0.0; 
       memset(out_str, 0, 20);
       out_str[0] = LCD_digits[device_number] ;
       for(i=0; i<strlen(text); i++)
       {
         out_str[1+i] = text[i];
       }
       voltage = k * adc + b;
       
       itoa_simple(&out_str[10],voltage);
       
       out_str[strlen(out_str)] = 0x0A;
       out_str[strlen(out_str)] = 0x0D;
       
       for(i=0; i<strlen(out_str); i++)
       {
         vWriteByteCOM((unsigned char) out_str[i]);
       }
       
       vControl();
     }
   }
  }
}

//////////////////////////////////////////////////////////////////

/**
  * @brief  Delay.
  * @param  nCount
  * @retval None
  */
void Delay(uint32_t nCount)
{
	/* Decrement nCount value */
	while (nCount != 0) {
		nCount--;
	}
}

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
#include "main.h"
#include "milis.h"
#include "daughterboard.h"
//#include "delay.h"
//#include "uart1.h"

void init(void)
{
    init_milis();
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz

    GPIO_Init(PWM_R_PORT, PWM_R_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(PWM_B_PORT, PWM_B_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(PWM_G_PORT, PWM_G_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(S1_PORT, S1_PIN,GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(S1_PORT, S1_PIN,GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(S1_PORT, S1_PIN,GPIO_MODE_IN_PU_NO_IT);

    TIM2_TimeBaseInit(TIM2_PRESCALER_16, 1000 - 1);
    TIM2_OC1Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE, 100 , TIM2_OCPOLARITY_HIGH);
    TIM2_OC2Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE, 200 , TIM2_OCPOLARITY_HIGH);
    TIM2_OC3Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE, 1000 , TIM2_OCPOLARITY_HIGH);

    TIM2_OC1PreloadConfig(ENABLE);
    TIM2_OC2PreloadConfig(ENABLE);
    TIM2_OC3PreloadConfig(ENABLE);

    TIM2_Cmd(ENABLE);
#if defined (BTN_PORT) || defined (BTN_PIN)
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);
#endif


    //init_uart1();
}


int main(void)
{
  
    uint32_t time = 0;

    init();

    while (1) {

        if (milis() - time > 333 ) {
            REVERSE(LED); 
            time = milis();
            //printf("%ld\n", time);
          }
        //delay_ms(333);
    }
}


/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"

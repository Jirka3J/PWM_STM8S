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
    GPIO_Init(S2_PORT, S2_PIN,GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(S3_PORT, S3_PIN,GPIO_MODE_IN_PU_NO_IT);

    TIM2_TimeBaseInit(TIM2_PRESCALER_16, 1000 - 1);
    TIM2_OC1Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE, 100 , TIM2_OCPOLARITY_HIGH);
    TIM2_OC2Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE, 0 , TIM2_OCPOLARITY_HIGH);
    TIM2_OC3Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE, 0 , TIM2_OCPOLARITY_HIGH);

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
    uint8_t btn = 0;
    uint32_t time = 0;
    uint8_t color = 0;
    uint16_t value = 1000;

    init();
    

    while (1) {
        switch (color){
            case 1:
                TIM2_SetCompare1(value);
            case 2:
                TIM2_SetCompare2(value);
            case 3:
                TIM2_SetCompare3(value);
        }
        if (milis()-time>10){
            time = milis();
            if (!PUSH(S1)&& btn) {            
                if (color++>3){
                    color=1;
                }
            }
            btn = PUSH(S1);

    }
}
}


/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"

#include <stdint.h>
#include "drivers/gpio/gpio.h"
#include "utils/delay.h"
#include "bsp/nano.h"

void Buzzer_Beep(uint16_t duration_ms)
{
    for (uint16_t i = 0; i < duration_ms / 2; i++)
    {
        GPIO_Write(D7, GPIO_HIGH);
        Delay(1);

        GPIO_Write(D7, GPIO_LOW);
        Delay(1);
    }

    GPIO_Write(D7, GPIO_LOW);
}

int main(void)
{
    GPIO_Init(D4, GPIO_INPUT);     
    GPIO_Write(D4, GPIO_HIGH);    

    GPIO_Init(D7, GPIO_OUTPUT);    
    GPIO_Write(D7, GPIO_LOW);     

    while (1)
    {
        if (GPIO_Read(D4) == 0)
        {
            Buzzer_Beep(300);
        }
        else
        {
            GPIO_Write(D7, GPIO_LOW);
        }

        Delay(20);
    }
}
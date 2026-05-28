#include <stdint.h>
#include "drivers/adc/adc.h"
#include "drivers/gpio/gpio.h"
#include "bsp/nano.h" 

#define POT1_X 600
#define POT1_Y 800
<<<<<<< HEAD
#define POT2_X 202
#define POT2_Y 400
=======
#define POT2_X 200
#define POT2_Y 400   
>>>>>>> d4fd6bf1b8e88ed6cec62f83ede20cc0dd6b96fe
#define POT3_X 800
#define POT3_Y 1000

int pot(int x) //functie pentru citirea valorii de la potentiometru x=1 selecteaza potentiometrul 1
                // x=2 selecteaza potentiometrul 2 x=3 selecteaza potentiometrul 3
{
    uint16_t pot_value = 0;
<<<<<<< HEAD

=======
    
>>>>>>> d4fd6bf1b8e88ed6cec62f83ede20cc0dd6b96fe
    if (x == 1)
    {
        pot_value = ADC_Read(0);
        if (pot_value >= POT1_X && pot_value <= POT1_Y)
            return 1;
        else
            return 0;
    }
    else if (x == 2)
    {
        pot_value = ADC_Read(1);
        if (pot_value >= POT2_X && pot_value <= POT2_Y)
            return 1;
        else
            return 0;
    }
    else if (x == 3)
    {
        pot_value = ADC_Read(2);
        if (pot_value >= POT3_X && pot_value <= POT3_Y)
            return 1;
        else
            return 0;
    }
<<<<<<< HEAD

=======
    
>>>>>>> d4fd6bf1b8e88ed6cec62f83ede20cc0dd6b96fe
    return 0;
}
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
<<<<<<< HEAD
    GPIO_Init(D4, GPIO_INPUT);
    GPIO_Write(D4, GPIO_HIGH);

    GPIO_Init(D7, GPIO_OUTPUT);
    GPIO_Write(D7, GPIO_LOW);
=======
    GPIO_Init(D4, GPIO_INPUT);     
    GPIO_Write(D4, GPIO_HIGH);    

    GPIO_Init(D7, GPIO_OUTPUT);    
    GPIO_Write(D7, GPIO_LOW);     
>>>>>>> d4fd6bf1b8e88ed6cec62f83ede20cc0dd6b96fe

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
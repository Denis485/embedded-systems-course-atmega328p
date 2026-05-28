#include "drivers/gpio/gpio.h"
#include "bsp/nano.h" 

int main(void) {
// test de IR SENSOR
    GPIO_Init(D7, GPIO_INPUT);     
    GPIO_Init(D4, GPIO_OUTPUT);    

    GPIO_Write(D4, GPIO_LOW);     

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




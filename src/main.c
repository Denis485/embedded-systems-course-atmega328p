#include <stdint.h>
#include "drivers/adc/adc.h"
#include "drivers/gpio/gpio.h"
#include "drivers/interrupt/external_interrupt.h"
#include "bsp/nano.h" 
#include "utils/delay.h"

#define POT1_X 602
#define POT1_Y 800

#define POT2_X 200
#define POT2_Y 400   

#define POT3_X 800
#define POT3_Y 1000

#define IR_SENZOR D4
#define VIBRATIE_SENZOR D3
#define BUZZER D7

#define LED_POT1 D10
#define LED_POT2 D11
#define LED_POT3 D12

volatile uint8_t senzor_vibratie = 0;

void Vibratie(void)
{
    senzor_vibratie = 1;
}

int pot(int x) //functie pentru citirea valorii de la potentiometru x=1,2 sau 3
{
    uint16_t pot_value = 0;
    
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
    
    return 0;
}

void Buzzer(uint16_t durata) //Beep buzzer passiv - durata in ms
{
    for (uint16_t i = 0; i < durata / 2; i++)
    {
        GPIO_Write(BUZZER, GPIO_HIGH);
        Delay(1);

        GPIO_Write(BUZZER, GPIO_LOW);
        Delay(1);
    }

    GPIO_Write(BUZZER, GPIO_LOW);
}

int main(void)
{
    ADC_Init();

    GPIO_Init(LED_POT1, GPIO_OUTPUT); 
    GPIO_Init(LED_POT2, GPIO_OUTPUT);
    GPIO_Init(LED_POT3, GPIO_OUTPUT);

    GPIO_Init(IR_SENZOR, GPIO_INPUT);

    GPIO_Init(VIBRATIE_SENZOR, GPIO_INPUT);
    GPIO_Write(VIBRATIE_SENZOR, GPIO_HIGH); 

    GPIO_Init(BUZZER, GPIO_OUTPUT);    
    GPIO_Write(BUZZER, GPIO_LOW);

    ExtInt_Init(INT_1, EXT_INT_ANY_CHANGE, Vibratie);

    while (1)
    {
        int p1 = pot(1);
        int p2 = pot(2);
        int p3 = pot(3);

        int pot_gresit = (!p1 || !p2 || !p3);

        // IR sensor

        int senzor = (GPIO_Read(IR_SENZOR) != 0);

        if(p1)
        {
            GPIO_Write(LED_POT1, GPIO_HIGH);   
        }
        else
        {
            GPIO_Write(LED_POT1, GPIO_LOW);    
        }

        if(p2)
        {
            GPIO_Write(LED_POT2, GPIO_HIGH);   
        }
        else
        {
            GPIO_Write(LED_POT2, GPIO_LOW);    
        }

        if(p3)
        {
            GPIO_Write(LED_POT3, GPIO_HIGH);   
        }
        else
        {
            GPIO_Write(LED_POT3, GPIO_LOW);    
        }

        if ((senzor && pot_gresit) || senzor_vibratie)
        {
            senzor_vibratie = 0;
            Buzzer(300);
        }
        else
        {
            GPIO_Write(BUZZER, GPIO_LOW);
        }

        Delay(1);
    }
}
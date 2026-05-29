#include <stdint.h>
#include "drivers/adc/adc.h"
#include "drivers/gpio/gpio.h"
#include "drivers/interrupt/external_interrupt.h"
#include "drivers/eeprom/eeprom.h"
#include "bsp/nano.h" 
#include "utils/delay.h"

<<<<<<< Updated upstream
#define POT1_X 600
#define POT1_Y 800

#define POT2_X 200
#define POT2_Y 400   

#define POT3_X 800
#define POT3_Y 1000
=======
uint8_t POT1_VALOARE = 175;  // aproximativ 700 / 4
uint8_t POT2_VALOARE = 75;   // aproximativ 300 / 4
uint8_t POT3_VALOARE = 225;  // aproximativ 900 / 4
>>>>>>> Stashed changes

#define IR_SENZOR D4
#define VIBRATIE_SENZOR D3
#define BUZZER D7
#define BUTON D2

#define LED_VERDE D5
#define LED_ROSU D6

#define LED_POT1 D10
#define LED_POT2 D11
#define LED_POT3 D12


volatile uint8_t senzor_vibratie = 0;

void Vibratie(void)
{
    senzor_vibratie = 1;
}

void IncarcaDinEEPROM(void)
{
    if (EEPROM_Read(0) == 123) // check for garbage values
    {
        POT1_VALOARE = EEPROM_Read(1);
        POT2_VALOARE = EEPROM_Read(2);
        POT3_VALOARE = EEPROM_Read(3);
    }
}

void SalveazaInEEPROM(void)
{
    EEPROM_Update(1, POT1_VALOARE);
    EEPROM_Update(2, POT2_VALOARE);
    EEPROM_Update(3, POT3_VALOARE);

    EEPROM_Update(0, 123); 
}

void SalveazaPozitiaNoua(void)
{
    POT1_VALOARE = ADC_Read(0) / 4; // citim valoarea de la potentiometru si o scalam la 0-255
    POT2_VALOARE = ADC_Read(1) / 4;
    POT3_VALOARE = ADC_Read(2) / 4;

    SalveazaInEEPROM();
}

int VerificaPot(uint8_t valoare_curenta, uint8_t valoare_salvata)
{
    uint8_t limita_jos = 0;
    uint8_t limita_sus = 0;

    if (valoare_salvata < 25)
    {
        limita_jos = 0;
    }
    else
    {
        limita_jos = valoare_salvata - 25;
    }

    if (valoare_salvata > 230)
    {
        limita_sus = 255;
    }
    else
    {
        limita_sus = valoare_salvata + 25;
    }

    if (valoare_curenta >= limita_jos && valoare_curenta <= limita_sus)
        return 1;
    else
        return 0;
}

int pot(int x) //functie pentru citirea valorii de la potentiometru x=1,2 sau 3
{
    uint8_t pot_value = 0;
    
    if (x == 1)
    {
        pot_value = ADC_Read(0) / 4;
        return VerificaPot(pot_value, POT1_VALOARE);
    }
    else if (x == 2)
    {
        pot_value = ADC_Read(1) / 4;
        return VerificaPot(pot_value, POT2_VALOARE);
    }
    else if (x == 3)
    {
        pot_value = ADC_Read(2) / 4;
        return VerificaPot(pot_value, POT3_VALOARE);
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
    uint8_t mod_setare = 0;
    uint8_t buton_acum = 1;
    uint8_t buton_vechi = 1;

    ADC_Init();

    IncarcaDinEEPROM();

    GPIO_Init(LED_POT1, GPIO_OUTPUT); 
    GPIO_Init(LED_POT2, GPIO_OUTPUT);
    GPIO_Init(LED_POT3, GPIO_OUTPUT);

    GPIO_Init(LED_VERDE, GPIO_OUTPUT);
    GPIO_Init(LED_ROSU, GPIO_OUTPUT);

    GPIO_Write(LED_VERDE, GPIO_LOW);
    GPIO_Write(LED_ROSU, GPIO_LOW);

    GPIO_Init(IR_SENZOR, GPIO_INPUT);

    GPIO_Init(VIBRATIE_SENZOR, GPIO_INPUT);
    GPIO_Write(VIBRATIE_SENZOR, GPIO_HIGH); 

    GPIO_Init(BUTON, GPIO_INPUT);
    GPIO_Write(BUTON, GPIO_HIGH);

    GPIO_Init(BUZZER, GPIO_OUTPUT);    
    GPIO_Write(BUZZER, GPIO_LOW);

    ExtInt_Init(INT_1, EXT_INT_ANY_CHANGE, Vibratie);

    buton_vechi = GPIO_Read(BUTON);

    while (1)
    {
        int p1 = pot(1);
        int p2 = pot(2);
        int p3 = pot(3);

        int pot_gresit = (!p1 || !p2 || !p3);

        int senzor = (GPIO_Read(IR_SENZOR) != 0);

        buton_acum = GPIO_Read(BUTON);

        if (buton_vechi != 0 && buton_acum == 0)
        {
            Delay(30);

            if (GPIO_Read(BUTON) == 0)
            {
                if (mod_setare == 0)
                {
                    if (!pot_gresit)
                    {
                        mod_setare = 1;
                        senzor_vibratie = 0;
                        GPIO_Write(BUZZER, GPIO_LOW);
                    }
                }
                else
                {
                    SalveazaPozitiaNoua();
                    mod_setare = 0;
                    Buzzer(200);
                }
            }
        }

        buton_vechi = buton_acum;

        if (mod_setare)
        {
            GPIO_Write(LED_POT1, GPIO_HIGH);
            GPIO_Write(LED_POT2, GPIO_HIGH);
            GPIO_Write(LED_POT3, GPIO_HIGH);

            GPIO_Write(LED_VERDE, GPIO_HIGH);
            GPIO_Write(LED_ROSU, GPIO_LOW);

            GPIO_Write(BUZZER, GPIO_LOW);
            senzor_vibratie = 0;
        }
        else
        {
            if (p1)
            {
                GPIO_Write(LED_POT3, GPIO_HIGH);   
            }
            else
            {
                GPIO_Write(LED_POT3, GPIO_LOW);    
            }

            if (p2)
            {
                GPIO_Write(LED_POT2, GPIO_HIGH);   
            }
            else
            {
                GPIO_Write(LED_POT2, GPIO_LOW);    
            }

            if (p3)
            {
                GPIO_Write(LED_POT1, GPIO_HIGH);   
            }
            else
            {
                GPIO_Write(LED_POT1, GPIO_LOW);    
            }

            if (pot_gresit)
            {
                GPIO_Write(LED_ROSU, GPIO_HIGH);
                GPIO_Write(LED_VERDE, GPIO_LOW);
            }
            else
            {
                GPIO_Write(LED_ROSU, GPIO_LOW);
                GPIO_Write(LED_VERDE, GPIO_HIGH);
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
        }

    }
}
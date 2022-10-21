/*
Title:      Program to display POT values on PUTTY screen and colours on leds
Author:     Dave Ross, Student ID, MCO455 Section __
Date:       Today's date
Description:    This program  will display  values from
                the GROVE POT on the PUTTY screen and will turn on
                BLUE, RED and GREEN leds for each of 3 ranges
                0.00 < 0.33, 0.33 < 0.66, and 0.66 to 1.00
                
*/

#include "mbed.h"
void clear(void);                     // clears the PC screen
void position(int x, int y);            // positions screen cursor at (x,y)

// Hardware pin Assignments
AnalogIn pot_input(A1);                     // POT connected to pin A1 on header
DigitalOut red_led(LED1);
DigitalOut green_led(LED2);
DigitalOut blue_led(LED3);

// main() runs in its own thread in the OS
int main()
{
    float value;
    red_led=green_led=blue_led=1;       // shut off all leds
    clear();                            // clear the screen
    position(11,32);                    // position title 
    printf("\e[1m");
    printf("Temperature");
    position(13,33);
    printf("\e[0m");                // shut off all colours
    printf("          ");           // clear cool normal hot messgae
    for(;;)
    {
        value=pot_input.read();            // get FLOAT value for POT input
        value=value*100;
        position(12,34);                // ouput both values on screen
        printf("\e[0m");                // shut off all colours
        printf("\e[1;37m");                // make bold white letters
        printf("%6.2f",value);
        if(value <33.0)
        {
            red_led=green_led=1;        // turn off red and green leds
            blue_led=0;                // turn on Green Led
            position(13,33);
            printf("\e[1;37;44m");           // set text colour to blue
            printf("   COLD   ");
            
        }
        else
        if(value < 66.0)
        {
            red_led=blue_led=1;         // turn off red and blue leds
            green_led=0;                // turn on green led
            position(13,33);
            printf("\e[1;30;42m");           // set text colour to blue
            printf("  NORMAL  ");            
        }
        else
        {
            green_led=blue_led=1;       // turn off green and blue
            red_led=0;
            position(13,33);
            printf("\e[1;37;41m");           // set text colour to blue
            printf("  DANGER  ");        
        }
        wait(0.1);
    } 
}

void clear(void)
{
       printf("\e[2J");                 // \e[2J clears the screen
       fflush(stdout);
}
void position(int x, int y)
{
      printf("\e[%d;%dH",x,y);          // position cursor at (x,y)
      fflush(stdout);
}
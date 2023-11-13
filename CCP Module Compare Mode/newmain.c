/*
 * File:   newmain.c
 * Author: moham
 *
 * Created on October 26, 2023, 2:40 PM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000

uint8_t x = 0;
void main(void) {
    //configure the led to blink every 0.5sec
    TRISB0 = 0;
    //configure timer1 to timer mode
    TMR1 = 0;
    TMR1CS = 0;
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    TMR1ON = 1;
    //preload the ccp1 reg with the number of tick = 50000
    //if you do 50000 and overflow the timer1 module ten times you will get 0.5 secs
    //so ccp1 reg will be preloaded with 50000 and timer1 will keep counting until it reaches that value
    //everytime it reaches it ccp1 will interrupt and drive the pin high or low or remains unchanged
    //we want ccp1 to drive the pin high every 0.5 secs and to clear the TMR1 reg everytime the compare matches
    //1011 = Compare mode, trigger special event (CCPxIF bit is set, CCPx pin is unaffected), CCP1 resets TMR1
    CCPR1 = 50000; //PRELOADING THE TICKS
    CCP1IF = 0;
    CCP1IE = 1;
    PEIE = 1;
    GIE = 1;
    CCP1M0 = 1;
    CCP1M1 = 1;
    CCP1M2 = 0;
    CCP1M3 = 1;
    while(1){
        //nothing really happens here and everything is taken care of in the ISR handler
    }
    return;
}

void __interrupt() ISR(){
    if(CCP1IF){
        x++;
        if(x == 10){
        RB0 = ~RB0;
        x = 0;
        }
        CCP1IF = 0;
    }
}
#include "main.h"
#include "system.h"
#include "gpio.h"

int main(void)
{

    GPIO led;
    Pin ledpin(PORTC,7);
    led.Init(ledpin, GPIO::Mode::OUTPUT, GPIO::Pull::NOPULL, GPIO::Speed::MEDIUM);
    System MySystem;
    MySystem.Init();
    while(1)
    {
        led.Toggle();
        MySystem.Delay(3000);
        led.Toggle();
        MySystem.Delay(3000);
        for(;;)
        {
            MySystem.Delay(300);
            led.Toggle();
            
        }
        
    }
    return 1;
}
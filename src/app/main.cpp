#include "main.h"
#include "system.h"
#include "gpio.h"




int main(void)
{

    daisy::GPIO led;
    daisy::Pin ledpin(daisy::PORTC,7);
    led.Init(ledpin, daisy::GPIO::Mode::OUTPUT, daisy::GPIO::Pull::NOPULL, daisy::GPIO::Speed::MEDIUM);
    daisy::System MySystem;
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
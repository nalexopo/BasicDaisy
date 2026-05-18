#include "main.h"
#include "DigitalDelay.h"
#include "adc.h"
#include "stdatomic.h"

#define DELAY_SAMPLE_DEPTH 480000U
DaisySeed Board;

DigitalDelay<float, DELAY_SAMPLE_DEPTH> DSY_SDRAM_BSS DDelay;
int i=0;
std::atomic<bool> UpdateSettings = false;
std::atomic<int> Passthrough = 0;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    if(UpdateSettings)
    {
        UpdateSettings = false;
        DDelay.AdjustMix(Board.adc.GetFloat(0));
        DDelay.AdjustFeedback(Board.adc.GetFloat(1));
        DDelay.AdjustDelay(Board.adc.GetFloat(2));
    }    
    for(size_t i = 0; i < size; i++)
    {
        
        /** Set each of our outputs to the value of this sine wave */
        if(!(Passthrough%2))
        {
            OUT_L[i] = IN_L[i];
        }
        else
        {
            OUT_L[i] = DDelay.Process(IN_L[i]);
        }
        
        //OUT_R[i] = IN_R[i];
    }
}
float knob0, knob1, knob2, knob3, knob4, knob5;
int main(void)
{
   
    Board.Init();
    
    DDelay.Reset(1.5f, 0.8f, 0.7f, 32000);
    //ADC Init
    AdcChannelConfig adcConfig[6];

    adcConfig[0].InitSingle(Board.GetPin(16));
    adcConfig[1].InitSingle(Board.GetPin(17));
    adcConfig[2].InitSingle(Board.GetPin(18));
    adcConfig[3].InitSingle(Board.GetPin(19));
    adcConfig[4].InitSingle(Board.GetPin(20));
    adcConfig[5].InitSingle(Board.GetPin(21));
    
    
    //D25, D26 fs
    //D22, D23 leds
    GPIO led1, led2;
    GPIO fs1, fs2;
    GPIO sw1, sw2, sw3, sw4;

    sw1.Init(seed::D10, GPIO::Mode::INPUT, GPIO::Pull::PULLUP);
    sw2.Init(seed::D9, GPIO::Mode::INPUT, GPIO::Pull::PULLUP);
    sw3.Init(seed::D8, GPIO::Mode::INPUT, GPIO::Pull::PULLUP);
    sw4.Init(seed::D7, GPIO::Mode::INPUT, GPIO::Pull::PULLUP);

    fs1.Init(seed::D25, GPIO::Mode::INPUT, GPIO::Pull::PULLUP);
    fs2.Init(seed::D26, GPIO::Mode::INPUT, GPIO::Pull::PULLUP);

    led1.Init(seed::D22, GPIO::Mode::OUTPUT, GPIO::Pull::NOPULL, GPIO::Speed::MEDIUM);
    led2.Init(seed::D23, GPIO::Mode::OUTPUT, GPIO::Pull::NOPULL, GPIO::Speed::MEDIUM);
  
    Board.adc.Init(adcConfig, 6);
    Board.adc.Start();
    
    Board.StartAudio(AudioCallback);


    led2.Toggle();

    while(1)
    {
        i++;

        

        Board.DelayMs(500);
        
        if(!fs1.Read())led1.Toggle();
        if(!fs1.Read())Passthrough++;
        if(!fs2.Read())led2.Toggle();

        if(!sw1.Read())led1.Toggle();
        if(!sw2.Read())led2.Toggle();
        if(!sw3.Read())led1.Toggle();
        if(!sw4.Read())led2.Toggle();

        
        
        UpdateSettings = true;

        knob0 = Board.adc.GetFloat(0);
        knob1 = Board.adc.GetFloat(1);
        knob2 = Board.adc.GetFloat(2);
        knob3 = Board.adc.GetFloat(3);
        knob4 = Board.adc.GetFloat(4);
        knob5 = Board.adc.GetFloat(5);
    }
    return 1;
}
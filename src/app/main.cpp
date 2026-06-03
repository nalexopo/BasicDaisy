#include "main.h"
#include "DigitalDelay.h"
#include "adc.h"
#include "stdatomic.h"

#define DELAY_SAMPLE_DEPTH 480000U
DaisySeed Board;

DigitalDelay<float, DELAY_SAMPLE_DEPTH> DSY_SDRAM_BSS DDelay;
int i=0;
std::atomic<bool> UpdateSettings = false;

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
        OUT_L[i] = DDelay.Process(IN_L[i]);
        //OUT_L[i] = IN_L[i];
        //OUT_R[i] = IN_R[i];
    }
}

int main(void)
{
   
    Board.Init();
    
    DDelay.Reset(1.5f, 0.8f, 0.7f, 32000);
    //ADC Init
    AdcChannelConfig adcConfig[4];
    adcConfig[0].InitSingle(Board.GetPin(16));
    adcConfig[1].InitSingle(Board.GetPin(17));
    adcConfig[2].InitSingle(Board.GetPin(18));
    adcConfig[3].InitSingle(Board.GetPin(19));
  
    Board.adc.Init(adcConfig, 4);
    Board.adc.Start();
    
    Board.StartAudio(AudioCallback);

    while(1)
    {
        i++;
        Board.DelayMs(100);
        UpdateSettings = true;
    }
    return 1;
}
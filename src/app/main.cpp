#include "main.h"
#include "DigitalDelay.h"
#include "adc.h"
#include "stdatomic.h"
#include "tremolo.h"
#include "lfo.h"


#define DELAY_SAMPLE_DEPTH 480000U
DaisySeed Board;

tremolo trem(48000.0f);
int i=0;
std::atomic<bool> UpdateSettings = false;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    if(UpdateSettings)
    {
        UpdateSettings = false;
        trem.AdjustRate(Board.adc.GetFloat(0));
        trem.AdjustDepth(Board.adc.GetFloat(1));
        trem.AdjustMix(Board.adc.GetFloat(2));
    }    
    for(size_t i = 0; i < size; i++)
    {
        /** Set each of our outputs to the value of this sine wave */
        OUT_L[i] = trem.Process(IN_L[i]);
        //OUT_L[i] = IN_L[i];
        //OUT_R[i] = IN_R[i];
    }
}

int main(void)
{
   
    Board.Init();
    
    //trem.SetWaveform(lfo::waveform::WAVE_TRI);
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
#include "main.h"
#include "DigitalDelay.h"
#include "adc.h"
#include "stdatomic.h"
#include "tremolo.h"
#include "lfo.h"
#include "knob.h"

#define DELAY_SAMPLE_DEPTH 480000U
DaisySeed Board;

tremolo trem(48000.0f);
knob knob[6];

int i=0;
std::atomic<bool> UpdateSettings = false;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    if(UpdateSettings)
    {
        UpdateSettings = false;
        trem.AdjustRate(knob[0].Process(Board.adc.GetFloat(0)));
        trem.AdjustDepth(knob[1].Process(Board.adc.GetFloat(1)));
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
    
    trem.AdjustWaveForm(lfo::waveform::WAVE_TRI);
    //ADC Init
    AdcChannelConfig adcConfig[4];
    adcConfig[0].InitSingle(Board.GetPin(16));
    adcConfig[1].InitSingle(Board.GetPin(17));
    adcConfig[2].InitSingle(Board.GetPin(18));
    adcConfig[3].InitSingle(Board.GetPin(19));
  
    Board.adc.Init(adcConfig, 4);
    Board.adc.Start();
    
    Board.StartAudio(AudioCallback);
    for(i=0;i<3;i++)
    {
        knob[i].UnityCalibrate(0.015f, 1.f, 0.017f, 0.97f);
    }
    knob[0].Init(knob::EXPONENTIAL);
    knob[1].Init();
    knob[2].Init();
    while(1)
    {
        i++;
        Board.DelayMs(100);
        UpdateSettings = true;
    }
    return 1;
}
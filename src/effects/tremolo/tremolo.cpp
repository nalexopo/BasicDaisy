#include "tremolo.h"


void tremolo::AdjustRate(float pot)
{
    float freq = (0.1f + pot * 10.0f);
    float absdiff = (freq_  > freq) ? freq_  - freq : freq - freq_ ;
    if(absdiff > 0.01f)
    {
        freq_ = freq;
        tremlfo_.SetFreq(freq);
    }
}

void tremolo::AdjustDepth(float pot)
{
    float depth = daisysp::fclamp(pot, 0.f, 1.f);
    
    depth_ = depth;
    tremlfo_.SetGain(depth) ;         
}

void tremolo::AdjustWaveForm(enum lfo::waveform waveform)
{
    tremlfo_.SetWaveform(waveform);
}

float tremolo::Process(float sample)
{
    return    sample + sample * tremlfo_.Process();
}
#include "dsp.h"
#include "lfo.h"


float lfo::CalcPhaseInc(float f)
{
    return f/sampleRate_;
}

float lfo::Process(void)
{
    float out, t;
    switch(waveform_)
    {
        
        case WAVE_SIN: out = sinf(phase_ * TWOPI_F); break;
        case WAVE_TRI:
            t   = -1.0f + (2.0f * phase_);
            out = 2.0f * (fabsf(t) - 0.5f);
        break;
        case WAVE_SAW: out = -1.0f * (((phase_ * 2.0f)) - 1.0f); break;
        case WAVE_RAMP: out = ((phase_ * 2.0f)) - 1.0f; break;
        case WAVE_SQUARE: out = phase_ < sqpulse_duty_ ? (1.0f) : -1.0f; break;
        default:
        break;
    }
    
    phase_ += phase_inc_;
    
    if(phase_ > 1.0f)
    {
        phase_ -= 1.0f;
        eoc_ = true;
    }
    else
    {
        eoc_ = false;
    }
    
    return out * gain_;
}


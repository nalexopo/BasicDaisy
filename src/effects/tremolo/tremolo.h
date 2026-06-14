#ifndef TREMOLO_H
#define TREMOLO_H
#include "lfo.h"
#include "dsp.h"

class tremolo
{
    
    public:

        tremolo(float sample_rate) : tremlfo_(sample_rate) {};
        ~tremolo(){};

        void AdjustRate(float pot);

        void AdjustDepth(float pot);

        void AdjustWaveForm(enum lfo::waveform waveform);

        float Process(float sample);

        void AdjustMix(float pot)
        {
            mix_ = pot;
        }
        
    private:
        lfo tremlfo_;
        float freq_ = 0.1f;
        float dcgain_ = 0.5f;
        float depth_ = 0.5f;
        float mix_ = 0.5f;

};


#endif //TREMOLO_H
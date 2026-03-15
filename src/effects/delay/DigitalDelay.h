#ifndef DSY_DELAY_H
#define DSY_DELAY_H
#include <stdlib.h>
#include <stdint.h>


template<typename T, uint32_t sample_depth>

class DigitalDelay
{
    public:
    DigitalDelay() {}
    ~DigitalDelay() {}

    void Init() {Reset();}

    void Reset(float gain = 1.0f, float feedback = 0.5f, float mix = 0.5f, uint32_t delaySamples = 1)
    {
        for(uint32_t i = 0; i<sample_depth; i++)
        {
            audioBuffer[i] = T(0);
        }
        writeIndex_ = 0;
        readIndex_ =  0;
        
        
        gain_ = gain;
        feedback_ = feedback;
        mix_ = mix;
        delaySamples_ = delaySamples;
    }

    void DelayLineWrite(T sampleIn)
    {
        uint32_t delayedWriteIndex = writeIndex_;
        delayedWriteIndex += delaySamples_;
        if(delayedWriteIndex < sample_depth)
        {
            audioBuffer[delayedWriteIndex] = sampleIn;
        }
        else
        {
            delayedWriteIndex -= sample_depth;
            audioBuffer[delayedWriteIndex] = sampleIn;
        }
        writeIndex_++;
        if(writeIndex_ == sample_depth)
        {
            writeIndex_ = 0;
        }
    }
    T DelayLineRead(void)
    {
        T sample = audioBuffer[readIndex_];
        readIndex_++;
        if(readIndex_ == sample_depth)
        {
            readIndex_ = 0;
        }

        return sample;
    }
    T Process(T sampleIn)
    {
        T dry = sampleIn;
        T wet = feedback_ * DelayLineRead();
        
        DelayLineWrite(dry+wet);

        return gain_*((1.0f-mix_) * dry + mix_ * wet );
    }
    void AdjustMix(float pot)
    {
        mix_ = pot;
    }

    void AdjustFeedback(float pot)
    {
        feedback_ = pot;
    }

    void AdjustDelay(float pot)
    {
        uint32_t delaySamples = static_cast<uint32_t>(100000.0f * pot);

        //Dead Zone to compensate from potensiometer noise - Distorts audio
        if(delaySamples_-delaySamples > 10000)
        {
            delaySamples_ = delaySamples;
        }

    }


    private:
    T  audioBuffer[sample_depth];
    float mix_;
    float gain_;
    float feedback_;
    uint32_t delaySamples_;
    uint32_t writeIndex_;
    uint32_t readIndex_;
    
};


#endif //DSY_DELAY_H
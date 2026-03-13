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

    void Reset()
    {
        for(uint32_t i = 0; i<sample_depth; i++)
        {
            audioBuffer[i] = T(0);
        }
        writeIndex = 0;
        readIndex =  0;
        feedback = 0.95;
        mix = 0.8;
        delaySamples = 30000;
    }

    void DelayLineWrite(T sampleIn)
    {
        uint32_t delayedWriteIndex = writeIndex;
        delayedWriteIndex += delaySamples;
        if(delayedWriteIndex < sample_depth)
        {
            audioBuffer[delayedWriteIndex] = sampleIn;
        }
        else
        {
            delayedWriteIndex -= sample_depth;
            audioBuffer[delayedWriteIndex] = sampleIn;
        }
        writeIndex++;
        if(writeIndex == sample_depth)
        {
            writeIndex = 0;
        }
    }
    T DelayLineRead(void)
    {
        T sample = audioBuffer[readIndex];
        readIndex++;
        if(readIndex == sample_depth)
        {
            readIndex = 0;
        }

        return sample;
    }
    T Process(T sampleIn)
    {
        T dry = sampleIn;
        T wet = feedback * DelayLineRead() + sampleIn;
        DelayLineWrite(wet);

        return 1.5*((1-mix) * dry + mix * wet);
    }
    T  audioBuffer[sample_depth];
    private:
    float mix;
    float feedback;
    uint32_t delaySamples;
    uint32_t writeIndex;
    uint32_t readIndex;
    
};


#endif //DSY_DELAY_H
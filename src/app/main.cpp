#include "main.h"
#include "DigitalDelay.h"


#define DELAY_SAMPLE_DEPTH 480000U
DaisySeed Board;

DigitalDelay<float, DELAY_SAMPLE_DEPTH> DSY_SDRAM_BSS Delay;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    for(size_t i = 0; i < size; i++)
    {
        /** Set each of our outputs to the value of this sine wave */
        OUT_L[i] = Delay.Process(IN_L[i]);
        //OUT_L[i] = IN_L[i];
        OUT_R[i] = IN_R[i];
    }
}

int main(void)
{
    int i=0;
    Board.Init();
    Delay.Reset(1.0f, 0.8f, 0.7f, 32000);
    Board.StartAudio(AudioCallback);
    while(1)
    {
        i++;
        
    }
    return 1;
}
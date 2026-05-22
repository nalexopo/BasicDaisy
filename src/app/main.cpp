#include "main.h"
#include "DigitalDelay.h"
#include "lfo.h"
#include "adc.h"
#include "stdatomic.h"

#define DELAY_SAMPLE_DEPTH 480000U
DaisySeed Board;

lfo TestSin(48000.0f);
//DSY_SDRAM_BSS float Buffer[48000];
int i=0;
int j=0;
std::atomic<bool> UpdateSettings = false;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    if(UpdateSettings)
    {
        UpdateSettings = false;

    }    
    for(size_t i = 0; i < size; i++)
    {
        /** Set each of our outputs to the value of this sine wave */
        OUT_L[i] = TestSin.Process();
        // Buffer[j] = OUT_L[i];
        // j++;
        // if(j==48000)j=0;
        //OUT_L[i] = IN_L[i];
        //OUT_R[i] = IN_R[i];
    }
}

int main(void)
{
   
    Board.Init();
    
    
    Board.StartAudio(AudioCallback);

    while(1)
    {
        i++;
        Board.DelayMs(100);
        UpdateSettings = true;
    }
    return 1;
}
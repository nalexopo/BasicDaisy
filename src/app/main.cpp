#include "main.h"

DaisySeed Board;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    for(size_t i = 0; i < size; i++)
    {
        /** Set each of our outputs to the value of this sine wave */
        OUT_L[i] = IN_L[i];
        OUT_R[i] = IN_R[i];
    }
}

int main(void)
{
    int i=0;
    Board.Init();
    Board.StartAudio(AudioCallback);
    while(1)
    {
        i++;
        
    }
    return 1;
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "DigitalDelay.h"

#define DELAY_SAMPLE_DEPTH 50U
DigitalDelay<float, DELAY_SAMPLE_DEPTH> Delay;

void printDelayLine()
{
  for(int i = 0; i<50 ; i++)
  {
    std::cout<<Delay.audioBuffer[i]<<"|";
    
  }
  std::cout << "\r\n";
  std::cout << "\r\n";
}

// Demonstrate some basic assertions.
TEST(Fuck, testttt) {

  float Samples[200] = {0};
  float Output[200] = {0};
  Samples[10] = 1000;
  Samples[9] = 500;
  Samples[11] = 500;
  Samples[8] = 200 ; 
  Samples[12] = 200;

  Delay.Init();

  for(int i = 0; i<200 ; i++)
  {
    Output[i] = Delay.Process(Samples[i]);
  }
  for(int i = 0; i<100 ; i++)
  {
    std::cout<< Output[i] <<"|";
  }
  std::cout << "\r\n";
  printDelayLine();
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
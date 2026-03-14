#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "DigitalDelay.h"

#define DELAY_SAMPLE_DEPTH 50U
DigitalDelay<float, DELAY_SAMPLE_DEPTH> Delay;

// Demonstrate some basic assertions.
TEST(DigitalDelayTest, Impulsetest) {

  float Samples[200] = {0};
  float Output[200] = {0};
  Samples[10] = 1000;
  Samples[9] = 500;
  Samples[11] = 500;
  Samples[8] = 200 ; 
  Samples[12] = 200;

  Delay.Reset(1.0f, 0.5f, 0.7f, 7);

  for(int i = 0; i<200 ; i++)
  {
    Output[i] = Delay.Process(Samples[i]);
  }
  for(int i = 0; i<200 ; i++)
  {
    std::cout<< Output[i] <<"|";
  }
  std::cout << "\r\n";

}
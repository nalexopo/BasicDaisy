# BasicDaisy
A basic project setup based on the daisy seed board by Electrosmith, to be used as an STM dev board.

The motivation for this setup is the fact that I wanted a cheap STM dev board with external RAM. After some research I went with Daisy Seed board. Obviously the Electrosmith daisy codebase is intented to support their whole line of products which was not my use case. Also their whole setup is C++17 and I wanted to have something working with C++23 to have an opportunity to learn the newer features.

The project contains the basic stuff (maybe a few more) from original Daisy codebase that are required to blink the onboard led. 
Project uses arm-none-eabi 14.3.1 version so it can be used with C++23.


Directions:

make <br />
make clean <br />
make program <br />

All work from parent project folder. Debugging is clunky and bugging through make, but works perfectly with VsCode Cortex M debug Addon by marus25. For now, I guess gdb scripts are out of the question.

I am planning to add google test support. Maybe I will do a non-HAL version. I will try to keep main branch in a basic project form and do my own dev on branches. 

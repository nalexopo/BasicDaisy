# BasicDaisy
A bare bones daisy seed based project with absolute minimum features to support digital audio effects development in C++23.

The motivation for this setup is the fact that I wanted a cheap STM dev board with external RAM. After some research I went with Daisy Seed board. Obviously the Electrosmith daisy codebase is intended to support their whole line of products which was not my use case. Also their whole setup is C++17 and I wanted to have something working with C++23 to have an opportunity to learn the newer features.

The project contains the basic stuff (maybe a few more) from original Daisy codebase that are required to develop an effect pedal(potensiometers, audio passthrough). 
 Project uses arm-none-eabi 14.3.1 version so it can be used with C++23.


### Directions:

#### Using cmake:
cd build <br />
cmake .. -DCMAKE_BUILD_TYPE=Debug/Release <br />
make clean <br />
make <br />
To flash: make program <br />

#### Testing with google test (only hello world for now)
cd test <br />
cmake -S . -B build <br />
cmake --build build <br />
cd build && ctest<br />

All work from parent project folder. Debugging works perfectly with VsCode Cortex M debug Addon by marus25. For now, I guess gdb scripts are out of the question.

Maybe I will do a non-HAL version. Pending to see how tests work with hardware dependencies. 

Blink led @ 12c2cb8e7459371a14212ea0384d66e50286da91. I will add the effects I make in main branch.

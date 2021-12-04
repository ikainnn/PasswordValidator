#ifndef TIMING_HPP
#define TIMING_HPP

#include <chrono>
#include <iostream>

namespace pswd::utils
{
    #define TIMER_START() ({ auto timerBegin = std::chrono::high_resolution_clock::now(); timerBegin; })
    #define TIMER_STOP(X) ({\
                auto timerEnd = std::chrono::high_resolution_clock::now();\
                auto timerDuration = std::chrono::duration<double, std::milli>(timerEnd - X);\
                std::printf("%s(): took me \033[33m[%f]ms\033[0m to execute!\n", __FUNCTION__, timerDuration.count());\
            })
}

#endif

// From coderodde
//https://codereview.stackexchange.com/questions/132852/easy-to-use-c-class-for-asking-current-time-stamp-in-milli-micro-and-nanose

#ifndef CURRENT_TIME_H
#define CURRENT_TIME_H

#include <chrono>
#include <cstdint>

class CurrentTime {
    std::chrono::high_resolution_clock m_clock;

public:
    uint64_t milliseconds();
    uint64_t microseconds();
    uint64_t nanoseconds();
    uint64_t seconds();
};

#endif  /* CURRENT_TIME_H */

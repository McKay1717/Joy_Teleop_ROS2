// From coderodde
//https://codereview.stackexchange.com/questions/132852/easy-to-use-c-class-for-asking-current-time-stamp-in-milli-micro-and-nanose
#include "CurrentTime.h"

uint64_t CurrentTime::milliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
              (m_clock.now().time_since_epoch()).count();
}

uint64_t CurrentTime::microseconds()
{
    return std::chrono::duration_cast<std::chrono::microseconds>
              (m_clock.now().time_since_epoch()).count();
}

uint64_t CurrentTime::nanoseconds()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>
              (m_clock.now().time_since_epoch()).count();
}
uint64_t CurrentTime::seconds()
{
    return std::chrono::duration_cast<std::chrono::seconds>
              (m_clock.now().time_since_epoch()).count();
}

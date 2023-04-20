#include <time.h>
#define POSIX 1
#define WINDOWS 2

#define PLATFORM WINDOWS

class Timer
{
#if PLATFORM == WINDOWS
    clock_t starttime_;
    clock_t stoptime_;
#else
    struct timespec starttime_;
    struct timespec stoptime_;
#endif
    double elapsedTime_;
    bool isstop_;
public:
    Timer();
    void reset();
    void start();
    void stop();
    double currtime();
    double starttime();
};

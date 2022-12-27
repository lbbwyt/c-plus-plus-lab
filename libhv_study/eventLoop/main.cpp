//
// Created by lbb on 2022/12/27.
//


#include "hv.h"
#include "EventLoop.h"

#define _MEMCHECK  atexit(_memcheck);


static inline void _memcheck(void) {
    printf("Test Memcheck => alloc:%ld free:%ld\n", hv_alloc_cnt(), hv_free_cnt());
}

using namespace hv;


static void onTimer(TimerID  timerID, int  n) {
    printf("tid=%ld timerID=%lu time=%lus n=%d\n", hv_gettid(), (unsigned long)timerID, (unsigned long)time(NULL), n);
}

int  main(int argc, char * argv[]) {
    _MEMCHECK;
    printf("main tid=%ld\n", hv_gettid());
    EventLoopPtr  loop(new EventLoop);
    // runEvery 1s
    loop->setInterval(1000, std::bind(onTimer, std::placeholders::_1, 200));
    // runAfter 10s
    loop->setTimeout(10000, [&loop](TimerID timerID){
        loop->stop();
    });

    loop->queueInLoop([](){
        printf("queueInLoop tid=%ld\n", hv_gettid());
    });

    loop->runInLoop([](){
        printf("runInLoop tid=%ld\n", hv_gettid());
    });

    // run until loop stopped
    loop->run();
    return  0;

}
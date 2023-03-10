#ifndef _APP_TIMER_H_
#define _APP_TIMER_H_

#include "app_common.h"

#define APP_TIMER_MAX_COUNT 20

typedef void (*timer_ind_cb_fcn)(union sigval v);
  
typedef struct{
  timer_t timerid;
  struct sigevent sev;   
  struct itimerspec its;
}_st_app_timer;

	int app_timer_init();
	int app_timer_deinit();
/*
* time_interval : ms 
*/
    timer_t app_startTimer(int time_interval, timer_ind_cb_fcn handler);
    void app_stopTimer(timer_t id);    


#endif


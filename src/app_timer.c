#include "app_timer.h"

#define CLOCKID       CLOCK_REALTIME
static unsigned int app_timer_is_init = 0;
_st_app_timer m_stTimer[APP_TIMER_MAX_COUNT];

int app_timer_init()
{
  memset(&m_stTimer, 0, sizeof(m_stTimer));
  return -1;
}

int app_timer_deinit()
{
  int i = 0;
  for(i = 0 ; i < APP_TIMER_MAX_COUNT; i++){
    if(m_stTimer[i].timerid != 0){
      DEBUGLOG("timer delete ret:%d\n", timer_delete (m_stTimer[i].timerid));
      memset(&m_stTimer[i], 0, sizeof(_st_app_timer));  
    }
  }
  return -1;
}

timer_t app_startTimer(int time_interval,  timer_ind_cb_fcn handler)
{
  int i = 0;
  timer_t id_ret = 0;

  for(i = 0 ; i < APP_TIMER_MAX_COUNT; i++){
    if(m_stTimer[i].timerid == 0){      
      /* Create the timer */   
      m_stTimer[i].sev.sigev_notify = SIGEV_THREAD;   
      m_stTimer[i].sev.sigev_notify_function = handler;        
      m_stTimer[i].sev.sigev_value.sival_int = i;
     
      if (timer_create(CLOCKID, &m_stTimer[i].sev, &(m_stTimer[i].timerid)) == -1)   {    
        DEBUGLOG("timer_create fail\n");   
      }
      
      /* Start the timer */
      m_stTimer[i].its.it_value.tv_sec = time_interval / 1000;   
      m_stTimer[i].its.it_value.tv_nsec = time_interval % 1000 * 1000 * 1000;   
      m_stTimer[i].its.it_interval.tv_sec = m_stTimer[i].its.it_value.tv_sec;   
      m_stTimer[i].its.it_interval.tv_nsec =m_stTimer[i].its.it_value.tv_nsec;   
      if (timer_settime(m_stTimer[i].timerid, 0, &m_stTimer[i].its, NULL) == -1)       
        DEBUGLOG("timer_settime fail\n");      
      
      id_ret = m_stTimer[i].timerid;
      break;

    }
    
  }
  

  return id_ret;
}

void app_stopTimer(timer_t timerid)
{
  int i = 0;
  
  for(i = 0 ; i < APP_TIMER_MAX_COUNT; i++){
    if(m_stTimer[i].timerid == timerid){
      DEBUGLOG("timer delete ret:%d\n", timer_delete (timerid));
      memset(&m_stTimer[i], 0, sizeof(_st_app_timer));  
    }
  }
}


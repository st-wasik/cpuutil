#ifndef ELAPSED_TIMER_H
#define ELAPSED_TIMER_H

typedef struct elapsed_timer elapsed_timer_t;

elapsed_timer_t* elapsed_timer_create(void);

void elapsed_timer_destroy(elapsed_timer_t* timer);

void elapsed_timer_restart(elapsed_timer_t* elapsed_timer);

long long elapsed_timer_get_elapsed_usec(elapsed_timer_t* elapsed_timer);

#endif // ELAPSED_TIMER_H
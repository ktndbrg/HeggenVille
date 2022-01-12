#ifndef UPDATE
#define UPDATE

#define DOWN 0
#define UP 1

#define WALK_TIMER 0.10f
#define IDLE_TIMER 0.10f
#define SHOOT_TIMER 0.10f
#define DIE_TIMER 0.10f
#define BULLET_TIMER 0.10f

void update (void);

extern double time_scale;
extern int prev_ticks;
extern int cur_ticks;

#endif

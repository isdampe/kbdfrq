#ifndef _KEYS_H
#define _KEYS_H
#include <pthread.h>
#include <stdbool.h>

#define EV_VAL_KEY_DOWN 0x1
#define EV_VAL_KEY_REPEAT 0x2
#define EVENT_KEY_PRESS(a) a == EV_VAL_KEY_DOWN || a == EV_VAL_KEY_REPEAT
#define EVENT_KEY_RELEASE(a) a != EV_VAL_KEY_DOWN && a != EV_VAL_KEY_REPEAT

static pthread_t write_thread;
static pthread_mutex_t write_lock;

struct keyboard_s {
	const char *input_path;
	unsigned long long key_map[256];
};

static void *write_log(void *data);
bool start_logging(struct keyboard_s *kbd);

#endif
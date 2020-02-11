#include "keys.h"
#include <unistd.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void *write_log(void *data)
{
	struct keyboard_s *kbd = data;
	while (1) {
		pthread_mutex_lock(&write_lock);

		time_t T= time(NULL);
		struct tm tm = *localtime(&T);

		char *line = calloc((40 + (10 * 256)), sizeof(char));
		char empty_line[15];

		char file_name[255];
		memset(file_name, 0x0, 255);
		sprintf(file_name, "%02d-%02d-%04d.json", tm.tm_mday, 
			tm.tm_mon + 1, tm.tm_year + 1900);

		sprintf(line, "\"%04d-%02d-%02d %02d:%02d:%02d\": {",
			tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
			tm.tm_hour, tm.tm_min, tm.tm_sec);

		for (int i=0; i<255; ++i) {
			if (kbd->key_map[i] > 0) {
				sprintf(empty_line, "\"0x%02x\": %llu, ", i, kbd->key_map[i]);
				strcat(line, empty_line);
				empty_line[0] = '\0';
			}
		}
		sprintf(empty_line, "\"0x%02x\": %llu", 255, kbd->key_map[255]);
		strcat(line, empty_line);
		strcat(line, "}\n");

		FILE *fh = fopen(file_name, "a");
		fwrite(line, 0x1, strlen(line), fh);
		fclose(fh);

		free(line);
		pthread_mutex_unlock(&write_lock);
		sleep(30);
	}
}

bool start_logging(struct keyboard_s *kbd)
{
	pthread_mutex_init(&write_lock, NULL);
	pthread_create(&write_thread, NULL, write_log, kbd);

	for (int i=0; i<256; ++i)
		kbd->key_map[i] = 0;

	int fd = open(kbd->input_path, O_RDONLY);
	if (fd < 0)
		return false;

	struct input_event event;
	while (1) {
		read(fd, &event, sizeof(struct input_event));
		if (event.type == EV_KEY && EVENT_KEY_PRESS(event.value)) {
			pthread_mutex_lock(&write_lock);
			kbd->key_map[event.code]++;
			pthread_mutex_unlock(&write_lock);
		}
	}

	close(fd);
	pthread_join(write_thread, NULL);
	return true;
}
#include <stdio.h>
#include "keys.h"

int main(const int argc, const char **argv)
{
	struct keyboard_s keyboard = {
		.input_path = "/dev/input/event16"
	};

	if (argc > 1)
		keyboard.input_path = argv[argc -1];

	if (! start_logging(&keyboard)) {
		fprintf(stderr, "Error: Couldn't open %s for reading. Are you running as sudo?\n",
			keyboard.input_path);
	}

	return 0;
}
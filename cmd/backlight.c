
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	if (argc != 2) return 1;
	char const *file = 0;
	char data[100];
	file = "/sys/class/backlight/rpi_backlight/bl_power";
	if (strcmp(argv[1], "on") == 0) {
		strcpy(data, "0\n");
	} else if (strcmp(argv[1], "off") == 0) {
		strcpy(data, "1\n");
	} else if (isdigit(argv[1][0] & 0xff)) {
		file = "/sys/class/backlight/rpi_backlight/brightness";
		sprintf(data, "%d\n", atoi(argv[1]));
	} else {
		file = 0;
	}
	if (file) {
		FILE *fp = fopen(file, "a");
		if (fp) {
			fputs(data, fp);
			fclose(fp);
		}
	}
	return 0;
}


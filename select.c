//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"

//selects an area of the image
void select_area(char *instruction, image *current_image)
{
	if (!current_image->loaded) {
		printf("%s\n", IMAGE_ERROR);
	} else if (strstr(instruction, "ALL")) {
		select_all_pixels(current_image);
		printf("%s\n", "Selected ALL");
	} else {
		int x1, y1, x2, y2;

		char *p = strstr(instruction, "SELECT") + strlen("SELECT");
		p = get_number(p, &x1);
		if (!p) {
			printf("%s\n", COMMAND_ERROR);
			return;
		}
		p = get_number(p, &y1);
		if (!p) {
			printf("%s\n", COMMAND_ERROR);
			return;
		}
		p = get_number(p, &x2);
		if (!p) {
			printf("%s\n", COMMAND_ERROR);
			return;
		}
		p = get_number(p, &y2);
		if (!p) {
			printf("%s\n", COMMAND_ERROR);
			return;
		}

		if (x1 > x2)
			swap_integers(&x1, &x2);

		if (y1 > y2)
			swap_integers(&y1, &y2);

		int ok = 1;

		if (x1 < 0 || x1 >= current_image->mat.width)
			ok = 0;
		if (x2 < 0 || x2 > current_image->mat.width)
			ok = 0;
		if (y1 < 0 || y1 >= current_image->mat.height)
			ok = 0;
		if (y2 < 0 || y2 > current_image->mat.height)
			ok = 0;
		if (x1 == x2)
			ok = 0;
		if (y1 == y2)
			ok = 0;

		if (ok) {
			current_image->coordinates.x1 = x1;
			current_image->coordinates.y1 = y1;
			current_image->coordinates.x2 = x2;
			current_image->coordinates.y2 = y2;
			printf("%s %d %d %d %d\n", "Selected", x1, y1, x2, y2);
		} else {
			printf("%s\n", "Invalid set of coordinates");
		}
	}
}

//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"
#include "utils.h"

int main(void)
{
	char *instruction;
	instruction = alloc_with_check(MAXIMUM_LENGTH);

	int exit_flag = 0;
	image current_image;
	current_image.loaded = 0;

	while (!exit_flag) {
		fgets(instruction, MAXIMUM_LENGTH, stdin);

		if (strstr(instruction, "LOAD") == instruction)
			load_image(instruction, &current_image);
		else if (strstr(instruction, "SELECT") == instruction)
			select_area(instruction, &current_image);
		else if (strstr(instruction, "ROTATE") == instruction)
			rotate_image(instruction, &current_image);
		else if (strstr(instruction, "CROP") == instruction)
			crop_image(&current_image);
		else if (strstr(instruction, "APPLY") == instruction)
			apply_filter(instruction, &current_image);
		else if (strstr(instruction, "SAVE") == instruction)
			save_image(instruction, &current_image);
		else if (strstr(instruction, "EXIT") == instruction)
			exit_flag = exit_program(&current_image);
		else
			printf("%s\n", COMMAND_ERROR);
	}
	free(instruction);

	return 0;
}

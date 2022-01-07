//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"

int main(void)
{
	char *instruction;
	instruction = (char *)malloc(MAXIMUM_LENGTH * sizeof(char));
	if (instruction == NULL) {
		fprintf(stderr, "%s\n", MEMORY_ERROR);
		return -1;
	}

	int exit_flag = 0;
	image current_image;
	current_image.loaded = 0;

	while (!exit_flag) {
		
		fgets(instruction, MAXIMUM_LENGTH, stdin);

		if (strstr(instruction, "LOAD"))
			load_image(instruction, &current_image);
		else if (strstr(instruction, "SELECT"))
			select_area(instruction, &current_image);
		else if (strstr(instruction, "ROTATE"))
			rotate_image(instruction, &current_image);
		else if (strstr(instruction, "CROP"))
			crop_image(&current_image);
		else if (strstr(instruction, "APPLY"))
			apply_filter(instruction, &current_image);
		else if (strstr(instruction, "SAVE"))
			save_image(instruction, &current_image);
		else if (strstr(instruction, "EXIT"))
			exit_flag = exit_program(&current_image);
		else
			printf("%s\n", COMMAND_ERROR);
	}

	free(instruction);
	
	return 0;
}

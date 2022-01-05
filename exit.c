//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"

int exit_program(image *current_image)
{
	if (!current_image->loaded) {
		printf("%s\n", IMAGE_ERROR);
		return 0;
	}
	free_matrix(current_image->mat.a, current_image->mat.height);
	return 1;
}

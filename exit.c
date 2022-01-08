//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"

//returns 0 when the image is not loaded (the program is not ended)
//returns 1 (the program is ended) and frees the memory otherwise
int exit_program(image *current_image)
{
	if (!current_image->loaded)
		printf("%s\n", IMAGE_ERROR);
	else
		free_matrix(current_image->mat.a, current_image->mat.height);
	return 1;
}

//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"
#include "utils.h"

//saves the image as file_name
//when "ascii" follows the file_name, the image is written as text file
//otherwise, it is written as binary file

int myround(double x)
{
	if ((int)x == (int)(x - 0.5))
		return (int)x + 1;
	return (int)x;
}

void save_image(char *instruction, image *current_image)
{
	if (!current_image->loaded) {
		printf("%s\n", IMAGE_ERROR);
		return;
	}
	char *p = strstr(instruction, "SAVE") + strlen("SAVE");
	char *file_name = NULL;
	file_name = alloc_with_check(MAXIMUM_LENGTH);
	p = get_name(p, file_name);

	FILE *out;
	out = fopen(file_name, "wt");

	if (!out) {
		fprintf(stderr, "%s\n", MEMORY_ERROR);
		free(file_name);
		return;
	}

	int max_value = MAX_VALUE;
	if (strstr(p, "ascii")) {
		if (current_image->type == 2 || current_image->type == 5)
			fprintf(out, "P%d\n", 2);
		else
			fprintf(out, "P%d\n", 3);
		fprintf(out, "%d ", current_image->mat.width);
		fprintf(out, "%d\n", current_image->mat.height);
		fprintf(out, "%d\n", max_value);
		for (int h = 0; h < current_image->mat.height; ++h) {
			for (int w = 0; w < current_image->mat.width; ++w) {
				if (current_image->type == 2 || current_image->type == 5) {
					fprintf(out, "%d ", myround(current_image->mat.a[h][w].r));
				} else {
					fprintf(out, "%d ", myround(current_image->mat.a[h][w].r));
					fprintf(out, "%d ", myround(current_image->mat.a[h][w].g));
					fprintf(out, "%d ", myround(current_image->mat.a[h][w].b));
				}
			}
			fprintf(out, "\n");
		}
	} else {
		if (current_image->type == 2 || current_image->type == 5)
			fprintf(out, "P%d\n", 5);
		else
			fprintf(out, "P%d\n", 6);
		fprintf(out, "%d ", current_image->mat.width);
		fprintf(out, "%d\n", current_image->mat.height);
		fprintf(out, "%d\n", max_value);
		fclose(out);
		out = fopen(file_name, "ab");
		for (int h = 0; h < current_image->mat.height; ++h) {
			for (int w = 0; w < current_image->mat.width; ++w) {
				unsigned char aux;
				if (current_image->type == 2 || current_image->type == 5) {
					aux = (unsigned char)myround(current_image->mat.a[h][w].r);
					fwrite(&aux, sizeof(unsigned char), 1, out);
				} else {
					aux = (unsigned char)myround(current_image->mat.a[h][w].r);
					fwrite(&aux, sizeof(unsigned char), 1, out);
					aux = (unsigned char)myround(current_image->mat.a[h][w].g);
					fwrite(&aux, sizeof(unsigned char), 1, out);
					aux = (unsigned char)myround(current_image->mat.a[h][w].b);
					fwrite(&aux, sizeof(unsigned char), 1, out);
				}
			}
		}
	}
	printf("%s %s\n", "Saved", file_name);
	free(file_name);
	fclose(out);
}

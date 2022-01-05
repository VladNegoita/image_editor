//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"

void load_image(char *instruction, image *current_image)
{
	char *p = strstr(instruction, "LOAD") + strlen("LOAD");
	char *file_name = NULL;
	file_name = (char *)malloc(MAXIMUM_LENGTH * sizeof(char));
	if(file_name == NULL) {
		fprintf(stderr, "%s\n", MEMORY_ERROR);
		return;
	}
	p = get_name(p, file_name);

	FILE *in = fopen(file_name, "rt");
	if(in == NULL) {
		printf("%s %s\n", "Failed to load ", file_name);
		return;
	}

	char *s = (char *)malloc(MAXIMUM_LENGTH * sizeof(char));

	current_image->loaded = 1;

	fgets(s, MAXIMUM_LENGTH, in);
	if (strstr(s, "P2")) {
		current_image->type = 2;
	}
	else if (strstr(s, "P3")) {
		current_image->type = 3;
	}
	else if (strstr(s, "P5")) {
		current_image->type = 5;
	}
	else if (strstr(s, "P6")) {
		current_image->type = 6;
	}
	else if (strstr(s, "P1")) {
		current_image->type = 1;
	}
	else if (strstr(s, "P4")) {
		current_image->type = 4;
	}
	else {
		printf("Inavalid image format");
		return;
	}

	fgets(s, MAXIMUM_LENGTH, in);
	while (strstr(s, "#"))
		fgets(s, MAXIMUM_LENGTH, in);

	p = get_number(s, &current_image->mat.height);
	p = get_number(p, &current_image->mat.width);

	pixel **aux;
	aux = alloc_matrix(current_image->mat.height, current_image->mat.width);
	current_image->mat.a = aux;

	select_all_pixels(current_image);

	if (current_image->type != 1 && current_image->type != 4) {
		fgets(s, MAXIMUM_LENGTH, in);
		while (strstr(s, "#"))
			fgets(s, MAXIMUM_LENGTH, in);

		int maximum_value;///////////////////////////////////////////////////
		p = get_number(s, &maximum_value);
	}
	if (current_image->type >= 4) {
		read_binary(in, current_image);
	} else {
		read_text(in, current_image);
	}

	printf("%s %s\n", "Loaded", file_name);

	fclose(in);
	free(file_name);
	free(s);
}

void read_text(FILE *in, image *current_image)
{
	for (int h = 0; h < current_image->mat.height; ++h) {
		for (int w = 0; w < current_image->mat.width; ++w) {
			if (current_image->type == 2) {
				fscanf(in, "%lf", &current_image->mat.a[h][w].r);
			} else {
				fscanf(in, "%lf", &current_image->mat.a[h][w].r);
				fscanf(in, "%lf", &current_image->mat.a[h][w].g);
				fscanf(in, "%lf", &current_image->mat.a[h][w].b);
			}
		}
	}
}

void read_binary(FILE *in, image *current_image)
{
	for (int h = 0; h < current_image->mat.height; ++h) {
		for (int w = 0; w < current_image->mat.width; ++w) {
			unsigned char aux;
			if (current_image->type == 5) {
				fread(&aux, sizeof(unsigned char), 1, in);
				current_image->mat.a[h][w].r = (double)aux;
			} else {
				fread(&aux, sizeof(unsigned char), 1, in);
				current_image->mat.a[h][w].r = (double)aux;
				fread(&aux, sizeof(unsigned char), 1, in);
				current_image->mat.a[h][w].g = (double)aux;
				fread(&aux, sizeof(unsigned char), 1, in);
				current_image->mat.a[h][w].b = (double)aux;
			}
		}
	}
}

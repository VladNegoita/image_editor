//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"

pixel** alloc_matrix(int lines, int columns)
{
	pixel **a = NULL;

	a = (pixel **) malloc(lines * sizeof(pixel *));
	if(a == NULL) {
		fprintf(stderr, "%s\n", MEMORY_ERROR);
		return NULL;
	}

	for (int i = 0; i < lines; ++i) {
		a[i] = (pixel *)malloc(columns * sizeof(pixel));
		if (a[i] == NULL) {
			for (int j = i - 1; j >= 0; --j) {
				free(a[j]);
			}
			free(a);
			fprintf(stderr, "%s\n", MEMORY_ERROR);
			return NULL;
		}
	}
	return a;
}

void free_matrix(pixel **a, int lines)
{
	for (int i = 0; i < lines; ++i)
		free(a[i]);
	free(a);
}

void select_all_pixels(image *current_image)
{
	current_image->coordinates.x1 = 0;
	current_image->coordinates.y1 = 0;
	current_image->coordinates.x2 = current_image->mat.width;
	current_image->coordinates.y2 = current_image->mat.height;
}

int is_digit(char character)
{
	return (character <= '9' && character >= '0');
}

void swap_integers(int *m, int *n)
{
	int aux;

	aux = *m;
	*m = *n;
	*n = aux;
}

char* get_number(char *instruction, int *number)
{
	int i = 0, sign = 1;
	while (i < (int)strlen(instruction) && !is_digit(instruction[i]) ) {
		++i;
	}

	if(i > 0 && instruction[i - 1] == '-')
		sign = -1;

	*number = 0;
	while(i < (int)strlen(instruction) && is_digit(instruction[i])) {
		*number = *number * 10 + (int)(instruction[i] - '0');
		++i;
	}

	*number = *number * sign;

	return instruction + i;
}

char* get_name(char *instruction, char *name)
{
	int i = 0, j = 0;
	while (i < (int)strlen(instruction) && strchr(SEP, instruction[i]))
		++i;
	while (i < (int)strlen(instruction) && !strchr(SEP, instruction[i]))
		name[j++] = instruction[i++];
	name[j] = 0;
	return instruction + i;
}

void init(image *new_image, image *current_image)
{
	new_image->type = current_image->type;
	new_image->loaded = current_image->loaded;
	new_image->mat.height = current_image->mat.height;
	new_image->mat.width = current_image->mat.width;
	pixel **aux = alloc_matrix(new_image->mat.height, new_image->mat.width);
	new_image->mat.a = aux;
	new_image->coordinates = current_image->coordinates;
}

pixel add(pixel p1, pixel p2)
{
	pixel sum;

	sum.r = p1.r + p2.r;
	sum.g = p1.g + p2.g;
	sum.b = p1.b + p2.b;

	return sum;
}

pixel multiply(pixel p1, double number)
{
	pixel product;

	product.r = p1.r * number;
	product.g = p1.g * number;
	product.b = p1.b * number;

	return product;
}

pixel clamp_pixel(pixel p)
{
	p.r = clamp(p.r);
	p.g = clamp(p.g);
	p.b = clamp(p.b);

	return p;
}

double clamp(double number)
{
	if (number < 0)
		return 0;
	if (number > MAX_VALUE)
		return MAX_VALUE;
	return number;
}

//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"
#include "utils.h"

//allocates memory for a matrix of pixels of dimensions lines and columns
pixel **alloc_matrix(int lines, int columns)
{
	pixel **a = NULL;

	a = (pixel **)malloc(lines * sizeof(pixel *));
	if (!a) {
		fprintf(stderr, "%s\n", MEMORY_ERROR);
		return NULL;
	}

	for (int i = 0; i < lines; ++i) {
		a[i] = (pixel *)malloc(columns * sizeof(pixel));
		if (!a[i]) {
			for (int j = i - 1; j >= 0; --j)
				free(a[j]);
			free(a);
			fprintf(stderr, "%s\n", MEMORY_ERROR);
			return NULL;
		}
	}
	return a;
}

//frees the memory for a matrix of pixels
void free_matrix(pixel **a, int lines)
{
	for (int i = 0; i < lines; ++i)
		free(a[i]);
	free(a);
}

//marks the whole image as selected
void select_all_pixels(image *current_image)
{
	current_image->coordinates.x1 = 0;
	current_image->coordinates.y1 = 0;
	current_image->coordinates.x2 = current_image->mat.width;
	current_image->coordinates.y2 = current_image->mat.height;
}

//returns 1 if the character is a digit and 0 otherwise
int is_digit(char character)
{
	return (character <= '9' && character >= '0');
}

//swaps the values of two int variables
void swap_integers(int *m, int *n)
{
	int aux;

	aux = *m;
	*m = *n;
	*n = aux;
}

//parse the input and extracts a number
char *get_number(char *instruction, int *number)
{
	int i = 0, sign = 1;
	while (i < (int)strlen(instruction) && instruction[i] == ' ')
		++i;

	if (instruction[i] == '-') {
		sign = -1;
		++i;
	}

	if (!is_digit(instruction[i]))
		return NULL;

	*number = 0;
	while (i < (int)strlen(instruction) && is_digit(instruction[i])) {
		*number = *number * 10 + (int)(instruction[i] - '0');
		++i;
	}

	*number = *number * sign;

	return instruction + i;
}

//parse the input and extracts a name (file_name for example)
char *get_name(char *instruction, char *name)
{
	int i = 0, j = 0;
	while (i < (int)strlen(instruction) && instruction[i] == ' ')
		++i;
	while (i < (int)strlen(instruction) && !strchr("\n ", instruction[i]))
		name[j++] = instruction[i++];
	name[j] = 0;

	if (j == 0)
		return NULL;

	return instruction + i;
}

//initialise the values of a new image based on the current image
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

//returns the sum (in a vectorial way) of the two pixels
pixel add(pixel p1, pixel p2)
{
	pixel sum;

	sum.r = p1.r + p2.r;
	sum.g = p1.g + p2.g;
	sum.b = p1.b + p2.b;

	return sum;
}

//multiplies the values of a pixel by a number
pixel multiply(pixel p1, double number)
{
	pixel product;

	product.r = p1.r * number;
	product.g = p1.g * number;
	product.b = p1.b * number;

	return product;
}

//restrict a pixel to a given interval
pixel clamp_pixel(pixel p)
{
	p.r = clamp(p.r);
	p.g = clamp(p.g);
	p.b = clamp(p.b);

	return p;
}

//restrict a number to a given interval
double clamp(double number)
{
	if (number < 0)
		return 0;
	if (number > MAX_VALUE)
		return MAX_VALUE;
	return number;
}

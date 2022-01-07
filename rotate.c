//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"

int entire_zone(image *current_image);
void rotate_zone(image *current_image);
void rotate_entire_image(image *current_image);

//this function deals with the angle and the number of rotations needed
//then calls other function to perform the effective rotation

void rotate_image(char *instruction, image *current_image)
{
	int angle;
	get_number(instruction, &angle);

	if (!current_image->loaded) {
		printf("%s\n", IMAGE_ERROR);
	} else if (angle % 90 || angle < -360 || angle > 360) {
		printf("%s\n", "Unsupported rotation angle");
	} else {
		int x1 = current_image->coordinates.x1;
		int y1 = current_image->coordinates.y1;
		int x2 = current_image->coordinates.x2;
		int y2 = current_image->coordinates.y2;

		if (x2 - x1 != y2 - y1 && !entire_zone(current_image)) {
			printf("%s\n", "The selection must be square");
		} else {
			
			printf("Rotated %d\n", angle);
			if (angle < 0)
				angle += 360;
			angle %= 360;

			int rotations_needed = angle / 90;

			for (int i = 0; i < rotations_needed; ++i)
				if (!entire_zone(current_image))
					rotate_zone(current_image);
				else
					rotate_entire_image(current_image);
		}
	}
}

//returns 1 if the entire image is selected and 0 otherwise
int entire_zone(image *current_image)
{
	if (current_image->coordinates.x1 != 0)
		return 0;
	if (current_image->coordinates.y1 != 0)
		return 0;
	if (current_image->coordinates.x2 != current_image->mat.width)
		return 0;
	if (current_image->coordinates.y2 != current_image->mat.height)
		return 0;
	return 1;
}

//effectively rotates to the right the selected area
void rotate_zone(image *current_image)
{
	image new_image;
	int x1 = current_image->coordinates.x1;
	int y1 = current_image->coordinates.y1;
	int x2 = current_image->coordinates.x2;
	int y2 = current_image->coordinates.y2;
	int height = current_image->mat.height;
	int width = current_image->mat.width;

	init(&new_image, current_image);

	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			if (h < y1 || h >= y2 || w < x1 || w >= x2) {
				new_image.mat.a[h][w] = current_image->mat.a[h][w];
			}
			else {
				pixel aux = current_image->mat.a[h][w];
				new_image.mat.a[y1 + w - x1][x2 - 1 - h + y1] = aux;
			}
		}
	}

	free_matrix(current_image->mat.a, current_image->mat.height);
	*current_image = new_image;
}

//rotates the entire image and performs other necessary changes
void rotate_entire_image(image *current_image)
{
	image new_image;
	int height = current_image->mat.height;
	int width = current_image->mat.width;

	new_image.mat.width = current_image->mat.height;
	new_image.mat.height = current_image->mat.width;
	pixel **auxp = alloc_matrix(new_image.mat.height, new_image.mat.width);
	new_image.mat.a = auxp;
	select_all_pixels(&new_image);
	new_image.type = current_image->type;
	new_image.loaded = current_image->loaded;

	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			pixel aux = current_image->mat.a[h][w];
			new_image.mat.a[w][height - 1 - h] = aux;
		}
	}

	free_matrix(current_image->mat.a, current_image->mat.height);
	*current_image = new_image;
}

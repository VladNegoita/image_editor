//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"

void rotate(image *current_image)
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

		if (x2 - x1 != y2 - y1) {
			printf("%s\n", "The selection must be square");
		} else {
			
			printf("Rotated %d\n", angle);
			if (angle < 0)
				angle += 360;
			angle %= 360;

			int rotations_needed = angle / 90;

			for (int i = 0; i < rotations_needed; ++i)
				rotate(current_image);
		}
	}
}

//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"

int max(int x, int y)
{
	if (x > y)
		return x;
	return y;
}

int min(int x, int y)
{
	if (x > y)
		return y;
	return x;
}

void calculus(image *current_image, int effect)
{
	image new_image;
	init(&new_image, current_image);

	//dh[] and dw[] are direction arrays
	//the first pair points to the element itself
	//the next 4 pairs point to the side neighbours (one side common)
	//the last 4 pairs point to the diagonal neighbours
	int dh[9] = {0, 0, 0, 1, -1, 1, -1, 1, -1};
	int dw[9] = {0, 1, -1, 0, 0, 1, -1, -1, 1};

	//these are the kernel matrices associated with the direction arrays
	double edge[9] = {8, -1, -1, -1, -1, -1, -1, -1, -1};
	double sharpen[9] = {5, -1, -1, -1, -1, 0, 0, 0, 0};
	double blur[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	double gaussian_blur[9] = {4, 2, 2, 2, 2, 1, 1, 1, 1};
	for (int i = 0; i < 9; ++i) {
		blur[i] /= 9;
		gaussian_blur[i] /= 16;
	}
	int x1 = current_image->coordinates.x1;
	int y1 = current_image->coordinates.y1;
	int x2 = current_image->coordinates.x2;
	int y2 = current_image->coordinates.y2;

	//this area, named interior area has all the elements in the zone
	// (x1, y1) -> (x2, y2) that have 8 neighbours
	int int_x1 = max(1, x1);
	int int_y1 = max(1, y1);
	int int_x2 = min(current_image->mat.width - 2, x2 - 1);
	int int_y2 = min(current_image->mat.height - 2, y2 - 1);

	for (int h = 0; h < current_image->mat.height; ++h) {
		for (int w = 0; w < current_image->mat.width; ++w) {
			if (h < int_y1 || h > int_y2 || w < int_x1 || w > int_x2) {
				new_image.mat.a[h][w] = current_image->mat.a[h][w];
				continue;
			}
			pixel sum = {0, 0, 0};///the resulting pixel
			for (int i = 0; i < 9; ++i) {
				pixel aux = current_image->mat.a[h + dh[i]][w + dw[i]];
				if (effect == 2)
					sum = add(sum, multiply(aux, sharpen[i]));
				else if (effect == 3)
					sum = add(sum, multiply(aux, blur[i]));
				else if (effect == 4)
					sum = add(sum, multiply(aux, gaussian_blur[i]));
				else if (effect == 1)
					sum = add(sum, multiply(aux, edge[i]));
			}
			sum = clamp_pixel(sum);
			new_image.mat.a[h][w] = sum;
		}
	}
	free_matrix(current_image->mat.a, current_image->mat.height);
	*current_image = new_image;
}

//this function applies an filter
//the options are: EDGE, SHARPEN, BLUR and GAUSSIAN_BLUR
void apply_filter(char *instruction, image *current_image)
{
	int effect = 0;
	char *p, *filter_name = (char *)malloc(MAXIMUM_LENGTH * sizeof(char));
	p = get_name(strstr(instruction, "APPLY") + strlen("APPLY"), filter_name);
	if (!p) {
		printf("%s\n", COMMAND_ERROR);
		free(filter_name);
		return;
	}
	if (strstr(filter_name, "SHARPEN")) {
		effect = 2;
	} else if (strstr(filter_name, "GAUSSIAN_BLUR")) {
		effect = 4;
	} else if (strstr(filter_name, "BLUR")) {
		effect = 3;
	} else if (strstr(filter_name, "EDGE")) {
		effect = 1;
	} else {
		printf("%s\n", "Invalid filter name");
		return;
	}
	free(filter_name);
	if (current_image->loaded == 0) {
		printf("%s\n", IMAGE_ERROR);
	} else if (current_image->type != 3 && current_image->type != 6) {
		printf("%s\n", "Easy, Charlie Chaplin");
	} else {
		calculus(current_image, effect);

		if (effect == 1)
			printf("APPLY EDGE done\n");
		else if (effect == 2)
			printf("APPLY SHARPEN done\n");
		else if (effect == 3)
			printf("APPLY BLUR done\n");
		else
			printf("APPLY GAUSSIAN_BLUR done\n");
	}
}

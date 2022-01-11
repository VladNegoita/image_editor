//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"
#include "utils.h"

//this function crops an image to the selected region
void crop_image(image *current_image)
{
	if (!current_image->loaded) {
		printf("%s\n", IMAGE_ERROR);
	} else {
		image new_image;

		int x1 = current_image->coordinates.x1;
		int y1 = current_image->coordinates.y1;
		int x2 = current_image->coordinates.x2;
		int y2 = current_image->coordinates.y2;

		new_image.loaded = current_image->loaded;
		new_image.type = current_image->type;
		new_image.mat.width = x2 - x1;
		new_image.mat.height = y2 - y1;
		select_all_pixels(&new_image);
		pixel **aux = alloc_matrix(new_image.mat.height, new_image.mat.width);
		new_image.mat.a = aux;

		for (int h = 0; h < new_image.mat.height; ++h)
			for (int w = 0; w < new_image.mat.width; ++w)
				new_image.mat.a[h][w] = current_image->mat.a[h + y1][w + x1];

		free_matrix(current_image->mat.a, current_image->mat.height);
		*current_image = new_image;
		printf("%s\n", "Image cropped");
	}
}

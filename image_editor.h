//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#ifndef IMAGE_EDITOR_HEADER
#define IMAGE_EDITOR_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_LENGTH 100
#define MAX_VALUE 255
#define MEMORY_ERROR "Memory allocation has failed"
#define COMMAND_ERROR "Invalid command"
#define IMAGE_ERROR "No image loaded"

//the 3 values that identify a pixel (red, green and blue)
typedef struct {
	double r, g, b;
} pixel;

//**a -> pointer to the elements of the matrix (pixel values)
//width, height -> dimensions of the matrix
typedef struct {
	pixel **a;
	int width, height;
} matrix;

//a rectangle surface delimited by two points:
//x1, y1 -> top-left point coordinates
//x2, y2 -> bottom-right point coordinates
//x1 <= x2 and y1 <= y2 relationship holds
//the selected zone is the rectangle delimited
//	by the segments [x1, x2) (horizontal) and [y1, y2) (vertical)
typedef struct {
	int x1, y1;
	int x2, y2;
} area;

//mat -> a matrix of pixels
//loaded = 1 if the image is loaded, 0 otherwise
//type is the number that was after P in the loaded file
typedef struct {
	matrix mat;
	int loaded, type;
	area coordinates;
} image;

int exit_program(image *current_image);
void apply_filter(char *instruction, image *current_image);
void crop_image(image *current_image);
void rotate_image(char *instruction, image *current_image);
void select_area(char *instruction, image *current_image);
void load_image(char *instruction, image *current_image);
void save_image(char *instruction, image *current_image);

#endif

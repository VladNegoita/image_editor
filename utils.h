//Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_editor.h"

#define MAXIMUM_LENGTH 100
#define MAX_VALUE 255
#define MEMORY_ERROR "Memory allocation has failed"
#define COMMAND_ERROR "Invalid command"
#define IMAGE_ERROR "No image loaded"

pixel **alloc_matrix(int lines, int columns);
void free_matrix(pixel **a, int lines);
void select_all_pixels(image *current_image);
int is_digit(char character);
void swap_integers(int *m, int *n);
char *get_number(char *instruction, int *number);
char *get_name(char *instruction, char *name);
double clamp(double number);
pixel clamp_pixel(pixel p);
pixel multiply(pixel p1, double number);
pixel add(pixel p1, pixel p2);
void init(image *new_image, image *current_image);
char *alloc_with_check(int count);

#endif

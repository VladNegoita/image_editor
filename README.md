# image_editor

## Part I: The structure used 

Image contains the following members:

-mat -> a matrix (memorized together with the 
		dimensions: height, width) of pixels(3 real numbers)
		
-loaded -> a flag that indicates if the matrix is empty or not

-type -> helps to identify the image 
		 type (grayscale, color, white & black)

-coordinates -> identifies a selected rectangle area on which 
				the transformations will take place

## Part II: The operations permitted

This app is developed to be used in the terminal. Here is what you can do:

1. LOAD <name_file> -> loads your image into the memory

					-> is designed to work with the ppm or pgm 
					   format (otherwise, you should convert your image
					   in a .ppm or .pgm)

					-> works with both binary and text files

					-> if another image si already loaded, it frees the
					   corresponding memory and loads the new one

					-> works with both plain and binary format of the
					   images. The format specifier is essential: after
					   reading it, we choose know what type of image we
					   have:

							-> P1 and P4 are the white & black images

							-> P2 and P5 are the grayscale images

							-> P3 and P6 are the color images

							-> Note: The second format is the binary one

					-> prints a succes message when succeded and a
					   failure message otherwise

2. SELECT <x1> <y1> <x2> <y2> -> the workspace will become the rectangle
								 identified by these coordinates:

									-> (x1, y1) -> top-left corner
									-> (x2, y2) -> bottom-right corner

							  -> prints a succes message when succeded
								 and a failure message otherwise

3. SELECT ALL -> the workspace will become the entire image

			  -> prints a succes message when finished

4. ROTATE <angle> -> rotates the selected area with the angle considered
					 clockwise (but can be negative)

				  -> works only with 90 degrees multiples (90, 180, 270,
					 -90, -180, -270). if the angle is not divisible
					 by 90, prints a specific error message

				  -> this action is performed by rotating 90 degrees the
					 image multiple (eventually) times

				  -> the rotation has meaning only when the selected area
					 is a square or the entire matrix is selected

				  -> prints a succes message when finished

5. CROP -> reduces the image only to the selected area

		-> frees the memory useless to the new image
		   (efficient dynamic allocation and deallocation)

		->prints a succes message

6. APPLY <PARAMETER> -> involves the application of the desired filter

					 -> using the specific (and pretty meaningful) kernel
						matrices, the selected area can suffer one of
						the following transformations:

							a. EDGE -> used for highlight the edges

							b. SHARPEN -> increases the contrast between
										  adjacent pixels

							c. BLUR -> blurs uniformly the image

							d. GAUSSIAN_BLUR -> blurs the image using
												another way

					 -> the kernel matrices are 3 x 3, so there are 9
					 values implied in the calculations. Those matrices
					 are linearised so that the number in the i-th position
					 correspond to the i-th neighbour

					 -> prints a succes message when finished

7. SAVE <file_name> -> creates a new image file with the edits made
					   this file will be saved in the same folder as
					   the program

					-> when receiving an extra parameter [ascii],
					   saves the image in a plain format (text);
					   otherwise, the pixels will be kept in a
					   binary form

					-> prints "Saved <file_name>" when the action is done

8. EXIT -> ends the program

###### Note: The parameters are the ones between angular parantheses

###### Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

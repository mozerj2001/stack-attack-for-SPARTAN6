/*
 * framework.h
 *
 *  Created on: Nov 24, 2021
 *      Author: József Mózer
 *
 *  This header file contains the declaration of all functionality that
 *  enables and handles writing to the screen.
 *  List:	*declaration of global object and character structures
 *  		*declaration of the following functions:
 *  			- setupObjects
 *  			- objectToFB
 *  			- characterToFB
 */

#ifndef FRAMEWORK_H_
#define FRAMEWORK_H_

#include "structures.h"
#include "xparameters.h"

// How many boxes the game can handle.
#define BOXES_COUNT 3 // 80 is the maximum number of 16x15 objects that fit on the screen.

// Declare global pointer to the starting address of the frame buffer.
extern int* FB_POINTER;

// Declare object variables. A maximum of 79 objects, excluding the character
// can fit on the screen.
extern struct object boxesArray[BOXES_COUNT];
// Declare character variable.
extern struct character playerC;
// Declare player character bitmap.
extern unsigned int characterPixels[16][15];

/*
 * The setupObjects function fills the bitmaps of the boxesArray objects and
 * the playerC character. It also sets the default values for all other variables
 * in these structs.
 * INPUTS: none
 * OUTPUTS: none
 * */
void setupObjects();

/*
 * The objectToFB function writes the object to its appropriate place int he frame buffer.
 * INPUTS: struct coords coordinates - a coords type struct, containing the coordinates
 * 										of the object's "top left" pixel
 * */
void objectToFB(struct coords coordinates);

/*
 * The characterToFB function writes the character's bitmap to its appropriate place in
 * the frame buffer.
 * INPUTS: 	unsigned int* rgbMap - a 16x15 bitmap to be written into the Frame Buffer
 * 			struct coords coordinates - a coords type struct, containing the
 * 				coordinates of the first pixel in the bitmap
 * OUTPUTS: none
 * */
void characterToFB(unsigned int** rgbMap, struct coords coordinates);

#endif /* FRAMEWORK_H_ */

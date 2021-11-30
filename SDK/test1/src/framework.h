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
 *  			- updateStates
 *  			- updatePositions
 */

#ifndef FRAMEWORK_H_
#define FRAMEWORK_H_

#include "structures.h"
#include "xparameters.h"


// How many boxes the game can handle.
#define BOXES_COUNT 10 // Number of 8x8 objects to fit on the screen.

// Declare global pointer to the starting address of the frame buffer.
extern int* FB_POINTER;

// Declare object variables.
extern struct object boxesArray[BOXES_COUNT];
// Declare character variable.
extern struct character playerC;
// Declare player character bitmap.
extern unsigned int characterPixels[16][15];
// Declare a variable that counts how many boxes are deployed. This can be used
// as a limit for indexing the boxesArray. Objects with a lower index than this
// number are all deployed. No objects with a higher index are deployed. In case
// boxes are removed from the screen, the entire boxesArray will be reorganized.
extern unsigned int deployedBoxes;

/*
 * The delay function is a generic delay function that idles the processor
 * to delay certain functions. Only for testing, shouldn't be used in the actual
 * implementation.
 * INPUT: x - This is how many times the function will count to 1000;
 * OUTPUT: none
 * */
void delay(unsigned int x);

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

/*
 * The deployBox function takes a position and puts a previously undeployed object in
 * that position. It needs to increment the deployedObjects variable.
 * INPUT: struct coords coordinates - a coords type struct that the new object's position
 * 				will be set to upon deployment.
 * OUTPUT: none
 * */
void deployBox(struct coords depPosition);

/*
 * The updateStates function checks all deployed boxes for positions and checks whether
 * they block each other or not. It accomplishes this by iterating through all deployed
 * objects for every other deployed object.
 * INPUT: none
 * OUTPUT: none
 *
 * TODO: Optimization. This is currently an n^2 alogithm.
 * */
void updateStates();

/*
 * The updatePositions function checks the movement states of each object and
 * the player character and updates their location accordingly. This should be called
 * every cycle to ensure smooth movement.
 * INPUTS: none
 * OUTPUTS: none
 * */
void updatePositions();



#endif /* FRAMEWORK_H_ */






















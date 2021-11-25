/*
 * structures.h
 *
 *
 *
 *  Created on: Nov 24, 2021
 *      Author: József Mózer
 *
 *  This header contains all structure declarations used in the program of the game.
 *  It also contains all global variable declarations that use these structures.
 *
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

/*
 * coords is a struct that stores the coordinates of an object.
 * Because of the 160x120 reduced screen resolution, the real position
 * should be calculated as such: (160 * y) + x (x: horizontal coordinate, y: vertical coordinate)
 * */

struct coords {
	unsigned int x;
	unsigned int y;
};

/*
 * object is a struct that stores the data of a box or any other object.
 * The position variable itself represents the location of the top left pixel (0th element
 * of the bitmap array).
 * If isFalling is 1, then the object is in falling state, if 0, then it is still.
 * If isDeployed is 1, then the object will be drawn to the given coordinates. Elsewise it won't "exist" in-game.
 * */

struct object {
	struct coords position;
	int isFalling;
	int isDeployed;
};


/*
 * character is a struct that stores the data of the controllable player character.
 * The position variable itself represents the location of the top left pixel (0th element
 * of the bitmap array).
 * vspeed represents the vertical speed of the character.
 * hspeed represents the horizontal speed of the character.
 * isFalling is 1 when the character is in free fall, 0 when it is on the ground.
 * This determines whether a vertical acceleration will be applied to its speed each cycle
 * or not.
 * pixels stores the raw RGB data of each pixel of the object.
 * */

struct character {
	struct coords position;
	int hspeed;
	int vspeed;
	int isFalling;
	unsigned int pixels[10][10];
};
























#endif /* STRUCTURES_H_ */

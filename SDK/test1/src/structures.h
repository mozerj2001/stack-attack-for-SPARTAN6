/*
 * structures.h
 *
 *
 *
 *  Created on: Nov 24, 2021
 *      Author: J?zsef M?zer
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
	unsigned long int x;
	unsigned long int y;
};

/*
 * object is a struct that stores the data of a box or any other object.
 * The position variable itself represents the location of the top left pixel (0th element
 * of the bitmap array).
 * If isFalling is 1, then the object is in falling state, if 0, then it is still.
 * isHorizontallyBlocked is 1, if the box can't move in any horizontal direction,
 * because an object or the screen border is blocking its way. There is no need to
 * make a distinction between right and left, as a box with either side blocked
 * can't be moved anymore.
 * */

struct object {
	struct coords position;
	int hspeed;
	int isFalling;
	int isHorizontallyBlocked;
};


/*
 * character is a struct that stores the data of the controllable player character.
 * The position variable itself represents the location of the top left pixel (0th element
 * of the bitmap array).
 * vspeed represents the vertical speed of the character.
 * hspeed represents the horizontal speed of the character.
 * isFalling is 1 when the character is in free fall, 0 when it is on the ground.
 * This determines whether a vertical acceleration will be applied to its speed each cycle.
 * isLeftBlocked and isRightBlocked are 1, if the character can't move in that direction,
 * because an object or the screen border is blocking its way.
 * or not.
 * pixels stores the raw RGB data of each pixel of the object.
 * */

struct character {
	struct coords position;
	int hspeed;
	int vspeed;
	int isFalling;
	int jumpStart;
	int isLeftBlocked;
	int isRightBlocked;
	unsigned int pixels[8][8];
};
























#endif /* STRUCTURES_H_ */

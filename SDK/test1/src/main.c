#include "xparameters.h"
#include "structures.h"
#include "framework.h"
#include "testfunctions.h"
#include "movement.h"

int main(void)
{
		int cntr = 0;
		int i;
		int k = 0;
		int genCounter = 0;
		struct coords deploymentTestLoc;



		setupObjects();
		playerC.hspeed = 4;
		playerC.position.x = 50;
		playerC.position.y = 50;
		while(1){
			for(k = 0; k < 19200; k++){
				*(FB_POINTER+k) = 0x03;
			}
			if(cntr % 5 == 0){ playerC.hspeed -= 2*playerC.hspeed; }
			if(cntr % 20 == 0){ /*jumpC();*/ }
			characterToFB(characterPixels, playerC.position);
			updateStates();
			updatePositions();
			delay(50);
			cntr++;
		}
}



























#include "xparameters.h"
#include "structures.h"
#include "framework.h"


volatile int* LED_PTR = XPAR_AXI_GPIO_LED_BASEADDR;
volatile int* DIG0_PTR = XPAR_AXI_APB_BRIDGE_0_BASEADDR + 0x0;
volatile int* DIG1_PTR = XPAR_AXI_APB_BRIDGE_0_BASEADDR + 0x4000;



int main()
{
	int cntr = 0;
	int i;
	int k = 0;


	*(LED_PTR+1) = 0x0;

	setupObjects();

	boxesArray[0].position.x = 50;
	boxesArray[0].position.y = 50;
	boxesArray[1].position.x = 100;
	boxesArray[1].position.y = 60;
	boxesArray[2].position.x = 0;
	boxesArray[2].position.y = 80;





	while(1)
	{
		*LED_PTR = cntr;
		*DIG0_PTR = cntr & 0xF;
		*DIG1_PTR = (cntr >> 4) & 0xF;		// counter shifted by 4, then masked
		cntr++;

		for(k = 0; k < 19200; k++){
			*(FB_POINTER+k) = 0x00;
		}

		for (i=0; i<5000000; i++);

		objectToFB(boxesArray[0].position);

		for (i=0; i<5000000; i++);

		objectToFB(boxesArray[1].position);

		for (i=0; i<5000000; i++);

		objectToFB(boxesArray[2].position);

		for (i=0; i<10000000; i++);

		characterToFB(playerC.pixels, playerC.position);

		for (i=0; i<10000000; i++);
		//===============================================//
		for(k = 0; k < 19200; k++){
			*(FB_POINTER+k) = 0x03;
		}

		for (i=0; i<5000000; i++);

		objectToFB(boxesArray[0].position);

		for (i=0; i<5000000; i++);

		objectToFB(boxesArray[1].position);

		for (i=0; i<5000000; i++);

		objectToFB(boxesArray[2].position);

		for (i=0; i<10000000; i++);

		characterToFB(playerC.pixels, playerC.position);

		for (i=0; i<10000000; i++);
		//===============================================//

		for(k = 0; k < 19200; k++){
			*(FB_POINTER+k) = 0xB0;
		}

		for (i=0; i<5000000; i++);

		objectToFB(boxesArray[0].position);

		for (i=0; i<5000000; i++);

		objectToFB(boxesArray[1].position);

		for (i=0; i<5000000; i++);

		objectToFB(boxesArray[2].position);

		for (i=0; i<10000000; i++);

		characterToFB(playerC.pixels, playerC.position);

		for (i=0; i<10000000; i++);
		//===============================================//

		for(k = 0; k < 19200; k++){
			*(FB_POINTER+k) = 0x30;
		}

		for (i=0; i<5000000; i++);

		objectToFB(boxesArray[0].position);

		for (i=0; i<5000000; i++);

		objectToFB(boxesArray[1].position);

		for (i=0; i<5000000; i++);

		objectToFB(boxesArray[2].position);

		for (i=0; i<10000000; i++);

		characterToFB(playerC.pixels, playerC.position);

		for (i=0; i<10000000; i++);

		// writing to the Frame Buffer
		/*for(i = 0; i < BOXES_COUNT; i++){
			objectToFB(boxesArray[i].position);
		}*/
		//characterToFB(playerC.pixels, playerC.position);

		//characterToFB(playerC.pixels, playerC.position);
		//objectToFB(boxesArray[0].position);

	}

}
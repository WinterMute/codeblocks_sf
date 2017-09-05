#include <string.h>
#include <stdio.h>

#include <3ds.h>

int main()
{

	gfxInitDefault();

	consoleInit(GFX_TOP, NULL);

	printf("Hello World!\n");

	// Main loop
	while (aptMainLoop()) {
		gspWaitForVBlank();
		hidScanInput();

		// Your code goes here

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	// Exit services
	gfxExit();
	return 0;
}

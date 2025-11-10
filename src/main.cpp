#include <nds.h>
#include <stdio.h>

static volatile int frame = 0;

//---------------------------------------------------------------------------------
// VBlank interrupt handler. This function is executed in IRQ mode - be careful!
//---------------------------------------------------------------------------------
static void Vblank()
{
	frame++;
}

int main(void)
{
	touchPosition touchXY;

	irqSet(IRQ_VBLANK, Vblank);

	consoleDemoInit();

	iprintf("      Hello DS dev'rs\n");
	iprintf("     \x1b[32mwww.devkitpro.org\n");
	iprintf("   \x1b[32;1mwww.drunkencoders.com\x1b[39m");

	while(pmMainLoop())
    {
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;

		touchRead(&touchXY);

		// print at using ansi escape sequence \x1b[line;columnH
		iprintf("\x1b[10;0HFrame = %d",frame);
		iprintf("\x1b[16;0HTouch x = %04X, %04X\n", touchXY.rawx, touchXY.px);
		iprintf("Touch y = %04X, %04X\n", touchXY.rawy, touchXY.py);

        swiWaitForVBlank();
	}

	return 0;
}
// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

// This example shows how to use the light sensor, see also libnx applet.h.

// Main program entrypoint
int main(int argc, char* argv[])
{
    // This example uses a text console, as a simple way to output text to the screen.
    // If you want to write a software-rendered graphics application,
    //   take a look at the graphics/simplegfx example, which uses the libnx Framebuffer API instead.
    // If on the other hand you want to write an OpenGL based application,
    //   take a look at the graphics/opengl set of examples, which uses EGL instead.
    consoleInit(NULL);

    printf("light-sensor example\n");
    printf("Press A to check light-sensor.\n");
    printf("Press + to exit.\n");

    // Main loop
    while (appletMainLoop())
    {
        // Scan all the inputs. This should be done once for each frame
        hidScanInput();

        // hidKeysDown returns information about which buttons have been
        // just pressed in this frame compared to the previous one
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS)
            break; // break in order to return to hbmenu

        if (kDown & KEY_A) {
            Result rc = 0;
            float fLux=0;
            bool availableflag=0;
            bool bOverLimit=0;

            rc = appletIsIlluminanceAvailable(&availableflag);
            printf("appletIsIlluminanceAvailable(): 0x%x", rc);
            if (R_SUCCEEDED(rc)) printf(", %d", availableflag);
            printf("\n");

            if (R_SUCCEEDED(rc) && availableflag) {
                // appletGetCurrentIlluminance(Ex) are the same except Ex has the bOverLimit param.

                rc = appletGetCurrentIlluminance(&fLux);
                printf("appletGetCurrentIlluminance(): 0x%x", rc);
                if (R_SUCCEEDED(rc)) printf(", %f", fLux);
                printf("\n");

                rc = appletGetCurrentIlluminanceEx(&bOverLimit, &fLux);
                printf("appletGetCurrentIlluminanceEx(): 0x%x", rc);
                if (R_SUCCEEDED(rc)) printf(", %d, %f", bOverLimit, fLux);
                printf("\n");
            }
        }

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);
    return 0;
}

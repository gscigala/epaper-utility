#include "EPD_2in15g.h"
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define CLEAN_STATE_DURATION_MS 10000

void display_splash_screen(const char *bmp_path)
{
	printf("%s\n", __func__);

	if(DEV_Module_Init() != 0) {
		return;
	}

	printf("%s: init\n", __func__);
	EPD_2IN15G_Init();

	/* clear sequence to possibly unplug the system after white clean */
	printf("%s: clear white\n", __func__);
	EPD_2IN15G_Clear(EPD_2IN15G_WHITE);
	DEV_Delay_ms(5000);

	UBYTE *image;
	UWORD Imagesize = ((EPD_2IN15G_WIDTH % 4 == 0)? (EPD_2IN15G_WIDTH / 4 ): (EPD_2IN15G_WIDTH / 4 + 1)) * EPD_2IN15G_HEIGHT;
	if((image = (UBYTE *)malloc(Imagesize)) == NULL) {
		printf("%s: failed to allocate image memory...\n", __func__);
		return;
	}

	Paint_NewImage(image, EPD_2IN15G_WIDTH, EPD_2IN15G_HEIGHT, 0, EPD_2IN15G_WHITE);
	Paint_SetScale(4);
	Paint_SelectImage(image);
	GUI_ReadBmp_RGB_4Color(bmp_path, 0, 0);
	EPD_2IN15G_Display(image);
	DEV_Delay_ms(5000);
    
	printf("%s: clear white\n", __func__);
	EPD_2IN15G_Clear(EPD_2IN15G_WHITE);

	printf("%s: go to sleep\n", __func__);
	EPD_2IN15G_Sleep();
	free(image);
	image = NULL;
	DEV_Delay_ms(2000); // required by Waveshare

	printf("%s: close 5V, Module enters 0 power consumption\n", __func__);
	DEV_Module_Exit();
}

void clean_screen(int cycles)
{
	printf("%s\n", __func__);

	if(DEV_Module_Init() != 0) {
		return;
	}

	printf("%s: init\n", __func__);
	EPD_2IN15G_Init();

	for (int i = 0; i < cycles; i++) {
		printf("%s: clear white\n", __func__);
		EPD_2IN15G_Clear(EPD_2IN15G_WHITE);
		DEV_Delay_ms(CLEAN_STATE_DURATION_MS);

		printf("%s: clear black\n", __func__);
		EPD_2IN15G_Clear(EPD_2IN15G_BLACK);
		DEV_Delay_ms(CLEAN_STATE_DURATION_MS);
	}

	printf("%s: clear white\n", __func__);
	EPD_2IN15G_Clear(EPD_2IN15G_WHITE);

	printf("%s: go to sleep\n", __func__);
	EPD_2IN15G_Sleep();
	DEV_Delay_ms(2000); // required by Waveshare

	printf("%s: close 5V, Module enters 0 power consumption\n", __func__);
	DEV_Module_Exit();
}

void print_usage(const char *program_name) {
	printf("Usage: %s [-c cycles] [-s splash_image_path]\n", program_name);
	printf("  -c, --cycles <number>  Number of cleaning cycles (default is 1).\n");
	printf("  -s, --splash <path>    Path to the splash screen image.\n");
}

int main(int argc, char *argv[]) {
	int opt;
	int cycles = 1;
	const char *splash_image_path = NULL;

	static struct option long_options[] = {
		{"cycles", required_argument, 0, 'c'},
		{"splash", required_argument, 0, 's'},
		{0, 0, 0, 0}
	};

	while ((opt = getopt_long(argc, argv, "c:s:", long_options, NULL)) != -1) {
		switch (opt) {
		case 'c':
			cycles = atoi(optarg);
			break;
		case 's':
			splash_image_path = optarg;
			break;
		default:
			print_usage(argv[0]);
			return 1;
		}
	}

	if (splash_image_path) {
		display_splash_screen(splash_image_path);
	} else {
		clean_screen(cycles);
	}

	return 0;
}

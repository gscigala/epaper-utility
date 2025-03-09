# epaper-utility
Tool to manage WaveShare 2.15 inch G+ e-paper screen, with cleaning sequence and splash screen.

## Features

- **Display Splash Screen**: Show a splash screen image from a specified BMP file.
- **Clean Screen**: Perform cleaning cycles to refresh the e-paper display and prevent ghosting.

## Requirements

- Waveshare 2.15 inch G+ e-paper display.

## Compilation

	meson setup build

	meson compile -C build

## Program options

    -c, --cycles <number>: clean cycle mode, with number of cleaning cycles to perform (default is 1).
    -s, --splash <path>: splash screen mode, with the splash screen image (BMP format).

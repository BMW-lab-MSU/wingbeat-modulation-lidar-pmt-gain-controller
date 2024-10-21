# Insect lidar gain controller MCU

This directory contains the source code for the insect lidar gain controller MCU. This project uses an MSP430FR2355.

## Overview

## Development

### Development environment setup
This project is developed using [VSCodium](https://vscodium.com/) (or VS Code) and [PlatformIO](https://platformio.org/). This is the preferred development environment, but [TI Code Composter Studio](https://www.ti.com/tool/CCSTUDIO) can also be used.

1. Download [VSCodium](https://vscodium.com/) or VS Code
2. Install the PlatformIO extension
3. Open the PlatformIO project that's in this repository
4. Install the lpmsp430fr2355 board in PlatformIO (this might already happen when you open the project)

### Unit tests
Unit tests go in the `test` folder. You can [run the unit tests with PlatformIO](https://docs.platformio.org/en/latest/advanced/unit-testing/index.html).
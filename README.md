# Simple Blink QBS Template Project
Simple blink as a template project with qbs build system. Qbs supported by Qt Creator because of which it was choosen. To configure Qt Creator for qbs and building stm32 pojects see [Configure Qt Creatot](https://github.com/0xebef/qube#qube---qt-creator-bare-metal-qbs-project-templates-for-stm32-development-with-stm32cubemx)

On template only used CMSIS (direct appeal to registers).
In current template used [Black Board](https://stm32-base.org/boards/STM32F103C8T6-Black-Board) with STM32F103C8 microcontroller (which is used in the famous Blue Pill).

## Build
Building by qbs via Qt Creator or by __make__ in the terminal in the project directory:

```sh
make
```

## Flash
Required utility __stlink__. On firmware directory:

```sh
st-flash write firmware.bin 0x08000000
```

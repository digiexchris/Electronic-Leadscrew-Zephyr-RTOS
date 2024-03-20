| Supported Targets |  |
| ----------------- | ----- |
| STM32F103C8T6 | (Blue Pill) |

# Leadscrew Warranty Voider

This is an electronic leadscrew inspired by espELS and Clough42. It aims to make threading easier on lathes that use manually changed changegears.

# Setup
- docker desktop with a wsl backend, and install winget install --interactive --exact dorssel.usbipd-win to allow usb passtrhough
- have the vscode dev containers extension, and rebuild and reopen in container
- open a terminal in the container to /workspaces/Electronic-Leadscrew-Zephyr-RTOS/ and execute west init
- run build.bat with one of the supported boards, eg build.bat rpi_pico

# Running the Tests
## deprecated
- add ZEPHYR_SDK to your environment variables for your user, this is the path to the bin dir that contains the zephyr gdb for arm
- install qemu, add bin dir to path
- use the Debug Tests launch configuration

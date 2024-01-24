| Supported Targets |  |
| ----------------- | ----- |
| STM32F103C8T6 | (Blue Pill) |

# Leadscrew Warranty Voider

This is an electronic leadscrew inspired by espELS and Clough42. It aims to make threading easier on lathes that use manually changed changegears.

# Setup
- install zephyr sdk and project
- west init
- run build.bat with one of the supported boards, eg build.bat rpi_pico

# Running the Tests
- add ZEPHYR_SDK to your environment variables for your user, this is the path to the bin dir that contains the zephyr gdb for arm
- install qemu, add bin dir to path
- use the Debug Tests launch configuration

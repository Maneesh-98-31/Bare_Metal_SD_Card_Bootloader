# Bare Metal SD Card Bootloader

A minimal bootloader implementation for ARM-based microcontrollers that initializes hardware peripherals and loads executable code from an SD card. Designed for bare-metal environments without an operating system.

## 🧠 Overview

This project demonstrates:
- Low-level hardware initialization (GPIO, RCC, SPI, UART)
- SD card interfacing via SPI
- Bootloading mechanism from SD card
- Vector table setup and interrupt handling
- Security abstraction for boot integrity

## 📁 Project Structure

| Folder/File         | Description |
|---------------------|-------------|
| `main.c`            | Entry point for bootloader logic |
| `vector_table.c/h`  | Interrupt vector setup |
| `security.c/h`      | Security checks and boot validation |
| `spi.c/h`           | SPI driver for SD card communication |
| `sd.c/h`            | SD card protocol implementation |
| `gpio.h`            | GPIO configuration macros |
| `rcc`               | Clock configuration (RCC) |
| `uart`              | UART driver (optional for debugging) |
| `linker.ld`         | Linker script for memory layout |
| `makefile`          | Build instructions |
| `.idea`, `.vscode`  | IDE configurations |
| `.gitignore`        | Git ignore rules |

## ⚙️ Features

- SPI-based SD card initialization and block reading
- Boot image validation via `security.c`
- Custom vector table setup
- Minimal footprint for embedded systems
- Configurable SPI clock speeds

## 🧰 Hardware Used

This bootloader was developed and tested on:

- **Microcontroller**: STM32F407G (ARM Cortex-M4)
- **Board**: STM32F4 Discovery or compatible development board
- **Storage**: MicroSD card connected via SPI
- **Debugging**: UART (optional) for serial output
- **Power**: USB or external 3.3V supply

### Pin Configuration (Example)

| Peripheral | STM32F407G Pin | Description |
|------------|----------------|-------------|
| SPI MOSI   | PB5            | SD card data input |
| SPI MISO   | PB4            | SD card data output |
| SPI SCK    | PB3            | Clock signal |
| SPI CS     | PA15           | Chip select |
| UART TX    | PA9            | Serial output (optional) |
| UART RX    | PA10           | Serial input (optional) |

## 🚀 Getting Started

### Prerequisites

- ARM toolchain (e.g., `arm-none-eabi-gcc`)
- QEMU or real ARM hardware
- Make utility

### Build Instructions

```bash
make 
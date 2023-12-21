 Here is a README file to explain the code, how to run it, and expected results:

# Micro:bit Encrypted Wireless Communication

This project implements encrypted and authenticated wireless communication between two BBC micro:bit devices.

## Overview

- One micro:bit acts as a **sender** to send encrypted commands
- The other micro:bit acts as a **receiver** to decrypt and execute commands
- AES-128 encryption is used to encrypt commands
- A pre-shared **secret code** provides authentication
- A random **salt** is used to generate a unique encryption key per message 

## Usage

To use this system:

1. Flash `sender.cpp` onto one micro:bit 
2. Flash `receiver.cpp` onto another micro:bit
3. Power on both devices. They should pair automatically over radio.
4. Press buttons on the **sender** to pick a command to send.
5. The **receiver** will decrypt, authenticate and execute the command.

## Supported Commands

The following commands are implemented:

- `LED_ON` - Turn receiver's LED display on
- `LED_OFF` - Turn receiver's LED display off 
- `DISPLAY_MESSAGE` - Scroll a text message on receiver's display

## Implementation

The key steps are:

1. Sender generates random 16 byte salt 
2. Sender generates 16 byte data encryption key (dpk) from salt and pre-shared secret code using SHA256 and MD5 
3. Command chosen by sender is encrypted with AES using the dpk
4. Encrypted command and salt are sent over radio
5. Receiver generates identical dpk from received salt and secret 
6. Decrypts command using dpk
7. Executes command if secret code authentication succeeds

See the source code for detailed documentation and implementation.

## Testing

- Flash `sender.cpp` and `receiver.cpp` onto two micro:bits
- Power on both devices 
- Press Button A on sender to turn receiver LED on  
- Press Button B on sender to turn receiver LED off
- Press Buttons A+B on sender to scroll a text message on receiver's display


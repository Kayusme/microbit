#include <MicroBit.h> // Base Micro:bit library
#include <MicroBitCrypto.h> // Provides SHA256 and MD5 functions
#include <aes.h> // AES encryption/decryption library
#include <radio.h> // For nRF radio communication
#include <Button.h> // to read button press for input

// Shared secret code used for authentication
#define SECRET_CODE "MySecretCode123"


// Commands to send over radio
enum Commands {
  LED_ON,
  LED_OFF,
  DISPLAY_MESSAGE  
};


// Generates 16 byte dpk from secret and salt
uint8_t generate_dpk(uint8_t salt[16]) {
  // Implements SHA256 + MD5 as sender 
}

// Execute received command 
void run_command(uint8_t command) {
  switch(command) {
    case LED_ON:
      uBit.led.on();
      break;
    case LED_OFF:
     uBit.led.off();
     break;
    case DISPLAY_MESSAGE:
     // display message
     break;
  }
}

int main() {

  // Receive encrypted command and salt   
  uint8_t cipher[16];
  uint8_t salt[16];
  
  uBit.radio.receive(cipher, 16);
  uBit.radio.receive(salt, 16);

  // Generate dpk from salt and secret
  uint8_t dpk[16] = generate_dpk(salt);
  
  // Decrypt command
  uint8_t command;
  aes_dec(cipher, dpk, &command);

  // Execute command
  run_command(command);

}
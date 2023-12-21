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

// Define your user input function here (e.g., button presses, serial input)
uint8_t user_input() {
  if (buttonA.isPressed()) {
    return LED_ON;
  } else if (buttonB.isPressed()) {
    return LED_OFF;
  } else if (buttonB.isPressed() && buttonA.isPressed()) {
    return DISPLAY_MESSAGE;
  }
  // Add other button-to-command logic here
  return NO_COMMAND; // Default value if no button is pressed
}


// Generates 16 byte dpk from secret code and salt 
uint8_t generate_dpk(uint8_t salt[16]) {
  uint8_t dpk[32];
  uint8_t secret[32];
  uint8_t secret_half1[16];
  
  // SHA256 hash of secret code  
  sha256(SECRET_CODE, strlen(SECRET_CODE), secret); 
  memcpy(secret_half1, secret, 16);
  
  // Append MD5 hash of salt
  md5(salt, 16, salt);
  memcpy(dpk, SECRET_CODE, 16 + sizeof(salt));



  // Hash salt to 128 bits 
  sha128(salt, 16, salt);

  // Combine secret half and hashed salt into dpk
  memcpy(dpk, secret_half1, 16);
  memcpy(dpk + 16, salt, 16);


  
  return dpk;
}

int main() {

  // Generate random salt
  uint8_t salt = uBit.random(255);
   
  // Command chosen by user 
  uint8_t command = user_input(); // chosen by user
  
  // Generate data encryption key
  uint8_t dpk[32] = generate_dpk(salt);

  // Encrypt command 
  uint8_t cipher[32];
  aes_enc(&command, dpk, cipher);

  // Send encrypted command and salt 
  uBit.radio.datagram.send(cipher, salt);
  //uBit.radio.send(cipher, 16);
  //uBit.radio.send(salt, 16);

}

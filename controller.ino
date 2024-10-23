// CAN Transmitter Code (Sparkfun Pro Micro 5v/16MHz): //
// CAN document is in HEX, Code uses DEC. Must convert.
// --------------------------------------------------- //

// Library for using SPI Communication
#include <SPI.h>

// Library for using CAN Communication
// Library source: https://github.com/autowp/arduino-mcp2515
#include <mcp2515.h>

// HID-Projects includes media key (also called consumer keys) functions
// Library source: https://github.com/NicoHood/HID
#include <HID-Project.h>
#include <HID-Settings.h>

#define HID_CUSTOM_LAYOUT;
#define LAYOUT_US_ENGLISH;

// Library for a timer to keep the module alive
// Library source: https://github.com/natnqweb/Simpletimer
#include <Simpletimer.h>

struct can_frame canMsg;

// Chip select Pin?
MCP2515 mcp2515(17); // CS pin on MCP2515

// CAN message bits
int bit0 = 0;
int bit1 = 0;
int bit2 = 0;
int bit3 = 0;
int bit4 = 0;
int bit5 = 0;
int bit6 = 0;
int bit7 = 0;

// Display button panel values
const int PWR = A0;
const int SOURCE = 8;
const int UP = 10;
const int DOWN = 9;
const int MENU = 5;
const int STATUS = 13;

// If OPMODE is 0, button panel operates in navigation mode
// If OPMODE is 1, button panel operates in media mode
int OPMODE = 0;

// Create the global timer object
Simpletimer timerPulse{};





void setup() {

  // Begins SPI communication
  SPI.begin();
  Serial.begin(115200);

  mcp2515.reset();

  pinMode(PWR, OUTPUT);
  pinMode(SOURCE, OUTPUT);
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);
  pinMode(MENU, OUTPUT);
  pinMode(STATUS, OUTPUT);

  digitalWrite(PWR, LOW);
  digitalWrite(SOURCE, LOW);
  digitalWrite(UP, LOW);
  digitalWrite(DOWN, LOW);
  digitalWrite(MENU, LOW);
  digitalWrite(STATUS, LOW);

  //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  canMsg.can_id = 0x5dd;
  canMsg.can_dlc = 8;
  canMsg.data[0] = 93;
  canMsg.data[1] = 0;
  canMsg.data[2] = 255;
  canMsg.data[3] = 255;
  canMsg.data[4] = 255;
  canMsg.data[5] = 255;
  canMsg.data[6] = 255;
  canMsg.data[7] = 255;

  // Necessary to establish media key comm function
  Keyboard.begin();

  // Keeps Ford Button panel awake
  timerPulse.register_callback(keepAlive);
}





void loop() {

  mcp2515.readMessage( & canMsg);

  // Set the duration of the timer (in ms)
  timerPulse.run(500);


  // Places captured packet data in variables
  if (canMsg.can_id == 0x2a0) {

    bit6 = canMsg.data[6]; // Volume knob events
    bit0 = canMsg.data[0]; // All the other buttons events



    // Eject button
    if ((canMsg.data[0]) == 52) {

        // Set media mode
        if (OPMODE == 0) {
            OPMODE = 1;
            delay(20);
        }

            // Set navigation mode
        else if (OPMODE == 1) {
            OPMODE = 0;
            delay(20);
        }
    }



    // Rotary knob right
    else if ((canMsg.data[6]) == 31) {

        // Navigate up
        if (OPMODE == 0) {
            Keyboard.write("down");
            delay(20);
        }

        // Volume up
        else if (OPMODE == 1) {
            Keyboard.write("+");
            delay(20);
        }
    }

    // Rotary knob left
    else if ((canMsg.data[6]) == 29) {

        // Navigate down
        if (OPMODE == 0) {
            Keyboard.write("up");
            delay(20);
        }

        // Volume down
        else if (OPMODE == 1) {
            Keyboard.write("-");
            delay(20);
        }
    }



    // Rotary knob center button
    else if (bit0 == 31) {

        // Navigation select item
        if (OPMODE == 0) {
            Keyboard.write("enter");
            delay(20);
        }

        // Media play/pause
        else if (OPMODE == 1) {
            Keyboard.write("space");
            delay(20);
        }

        while (bit0 != 255) {
            delay(100);
            mcp2515.readMessage( & canMsg);
            if (canMsg.can_id == 0x2a0) {
            bit0 = canMsg.data[0];
            }
        }

        delay(10);
    }



    // Forward button
    else if (bit0 == 51) {

        // Navigation next view
        if (OPMODE == 0) {
            Keyboard.write("tab");
            delay(20);
        }

        // Media next track
        else if (OPMODE == 1) {
            Keyboard.write(">");
            delay(20);
        }

      while (bit0 != 255) {
        delay(100);
        mcp2515.readMessage( & canMsg);
        if (canMsg.can_id == 0x2a0) {
          bit0 = canMsg.data[0];
        }
      }

      delay(10);
    }

    // Previous button
    else if (bit0 == 50) {

        // Navigation previous view
        if (OPMODE == 0) {
            Keyboard.write("tab");
            delay(20);
        }

        // Media previous track
        else if (OPMODE == 1) {
            Keyboard.write("<");
            delay(20);
        }

      while (bit0 != 255) {
        delay(100);
        mcp2515.readMessage( & canMsg);
        if (canMsg.can_id == 0x2a0) {
          bit0 = canMsg.data[0];
        }
      }

      delay(10);

    }



    // Tune+ button
    else if (bit0 == 74) {

        // Navigation move cursor right (no effect)
        if (OPMODE == 0) {
            Keyboard.write("right");
            delay(20);
        }

        // Media seek track forward
        else if (OPMODE == 1) {
            Keyboard.write("]");
            delay(20);
        }

      while (bit0 != 255) {
        delay(100);
        mcp2515.readMessage( & canMsg);
        if (canMsg.can_id == 0x2a0) {
          bit0 = canMsg.data[0];
        }
      }

      delay(10);
    }

    // Tune- button
    else if (bit0 == 75) {

        // Navigation move cursor left (no effect)
        if (OPMODE == 0) {
            Keyboard.write("left");
            delay(20);
        }

        // Media seek track backwards
        else if (OPMODE == 1) {
            Keyboard.write("[");
            delay(20);
        }

      while (bit0 != 255) {
        delay(100);
        mcp2515.readMessage( & canMsg);
        if (canMsg.can_id == 0x2a0) {
          bit0 = canMsg.data[0];
        }
      }
      
      delay(10);
    }



    // Sound button event
    else if (bit0 == 24) {

        // Media random track
        else if (OPMODE == 0) {
            Keyboard.write("s");
            delay(20);
        }

        // Navigation random track
        else if (OPMODE == 1) {
            Keyboard.write("s");
            delay(20);
        }

        while (bit0 != 255) {
            delay(100);
            mcp2515.readMessage( & canMsg);
            if (canMsg.can_id == 0x2a0) {
            bit0 = canMsg.data[0];
            }
        }

        delay(10);
    }



    // Power off display
    else if (bit0 == 80) { // DISP Button
      digitalWrite(PWR, HIGH);
      delay(100);
      digitalWrite(PWR, LOW);
      while (bit0 != 255) {
        delay(100);
        mcp2515.readMessage( & canMsg);
        if (canMsg.can_id == 0x2a0) {
          bit0 = canMsg.data[0];
        }
      }
    }

    // Change input source
    else if (bit0 == 79) { // SOURCE Button
      digitalWrite(SOURCE, HIGH);
      delay(100);
      digitalWrite(SOURCE, LOW);
      while (bit0 != 255) {
        delay(100);
        mcp2515.readMessage( & canMsg);
        if (canMsg.can_id == 0x2a0) {
          bit0 = canMsg.data[0];
        }
      }
    }

  } // End parent if block

} // End loop





void keepAlive() {

  Serial.println("Pulse");
  digitalWrite(STATUS, HIGH);
  delay(100);
  digitalWrite(STATUS, LOW);
  canMsg.can_id = 0x5dd;
  canMsg.can_dlc = 8;
  canMsg.data[0] = 93;
  canMsg.data[1] = 0;
  canMsg.data[2] = 255;
  canMsg.data[3] = 255;
  canMsg.data[4] = 255;
  canMsg.data[5] = 255;
  canMsg.data[6] = 255;
  canMsg.data[7] = 255;

  mcp2515.sendMessage( & canMsg);

  bit0 = 0;
  bit1 = 0;
  bit2 = 0;
  bit3 = 0;
  bit4 = 0;
  bit5 = 0;
  bit6 = 0;
  bit7 = 0;

}

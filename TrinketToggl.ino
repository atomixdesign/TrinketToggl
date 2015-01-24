// see tutorial at http://learn.adafruit.com/trinket-usb-volume-knob

#include "TrinketHidCombo.h"
#include <Adafruit_NeoPixel.h>

#define PIN_BUTTON 2
#define NEOPIN 0 // NEOPIXEL on this PIN

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1



int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup()
{

  activatePixel();
  pinMode(PIN_BUTTON, INPUT);

  // setting input pins to high means turning on internal pull-up resistors
  digitalWrite(PIN_BUTTON, HIGH);
  // remember, the buttons are active-high, they read HIGH when they are not pressed

  TrinketHidCombo.begin(); // start the USB device engine and enumerate
}

void activatePixel() {
  // Parameter 1 = number of pixels in strip
  // Parameter 2 = Arduino pin number (most are valid)
  // Parameter 3 = pixel type flags, add together as needed:
  //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
  //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
  //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
  //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_RGB + NEO_KHZ800);
  pixels.begin();
  pixels.setBrightness(255); // set brightness
  pixels.setPixelColor(0,pixels.Color(255,255,255));
  pixels.show(); // Initialize all pixels
}

void loop()
{
  // the poll function must be called at least once every 10 ms
  // or cause a keystroke
  // if it is not, then the computer may think that the device
  // has stopped working, and give errors
  TrinketHidCombo.poll(); // check if USB needs anything done

  // read the state of the switch into a local variable:
  int reading = digitalRead(PIN_BUTTON);


  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        // White
       // pixels.setPixelColor(0,pixels.Color(255,255,255));

        //TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_UP);
        //TrinketHidCombo.typeChar(KEYCODE_F);
        TrinketHidCombo.pressKey(KEYCODE_MOD_RIGHT_CONTROL,KEYCODE_F8); // Send Ctrl+F8

        // // This releases the modifier keys!
        TrinketHidCombo.pressKey(0, 0);
      }
      else {
        // Black
        //pixels.setPixelColor(0,pixels.Color(0,0,0));
      }
      //pixels.show();

    }
  }


  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;

}

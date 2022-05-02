
//**********************************************
//******FUENTE ARDUINO MEGA ********************
//******Controlador de pantalla led 32x64*******
//**********************************************
//Lee desde Serial1 los datos enviados por shield USB
//que conecta teclado normal
//Luego envía lo tecleado a pantall para visualizarlo
//****Pablo Fierro 01 mayo 2022*****************


// RGB Panel GFX Demo example for 16x32 panel
// By Marc MERLIN <marc_soft@merlins.org>
// Contains code (c) Adafruit, license BSD

// WILL NOT FIT on ARDUINO UNO -- requires a Mega, M0 or M4 board

// Convert image to c file here http://www.rinkydinkelectronics.com/t_imageconverter565.php

#include <RGBmatrixPanel.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

//#define CLK  8 // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
#define CLK 11   // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3


// Enable double buffering
RGBmatrixPanel *matrix = new RGBmatrixPanel(A, B, C, D, CLK, LAT, OE, true, 64);

// Panel Matrix doesn't fully work like Neomatrix (which I originally
// wrote this demo for), so map a few calls to be compatible. The rest
// comes from Adafruit_GFX and works the same on both backends.
#define setBrightness(x) fillScreen(0) // no-op, no brightness on this board
#define clear()          fillScreen(0)
#define show()           swapBuffers(true)



int x=0;
int y=0;
int ciclos = 0;

void loop() {
  if(Serial1.available() > 0 ){
      if(x>=60){
        y=y+8;
        x=0;
        if(y>24){
          y=0;x=0;
          matrix->clear();
        }
      }
      
      char Dato = Serial1.read();
      Serial.print(x);
      Serial.print(":");
      Serial.print(y);
      Serial.print(">");
      Serial.println(Dato);
      ciclos++;
      delay(100);
      matrix->setCursor(x, y); 
      x=x+6;
      
      
      matrix->print(Dato);
      matrix->show();
  }
}




void setup() { 
    Serial.begin( 9600 );
    Serial1.begin( 9600 );
    Serial.println( "S" );
    matrix->begin();
    matrix->clear(); //Set image to black
    
    // matrix.begin();
    // matrix.setTextWrap(false); // Allow text to run off right edge
    // matrix.setTextSize(2);
    // matrix.drawPixel(x, y, matrix.Color333(r, g, b));
    //What pins does USB Host Shield use?
    //This is on digital pins 10, 11, 12, and 13 on the Uno 
    //and pins 10, 50, 51, and 52 on the Mega. 
    
    //On both boards, pin 10 is used to select the MAX3421E. 
    //Pins 7, 8 and 9 are used for GPX, INT and RES pins.
    
    //GPIO5 : SS, GPIO17 : INT, GPIO18 : SCK, GPIO19 : MISO, GPIO23 : MOSI
    //while for the RST i connected it to EN pin of the DOIT ESP32 Dev Kit V1.
    //for the power, 5V is supplied only to the VBUS (the MAX3421E is supplied by 3.3V)

    matrix->setCursor(0, 0);
    
    matrix->setTextColor(matrix->ColorHSV(255, 255, 255, true));
   
    matrix->print("Titi escribe");
    matrix->show();
    delay(4000);
}

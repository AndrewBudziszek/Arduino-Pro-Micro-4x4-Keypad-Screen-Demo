#include <Keypad.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {4, 5, 6, 7}; 
byte colPins[COLS] = {8, 9, 10, 16}; 

String currentMessage = "Hello";

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(4);           
  display.setTextColor(SSD1306_WHITE);      
  display.setCursor(0,0); 
  display.print(currentMessage);
  display.display();
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey == '*'){
    currentMessage = "";
    displayMessage();
  } else if(customKey != NO_KEY && currentMessage.length() < 6) {
    currentMessage = String(currentMessage + customKey);
    displayMessage();
  }

  Serial.println(currentMessage);
}

void displayMessage() {
  display.clearDisplay();
  display.setTextSize(4);
  display.setCursor(0,0);
  display.print(currentMessage);
  display.display();
}

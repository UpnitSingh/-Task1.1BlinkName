#include <Arduino.h>

int ledPin = 13;
int buttonPin = 2;
char* UPNIT_morse = "..- .--. -. .. -";

int CurrentMorseIndex = 0;

// time
int dot_time = 450;
int dash_time = 1700;
int pause_between = 250;
int letter_pause = 750;

bool isMorseRunning = false;
bool isMorseFinished = true;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(ledPin, LOW);

 
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
}

void loop() {
  
  if (digitalRead(buttonPin) == LOW && isMorseFinished) {
    delay(50);  // Debounce
    if (digitalRead(buttonPin) == LOW) {
      isMorseRunning = true;
      isMorseFinished = false;
      CurrentMorseIndex = 0;
      Serial.println("Starting Morse code for UPNIT...");
      while (digitalRead(buttonPin) == LOW) {}  
    }
  }

  if (isMorseRunning) {
    do_morse_blink();
  } else {
    digitalWrite(ledPin, LOW); 
  }
}

void do_morse_blink() {
  char c = UPNIT_morse[CurrentMorseIndex];

  if (c == '.') {
    digitalWrite(ledPin, HIGH);
    Serial.print("."); 
    delay(dot_time);
    digitalWrite(ledPin, LOW);
    delay(pause_between);
  } else if (c == '-') {
    digitalWrite(ledPin, HIGH);
    Serial.print("-");  
    delay(dash_time);
    digitalWrite(ledPin, LOW);
    delay(pause_between);
  } else if (c == ' ') {
    Serial.print(" "); 
    delay(letter_pause);
  } else if (c == '\0') {
    Serial.println(); 
    Serial.println("Morse code for UPNIT completed.");
    isMorseRunning = false;  
    isMorseFinished = true;  
    return; 
  }

  CurrentMorseIndex++;
}

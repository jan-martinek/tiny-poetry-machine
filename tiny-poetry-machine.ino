const int buttonPin = 4;
const int ledPin = 3;

void setup() {
  // wait for the mp3 module to initialize for sure
  delay(500);

  // module starts playing automatically
  // pause playback
  pause();

  // reset volume level by going to zero
  // and one step up
  volumeDown();
  volumeDown();
  volumeDown();
  volumeUp();

  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT); 
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  
  if (buttonState == LOW) {
    
    // turn on the led to signal
    // that you may press the button
    digitalWrite(ledPin, HIGH);
    
  } else {

    // turn off the led
    digitalWrite(ledPin, LOW);

    // play 30 seconds from the selected song
    play();
    delay(30*1000);

    // pause playback
    pause();

    // skip several songs
    skipRandom();
    
  }

  delay(10);
}

// 4 mp3 module's buttons are controlled 
// via 3 pins connected to 4 optocouplers
void pressButton(int pin1, int pin2, bool longPress) {

  // light on the selected optocoupler
  pinMode(pin1, OUTPUT);
  digitalWrite(pin1, HIGH);
  pinMode(pin2, OUTPUT);
  digitalWrite(pin2, LOW);

  // maintain press
  if (longPress == true) {
    delay(2500);
  } else {
    delay(300);  
  }

  // reset both pins back to input
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);

  // wait between button presses
  delay(100);
}

void play() {
  pressButton(1, 0, false); 
}

// without any reliable knowledge of the mp3 module's state
// pause is just an alias to use when the intent is pausing
void pause() {
  play();
}

void playNext() {
  pressButton(1, 2, false);
}

void playPrev() {
  pressButton(2, 1, false);
}

void volumeUp() {
  pressButton(1, 2, true);
}

void volumeDown() {
  pressButton(2, 1, true);
}

void skipRandom() {
  int skipSteps = random(0, 5);

  // skip several songs (0-5)
  for(int i = 0; i < skipSteps; i++) {
    playNext();
  }

  // playNext() will cause playback to start
  // hence a pause() call is required
  // after a brief pause to allow the song
  // to start
  delay(1000);
  pause();
}


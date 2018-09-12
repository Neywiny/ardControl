char mode = 0;

char speakerPin = 3;
char notes[] = "cdefgabC "; // a space represents a rest
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
    delay(50);
  }
}

void setup() {
  for(char i = 12; i >= 5; i--){
    pinMode(i, OUTPUT);
    pinMode(speakerPin, OUTPUT);
  }
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  switch(mode){
    case 0:
    // no led's
    for(char i = 12; i >= 5; i--){
      digitalWrite(i, LOW);
    }
    break;
    case 1:
    // all led's
    for(char i = 12; i >= 5; i--){
      digitalWrite(i, HIGH);
    }
    break;
    case 2:
    // blink fast
    for(char i = 12; i >= 5; i--){
      digitalWrite(i, HIGH);
    }
    delay(100);
    for(char i = 12; i >= 5; i--){
      digitalWrite(i, LOW);
    }
    delay(100);
    break;
    case 3:
    //blink slow
    for(char i = 12; i >= 5; i--){
      digitalWrite(i, HIGH);
    }
    delay(1000);
    for(char i = 12; i >= 5; i--){
      digitalWrite(i, LOW);
    }
    delay(1000);
    break;
    case 4:
    // all on -> all off
    for(char i = 12; i >= 5; i--){
      digitalWrite(i, HIGH);
    }
    delay(300);
    for(char i = 12; i >= 5; i--){
      digitalWrite(i, LOW);
    }
    delay(300);
    mode = 0;
    break;
    case 5:
    // ripple 3
    for(char i = 12; i >= 7; i--){
      digitalWrite(i, HIGH);
      digitalWrite(i-1, HIGH);
      digitalWrite(i-2, HIGH);
      delay(100);
      digitalWrite(i, LOW);
      digitalWrite(i-1, LOW);
      digitalWrite(i-2, LOW);
    }
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    digitalWrite(12, LOW);
    
    digitalWrite(5, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    break;
    case 6:
    // ripple 2
    for(char i = 12; i >= 6; i--){
      digitalWrite(i, HIGH);
      digitalWrite(i-1, HIGH);
      delay(100);
      digitalWrite(i, LOW);
      digitalWrite(i-1, LOW);
    }
    digitalWrite(4, HIGH);
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(4, LOW);
    digitalWrite(12, LOW);
    break;
    case 7:
    // riple 1
    for(char i = 12; i >= 5; i--){
      digitalWrite(i, HIGH);
      delay(150);
      digitalWrite(i, LOW);
    }
    break;
    case 8 ... 15:
    // 8-15 piezo tones
    if(mode <= 15){
      playNote(notes[mode-8],100);
    }
    else{
      mode = 0;
    }
    break;
    default:
      mode = 7;
  }
  while (Serial.available() > 0) {
    mode = (char)Serial.parseInt();
  }
  if(!digitalRead(2)){
    mode = 0;
    Serial.println("ack");
    for(int i = 3; i >= 0; i--){ 
      playNote(notes[i],50);
    }
    delay(100);
  }
}


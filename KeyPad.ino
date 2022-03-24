#include <Keypad.h>
#define Password_Length 5   // Length of password + 1 for null character

// binary input pins for triggering sound board. This version of the script is for the sound board in "Intergrated Mode 0"
// Dip switches on sound board should be set to (0,0,0)
#define s1 A0 
#define s2 A1
#define s3 A2
#define s4 A3


class Sound_Trigger{
  private:
    byte Pin_1; 
    byte Pin_2;
    byte Pin_3;
    byte Pin_4;
   
  public:
    Sound_Trigger(byte Pin_1,byte Pin_2,byte Pin_3,byte Pin_4){
      this->Pin_1 = Pin_1;
      this->Pin_2 = Pin_2;
      this->Pin_3 = Pin_3;
      this->Pin_4 = Pin_4;
      initialize();}
  void initialize(){
    pinMode (Pin_1,OUTPUT);
    digitalWrite(Pin_1,HIGH);
    pinMode (Pin_2,OUTPUT);
    digitalWrite(Pin_2,HIGH);
    pinMode (Pin_3,OUTPUT);
    digitalWrite(Pin_3,HIGH);
    pinMode (Pin_4,OUTPUT);
    digitalWrite(Pin_4,HIGH);}
  
  void Play_Sound(byte Track_num, int Duration){   
   if(Track_num==1){
      digitalWrite(Pin_1,LOW);
        delay(Duration);
      digitalWrite(Pin_1,HIGH);}
    else if(Track_num==2){
      digitalWrite(Pin_2,LOW);
        delay(Duration);
      digitalWrite(Pin_2,HIGH);}
    else if(Track_num==3){
      digitalWrite(Pin_1,LOW);
      digitalWrite(Pin_2,LOW);
        delay(Duration);
      digitalWrite(Pin_1,HIGH);
      digitalWrite(Pin_2,HIGH);}
    else if(Track_num==4){
      digitalWrite(Pin_3,LOW);
        delay(Duration);
      digitalWrite(Pin_3,HIGH);}
    else if(Track_num==5){
      digitalWrite(Pin_1,LOW);
      digitalWrite(Pin_3,LOW);
        delay(Duration);
      digitalWrite(Pin_1,HIGH);
      digitalWrite(Pin_3,HIGH);}
    else if(Track_num==6){
      digitalWrite(Pin_2,LOW);
      digitalWrite(Pin_3,LOW);
        delay(Duration);
      digitalWrite(Pin_2,HIGH);
      digitalWrite(Pin_3,HIGH);}    
    else if(Track_num==7){   
      digitalWrite(Pin_1,LOW);
      digitalWrite(Pin_2,LOW);
      digitalWrite(Pin_3,LOW);
        delay(Duration);
      digitalWrite(Pin_1,HIGH);
      digitalWrite(Pin_2,HIGH);
      digitalWrite(Pin_3,HIGH);} 
    else if(Track_num==8){
      digitalWrite(Pin_4,LOW);
        delay(Duration);
      digitalWrite(Pin_4,HIGH);}   
    else if(Track_num==9){
      digitalWrite(Pin_1,LOW);
      digitalWrite(Pin_4,LOW);
        delay(Duration);
      digitalWrite(Pin_1,HIGH);
      digitalWrite(Pin_4,HIGH);} 
    else if(Track_num==10){
      digitalWrite(Pin_2,LOW);
      digitalWrite(Pin_4,LOW);
        delay(Duration);
      digitalWrite(Pin_2,HIGH);
      digitalWrite(Pin_4,HIGH);} 
    else if(Track_num==11){   
      digitalWrite(Pin_1,LOW);
      digitalWrite(Pin_2,LOW);
      digitalWrite(Pin_4,LOW);
        delay(Duration);
      digitalWrite(Pin_1,HIGH);
      digitalWrite(Pin_2,HIGH);
      digitalWrite(Pin_4,HIGH);} 
    else if(Track_num==12){
      digitalWrite(Pin_3,LOW);
      digitalWrite(Pin_4,LOW);
        delay(Duration);
      digitalWrite(Pin_3,HIGH);
      digitalWrite(Pin_4,HIGH);}}   };   
      
Sound_Trigger Sound_byte (s1,s2,s3,s4);
byte ahahah = 1;
byte failed = 2;
byte come_back = 3;

byte beep = 4;

byte chain_unlock = 5;
byte light_transition = 6;
byte choir = 7;
byte notify =8;
byte welcome = 9;

int ahahah_len = 1000;
int failed_len = 1000;
int come_back_len = 2000;

int beep_len = 500;

int chain_unlock_len = 3000;
int light_transition_len = 4000;
int choir_len = 2000;
int notify_len =3000;
int welcome_len = 2000;

byte attempt_limit = 6;
int lock_out = 10000;
char Data[Password_Length]; // Character to hold password input
char Master[Password_Length] = "5973"; // Password
int lockOutput = 10; // Pin connected to lock relay input
int StayOpen = 5000; // Time in Mills lock stays open after correct password is input
byte data_count = 0; // Counter for character entries
char customKey; // Character to hold key input
int Wrong_count = 0; // Count for playing different failure noises

// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;

// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'} };

// Keypad Connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); // Create keypad object

void setup() {
  Serial.begin(9600);
  // Set lockOutput as an OUTPUT pin
  pinMode(lockOutput, OUTPUT);
  digitalWrite(lockOutput, LOW);}

void loop() {
  
  // Look for keypress
  customKey = customKeypad.getKey();
  
  if (customKey) {
    // Enter keypress into array and increment counter
    Sound_byte.Play_Sound(beep,beep_len);
    Data[data_count] = customKey;
    Serial.print(Data[data_count]);
    data_count++;}

  // See if we have reached the password length
  if (data_count == Password_Length - 1) {
    Serial.println(" ");
    Serial.println("....");
    
    if (!strcmp(Data, Master)) {
      // Password is correct
      Serial.println("CORRECT");
      Serial.println("_______");
      // Turn on relay for 5 seconds
      digitalWrite(lockOutput, HIGH);
      Sound_byte.Play_Sound(random(5,8),3000);
      Sound_byte.Play_Sound(welcome,welcome_len);
      delay(StayOpen);
      digitalWrite(lockOutput, LOW);
      Wrong_count = 0;}
      
    else {
      // Password is incorrect
      if (Wrong_count == attempt_limit){
      Wrong_count = 0;
      Sound_byte.Play_Sound(failed,failed_len);
      Sound_byte.Play_Sound(come_back,come_back_len);
      delay(lock_out);}
      
      Sound_byte.Play_Sound(ahahah,ahahah_len);
      Wrong_count++;
      Serial.println("Wrong");
      Serial.println("_____");
      delay(1000);}
     
    clearData(); } }

void clearData() {
  // Go through array and clear data
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}

#include <Keypad.h> 

int greenLed = 13;                               //Green led
int Sol = 11;                                    //Lock Relay
int buzzer = 12;                                 //Buzzer

const byte rows = 4;    //rows
const byte columns = 4; //columns
char correctPassword[4] = {'1', '3', '7', '9'}; //Correct password
char enteredPassword[4];                        //Entered password on keypad
char charKey;                                   //Key on keypad 
int i = 0;                                      //Counter
char keypad[4][4] =                             //Keypad array
{ 
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowsPins[4] = {9, 8, 7, 6};           //Rows pins 
byte columnspPins[4] = {5, 4, 3, 2};         //Columns pins 

Keypad kpad = Keypad(makeKeymap(keypad), 
rowsPins, columnspPins, 4, 4);                 //Keypad map

void setup() 
{
  pinMode(greenLed, OUTPUT);  
  pinMode(buzzer, OUTPUT);
  pinMode(Sol, OUTPUT);
  digitalWrite(Sol, HIGH);
  
  Serial.begin(9600);    
  Serial.println("Keypad Door Lock\n");
  Serial.println("Please Enter Password\n");  
}

void loop() 
{
  digitalWrite(greenLed,LOW);
  charKey = kpad.getKey();  

  if(charKey)  
  {
    enteredPassword[i++] = charKey;  
    
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
  }

  if (i == 4)
  { 
    delay(200);
 
    if ((strncmp(enteredPassword, correctPassword, 4) == 0))
    {
      Serial.println("\nAcess Granted\n");
      digitalWrite(greenLed, HIGH);
      digitalWrite(buzzer, HIGH);
      digitalWrite(Sol, LOW);
      delay(1000);
      digitalWrite(buzzer, LOW);
      delay(2000);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(Sol, HIGH);
      digitalWrite(greenLed, LOW);
      digitalWrite(buzzer, LOW);
      delay(3000);
      i = 0;
    }

    else
    {
      Serial.println("\nAcess Denied\n");
      digitalWrite(greenLed, LOW);
      digitalWrite(buzzer, HIGH);
      delay(5000);
      digitalWrite(buzzer, LOW);
      delay(1000);
      i = 0;
    }
  }
}

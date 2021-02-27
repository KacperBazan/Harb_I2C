//This is the MASTER

#include <Wire.h>

//Data being sent/
int s1[] = {99, 2, 9, 13};        //99 is the buffer byte
char s2[] = {'x', 'a', 'b', 'c'}; //'x' is the buffer byte

//Data being received.
char rec1[3];
char rec2[3];

void setup()
{

  Serial.begin(9600);
  Serial.flush();

  //Master does not require declaration of name
  Wire.begin();
}

void loop()
{
  for (int i = 0; i < 4; i++)
  {
    //Send to slave named 8.
    Wire.beginTransmission(8);
    Wire.write(s1[i]);
    Wire.endTransmission();

    //Send to slave named 9.
    Wire.beginTransmission(9);
    Wire.write(s2[i]);
    Wire.endTransmission();
    delay(100);
  }

  //We only request three bytes. (8)
  Wire.requestFrom(8, 3);
  while (Wire.available())
  {
    //Recieved characters are saved into a
    //temporary variable called c.
    char c = Wire.read();

    //Checks if position in string is empty.
    //If it is, it inserts the character and breaks.
    for (int i = 0; i < 3; i++)
    {
      if (rec1[i] == '\0')
      {
        rec1[i] = c;
        break;
      }
    }
  }

  //We only request three bytes. (9)
  Wire.requestFrom(9, 3);
  while (Wire.available())
  {
    //Recieved characters are saved into a
    //temporary variable called c.
    char c = Wire.read();

    //Checks if position in string is empty.
    //If it is, it inserts the character and breaks.
    for (int i = 0; i < 3; i++)
    {
      if (rec2[i] == '\0')
      {
        rec2[i] = c;
        break;
      }
    }
  }
  delay(100);

  //Prints out values for both strings.
  Serial.print("Rec_1: ");
  Serial.print(rec1[0]);
  Serial.print(rec1[1]);
  Serial.println(rec1[2]);
  Serial.print("Rec_2: ");
  Serial.print(rec2[0]);
  Serial.print(rec2[1]);
  Serial.println(rec2[2]);
  Serial.println("-----------");

  //Resets the strings to empty.
  for (int i = 0; i < 3; i++)
  {
    rec1[i] = '\0';
    rec2[i] = '\0';
  }
}

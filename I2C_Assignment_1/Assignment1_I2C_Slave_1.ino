//This is the SLAVE 1

#include <Wire.h>

int x = 0;
int counter = 0;
bool v = false;
int rec1[3];

void setup()
{
  Serial.begin(9600);
  Serial.flush();

  //Define slave as number 8.
  Wire.begin(8);

  //Attach function to recieving of data.
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void requestEvent()
{
  Wire.write("xyz");
}

void receiveEvent(int bytes)
{
  x = Wire.read();

  //If the buffer byte is true, transmition of all bytes
  //was completed. Makes v = true to allow printing of data.
  if (x == 99)
  {
    v = true;
    //Resets the counter to 0 to correctly index new bytes.
    counter = 0;
  }
  else
  {
    //If not buffer byte, it must be data we care about.
    //Save data and increment the counter.
    rec1[counter] = x;
    counter++;
  }
}

void loop()
{
  if (v)
  {
    Serial.print("Rec_1: ");
    Serial.print(rec1[0]);
    Serial.print(", ");
    Serial.print(rec1[1]);
    Serial.print(", ");
    Serial.println(rec1[2]);
    Serial.println("-----------");
    v = false; //Reset v to false to only print once.
  }
}

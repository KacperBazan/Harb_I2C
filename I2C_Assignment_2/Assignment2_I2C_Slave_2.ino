//This is the SLAVE 2

#include <Wire.h>

int x2 = 0;
int counter = 0;
bool v = false;
int rec2[6];

void setup()
{
  Serial.begin(9600);
  Serial.flush();

  //Define slave as number 9.
  Wire.begin(9);

  //Attach function to recieving of data.
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void requestEvent()
{
  Wire.write("SLAVE2");
}

void receiveEvent(int bytes)
{
  x2 = Wire.read();

  //If the buffer byte is true, transmition of all bytes
  //was completed. Makes v = true to allow printing of data.
  if (x2 == 99)
  {
    v = true;
    counter = 0;
  }
  else
  {
    //If not buffer byte, it must be data we care about.
    //Save data and increment the counter.
    rec2[counter] = x2;
    counter++;
  }
}

void loop()
{
  if (v)
  {
    for (int i = 0; i < 6; i++)
    {
      Serial.print(String(rec2[i]) + " ");
    }
    Serial.println();
    v = false; //Reset v to false to only print once.
  }
}

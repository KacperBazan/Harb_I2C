//This is the SLAVE 3

#include <Wire.h>

int x3 = 0;
int counter = 0;
bool v = false;
int rec3[11];

void setup()
{
  Serial.begin(9600);
  Serial.flush();

  //Define slave as number 10.
  Wire.begin(10);

  //Attach function to recieving of data.
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void requestEvent()
{
  Wire.write("SLAVE3");
}

void receiveEvent(int bytes)
{
  x3 = Wire.read();

  //If the buffer byte is true, transmition of all bytes
  //was completed. Makes v = true to allow printing of data.
  if (x3 == 'x')
  {
    v = true;
    counter = 0;
  }
  else
  {
    //If not buffer byte, it must be data we care about.
    //Save data and increment the counter.
    rec3[counter] = x3;
    counter++;
  }
}

void loop()
{
  if (v)
  {
    for (int i = 0; i < 11; i++)
    {
      Serial.write(rec3[i]);
    }
    Serial.println();
    v = false; //Reset v to false to only print once.
  }
}

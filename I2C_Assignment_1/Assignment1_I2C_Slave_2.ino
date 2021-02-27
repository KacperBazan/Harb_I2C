//This is the SLAVE 2

#include <Wire.h>

int y = 0;
int counter = 0;
bool v = false;
int rec2[3];

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
  Wire.write("#:)");
}

void receiveEvent(int bytes)
{
  y = Wire.read();

  //If the buffer byte is true, transmition of all bytes
  //was completed. Makes v = true to allow printing of data.
  if (y == 'x')
  {
    v = true;
    //Resets the counter to 0 to correctly index new bytes.
    counter = 0;
  }
  else
  {
    //If not buffer byte, it must be data we care about.
    //Save data and increment the counter.
    rec2[counter] = y;
    counter++;
  }
}

void loop()
{
  if (v)
  {
    Serial.print("Rec_2: ");
    Serial.write(rec2[0]);
    Serial.print(", ");
    Serial.write(rec2[1]);
    Serial.print(", ");
    Serial.write(rec2[2]);
    Serial.println();
    Serial.println("-----------");
    v = false; //Reset v to false to only print once.
  }
}

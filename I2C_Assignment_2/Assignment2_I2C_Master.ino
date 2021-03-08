//This is the MASTER

#include <Wire.h>

int td = 25;

//Data being sent/
int s1[7] = {99, 0, 2, 4, 6, 8, 10};                                   //99 -> Buffer
int s2[7] = {99, 1, 3, 5, 7, 9, 11};                                   //99 -> Buffer
char s3[11] = {'x', 'S', 't', 'r', 'a', 'w', 'b', 'e', 'r', 'r', 'y'}; //'x' -> Buffer
int s4[7] = {99, 1, 2, 4, 8, 16, 32};                                  //99 -> Buffer

//Data being received.
char rec1[6], rec2[6], rec3[6], rec4[6];

void setup()
{
  Serial.begin(9600);
  Serial.flush();
  Wire.begin(); //Master does not require declaration of name
}

void RequestData(int numSlave, int numBytes, char saveData[])
{
  Wire.requestFrom(numSlave, numBytes);
  while (Wire.available())
  {
    char c = Wire.read();
    for (int i = 0; i < numBytes; i++)
    {
      if (saveData[i] == NULL)
      {
        saveData[i] = c;
        break;
      }
    }
  }

  PrintReceived(saveData, numBytes);
  delay(td);
}

void SendData_Int(int numSlave, int numBytes, int sendData[])
{
  Wire.beginTransmission(numSlave);
  for (int i = 0; i < numBytes; i++)
  {
    Wire.write(sendData[i]);
  }
  Wire.endTransmission();
  delay(td);
}

void SendData_Char(int numSlave, int numBytes, char sendData[])
{
  Wire.beginTransmission(numSlave);
  for (int i = 0; i < numBytes; i++)
  {
    Wire.write(sendData[i]);
  }
  Wire.endTransmission();
  delay(td);
}

void PrintReceived(char receiveData[], int len)
{
  for (int i = 0; i < len; i++)
  {
    Serial.write(receiveData[i]);
  }
  Serial.println();
}

void ClearData(char receiveData[], int len)
{
  for (int i = 0; i < len; i++)
  {
    receiveData[i] = NULL;
  }
}

void loop()
{

  SendData_Int(8, 7, s1);
  SendData_Int(9, 7, s2);
  SendData_Char(10, 11, s3);
  SendData_Int(11, 7, s4);

  RequestData(8, 6, rec1);
  RequestData(9, 6, rec2);
  RequestData(10, 6, rec3);
  RequestData(11, 6, rec4);

  ClearData(rec1, 6);
  ClearData(rec2, 6);
  ClearData(rec3, 6);
  ClearData(rec4, 6);
}

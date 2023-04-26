#include <SoftwareSerial.h>
// We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 2 is connected to the DataIn
 pin 4 is connected to the CLK
 pin 3 is connected to LOAD
 We have only a single MAX72XX.
 */
LedControl lc = LedControl(2, 4, 3, 1);

/* we always wait a bit between updates of the display */
unsigned long delaytime = 1000;

void setup()
{
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */

  Serial.begin(9600); // 启动串口通信
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix.
 (you need at least 5x7 leds to see the whole chars)
 */
void writeArduinoOnMatrix()
{
  /* here is the data for the characters */
  byte a[5] = {B01111110, B10001000, B10001000, B10001000, B01111110};
  byte r[5] = {B00111110, B00010000, B00100000, B00100000, B00010000};
  byte d[5] = {B00011100, B00100010, B00100010, B00010010, B11111110};
  byte u[5] = {B00111100, B00000010, B00000010, B00000100, B00111110};
  byte i[5] = {B00000000, B00100010, B10111110, B00000010, B00000000};
  byte n[5] = {B00111110, B00010000, B00100000, B00100000, B00011110};
  byte o[5] = {B00011100, B00100010, B00100010, B00100010, B00011100};

  /* now display them one by one with a small delay */
  lc.setRow(0, 0, a[4]);
  lc.setRow(0, 1, a[3]);
  lc.setRow(0, 2, a[2]);
  lc.setRow(0, 3, a[1]);
  lc.setRow(0, 4, a[0]);
  delay(delaytime);
  lc.setRow(0, 0, r[4]);
  lc.setRow(0, 1, r[3]);
  lc.setRow(0, 2, r[2]);
  lc.setRow(0, 3, r[1]);
  lc.setRow(0, 4, r[0]);
  delay(delaytime);
  lc.setRow(0, 0, d[4]);
  lc.setRow(0, 1, d[3]);
  lc.setRow(0, 2, d[2]);
  lc.setRow(0, 3, d[1]);
  lc.setRow(0, 4, d[0]);
  delay(delaytime);
  lc.setRow(0, 0, u[4]);
  lc.setRow(0, 1, u[3]);
  lc.setRow(0, 2, u[2]);
  lc.setRow(0, 3, u[1]);
  lc.setRow(0, 4, u[0]);
  delay(delaytime);
  lc.setRow(0, 0, i[4]);
  lc.setRow(0, 1, i[3]);
  lc.setRow(0, 2, i[2]);
  lc.setRow(0, 3, i[1]);
  lc.setRow(0, 4, i[0]);
  delay(delaytime);
  lc.setRow(0, 0, n[4]);
  lc.setRow(0, 1, n[3]);
  lc.setRow(0, 2, n[2]);
  lc.setRow(0, 3, n[1]);
  lc.setRow(0, 4, n[0]);
  delay(delaytime);
  lc.setRow(0, 0, o[4]);
  lc.setRow(0, 1, o[3]);
  lc.setRow(0, 2, o[2]);
  lc.setRow(0, 3, o[1]);
  lc.setRow(0, 4, o[0]);
  delay(delaytime);
  lc.setRow(0, 0, 0);
  lc.setRow(0, 1, 0);
  lc.setRow(0, 2, 0);
  lc.setRow(0, 3, 0);
  lc.setRow(0, 4, 0);
  delay(delaytime);
}

void setrow(byte a[])
{
  lc.setRow(0, 0, a[0]);
  lc.setRow(0, 1, a[1]);
  lc.setRow(0, 2, a[2]);
  lc.setRow(0, 3, a[3]);
  lc.setRow(0, 4, a[4]);
  lc.setRow(0, 5, a[5]);
  lc.setRow(0, 6, a[6]);
  lc.setRow(0, 7, a[7]);
}
void smile()
{
  /* here is the data for the characters */
  byte a[8] = {
      B00000000,
      B00100000,
      B01000110,
      B00100000,
      B01000000,
      B00100110,
      B00000000,
      B00000000,
  };

  setrow(a);
  // delay(delaytime);
}

void cry()
{
  /* here is the data for the characters */
  byte a[8] = {
      B11111111,
      B00100000,
      B01011110,
      B00100000,
      B01000000,
      B00111110,
      B00000000,
      B00000000,
  };

  setrow(a);
  // delay(delaytime);
}

/*
  This function lights up a some Leds in a row.
 The pattern will be repeated on every row.
 The pattern will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void rows()
{
  for (int row = 0; row < 8; row++)
  {
    delay(delaytime);
    lc.setRow(0, row, B10100000);
    delay(delaytime);
    lc.setRow(0, row, (byte)0);
    for (int i = 0; i < row; i++)
    {
      delay(delaytime);
      lc.setRow(0, row, B10100000);
      delay(delaytime);
      lc.setRow(0, row, (byte)0);
    }
  }
}

/*
  This function lights up a some Leds in a column.
 The pattern will be repeated on every column.
 The pattern will blink along with the column-number.
 column number 4 (index==3) will blink 4 times etc.
 */
void columns()
{
  for (int col = 0; col < 8; col++)
  {
    delay(delaytime);
    lc.setColumn(0, col, B10100000);
    delay(delaytime);
    lc.setColumn(0, col, (byte)0);
    for (int i = 0; i < col; i++)
    {
      delay(delaytime);
      lc.setColumn(0, col, B10100000);
      delay(delaytime);
      lc.setColumn(0, col, (byte)0);
    }
  }
}

/*
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void single()
{
  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++)
    {
      delay(delaytime);
      lc.setLed(0, row, col, true);
      delay(delaytime);
      for (int i = 0; i < col; i++)
      {
        lc.setLed(0, row, col, false);
        delay(delaytime);
        lc.setLed(0, row, col, true);
        delay(delaytime);
      }
    }
  }
}

void loop()
{
  if (Serial.available() > 0)
  {

    String serialValue = Serial.readString();
    serialValue.trim(); // 去除字符串首尾的空格、回车符和换行符
    Serial.print(serialValue);
    if (serialValue == "a")
    {
      Serial.print("crying");
      cry();
    }
    else
    {
      // smile();
    } 
  }
  delay(200);
}

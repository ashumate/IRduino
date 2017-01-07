/*-------------------------------------------------------------------------- +
  IRduino.cpp
  2014 Copyright (c) Longan Lab.  All right reserved.
 
  Author:Llama
  2014-7-6
  
  https://github.com/LonganLab/IRduino
  
  -------------------
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
-----------------------------------------------------------------------------*/
#include <Arduino.h>
#include <IRDuino.h>
#include <IRDuinoRecv.h>

#define PINIR               6

#define __DBG               0

void IRduino::begin()
{
    num_code= 0;

    Keyboard.begin();
    IR.Init(PINIR);
    
    for(int i=A0; i<=A5; i++)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);                      // all led off
    }
    
    led(B1, 1);
    led(B2, 1);
}

// control led
void IRduino::led(int pin, int state)
{
    if(pin>A5 || pin<A0)return;                     // err pin
    
    int pin_off = (pin<=A2) ? 0 : 3;
    
    for(int i=A0+pin_off; i<=(A2+pin_off); i++)     // all led off in one side
    {
        digitalWrite(i, HIGH);
    }
    digitalWrite(pin, 1-state);
}

// all led off
void IRduino::all_led_off()
{
    for(int i=A0; i<=A5; i++)
    {
        digitalWrite(i, HIGH);
    }
}

// press a key, then release it
void IRduino::keyPressRelease(unsigned char keyNum)
{
    Keyboard.press(keyNum);
    delay(1);
    Keyboard.release(keyNum);
}

/*
 * enter a string
 */
void IRduino::printf(char *str)
{
    if(NULL == str)return;

    while(*str)
    {
        keyPressRelease(str[0]);
        str++;
    }

}

/*
 * find if this ir code was stored, if not return -1
 */
int IRduino::find_ir_code(int irCode)
{
    for(int i=0; i<num_code; i++)
    {
        if(irCode == ir_code[i])
        {
            return i;
        }
    }

    return -1;
}


/*
 * add an task
 */
bool IRduino::addItem(int irCode, void (*pfun)())
{
    ir_code[num_code]    = irCode;
    task_fun[num_code++] = pfun;
      // FIXME: undocumented symantics... asumming returning true means successful add
    return true;
}

/* process */
void IRduino::process()
{
    if(!isGetIrDta())return;


    int irCode = getIrDta();

    Serial.println("+------------------------------------------------------+");
    if(irCode<=0)
    {
        Serial.println("get error code, try again");
        
    }
    else
    {
        Serial.print("get IR Code: 0x");
        Serial.println(irCode, HEX);
    }
    
    int task_loca = find_ir_code(irCode);
    
    if(task_loca >= 0)                  // find
    {
        Serial.print("task_loca = ");
        Serial.println(task_loca);
        
        led(G1, 1);
        led(G2, 1);
        delay(100);
        led(G1, 0);
        led(G2, 0);
        
        (task_fun[task_loca])();
    }
    else
    {
        Serial.println("can't find this ir code");
        led(R1, 1);
        led(R2, 1);
        delay(100);
        led(R1, 0);
        led(R2, 0);
    }
    
    Serial.println("+------------------------------------------------------+\r\n\r\n");
}



IRduino iRduino;

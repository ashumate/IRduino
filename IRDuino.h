/*-------------------------------------------------------------------------- +
  IRduino.h
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
#ifndef __IRDUINO_H__
#define __IRDUINO_H__

#include <Arduino.h>
#include <IRDuinoRecv.h>
//Include Keyboard.h to fix compile errors
#include <Keyboard.h>

#define MAX_IR_CODE     50

/*
#define KEY_LEFT_CTRL		0x80
#define KEY_LEFT_SHIFT		0x81
#define KEY_LEFT_ALT		0x82
#define KEY_LEFT_GUI		0x83
#define KEY_RIGHT_CTRL		0x84
#define KEY_RIGHT_SHIFT		0x85
#define KEY_RIGHT_ALT		0x86
#define KEY_RIGHT_GUI		0x87

#define KEY_UP_ARROW		0xDA
#define KEY_DOWN_ARROW		0xD9
#define KEY_LEFT_ARROW		0xD8
#define KEY_RIGHT_ARROW		0xD7
#define KEY_BACKSPACE		0xB2
#define KEY_TAB				0xB3
#define KEY_RETURN			0xB0
#define KEY_ESC				0xB1
#define KEY_INSERT			0xD1
#define KEY_DELETE			0xD4
#define KEY_PAGE_UP			0xD3
#define KEY_PAGE_DOWN		0xD6
#define KEY_HOME			0xD2
#define KEY_END				0xD5
#define KEY_CAPS_LOCK		0xC1
#define KEY_F1				0xC2
#define KEY_F2				0xC3
#define KEY_F3				0xC4
#define KEY_F4				0xC5
#define KEY_F5				0xC6
#define KEY_F6				0xC7
#define KEY_F7				0xC8
#define KEY_F8				0xC9
#define KEY_F9				0xCA
#define KEY_F10				0xCB
#define KEY_F11				0xCC
#define KEY_F12				0xCD
*/

#define KEY_SPACE           32


// B1 below collids with the value from binary.h
#ifdef B1
#	undef B1
#endif

#define R1                  A0
#define G1                  A1
#define B1                  A2
#define R2                  A3
#define G2                  A4
#define B2                  A5


class IRduino{

private:

    int num_code;
    int ir_code[MAX_IR_CODE];
    void (*task_fun[MAX_IR_CODE])(void);


private:

    int find_ir_code(int irCode);
    
public:

    void begin();
    
    void led(int pin, int state);
    void all_led_off();
    
    bool addItem(int irCode, void (*pfun)());
    
    void process();
    
    
    void keyPressRelease(unsigned char keyNum);
    
    void press(unsigned char keyNum)
    {
        Keyboard.press(keyNum);
    }
    
    void release(unsigned char keyNum)
    {
        Keyboard.release(keyNum);
    }
    
    void releaseAll()
    {
        Keyboard.releaseAll();
    }
    
    void printf(char *str);
    
    
    
    int isGetIrDta()                                        // if anything got from IR
    {
        return IR.IsDta();
    }
    
    int getIrDta()                                           // get IR code
    {
        return IR.Recv();
    }
    
    void winR()
    {
        press(KEY_RIGHT_GUI);           // window
        press('r');                     // win+R, you know that if you use a Windows system
        delay(200);
        releaseAll();
    }
    
    void enter()
    {
        press(KEY_RETURN);
        delay(20);
        release(KEY_RETURN);
    }

};


extern IRduino iRduino;

#endif

 /*
 * This file is part of the bk-0010-01 (https://github.com/tigertv/bk-0010-01).
 * Copyright (c) 2020 Max Vetrov(tigertv).
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef KEYBOARD_H
#define KEYBOARD_H

class Bus;
class Processor;

class Keyboard {
private:
    Bus* bus;
    Processor* processor;

public:
    void pressKey(char key);
    void setBus(Bus* bus);
    void setProcessor(Processor* processor);
};

enum class BK_KEYS : unsigned char {
    LEFT = 010,
    ENTER = 012,
    RUS = 016,
    LAT,
    BACKSPACE = 030,
    RIGHT,
    UP,
    DOWN,
    LEFTBRACE = 0x7b,
    VERTICALBAR,
    RIGHTBRACE
};

#endif

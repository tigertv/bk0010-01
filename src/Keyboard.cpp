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


#include "Keyboard.h"
#include "Bus.h"
#include "Processor.h"

#include <iostream>

void Keyboard::pressKey(char key) {
    // Регистр состояния клавиатуры имеет адрес 177660.
    // Регистр данных клавиатуры имеет адрес 177662.
    uint16_t keyboardStateReg = 0177660;
    uint16_t keyboardDataReg = 0177662;
    //uint16_t pressedKeyReg = 0177716;

    uint16_t data;

    // put key in register
    data = bus->readWord(keyboardDataReg);
    data = (data & 0177600) | (key & 0177);
    std::cout << "KEYCODE: 0x" << std::hex << data << std::endl;
    bus->writeWord(keyboardDataReg, data);

    // set ready bit
    data = bus->readWord(keyboardStateReg);
    data |= 0x0080;
    bus->writeByte(keyboardStateReg, data);

    data = bus->readWord(keyboardStateReg);
    // check the flag of interruption permission
    if (data & 0x0040) {
        // interreptions are forbitten
        return;
    }
    // rise an interruption
    //processor->irq = 060;
    //*
    if (key & 0x80) {
        processor->irq = 0274;
    } else {
        processor->irq = 060;
    }
    //*/
    
    
}

void Keyboard::setBus(Bus* bus) {
    this->bus = bus;
}

void Keyboard::setProcessor(Processor* processor) {
    this->processor = processor;
}
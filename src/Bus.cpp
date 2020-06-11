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


#include "Bus.h"
#include "BK.h"
#include <iostream>

uint16_t Bus::readWord(uint16_t address) {
    //std::cout << "READ WORD DATA FROM MEMORY" << std::endl;
    if (address == 0177662) { // keyboardDataReg
        memory[0177660] &= 0x7f;
    }

    return memory[address] | (memory[address + 1] << 8);
}

void Bus::writeWord(uint16_t address, uint16_t data) {
    //std::cout << "WRITE WORD DATA TO MEMORY" << std::endl;
    memory[address] = data & 0xff;
    memory[address + 1] = data >> 8;

    //*
    if ((address >= 0040000) && (address < 0100000)) {
        // update videomemory
        std::cout << "BKK:" << std::endl;
        bk->needToUpdateScreen = true;
        bk->addrs.push_back(address);
        bk->addrs.push_back(address + 1);
    }
    //*/
}

uint8_t Bus::readByte(uint16_t address) {
    return memory[address];
}

void Bus::writeByte(uint16_t address, uint8_t data) {
    memory[address] = data;
    //*
    if ((address >= 0040000) && (address < 0100000)) {
        // update videomemory
        std::cout << "BKK Byte:" << std::endl;
        bk->needToUpdateScreen = true;
        bk->addrs.push_back(address);
    }
    //*/
}

/*
void connect(uint16_t address, uint16_t size, IReadWrite* device) {
    
}
//*/

void Bus::setBK(BK* bk) {
    this->bk = bk;
}
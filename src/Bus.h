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


#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include "IReadWrite.h"

class BK;

#define ADDRESS_SPACE 0x10000

class Bus : public IReadWrite {
private:
    uint8_t memory[ADDRESS_SPACE] = {0};
    BK* bk;
    
public:
    uint16_t readWord(uint16_t address) override;
    void writeWord(uint16_t address, uint16_t data) override;
    uint8_t readByte(uint16_t address) override;
    void writeByte(uint16_t address, uint8_t data) override;
    void connect(uint16_t address, uint16_t size, IReadWrite* device);

    void setBK(BK* bk);
};

#endif

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


#include "MovbOperation.h"
#include <iostream>
#include <iomanip>

MovbOperation::MovbOperation(Processor* processor) : TwoOperandOperation(processor) {

}

void MovbOperation::execute() {
    std::cout << "MOVB OPERATION" << std::endl;
    decode();
    uint8_t result = readWriteSrc->readByte(addressSrc);
    
    if (readWriteDest == processor) {
        uint16_t temp = (int8_t)result;
        readWriteDest->writeWord(addressDest, temp);
    } else {
        readWriteDest->writeByte(addressDest, result);
    }
    
    processor->clearBitV();
    // bitC not affected

    std::cout << "result    : 0x" << std::hex << std::setfill('0') << std::setw(2) << (uint16_t)result << std::endl;
    std::cout << "result oct:   " << std::oct << std::setfill('0') << std::setw(3) << (uint16_t)result << std::endl;
    checkNZ(result);
}
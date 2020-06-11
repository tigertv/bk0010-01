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


#include "MovOperation.h"
#include <iostream>
#include <iomanip>

MovOperation::MovOperation(Processor* processor) : TwoOperandOperation(processor) {

}

void MovOperation::execute() {
    std::cout << "MOV OPERATION" << std::endl;
    decode();
    uint16_t result = readWriteSrc->readWord(addressSrc);
    readWriteDest->writeWord(addressDest, result);
    processor->clearBitV();
    // bitC not affected

    std::cout << "result    : 0x" << std::hex << std::setfill('0') << std::setw(4) << result << std::endl;
    std::cout << "result oct:   " << std::oct << std::setfill('0') << std::setw(6) << result << std::endl;
    checkNZ(result);
}
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


#include "BisbOperation.h"
#include <iostream>
#include <iomanip>

BisbOperation::BisbOperation(Processor* processor) : TwoOperandOperation(processor) {

}

void BisbOperation::execute() {
    std::cout << "BISB OPERATION" << std::endl;
    decode();
    
    uint8_t srcOperand = readWriteSrc->readByte(addressSrc);
    uint8_t destOperand = readWriteDest->readByte(addressDest);

    std::cout << "OP_BISB src: " << std::hex << std::setfill('0') << std::setw(2) << (uint16_t)srcOperand << std::endl;
    std::cout << "OP_BISB dest: " << std::hex << std::setfill('0') << std::setw(2) << (uint16_t)destOperand << std::endl;
    
    uint8_t result = destOperand | srcOperand;
    readWriteDest->writeByte(addressDest, result);
    processor->clearBitV();
    // bitC not affected

    checkNZ(result);
}
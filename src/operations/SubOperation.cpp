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


#include "SubOperation.h"
#include <iostream>
#include <iomanip>

SubOperation::SubOperation(Processor* processor) : TwoOperandOperation(processor) {

}

void SubOperation::execute() {
    std::cout << "SUB OPERATION" << std::endl;
    decode();
    
    uint16_t srcOperand = readWriteSrc->readWord(addressSrc);
    uint16_t destOperand = readWriteDest->readWord(addressDest);
    
    std::cout << "OP_SUB src:  0x" << std::hex << srcOperand << std::endl;
    std::cout << "OP_SUB src:  " << std::oct << std::setfill('0') << std::setw(6) << srcOperand << std::endl;
    std::cout << "OP_SUB dest: 0x" << std::hex << destOperand << std::endl;
    std::cout << "OP_SUB dest: " << std::oct << std::setfill('0') << std::setw(6) << destOperand << std::endl;
    
    uint16_t result = checkVCsum(~srcOperand + 1, destOperand);
    // borrow for subtruction, inverse carry
    if (processor->getBitC()) {
        processor->clearBitC();
    } else {
        processor->setBitC();
    }

    readWriteDest->writeWord(addressDest, result);

    checkNZ(result);
}
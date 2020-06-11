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


#include "CmpOperation.h"
#include <iostream>
#include <iomanip>


CmpOperation::CmpOperation(Processor* processor) : TwoOperandOperation(processor) {

}

void CmpOperation::execute() {
    std::cout << "CMP OPERATION" << std::endl;
    decode();
    
    uint16_t srcOperand = readWriteSrc->readWord(addressSrc);
    uint16_t destOperand = readWriteDest->readWord(addressDest);
    
    std::cout << "OP_CMP src:  0x" << std::hex << srcOperand << std::endl;
    std::cout << "OP_CMP src:  " << std::oct << std::setfill('0') << std::setw(6) << srcOperand << std::endl;
    std::cout << "OP_CMP dest: 0x" << std::hex << destOperand << std::endl;
    std::cout << "OP_CMP dest: " << std::oct << std::setfill('0') << std::setw(6) << destOperand << std::endl;
    
    uint16_t result = checkVCsum(srcOperand, ~destOperand + 1);
    // borrow for subtruction, inverse carry
    if (processor->getBitC()) {
        processor->clearBitC();
    } else {
        processor->setBitC();
    }

    checkNZ(result);

    std::cout << "result    : 0x" << std::hex << std::setfill('0') << std::setw(4) << result << std::endl;
    std::cout << "result oct:   " << std::oct << std::setfill('0') << std::setw(6) << result << std::endl;
    
}
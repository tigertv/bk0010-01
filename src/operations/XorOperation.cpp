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


#include "XorOperation.h"
#include <iostream>

XorOperation::XorOperation(Processor* processor) : RegOperandOperation(processor) {

}

void XorOperation::execute() {
    std::cout << "XOR OPERATION" << std::endl;
    decode();

    uint16_t result = processor->readWord(regOperand);
    result ^= readWrite->readWord(address);
    
    readWrite->writeWord(address, result);

    processor->clearBitV();
    // Bit C unaffected
    checkNZ(result);
}
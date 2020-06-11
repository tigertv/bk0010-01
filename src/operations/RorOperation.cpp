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


#include "RorOperation.h"
#include <iostream>

RorOperation::RorOperation(Processor* processor) : OneOperandOperation(processor) {

}

void RorOperation::execute() {
    std::cout << "ROR OPERATION" << std::endl;
    decode();
    
    uint16_t result = readWrite->readWord(address);
	uint16_t lowBit = result & 1;
	uint16_t bitC = processor->getBitC();
	result >>= 1;
	result |= bitC << 15;
	readWrite->writeWord(address, result);

	if (bitC != lowBit) {
		processor->setBitV();
	} else {
		processor->clearBitV();
	}
	
	if (lowBit == 0) {
		processor->clearBitC();
	} else {
		processor->setBitC();
	}

	checkNZ(result);
}
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


#include "AsrOperation.h"
#include <iostream>

AsrOperation::AsrOperation(Processor* processor) : OneOperandOperation(processor) {

}

void AsrOperation::execute() {
    std::cout << "ASR OPERATION" << std::endl;
    decode();
    
    uint16_t result = readWrite->readWord(address);
	uint16_t highBit = result & 0x8000;
	uint16_t lowBit = result & 1;
	result >>= 1;
	result |= highBit;
	readWrite->writeWord(address, result);

	if ((highBit >> 15) != lowBit) {
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
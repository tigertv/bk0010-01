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


#include "AsrbOperation.h"
#include <iostream>

AsrbOperation::AsrbOperation(Processor* processor) : OneOperandOperation(processor) {

}

void AsrbOperation::execute() {
    std::cout << "ASRB OPERATION" << std::endl;
    decode();
    
    uint8_t result = readWrite->readByte(address);
	uint8_t highBit = result & 0x80;
	uint8_t lowBit = result & 1;
	result >>= 1;
	result |= highBit;
	readWrite->writeByte(address, result);

	if ((highBit >> 7) != lowBit) {
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
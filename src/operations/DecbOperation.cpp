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


#include "DecbOperation.h"
#include <iostream>
#include <iomanip>


DecbOperation::DecbOperation(Processor* processor) : OneOperandOperation(processor) {

}

void DecbOperation::execute() {
    std::cout << "DECB OPERATION" << std::endl;
    decode();
    uint8_t result = readWrite->readByte(address) - 1;
	readWrite->writeByte(address, result);

	if (result == 0x7f) { // for byte
		processor->setBitV();
	} else {
		processor->clearBitV();
	}
	// bitC not affected
	checkNZ(result);

	std::cout << "result    : 0x" << std::hex << std::setfill('0') << std::setw(2) << (uint16_t)result << std::endl;
    std::cout << "result oct:   " << std::oct << std::setfill('0') << std::setw(3) << (uint16_t)result << std::endl;
    
}
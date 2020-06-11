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


#include "DecOperation.h"
#include <iostream>
#include <iomanip>


DecOperation::DecOperation(Processor* processor) : OneOperandOperation(processor) {

}

void DecOperation::execute() {
    std::cout << "DEC OPERATION" << std::endl;
    decode();
    uint16_t result = readWrite->readWord(address) - 1;
	readWrite->writeWord(address, result);

	if (result == 0x7fff) { // for word
		processor->setBitV();
	} else {
		processor->clearBitV();
	}
	// bitC not affected
	checkNZ(result);

	std::cout << "result    : 0x" << std::hex << std::setfill('0') << std::setw(4) << result << std::endl;
    std::cout << "result oct:   " << std::oct << std::setfill('0') << std::setw(6) << result << std::endl;
    
}
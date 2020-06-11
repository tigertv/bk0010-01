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


#include "SwabOperation.h"
#include <iostream>

SwabOperation::SwabOperation(Processor* processor) : OneOperandOperation(processor) {

}

void SwabOperation::execute() {
    std::cout << "SWAB OPERATION" << std::endl;
    decode();
    
    uint16_t result = readWrite->readWord(address);
	uint8_t temp = result >> 8;
	result = temp | (result << 8);
	readWrite->writeWord(address, result);

	processor->clearBitV();
	processor->clearBitC();
	
	checkNZ(temp);
}
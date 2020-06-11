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


#include "ComOperation.h"
#include <iostream>

ComOperation::ComOperation(Processor* processor) : OneOperandOperation(processor) {

}

void ComOperation::execute() {
    std::cout << "COM OPERATION" << std::endl;
    decode();

	uint16_t result = ~(readWrite->readWord(address));
	readWrite->writeWord(address, result);
	processor->clearBitV();
	processor->setBitC();

	checkNZ(result);
}
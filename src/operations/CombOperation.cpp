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


#include "CombOperation.h"
#include <iostream>

CombOperation::CombOperation(Processor* processor) : OneOperandOperation(processor) {

}

void CombOperation::execute() {
    std::cout << "COMB OPERATION" << std::endl;
    decode();

	uint8_t result = ~(readWrite->readByte(address));
	readWrite->writeByte(address, result);
	processor->clearBitV();
	processor->setBitC();

	checkNZ(result);
}
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


#include "AdcbOperation.h"
#include <iostream>

AdcbOperation::AdcbOperation(Processor* processor) : OneOperandOperation(processor) {

}

void AdcbOperation::execute() {
    std::cout << "ADCB OPERATION" << std::endl;
    decode();

	uint8_t result = readWrite->readByte(address);
	uint8_t bitC = processor->getBitC();

	if (result == 0x7f && bitC == 1) {
		processor->setBitV(); 
	} else {
		processor->clearBitV();
	}

	if (result == 0xff && bitC == 1) {
		processor->setBitC();
	} else {
		processor->clearBitC();
	}

	result += bitC;
	readWrite->writeByte(address, result);

	checkNZ(result);
}
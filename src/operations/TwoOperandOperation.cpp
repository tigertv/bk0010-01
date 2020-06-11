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


#include "TwoOperandOperation.h"
#include <iostream>
#include <iomanip>

TwoOperandOperation::TwoOperandOperation(Processor* processor) : BaseOperation(processor) {

}

void TwoOperandOperation::decode() {
	uint16_t instruction = processor->getCurrentInstruction();
	uint16_t modSrc = (instruction & 07000) >> 9;
    uint16_t regSrc = (instruction & 00700) >> 6;
    uint16_t modDest = (instruction & 00070) >> 3;
    uint16_t regDest = instruction & 00007;
	uint16_t isByteOp = instruction & 0100000;
	if (isByteOp && ((instruction & 0060000) != 0060000)) {
		addressSrc = processor->getModAddressByte(modSrc, regSrc);
	} else {
		addressSrc = processor->getModAddress(modSrc, regSrc);
	}

	if (modSrc == 0) {
		// the operand in a register
		readWriteSrc = processor;
	} else {
		// the operand in memory
		readWriteSrc = processor->getBus();
	}

	if (isByteOp && ((instruction & 0060000) != 0060000)) {
		addressDest = processor->getModAddressByte(modDest, regDest);
	} else {
		addressDest = processor->getModAddress(modDest, regDest);
	}

	if (modDest == 0) {
		// the operand in a register
		readWriteDest = processor;
	} else {
		// the operand in memory
		readWriteDest = processor->getBus();
	}

	std::cout << std::hex << "src mod: " << modSrc << std::endl;
    std::cout << std::hex << "src reg: " << regSrc << std::endl;
	std::cout << std::oct << "src address oct: " << std::setw(6) << addressSrc << std::endl;
	std::cout << std::hex << "src address    : 0x" << std::setw(4) << addressSrc << std::endl;
	std::cout << std::hex << "dest mod: " << modDest << std::endl;
    std::cout << std::hex << "dest reg: " << regDest << std::endl;
	std::cout << std::oct << "dest address oct: " << std::setw(6) << addressDest << std::endl;
	std::cout << std::hex << "dest address    : 0x" << std::setw(4) << addressDest << std::endl;
}
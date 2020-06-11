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


#include "RegOperandOperation.h"
#include <iostream>
#include <iomanip>

RegOperandOperation::RegOperandOperation(Processor* processor) : BaseOperation(processor) {

}

void RegOperandOperation::decode() {
	uint16_t instruction = processor->getCurrentInstruction();
	regOperand = (instruction &0700) >> 6;
    uint16_t mod = (instruction & 0070) >> 3;
    uint16_t reg = instruction & 0007;
    address = processor->getModAddress(mod, reg);
    
	if (mod == 0) {
		// the operand in a register
		readWrite = processor;
	} else {
		// the operand in memory
		readWrite = processor->getBus();
	}
	
	std::cout << std::hex << "regOperand: " << regOperand << std::endl;
	std::cout << std::hex << "mod: " << mod << std::endl;
    std::cout << std::hex << "reg: " << reg << std::endl;
	std::cout << std::oct << "address oct: " << std::setw(6) << address << std::endl;
	std::cout << std::hex << "address    : 0x" << std::setw(4) << address << std::endl;
}
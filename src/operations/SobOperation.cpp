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


#include "SobOperation.h"
#include <iostream>
#include <iomanip>

SobOperation::SobOperation(Processor* processor) : BaseOperation(processor) {

}

void SobOperation::execute() {
	std::cout << "SOB OPERATION" << std::endl;
    
	uint16_t instruction = processor->getCurrentInstruction();
	uint16_t reg = (instruction & 00700) >> 6;
	uint16_t offset = (instruction & 00077) << 1;
	std::cout << std::hex << "reg: " << reg << std::endl;
	std::cout << std::oct << "offset oct: " << std::setw(6) << offset << std::endl;
	std::cout << std::hex << "offset    : 0x" << std::setw(4) << offset << std::endl;
	
	uint16_t operand = processor->readWord(reg);
	operand--;
	processor->writeWord(reg, operand);
	if (operand == 0) return;
	
	processor->setPC(processor->getPC() - offset);
	// flags not affected
}
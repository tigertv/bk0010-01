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


#include "RetOperation.h"
#include <iostream>
#include <iomanip>

RetOperation::RetOperation(Processor *processor) : BaseOperation(processor) {
	
}

void RetOperation::execute() {
	std::cout << "RET OPERATION" << std::endl;

	uint16_t instruction = processor->getCurrentInstruction();
	uint16_t reg = instruction & 7;
	std::cout << std::hex << "reg: " << reg << std::endl;

	uint16_t operand = processor->readWord(reg);
	processor->setPC(operand);

	// pop reg from stack
	uint16_t sp = processor->getSP();
	operand = processor->getBus()->readWord(sp);
	processor->writeWord(reg, operand);

	sp += 2;
	processor->setSP(sp);
}
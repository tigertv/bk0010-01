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


#include "CompositeOperation.h"
#include <iostream>
#include <iomanip>
#include "RetOperation.h"

CompositeOperation::CompositeOperation(Processor *processor, uint16_t size, uint16_t opcodeMask) :  // operations(size),
		BaseOperation(processor), opcodeMask(opcodeMask) {
}

void CompositeOperation::addOperation(BaseOperation* op, int16_t opcode) {
	operations[opcode] = op;
}

void CompositeOperation::execute() {
	std::cout << "COMPOSITE OPERATION" << std::endl;

	// decode
	uint16_t instruction = processor->getCurrentInstruction();
	uint16_t opcode = instruction & opcodeMask;
	std::cout << "opcode = " << opcode << std::endl;
	operations[opcode]->execute();
}
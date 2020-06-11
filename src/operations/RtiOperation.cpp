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


#include "RtiOperation.h"
#include <iostream>
#include <iomanip>

RtiOperation::RtiOperation(Processor *processor) : BaseOperation(processor) {
	
}

void RtiOperation::execute() {
	std::cout << "RTI OPERATION" << std::endl;

	uint16_t sp = processor->getSP();
	IReadWrite* memory = processor->getBus();
	
	uint16_t operand = memory->readWord(sp);
	sp += 2;
	processor->setPC(operand);
	
	operand = memory->readWord(sp);
	sp += 2;
	processor->setPSW(operand);
	
	processor->setSP(sp);
}
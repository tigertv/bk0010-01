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


#include "BisOperation.h"
#include <iostream>

BisOperation::BisOperation(Processor* processor) : TwoOperandOperation(processor) {

}

void BisOperation::execute() {
    std::cout << "BIS OPERATION" << std::endl;
    decode();
    
	uint16_t srcOperand = readWriteSrc->readWord(addressSrc);
	uint16_t destOperand = readWriteDest->readWord(addressDest);
	
	std::cout << "OP_BIS src: " << srcOperand << std::endl;
	std::cout << "OP_BIS dest: " << destOperand << std::endl;
	
	uint16_t result = destOperand | srcOperand;
	readWriteDest->writeWord(addressDest, result);
	processor->clearBitV();
	// bitC not affected

	checkNZ(result);
}
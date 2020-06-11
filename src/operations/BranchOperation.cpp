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


#include "BranchOperation.h"
#include <iostream>
#include <iomanip>

BranchOperation::BranchOperation(Processor* processor) : BaseOperation(processor) {

}

void BranchOperation::decode() {
    uint16_t instruction = processor->getCurrentInstruction();
    offset = ((short)(char)(instruction & 0xff)) * 2;

    std::cout << std::hex << "offset: 0x" << offset << std::endl;
    std::cout << std::oct << "offset oct: " << std::setw(6) << offset << std::endl;
}
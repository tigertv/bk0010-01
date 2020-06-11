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


#include "EmtOperation.h"
#include <iostream>
#include <iomanip>

EmtOperation::EmtOperation(Processor *processor) : BaseOperation(processor) {
    
}

void EmtOperation::execute() {
    std::cout << "EMT OPERATION" << std::endl;

    uint16_t sp = processor->getSP();
    IReadWrite* memory = processor->getBus();
    uint16_t operand = processor->getPSW();
    
    sp -= 2;
    memory->writeWord(sp, operand);
    
    sp -= 2;
    operand = processor->getPC();
    memory->writeWord(sp, operand);
    
    processor->setSP(sp);

    operand = memory->readWord(030);
    processor->setPC(operand);
    operand = memory->readWord(032);
    processor->setPSW(operand);
}
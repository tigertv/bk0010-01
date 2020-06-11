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


#ifndef BASE_OPERATION_H
#define BASE_OPERATION_H

#include <cstdint>

class Processor;
#include "../Processor.h"


class BaseOperation {
protected:
    Processor* processor;
    void checkNZ(uint8_t result);
    void checkNZ(uint16_t result);
    uint8_t checkVCsum(uint8_t operand1, uint8_t operand2);
    uint16_t checkVCsum(uint16_t operand1, uint16_t operand2);
    
public:
    BaseOperation(Processor* processor);
    virtual void execute() = 0;
    
};

#endif

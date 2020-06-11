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


#include "BaseOperation.h"

BaseOperation::BaseOperation(Processor* processor) {
    this->processor = processor;
}

void BaseOperation::checkNZ(uint8_t result) {
    if (result >> 7) { // for byte
        processor->setBitN();
    } else {
        processor->clearBitN();
    }

    if (result == 0) {
        processor->setBitZ();
    } else {
        processor->clearBitZ();
    }
}

void BaseOperation::checkNZ(uint16_t result) {
    if (result >> 15) { // for word
        processor->setBitN();
    } else {
        processor->clearBitN();
    }

    if (result == 0) {
        processor->setBitZ();
    } else {
        processor->clearBitZ();
    }	

}

uint8_t BaseOperation::checkVCsum(uint8_t operand1, uint8_t operand2) {
    uint8_t oper1Sign = operand1 >> 7;
    uint8_t oper2Sign = operand2 >> 7;
    uint8_t result = (operand1 & 0x7f) + (operand2 & 0x7f);
    uint8_t resultSign = result >> 7;
    resultSign += oper1Sign + oper2Sign;
    
    uint8_t carry = resultSign >> 1;
    resultSign &= 1;
    result = (result & 0x7f) | (resultSign << 7);

    if (carry) {
        processor->setBitC();
    } else {
        processor->clearBitC();
    }

    if (oper1Sign == oper2Sign && resultSign) {
        processor->setBitV();
    } else {
        processor->clearBitV();
    }

    return result;
}

uint16_t BaseOperation::checkVCsum(uint16_t operand1, uint16_t operand2) {
    uint16_t oper1Sign = operand1 >> 15;
    uint16_t oper2Sign = operand2 >> 15;
    uint16_t result = (operand1 & 0x7fff) + (operand2 & 0x7fff);
    uint16_t resultSign = result >> 15;
    resultSign += oper1Sign + oper2Sign;
    
    uint16_t carry = resultSign >> 1;
    resultSign &= 1;
    result = (result & 0x7fff) | (resultSign << 15);

    if (carry) {
        processor->setBitC();
    } else {
        processor->clearBitC();
    }

    if (oper1Sign == oper2Sign && resultSign) {
        processor->setBitV();
    } else {
        processor->clearBitV();
    }

    return result;
}
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


#include "BleOperation.h"
#include <iostream>

BleOperation::BleOperation(Processor* processor) : BranchOperation(processor) {

}

void BleOperation::execute() {
    std::cout << "BLE OPERATION" << std::endl;
    //if(((processor->getBitV() + processor->getBitN() + processor->getBitZ()) & 1) != 1) return;
    if ( (processor->getBitV() ^ processor->getBitN()) == 0 && (processor->getBitZ() == 0) ) return;
    
    decode();

    uint16_t address = processor->getPC() + offset;
	processor->setPC(address);

	// frags not affected
}
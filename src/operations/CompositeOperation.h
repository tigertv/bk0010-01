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


#ifndef COMPOSITE_OPERATION_H
#define COMPOSITE_OPERATION_H

#include "BaseOperation.h"
#include <map>

class CompositeOperation : public BaseOperation {
private:
	std::map<uint16_t, BaseOperation *> operations;
	uint16_t opcodeMask;

public:
	CompositeOperation(Processor *processor, uint16_t size, uint16_t opcodeMask);
	void addOperation(BaseOperation* op, int16_t opcode);
	void execute() override;
};

#endif
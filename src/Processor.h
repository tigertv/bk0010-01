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


#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <cstdint>
#include <vector>
#include <map>
#include "Bus.h"
#include "IReadWrite.h"

class BaseOperation;
#include "operations/BaseOperation.h"

#define REGISTERS_SIZE 8
#define PSW_C 0b0000001
#define PSW_V 0b0000010
#define PSW_Z 0b0000100
#define PSW_N 0b0001000
#define PSW_T 0b0010000
#define PSW_P 0b1000000


class Processor : public IReadWrite {
private:
	uint16_t registers[REGISTERS_SIZE] = {0};
	// R6 = SP, R7 = PC
	uint16_t& sp = registers[6];
	uint16_t& pc = registers[7];
	uint16_t psw = 0;

	// external memory, maybe here should be a bus
	Bus* bus = nullptr;

	std::vector<BaseOperation*> operations;
	void addOperation(BaseOperation* op, uint16_t fromOpcode, uint16_t toOpcode);
	uint16_t currentInstruction;
	

public:
	Processor();
	void init(Bus* bus);
	int update();

	// for operations
	uint16_t getCurrentInstruction();
	uint16_t getPC();
	void setPC(uint16_t pc);
	uint16_t getSP();
	void setSP(uint16_t sp);
	uint16_t getPSW();
	void setPSW(uint16_t psw);
	uint16_t getModAddress(uint16_t mod, uint16_t reg); // decode address
	uint16_t getModAddressByte(uint16_t mod, uint16_t reg); // decode address
	IReadWrite* getBus();

	// non-direct access to registers
	uint16_t readWord(uint16_t address) override;
	void writeWord(uint16_t address, uint16_t data) override;
	uint8_t readByte(uint16_t address) override;
	void writeByte(uint16_t address, uint8_t data) override;
	
	// PSW Bits
	void setBitC(); // carry flag
	void setBitV(); // overflow flag
	void setBitZ(); // zero flag
	void setBitN(); // negative flag
	void setBitT(); 
	void setBitP();

	void clearBitC();
	void clearBitV();
	void clearBitZ();
	void clearBitN();
	void clearBitT();
	void clearBitP();

	uint16_t getBitC();
	uint16_t getBitV();
	uint16_t getBitZ();
	uint16_t getBitN();
	uint16_t getBitT();
	uint16_t getBitP();
	// PSW Bits END

	uint16_t irq;
	void handleIRQ();
};

#endif

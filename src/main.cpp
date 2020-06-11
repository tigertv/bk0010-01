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


#include <iostream>
#include <fstream>
#include <vector>
#include "BK.h"

std::vector<char> ReadAllBytes(char const* filename) {
    std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();
    std::vector<char> result(pos);
    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);
    return result;
}

int main() {
	BK bk;
	

	/*
	uint8_t program[] = {
		0x85, 0x0a, // INC R5 
		//0x84, 0x0a, // INC R4 
		//0x85, 0x0a, // INC R5 
		//0x83, 0x0a, // INC R3 
		//0x85, 0x8a, // INC R5 
		0x83, 0x10, // MOV R2, R3
		//0xc5, 0x15, 0x49, 0x12, // MOV #11111, R5
		0xfc, 0x06, // GBT M1
		0x77, 0x00, 0xf2, 0xff, // JMP M1
	};
	//*/

	std::vector<char> ret = ReadAllBytes("MONIT10.ROM");
	uint8_t* rom = (uint8_t*)ret.data();
	bk.loadRom(rom, 0100000, ret.size());

	/*
	std::vector<char> ret = ReadAllBytes("monit10.rom");
	uint8_t* rom = (uint8_t*)ret.data();
	bk.loadRom(rom, 0100000, ret.size());
	//*/

	std::vector<char> basic1 = ReadAllBytes("BASIC10.ROM");
	rom = (uint8_t*)basic1.data();
	bk.loadRom(rom, 0120000, basic1.size());
	
	/*
	std::vector<char> basic1 = ReadAllBytes("basic10_1.rom");
	rom = (uint8_t*)basic1.data();
	bk.loadRom(rom, 0120000, basic1.size());

	std::vector<char> basic2 = ReadAllBytes("basic10_2.rom");
	rom = (uint8_t*)basic2.data();
	bk.loadRom(rom, 0140000, basic2.size());

	std::vector<char> basic3 = ReadAllBytes("basic10_3.rom");
	rom = (uint8_t*)basic3.data();
	bk.loadRom(rom, 0160000, basic3.size());
	//*/
	bk.start();

	return 0;
}

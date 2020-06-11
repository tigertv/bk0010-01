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


#ifndef BK_H
#define BK_H

#include <cstdint>
#include <vector>
#include <map>

#include "Processor.h"
#include "Bus.h"
#include "Keyboard.h"

#include <SDL2/SDL.h> 
//#include <SDL2/SDL_image.h>

class BK {
private:
	Bus bus;
	Processor processor;
	Keyboard keyboard;
	bool isProcessing;
	SDL_Window *window = nullptr;
    SDL_Renderer *wrenderer = nullptr;
	SDL_Texture *texTarget = nullptr;
	std::map<SDL_Keycode, BK_KEYS> keys;
	std::map<SDL_Keycode, SDL_Keycode> shiftKeys;
	void init();
	void processInput();
	void render();
	int update();
	void printAllRegisters();
	void keyboardMapping();
	
public:
	std::vector<uint16_t> addrs;
	bool needToUpdateScreen = false;
	void start();
	void loadRom(uint8_t* program, uint16_t address, uint16_t size);
};

#endif

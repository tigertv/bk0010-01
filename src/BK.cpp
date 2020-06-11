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


#include "BK.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <ctime>
#include <iomanip>

void BK::loadRom(uint8_t* program, uint16_t address, uint16_t size) {
    for(uint16_t i = 0; i < size; i++) {
        bus.writeByte(i + address, program[i]);
    }
}

void BK::init() {
    processor.init(&bus);
    bus.setBK(this);
    keyboard.setBus(&bus);
    keyboard.setProcessor(&processor);
    keyboardMapping();
    // make window

    const int SCREEN_WIDTH = 512;
    const int SCREEN_HEIGHT = 256;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to init SDL: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow("BK-0010", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return;
    }

    wrenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    texTarget = SDL_CreateTexture(
        wrenderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT
    );

    //Now render to the texture
    SDL_SetRenderTarget(wrenderer, texTarget);
    SDL_SetRenderDrawColor(wrenderer, 0, 0, 0, 255);
    SDL_RenderClear(wrenderer);
    //Detach the texture
    SDL_SetRenderTarget(wrenderer, NULL);

    SDL_RenderClear(wrenderer);
    SDL_RenderPresent(wrenderer);
}

int BK::update() {
    return processor.update();
}

void BK::start() {
    std::cout << "BK is starting ..." << std::endl;
    this->init();
    
    this->isProcessing = true;
    const std::clock_t frame = 0l;

    while(this->isProcessing) {
        // begin frame
        std::clock_t c_start = std::clock();
        
        this->processInput();
        //*
        if (processor.irq) {
            processor.handleIRQ();
        }

        if (this->update() != 0) {
            std::cout << "NON legal operation" << std::endl;
            this->isProcessing = false;
        }

        if (needToUpdateScreen) {
            this->render();
            needToUpdateScreen = false;   
            std::cout << "RENDEREDDD" << std::endl;
        }
        //*/
        
        // end frame
        std::clock_t c_end = std::clock();
        std::clock_t diff = frame - c_end + c_start;
        
        // delay
        if (diff < 0) diff = 0;
        usleep(diff);
        
    }

    printAllRegisters();

    SDL_DestroyTexture(texTarget);
    SDL_DestroyRenderer(wrenderer);
    wrenderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

void BK::processInput() {

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
    //while (SDL_WaitEvent(&e)) {
        if (e.type == SDL_QUIT) {
            this->isProcessing = false;
            break;
        }

        if (e.type == SDL_KEYDOWN) {
            SDL_Keysym ks = e.key.keysym;
            unsigned char key;
            
            SDL_Keycode k = ks.sym;

            if ((shiftKeys[k] != 0) && ((ks.mod & KMOD_SHIFT) != 0) ) {
                k = shiftKeys[k];
            }

            //*
            if (keys[k] != (BK_KEYS)0) {
                key = (unsigned char)keys[k];
            } else {
                key = k & 0xff;
            }
            //*/

            std::cout << "---------KEYDOWN-------------------" << std::endl;
            std::cout << "key.keysym.sym: 0x" << std::hex << ks.sym << " " << (char)( ks.sym) << std::endl;
            //std::cout << "key.keysym.scancode: 0x" << std::hex << ks.scancode << " " << (char)(0xff & ks.scancode) << std::endl;
            std::cout << "key.keysym.mod: 0x" << std::hex << ks.mod << std::endl;
            //std::cout << "type: 0x" << std::hex << e.key.type << std::endl;
            //std::cout << "text: " << e.text.text << std::endl;
            std::cout << "----------------------------" << std::endl;
            
            if (k != SDLK_LSHIFT && k != SDLK_RSHIFT) {
            //if ( (k & 0x40000000) == 0 ) {
                if (ks.mod & KMOD_SHIFT) {
                    if (key >= 'a' && key <= 'z') {
                        key -= 0x20;
                    }
                }
                
                keyboard.pressKey(key);
                
            } 
            /*
            if (ks.mod & KMOD_CTRL) {
                
            }
            //key &= 0xff;
            std::cout << "key: 0x" << std::hex << key << std::endl;
            if (key >= 'a' && key <= 'z') {
                if (ks.mod & KMOD_SHIFT) {
                    key -= 0x20;
                    std::cout << "Shift: 0x" << std::hex << key << std::endl;
                }
            } else if (key == SDLK_RETURN || key == SDLK_RETURN2 || key == SDLK_KP_ENTER) {
                key = 0x0a;
            } else if (key >= '0' && key <= '9') {
                if (ks.mod & KMOD_SHIFT) {
                    if(key == '0') {
                        key = 0x7b;
                    } else {
                        key -= 0x10;
                    }
                }
            } else if (key == SDLK_KP_SPACE || key == SDLK_SPACE) { // space
                key = 0x20;
            } else if (key == SDLK_UP) { //
                key = 0x1a;
            } else if (key == SDLK_DOWN) { //
                key = 0x1b;
            } else if (key == SDLK_LEFT) { //
                key = 0x8;
            } else if (key == SDLK_RIGHT) { //
                key = 0x19;
            } else if (key == SDLK_EQUALS || key == SDLK_MINUS) { //
            
            } else if (key == SDLK_BACKSPACE) { // backspace
                key = 0x18;
            } else {
                std::cout << "NO HANDLE" << std::endl;
                return;
            }
            //*/

            

            /*
            if(key == 'q') {
                this->isProcessing = false;
            } else if (key == 'z') {
                break;
            } else if (key == 'p') {
                printAllRegisters();
            } else {
                keyboard.pressKey(key);
            }
            //*/
        }

        /*
         if (e.type == SDL_TEXTINPUT) {
            SDL_Keysym ks = e.key.keysym;
            
            std::cout << "---------TEXTINPUT-------------------" << std::endl;
            std::cout << "key.keysym.sym: 0x" << std::hex << ks.sym << " " << (uint8_t)(0xff & ks.sym) << std::endl;
            std::cout << "key.keysym.scancode: 0x" << std::hex << ks.scancode << " " << (uint8_t)(0xff & ks.scancode) << std::endl;
            std::cout << "key.keysym.mod: 0x" << std::hex << ks.mod << std::endl;
            std::cout << "type: 0x" << std::hex << e.key.type << std::endl;
            std::cout << "text: " << e.text.text << std::endl;
            std::cout << "----------------------------" << std::endl;
         }
        //*/
    }
}

void BK::printAllRegisters() {
    // print all registers
    for (int i = 0; i < REGISTERS_SIZE; i++) {
        std::cout << "R[" << i << "] : 0x" << std::hex << std::setfill('0') << std::setw(4) << processor.readWord(i);
        std::cout << " oct: " << std::oct << std::setfill('0') << std::setw(6) << processor.readWord(i) << std::endl;
    }
    
    // print flags
    std::cout << "PC : 0x" << std::hex << std::setfill('0') << std::setw(4) << processor.getPC() << std::endl;
    std::cout << "SP : 0x" << std::hex << std::setfill('0') << std::setw(4) << processor.getSP() << std::endl;
    std::cout << "Z:" << processor.getBitZ() << " C:" << processor.getBitC() << " V:" << processor.getBitV();
    std::cout << " N:" << processor.getBitN() << " T:" << processor.getBitT() << " P:" << processor.getBitP() << std::endl;

    // print bk registers 177600 - 177777 
    for (uint16_t i = 0177600; i != 0; i += 2) {
        std::cout  << std::oct << i << ": " << std::setfill('0') << std::setw(6) << bus.readWord(i) << std::endl;	
    }

    // print bk begin memory 0 - 320 
    for (uint16_t i = 0; i != 0000320; i += 2) {
        std::cout  << std::setfill('0') << std::setw(6) << std::oct << i << ": " << std::setfill('0') << std::setw(6) << bus.readWord(i) << std::endl;	
    }
}

void BK::render() {
    //Now render to the texture
    SDL_SetRenderTarget(wrenderer, texTarget);
    // write points here
    uint16_t videoBegin = 0040000;
    const uint16_t DOTS_IN_BYTE = 8;
    const uint16_t BYTES_IN_LINE = 512 / DOTS_IN_BYTE;
        
    SDL_SetRenderDrawColor(wrenderer, 0, 55, 255, 255);

    while(addrs.size()) {
        uint16_t address = addrs.back();
        uint16_t temp = address - videoBegin;
        uint16_t y = temp / BYTES_IN_LINE;
        uint16_t x = (temp - y * BYTES_IN_LINE) * DOTS_IN_BYTE;
        uint8_t operand = bus.readByte(address);
        uint8_t sel = 1;//(1 << (8/DOTS_IN_BYTE)) - 1;

        for (int j = 0; j < DOTS_IN_BYTE; j++) {
            if ((operand & sel) != 0) {
                SDL_SetRenderDrawColor(wrenderer, 0, 55, 255, 255);
            } else {
                SDL_SetRenderDrawColor(wrenderer, 10, 10, 10, 255);
            }
            SDL_RenderDrawPoint(wrenderer, x+j, y);
            sel <<= 1;//(8/DOTS_IN_BYTE);
        }

        addrs.pop_back();
    }

    //Detach the texture
    SDL_SetRenderTarget(wrenderer, NULL);

    SDL_RenderCopy(wrenderer, texTarget, NULL, NULL);
    SDL_RenderPresent(wrenderer);
}

void BK::keyboardMapping() {
    keys[SDLK_DOWN] = BK_KEYS::DOWN;
    keys[SDLK_UP] = BK_KEYS::UP;
    keys[SDLK_LEFT] = BK_KEYS::LEFT;
    keys[SDLK_RIGHT] = BK_KEYS::RIGHT;
    keys[SDLK_RETURN] = BK_KEYS::ENTER;
    keys[SDLK_BACKSPACE] = BK_KEYS::BACKSPACE;
    
    keys[SDLK_LCTRL] = BK_KEYS::RUS;
    keys[SDLK_RCTRL] = BK_KEYS::LAT;
    keys[SDLK_KP_LEFTBRACE] = BK_KEYS::LEFTBRACE;
    keys[SDLK_KP_RIGHTBRACE] = BK_KEYS::RIGHTBRACE;
    keys[SDLK_KP_VERTICALBAR] = BK_KEYS::VERTICALBAR;
    
    //*
    shiftKeys[SDLK_SLASH] = SDLK_QUESTION;
    shiftKeys[SDLK_1] = SDLK_EXCLAIM;
    shiftKeys[SDLK_2] = SDLK_AT;
    shiftKeys[SDLK_3] = SDLK_HASH;
    shiftKeys[SDLK_4] = SDLK_DOLLAR;
    shiftKeys[SDLK_5] = SDLK_PERCENT;
    shiftKeys[SDLK_6] = SDLK_CARET;
    shiftKeys[SDLK_7] = SDLK_AMPERSAND;
    shiftKeys[SDLK_8] = SDLK_ASTERISK;
    shiftKeys[SDLK_9] = SDLK_LEFTPAREN;
    shiftKeys[SDLK_0] = SDLK_RIGHTPAREN;
    shiftKeys[SDLK_MINUS] = SDLK_UNDERSCORE;
    shiftKeys[SDLK_EQUALS] = SDLK_PLUS;
    shiftKeys[SDLK_SEMICOLON] = SDLK_COLON;
    shiftKeys[SDLK_QUOTE] = SDLK_QUOTEDBL;
    shiftKeys[SDLK_LEFTBRACKET] = SDLK_KP_LEFTBRACE;
    shiftKeys[SDLK_RIGHTBRACKET] = SDLK_KP_RIGHTBRACE;
    shiftKeys[SDLK_BACKSLASH] = SDLK_KP_VERTICALBAR;
    
    //*/
}
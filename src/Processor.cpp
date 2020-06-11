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


#include "Processor.h"
#include <iomanip>
#include <iostream>

#include "operations/NonLegalOperation.h"
#include "operations/JmpOperation.h"
#include "operations/SobOperation.h"
#include "operations/JsrOperation.h"
#include "operations/RetOperation.h"

#include "operations/ClrOperation.h"
#include "operations/ClrbOperation.h"
#include "operations/ComOperation.h"
#include "operations/CombOperation.h"
#include "operations/IncOperation.h"
#include "operations/IncbOperation.h"
#include "operations/DecOperation.h"
#include "operations/DecbOperation.h"
#include "operations/NegOperation.h"
#include "operations/NegbOperation.h"
#include "operations/AdcOperation.h"
#include "operations/AdcbOperation.h"
#include "operations/SbcOperation.h"
#include "operations/SbcbOperation.h"
#include "operations/TstOperation.h"
#include "operations/TstbOperation.h"
#include "operations/RorOperation.h"
#include "operations/RorbOperation.h"
#include "operations/RolOperation.h"
#include "operations/RolbOperation.h"
#include "operations/AsrOperation.h"
#include "operations/AsrbOperation.h"
#include "operations/AslOperation.h"
#include "operations/AslbOperation.h"
#include "operations/SxtOperation.h"

#include "operations/MovOperation.h"
#include "operations/MovbOperation.h"
#include "operations/CmpOperation.h"
#include "operations/CmpbOperation.h"
#include "operations/BitOperation.h"
#include "operations/BitbOperation.h"
#include "operations/BicOperation.h"
#include "operations/BicbOperation.h"
#include "operations/BisOperation.h"
#include "operations/BisbOperation.h"
#include "operations/AddOperation.h"
#include "operations/SubOperation.h"

#include "operations/BrOperation.h"
#include "operations/BneOperation.h"
#include "operations/BeqOperation.h"
#include "operations/BplOperation.h"
#include "operations/BmiOperation.h"
#include "operations/BvcOperation.h"
#include "operations/BvsOperation.h"
#include "operations/BccOperation.h"
#include "operations/BcsOperation.h"
#include "operations/BgeOperation.h"
#include "operations/BltOperation.h"
#include "operations/BgtOperation.h"
#include "operations/BleOperation.h"
#include "operations/BhiOperation.h"
#include "operations/BlosOperation.h"

#include "operations/CompositeOperation.h"
#include "operations/CccOperation.h"
#include "operations/SccOperation.h"
#include "operations/EmtOperation.h"
#include "operations/TrapOperation.h"
#include "operations/BptOperation.h"
#include "operations/IotOperation.h"
#include "operations/RtiOperation.h"
#include "operations/HaltOperation.h"
#include "operations/SwabOperation.h"
#include "operations/MtpsOperation.h"
#include "operations/XorOperation.h"
#include "operations/ResetOperation.h"


Processor::Processor() : operations(1024) {
    BaseOperation *illegalop = new NonLegalOperation(this);
    // in the beginning, all operations are illegal
    for (auto &op : operations) {
        op = illegalop;
    }

    ///////////////////////////////////////////////////////////////////

    CompositeOperation* compOp = new CompositeOperation(this, 64, 077);
    operations[00000] = compOp;

    for (int i = 0; i < 64; i++) {
        compOp->addOperation(illegalop, i);
    }

    compOp->addOperation(new HaltOperation(this), 0);
    compOp->addOperation(new RtiOperation(this), 2);
    compOp->addOperation(new BptOperation(this), 3);
    compOp->addOperation(new IotOperation(this), 4);
    compOp->addOperation(new ResetOperation(this), 5);

    ///////////////////////////////////////////////////////////////////

    operations[00001] = new JmpOperation(this);

    ///////////////////////////////////////////////////////////////////

    compOp = new CompositeOperation(this, 8, 070);
    operations[00002] = compOp;

    compOp->addOperation(new RetOperation(this), 0);
    for (int i = 1; i < 4; i++) {
        compOp->addOperation(illegalop, i << 3);
    }
    BaseOperation *op = new CccOperation(this);
    compOp->addOperation(op, 040);
    compOp->addOperation(op, 050);
    op = new SccOperation(this);
    compOp->addOperation(op, 060);
    compOp->addOperation(op, 070);
    
    ///////////////////////////////////////////////////////////////////

    operations[00003] = new SwabOperation(this);

    // branch operations
    addOperation(new BrOperation(this), 00004, 00010);
    addOperation(new BneOperation(this), 00010, 00014);
    addOperation(new BeqOperation(this), 00014, 00020);
    addOperation(new BgeOperation(this), 00020, 00024);
    addOperation(new BltOperation(this), 00024, 00030);
    addOperation(new BgtOperation(this), 00030, 00034);
    addOperation(new BleOperation(this), 00034, 00040);

    addOperation(new SobOperation(this), 00770, 01000);

    addOperation(new BplOperation(this), 01000, 01004);
    addOperation(new BmiOperation(this), 01004, 01010);
    addOperation(new BhiOperation(this), 01010, 01014);
    addOperation(new BlosOperation(this), 01014, 01020);
    addOperation(new BvcOperation(this), 01020, 01024);
    addOperation(new BvsOperation(this), 01024, 01030);
    addOperation(new BccOperation(this), 01030, 01034);
    addOperation(new BcsOperation(this), 01034, 01040);

    // subroutine
    addOperation(new JsrOperation(this), 00040, 00050);
    // interrupts
    addOperation(new EmtOperation(this), 01040, 01044);
    addOperation(new TrapOperation(this), 01044, 01050);

    // one operand operations
    operations[00050] = new ClrOperation(this);
    operations[01050] = new ClrbOperation(this);
    operations[00051] = new ComOperation(this);
    operations[01051] = new CombOperation(this);
    operations[00052] = new IncOperation(this);
    operations[01052] = new IncbOperation(this);
    operations[00053] = new DecOperation(this);
    operations[01053] = new DecbOperation(this);
    operations[00054] = new NegOperation(this);
    operations[01054] = new NegbOperation(this);
    operations[00055] = new AdcOperation(this);
    operations[01055] = new AdcbOperation(this);
    operations[00056] = new SbcOperation(this);
    operations[01056] = new SbcbOperation(this);
    operations[00057] = new TstOperation(this);
    operations[01057] = new TstbOperation(this);
    operations[00060] = new RorOperation(this);
    operations[01060] = new RorbOperation(this);
    operations[00061] = new RolOperation(this);
    operations[01061] = new RolbOperation(this);
    operations[00062] = new AsrOperation(this);
    operations[01062] = new AsrbOperation(this);
    operations[00063] = new AslOperation(this);
    operations[01063] = new AslbOperation(this);
    operations[01064] = new MtpsOperation(this);
    operations[00067] = new SxtOperation(this);

    // two operand operations
    addOperation(new MovOperation(this), 00100, 00200);
    addOperation(new MovbOperation(this), 01100, 01200);
    addOperation(new CmpOperation(this), 00200, 00300);
    addOperation(new CmpbOperation(this), 01200, 01300);
    addOperation(new BitOperation(this), 00300, 00400);
    addOperation(new BitbOperation(this), 01300, 01400);
    addOperation(new BicOperation(this), 00400, 00500);
    addOperation(new BicbOperation(this), 01400, 01500);
    addOperation(new BisOperation(this), 00500, 00600);
    addOperation(new BisbOperation(this), 01500, 01600);
    addOperation(new AddOperation(this), 00600, 00700);
    addOperation(new SubOperation(this), 01600, 01700);

    addOperation(new XorOperation(this), 00740, 00750);
}

void Processor::init(Bus *bus) {
    this->bus = bus;

    uint16_t sysReg;
    // = memory->readWord(0177716);
    sysReg = 0100000;
    pc = sysReg & 0177400;
    this->psw = 0340;
    //bus->writeWord(0177664, 01330);
}

void Processor::addOperation(BaseOperation *op, uint16_t fromOpcode, uint16_t toOpcode) {
    for (uint16_t i = fromOpcode; i < toOpcode; i++) {
        operations[i] = op;
    }
}

uint16_t Processor::getCurrentInstruction() {
    return currentInstruction;
}

uint16_t Processor::getPC() {
    return this->pc;
}

void Processor::setPC(uint16_t pc) {
    this->pc = pc;
}

uint16_t Processor::getSP() {
    return this->sp;
}

void Processor::setSP(uint16_t sp) {
    this->sp = sp;
}

uint16_t Processor::getPSW() {
    return this->psw;
}

void Processor::setPSW(uint16_t psw) {
    this->psw = psw;
}

IReadWrite *Processor::getBus() {
    return this->bus;
}

int Processor::update() {
    uint16_t current = pc;
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "pc    : 0x" << std::hex << std::setfill('0') << std::setw(4) << +pc << std::endl;
    std::cout << "pc oct: " << std::oct << std::setfill('0') << std::setw(6) << pc << std::endl;
    currentInstruction = bus->readWord(pc);
    pc += 2;
    std::cout << "instruction:0x" << std::hex << std::setfill('0') << std::setw(4) << +currentInstruction << std::endl;
    std::cout << "instruction oct: " << std::oct << std::setfill('0') << std::setw(6) << +currentInstruction << std::endl;

    // instruction decoding
    uint16_t opcode = currentInstruction >> 6;
    std::cout << "opcode oct: " << std::oct << std::setfill('0') << std::setw(4) << opcode << std::endl;
    BaseOperation *op = operations[opcode];
    if (dynamic_cast<NonLegalOperation*>(op) != nullptr) {
        return 1;
    } else {
        
    }
    op->execute();
    /*
    if ((dynamic_cast<RetOperation*>(op) != nullptr) || (dynamic_cast<RtiOperation*>(op) != nullptr)) {
        // print all registers
        for (int i = 0; i < REGISTERS_SIZE; i++) {
            std::cout << "R[" << i << "] : 0x" << std::hex << std::setfill('0') << std::setw(4) << readWord(i);
            std::cout << " oct: " << std::oct << std::setfill('0') << std::setw(6) << readWord(i) << std::endl;
        }
        
        // print flags
        std::cout << "PC : 0x" << std::hex << std::setfill('0') << std::setw(4) << getPC() << std::endl;
        std::cout << "SP : 0x" << std::hex << std::setfill('0') << std::setw(4) << getSP() << std::endl;
        std::cout << "Z:" << getBitZ() << " C:" << getBitC() << " V:" << getBitV();
        std::cout << " N:" << getBitN() << " T:" << getBitT() << " P:" << getBitP() << std::endl;
        //*
        // print bk registers 177600 - 177777 
        for (uint16_t i = 0177600; i != 0; i += 2) {
            std::cout  << std::oct << i << ": " << std::setfill('0') << std::setw(6) << bus->readWord(i) << std::endl;	
        }

        // print bk begin memory 0 - 320 
        for (uint16_t i = 0; i != 0000320; i += 2) {
            std::cout  << std::setfill('0') << std::setw(6) << std::oct << i << ": " << std::setfill('0') << std::setw(6) << bus->readWord(i) << std::endl;	
        }
        // * /
    } else {
        std::cout << "NOT RET OR RTI" << std::endl;
    }
    //*/
    return 0;
}

uint16_t Processor::getModAddress(uint16_t mod, uint16_t reg) {
    uint16_t address = 0;
    uint16_t operand = 0;

    switch (mod) {
    case 0: // a register contains the operand
        address = reg;
        break;
    case 1: // a register contains the address of the operand
        address = registers[reg];
        break;
    case 2: // like case 1, but it increments the register
            // after operation by 2(word) or by 1(byte)
        address = registers[reg];
        registers[reg] += 2; // for word
        break;
    case 3: // a register contains the address on the pointer on the operand
            // it increments the register after operation by 2
        address = bus->readWord(registers[reg]);
        registers[reg] += 2; // only word
        break;
    case 4:					 // like the case 2, only decrement before operation
        registers[reg] -= 2; // for word
        address = registers[reg];
        break;
    case 5:					 // like the case 3, only decrement before operation
        registers[reg] -= 2; // only word
        address = bus->readWord(registers[reg]);
        break;
    case 6: // here we use addition the register and the immediate operand
        operand = bus->readWord(pc);
        pc += 2;
        address = registers[reg] + operand;
        break;
    case 7: // like 6, but in addition it contains a pointer on the operand
        operand = bus->readWord(pc);
        pc += 2;
        address = registers[reg] + operand;
        address = bus->readWord(address);
        break;
    default:
        // error
        break;
    }

    return address;
}

uint16_t Processor::getModAddressByte(uint16_t mod, uint16_t reg) {
    uint16_t address = 0;
    uint16_t operand = 0;

    switch (mod) {
    case 0: // a register contains the operand
        address = reg;
        break;
    case 1: // a register contains the address of the operand
        address = registers[reg];
        break;
    case 2: // like case 1, but it increments the register
            // after operation by 2(word) or by 1(byte)
        address = registers[reg];
        registers[reg] += 1 + (reg >= 6); // for byte
        break;
    case 3: // a register contains the address on the pointer on the operand
            // it increments the register after operation by 2
        address = bus->readWord(registers[reg]);
        registers[reg] += 2; // only word
        break;
    case 4:					 // like the case 2, only decrement before operation
        registers[reg] -= 1  + (reg >= 6); // for byte
        address = registers[reg];
        break;
    case 5:					 // like the case 3, only decrement before operation
        registers[reg] -= 2; // only word
        address = bus->readWord(registers[reg]);
        break;
    case 6: // here we use addition the register and the immediate operand
        operand = bus->readWord(pc);
        pc += 2;
        address = registers[reg] + operand;
        break;
    case 7: // like 6, but in addition it contains a pointer on the operand
        operand = bus->readWord(pc);
        pc += 2;
        address = registers[reg] + operand;
        address = bus->readWord(address);
        break;
    default:
        // error
        break;
    }

    return address;
}

// PSW Bits methods

void Processor::setBitC() {
    psw |= PSW_C;
}

void Processor::setBitV() {
    psw |= PSW_V;
}

void Processor::setBitZ() {
    psw |= PSW_Z;
}

void Processor::setBitN() {
    psw |= PSW_N;
}

void Processor::setBitT() {
    psw |= PSW_T;
}

void Processor::setBitP() {
    psw |= PSW_P;
}

void Processor::clearBitC() {
    psw &= ~PSW_C;
}

void Processor::clearBitV() {
    psw &= ~PSW_V;
}

void Processor::clearBitZ() {
    psw &= ~PSW_Z;
}

void Processor::clearBitN() {
    psw &= ~PSW_N;
}

void Processor::clearBitT() {
    psw &= ~PSW_T;
}

void Processor::clearBitP() {
    psw &= ~PSW_P;
}

uint16_t Processor::getBitC() {
    return (psw & PSW_C) != 0;
}

uint16_t Processor::getBitV() {
    return (psw & PSW_V) != 0;
}

uint16_t Processor::getBitZ() {
    return (psw & PSW_Z) != 0;
}

uint16_t Processor::getBitN() {
    return (psw & PSW_N) != 0;
}

uint16_t Processor::getBitT() {
    return (psw & PSW_T) != 0;
}

uint16_t Processor::getBitP() {
    return (psw & PSW_P) != 0;
} // PSW Bits methods END

// implementation of IReadWrite
uint16_t Processor::readWord(uint16_t address) {
    return registers[address & 0x7];
}

void Processor::writeWord(uint16_t address, uint16_t data) {
    //std::cout << "WRITE DATA TO REGISTER" << std::endl;
    registers[address & 0x7] = data;
}

uint8_t Processor::readByte(uint16_t address) {
    return registers[address & 0x7] & 0xff;
}

void Processor::writeByte(uint16_t address, uint8_t data) {
    address &= 0x7; // can't be more R7
    
    // check negative sign
    if (data & 0x80) {
        registers[address] &= 0xff00;
    } else {
        registers[address] = 0;
    }
    
    registers[address] |= data;
} // implementation of IReadWrite END

void Processor::handleIRQ() {
    std::cout << "==============================" << std::endl;
    std::cout << "  HANDLE IRQ" << std::endl;

    // check PSW interrupt bit
    if (psw & 0x0080) {
        // forbitten
        irq = 0;
        return;
    }

    // priority need
    switch(irq) {
        case 060:
        case 0274: {
            // keyboard
            IReadWrite* memory = this->getBus();
            
            sp -= 2;
            memory->writeWord(sp, psw);
            
            sp -= 2;
            memory->writeWord(sp, pc);

            pc = memory->readWord(irq);
            psw = memory->readWord(irq + 2);
            break; 
        }
        default:
            break;
    }

    irq = 0;

    
}
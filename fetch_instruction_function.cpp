#include "CPU_n_Memory_structures.h"
#include <iostream>
using namespace std;

byte CPU::fetch_instruction(Memory& mem, int& cycles)
{
	byte instruction_opcode = mem.memory[PC];
	switch (instruction_opcode)
	{
	case INS_LDA_IMMEDIATE:
	{
		cycles = 2;
		break;
	}
	case INS_LDA_ZEROPAGE:
	{
		cycles = 3;
		break;
	}
	case INS_LDA_ZEROPAGEX:
	{
		cycles = 4;
		break;
	}
	case INS_LDA_ABSOLUTE:
	{
		cycles = 4;
		break;
	}
	case INS_STA_ZEROPAGE:
	{
		cycles = 3;
		break;
	}
	case INS_STA_ZEROPAGEX:
	{
		cycles = 4;
		break;
	}
	case INS_STA_ABSOLUTE:
	{
		cycles = 4;
		break;
	}
	case INS_STA_ABSOLUTEX:
	{
		cycles = 5;
		break;
	}
	default:
	{
		std::cout << "Instruction not handled" << std::endl;
		exit(-1);
		break;
	}
	}
	cycles--;
	return instruction_opcode;
}
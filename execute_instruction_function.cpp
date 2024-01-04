#include "CPU_n_Memory_structures.h"
#include <iostream>
using namespace std;

void CPU::execute_instruction(Memory& mem, byte reg_instruction, int& cycles)
{
	switch (reg_instruction)
	{
	case INS_LDA_IMMEDIATE:
	{
		// LDA in immediate addressing mode
		while (cycles != 0)
		{
			reg_AC = fetch_data(mem);
			flag_Z = (reg_AC == 0);
			flag_N = (reg_AC & 0b10000000) > 0;
			cycles--;
			PC++;
		}
		CPU::invertReadingFlags();
		break;
	}
	case INS_LDA_ZEROPAGE:
	{
		while (cycles != 0)
		{
			byte zeropage_address = fetch_data(mem);
			cycles--;
			reg_AC = mem.memory[zeropage_address];
			cycles--;
			flag_N = (reg_AC == 0);
			flag_Z = (reg_AC & 0b10000000) > PC++;
		}
		CPU::invertReadingFlags();
		break;
	}
	case INS_LDA_ZEROPAGEX:
	{
		byte zeropage_address = fetch_data(mem);
		cycles--;
		cycles--; // This cycles-- is done because it reads the register to read from, in this case, it is reg_X
		reg_AC = mem.memory[zeropage_address + reg_X];
		cycles--;
		flag_N = (reg_AC == 0);
		flag_Z = (reg_AC & 0b10000000) > 0;
		CPU::invertReadingFlags();
		break;
	}
	case INS_LDA_ABSOLUTE:
	{
		byte L2B = fetch_data(mem);
		byte F2B = fetch_data(mem);
		big_byte actual_address = (F2B << 8) + (L2B);
		cycles--;
		reg_AC = mem.memory[actual_address];
		cycles--;
		cycles--;
		flag_N = (reg_AC == 0);
		flag_Z = (reg_AC & 0b10000000) > 0;
		invertReadingFlags();
		break;
	}
	case INS_STA_ZEROPAGE:
	{
		while (cycles != 0)
		{
			byte address = fetch_data(mem);
			cycles--;
			mem.memory[address] = reg_AC;
			cycles--;
			PC++;
			// No flags are affected
		}
		CPU::invertReadingFlags();
		break;
	}
	case INS_STA_ZEROPAGEX:
	{
		while (cycles != 0)
		{
			byte address = fetch_data(mem);
			cycles--;
			mem.memory[address] = reg_X;
			cycles--;
			PC++;
			// No flags are affected
		}
		CPU::invertReadingFlags();
		break;
	}
	case INS_STA_ABSOLUTE:
	{
		while (cycles != 0)
		{
			byte LB = fetch_data(mem); // Last 2 digits in 16 bit HEX number
			cycles--;
			byte HB = fetch_data(mem); // First 2 digits in 16 bit HEX number
			cycles--;
			mem.memory[HB + LB] = reg_AC;
			cycles--;
			PC++;
			//No flags are affected
		}
		break;
	}
	}
}
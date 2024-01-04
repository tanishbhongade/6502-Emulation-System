#include "CPU_n_Memory_structures.h"
#include <iostream>

void Memory::makeMemoryZero() {
	for (int i = 0; i < MEMORY_BYTES; i++)
	{
		// Make each memory address as 0
		memory[i] = 0x00;
	}
}

void CPU::reset(Memory& mem)
{
	PC = 0xFFFC; // Initially, the PC gets resetted to the OxFFFC in the memory
	SP = 0x0000;
	flag_N = flag_V = flag_B = flag_D = flag_I = flag_Z = reg_AC = 0;
	mem.makeMemoryZero();
}

void CPU::invertReadingFlags()
{
	if (opcode_reading_status == true)
	{
		opcode_reading_status = false;
	}
	else
	{
		opcode_reading_status = true;
	}

	if (data_reading_status == true)
	{
		data_reading_status = false;
	}
	else
	{
		data_reading_status = true;
	}
}

byte CPU::fetch_data(Memory& mem) {
	byte data = mem.memory[PC];
	PC++;
	return data;
}

void CPU::run(int cycles, Memory& mem) {
	if (opcode_reading_status == true && data_reading_status == false)
	{
		reg_instruction = fetch_instruction(mem, cycles);
		PC++;
		CPU::invertReadingFlags();
	}
	//std::cout << "The value of instruction register is " << +reg_instruction << std::endl;
	if (opcode_reading_status == false && data_reading_status == true)
	{
		execute_instruction(mem, reg_instruction, cycles);
	}
}

void CPU::getCPUStatus() {
	std::cout << "A: " << +reg_AC << std::endl;
	std::cout << "Z: " << flag_Z << ", ";
	std::cout << "N: " << flag_N << " " << std::endl;
	std::cout << "PC: " << PC << ", ";
	std::cout << "SP: " << SP << " ";
	std::cout << std::endl
		<< std::endl;
}

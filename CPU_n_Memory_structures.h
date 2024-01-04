#pragma once
#pragma once
#include <cstdint>

using namespace std;
using byte = uint8_t; // Create an alias for 8-bit integer (Most prolly for CPU instructions)
using big_byte = uint16_t; // Create an alias for 16-bit integer (Most probably for addresses)
using bit = bool; // Create an alias for a bit

struct Memory {
	static constexpr unsigned int MEMORY_BYTES = 1024 * 64;

	// An 6502 can address 64K of memory hence we assigned that number in the square brackets
	uint8_t* memory = new byte[MEMORY_BYTES]; // Each location in 0 to 65535 can hold 8-bits of data

	void makeMemoryZero();
};

struct CPU {
	// The name of variables say their function
	byte reg_AC = 0;       // Accmulator
	byte reg_X, reg_Y = 0; // Registers
	big_byte PC = 0;       // Program counter
	big_byte SP = 0;       // Stack pointer
	byte reg_instruction; // Instruction register

	// Flag registers
	bit flag_N = 0;
	bit flag_V = 0;
	bit flag_B = 0;
	bit flag_D = 0;
	bit flag_I = 0;
	bit flag_Z = 0;
	bit flag_C = 0;

	bit opcode_reading_status = true;
	bit data_reading_status = false;

	static constexpr byte INS_LDA_IMMEDIATE = 0xA9; // LDA instruction with 0xA9 op-code
	static constexpr byte INS_LDA_ZEROPAGE = 0xA5;  // LDA instruction with 0xA5 op-code
	static constexpr byte INS_LDA_ZEROPAGEX = 0xB5; // LDA instruction with 0xB5 op-code
	static constexpr byte INS_LDA_ABSOLUTE = 0xAD; // LDA instruction with 0xAD op-code
	static constexpr byte INS_LDA_ABSOLUTEX = 0xBD;
	static constexpr byte INS_LDA_ABSOLUTEY = 0xB9;
	//static constexpr byte INS_LDA_

	static constexpr byte INS_STA_ZEROPAGE = 0x85;  // STA instruction with 0x85 op-code
	static constexpr byte INS_STA_ZEROPAGEX = 0x95; // STA instruction with 0x95 op-code
	static constexpr byte INS_STA_ABSOLUTE = 0x8D; // STA instruction with 0x8D op-code
	static constexpr byte INS_STA_ABSOLUTEX = 0x9D;

	void reset(Memory& mem);
	void invertReadingFlags();
	void run(int, Memory& mem);
	byte fetch_instruction(Memory& mem, int& cycles);
	byte fetch_data(Memory& mem);
	void execute_instruction(Memory& mem, byte reg_instruction, int& cycles);
	void getCPUStatus();
};
// printcpualert search it to remove getCPUStatus for debugging purposes

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include "CPU_n_Memory_structures.h"

using namespace std;

int main()
{
	CPU Computer;
	Memory MEM;
	Computer.reset(MEM);

	MEM.memory[0xFFFC] = CPU::INS_LDA_ABSOLUTE;
	MEM.memory[0xFFFD] = 0xCD;
	MEM.memory[0xFFFE] = 0xAB;
	MEM.memory[0xAB00 + 0xCD] = 0x0F;

	Computer.run(4, MEM);
	Computer.getCPUStatus();

	return 0;
}
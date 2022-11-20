#include <iostream>
#include "Memory.h"

struct offsets {
	uintptr_t entitylist = 0x10f4f8;
	uintptr_t localPlayer = 0x10f4f4;

	uintptr_t health = 0xF8;

	uintptr_t isPlayer = 0x10;
	uintptr_t name = 0x225;
} offsets;

typedef char ac_name[16];

int main()
{
	Memory mem("ac_client.exe");

	uintptr_t moduleBase = mem.GetModuleAddress("ac_client.exe");

	while (true) {
		if (GetAsyncKeyState(VK_END)) {
			break;
		}

		for (int i = 1; i < 32; i++) {
			auto entityList = mem.Read<uintptr_t>(moduleBase + offsets.entitylist);
			auto curEnt = mem.Read<uintptr_t>(entityList + (uintptr_t)(i * 0x4));
			auto isPlayer = mem.Read<uintptr_t>(curEnt + offsets.isPlayer);
			if (curEnt != 0x00000000 && isPlayer == 0) {
				auto health = mem.Read<int>(curEnt + offsets.health);
				if (health != 0x00000000)
				{
					char* name = mem.ReadString(curEnt + offsets.name);
					printf("%s ", name);
					std::cout << std::dec << health << " at index " << std::hex << (uintptr_t)(i * 0x4) << "\n";
					Sleep(500);
				}
			}
		}
		Sleep(1);
	}

	return 0;
}
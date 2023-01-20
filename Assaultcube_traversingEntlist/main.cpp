#include <iostream>
#include "Memory.h"
#include "Entity.h"
#include <cstddef>
struct offsets {
	uintptr_t entitylist = 0x10f4f8;
	uintptr_t localPlayer = 0x10f4f4;

	uintptr_t health = 0xF8;

	uintptr_t isPlayer = 0x10;
	uintptr_t name = 0x225;

	uintptr_t entCount = 0x10F500;
} offsets;

typedef char ac_name[16];

int main()
{
	Memory mem("ac_client.exe");
	Entity ent = { 0 };
	uintptr_t moduleBase = mem.GetModuleAddress("ac_client.exe");

	while (true) {
		if (GetAsyncKeyState(VK_END)) {
			break;
		}

		//uintptr_t lpPtr = mem.Read<uintptr_t>(moduleBase + offsets.localPlayer);

		//Entity localPlayer = mem.Read<Entity>(lpPtr);

		int entityCount = mem.Read<int>(moduleBase + offsets.entCount);
		auto entityList = mem.Read<uintptr_t>(moduleBase + offsets.entitylist);
		for (int i = 1; i < entityCount; i++) {
			uintptr_t curEntPtr = mem.Read<uintptr_t>(entityList + (uintptr_t)(i * 0x4));
			Entity curEnt = mem.Read<Entity>(curEntPtr);
			auto isPlayer = curEnt.isPlayer;

			auto health = curEnt.health;
			std::cout << "health of ent " << i << " : ( " << curEnt.Name << ") " << health << std::endl;
		}

		//auto localPlayer = mem.Read<uintptr_t>(moduleBase + offsets.localPlayer);

		//DWORD ptr;
		//BYTE buffer[0x1000];
		//ptr = mem.Read<DWORD>(moduleBase + offsets.localPlayer); // local player location
		//ReadProcessMemory(mem.processHandle, (LPCVOID)ptr, &buffer, 0x1000, NULL); // read 1000 bytes from local player location forwards into buffer
		//int health1 = *(int*)((DWORD)buffer + offsetof(Entity, health)); // health is just the offset forwards into this buffer

		//for (int i = 1; i < 32; i++) {
		//	auto entityList = mem.Read<uintptr_t>(moduleBase + offsets.entitylist);
		//	auto curEnt = mem.Read<uintptr_t>(entityList + (uintptr_t)(i * 0x4));
		//	auto isPlayer = mem.Read<uintptr_t>(curEnt + offsets.isPlayer);
		//	if (curEnt != 0x00000000 && isPlayer == 0) {
		//		auto health = mem.Read<int>(curEnt + offsets.health);
		//		if (health != 0x00000000)
		//		{
		//			char* name = mem.ReadString(curEnt + offsets.name);
		//			printf("%s ", name);
		//			std::cout << std::dec << health << " at index " << std::hex << (uintptr_t)(i * 0x4) << "\n";
		//			Sleep(500);
		//		}
		//	}
		//}
		Sleep(1);
	}

	return 0;
}
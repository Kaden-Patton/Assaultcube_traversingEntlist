#pragma once

class Entity {
public:
	char pad_0000[16]; //0x0000
	int isPlayer; //0x0010
	char pad_0014[228]; //0x0014
	int health; //0x00F8
	char pad_00FC[296]; //0x00FC
	char padding; //0x0224
	char Name[16]; //0x0225
};
#pragma once
#include "common.h"
#include "mod.h"

class CMemoryMod : public CMod
{
public:
	CMemoryMod() : CMod( "Memory Mod" ) {}
private:
	void Main() override;
	void Think() override;
};
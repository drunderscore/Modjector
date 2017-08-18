#pragma once
#include "common.h"
#include "mod.h"

class CTestMod : public CMod
{
public:
	CTestMod() : CMod( "Test Mod" ) {}
	void Main() override;
	void Think() override;
};
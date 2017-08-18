#pragma once
#include "common.h"

class CMod
{
public:
	CMod( std::string name ) { this->name = name; }

	std::string GetName() { return name; }
	void Start();
private:
	std::string name;
	virtual void Think() {};
	virtual void Main() {};
};

static void __stdcall StartMod( CMod *mod )
{
	if( mod == nullptr || mod == NULL )
	{
		fprintf( GetConsoleOutput(), "Attempted to start an invalid mod. Not starting!\n" );
		return;
	}
	mod->Start();
}
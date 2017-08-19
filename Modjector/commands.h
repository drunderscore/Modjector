#pragma once
#include "common.h"
#include "mod.h"
#include "convar.h"
#include <map>

typedef void( *CmdPtr )(std::vector<std::string>);
std::map<std::string, CmdPtr> GetCommands();
std::map<std::string, CConvar> GetConvars();

void AddCommand( std::string cmd, CmdPtr func );
bool RunCommand( std::string cmd, std::vector<std::string> args );
void AddConvar( std::string name, std::string initialValue );
bool ConvarExists( std::string name );

class CCommandsMod : public CMod
{
public:
	CCommandsMod() : CMod( "Command Mod" ) {}
private:
	void Main() override;
	void Think() override;
};

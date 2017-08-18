#include "common.h"
#include "commands.h"
#include "command_list.h"
std::map<std::string, CmdPtr> commands;
std::map<std::string, Convar> convars;

std::map<std::string, CmdPtr> GetCommands()
{
	return commands;
}

std::map<std::string, Convar> GetConvars()
{
	return convars;
}

void AddCommand( std::string cmd, CmdPtr func )
{
	commands[cmd] = func;
}

bool ConvarExists( std::string name )
{
	return convars.find( name ) != convars.end();
}

int GetConvarValue( std::string name )
{
	if( !ConvarExists( name ) )
		throw std::invalid_argument( "Invalid convar name" );
	return convars[name].value;
}

void AddConvar( std::string name, int initialValue )
{
	Convar cvar;
	cvar.name = name;
	cvar.defaultValue = initialValue;
	cvar.value = initialValue;
	convars[name] = cvar;
}

bool RunCommand( std::string cmd, std::vector<std::string> args )
{
	if( commands.find( cmd ) == commands.end() )
		return false;
	return commands[cmd]( args );
}

std::vector<std::string> Split( std::string str, std::string sep )
{
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	std::vector<std::string> arr;
	current = strtok( cstr, sep.c_str() ); // TODO: Not secure mate. Fix this shit.
	while( current != NULL )
	{
		arr.push_back( current );
		current = strtok( NULL, sep.c_str() ); // TODO: Not secure mate. Fix this shit.
	}
	return arr;
}

std::string Trim( std::string& str )
{
	size_t first = str.find_first_not_of( ' ' );
	if( first == std::string::npos )
		return "";
	size_t last = str.find_last_not_of( ' ' );
	return str.substr( first, (last - first + 1) );
}

void CCommandsMod::Main()
{
	RegisterConsoleCommands();
	fprintf( GetConsoleOutput(), "There are %d commands and %d convars available.\n", GetCommands().size(), GetConvars().size() );
}
void CCommandsMod::Think()
{
	std::string line;
	std::getline( std::cin, line );
	if( Trim( line ).empty() )
		return;
	std::vector<std::string> args = Split( line, " " );
	bool ret = RunCommand( args[0], args );
	if( !ret )
	{
		if( !ConvarExists( args[0] ) )
			fprintf( GetConsoleOutput(), "Unknown command \"%s\"\n", args[0].c_str() );
		else
		{
			Convar cvar = convars[args[0]];
			if( args.size() >= 2 )
				convars[args[0]].value = atoi( args[1].c_str() );
			else
				if( cvar.value == cvar.defaultValue )
					fprintf( GetConsoleOutput(), "\"%s\" = \"%d\"\n", args[0].c_str(), cvar.value );
				else
					fprintf( GetConsoleOutput(), "\"%s\" = \"%d\" (def. \"%d\")\n", args[0].c_str(), cvar.value, cvar.defaultValue );
		}
	}
}
#include "common.h"
#include "commands.h"
#include "command_list.h"

std::map<std::string, CmdPtr> commands;
std::map<std::string, CConvar> convars;

std::map<std::string, CmdPtr> GetCommands()
{
	return commands;
}

std::map<std::string, CConvar> GetConvars()
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

void AddConvar( std::string name, std::string defValue )
{
	convars[name] = CConvar( name, defValue );
}

bool RunCommand( std::string cmd, std::vector<std::string> args )
{
	if( commands.find( cmd ) == commands.end() )
		return false;
	commands[cmd]( args );
	return true;
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
			CConvar cvar = convars[args[0]];
			if( args.size() >= 2 )
			{
				std::string newVal = std::string();
				for( int i = 1; i < args.size(); i++ )
				{
					newVal += args[i] + " ";
				}
				convars[args[0]].SetValue( Trim( newVal ) );
			}
			else
				if( cvar.GetValue().compare( cvar.GetDefaultValue() ) == 0 )
					fprintf( GetConsoleOutput(), "\"%s\" = \"%s\"\n", cvar.GetName().c_str(), cvar.GetValue().c_str() );
				else
					fprintf( GetConsoleOutput(), "\"%s\" = \"%s\" (def. \"%s\")\n", args[0].c_str(), cvar.GetValue().c_str(), cvar.GetDefaultValue().c_str() );
		}
	}
}
#include "common.h"
#include "commands.h"

// Default commands. Try not to overwrite them and please keep them.

bool ListCommand( std::vector<std::string> args )
{
	fprintf( GetConsoleOutput(), "There are %d commands and %d convars available.\n", GetCommands().size(), GetConvars().size() );
	for( const auto &myPair : GetCommands() )
		fprintf( GetConsoleOutput(), "%s\n", myPair.first.c_str() );
	for( const auto &myPair : GetConvars() )
		if( myPair.second.value == myPair.second.defaultValue )
			fprintf( GetConsoleOutput(), "\"%s\" = \"%d\"\n", myPair.first.c_str(), myPair.second.value );
		else
			fprintf( GetConsoleOutput(), "\"%s\" = \"%d\" (def. \"%d\")\n", myPair.first.c_str(), myPair.second.value, myPair.second.defaultValue );
	return true;
}

bool ClearCommand( std::vector<std::string> args )
{
	std::cout.clear();
	return true;
}

void RegisterConsoleCommands()
{
	// Commands
	AddCommand( "list", ListCommand );
	AddCommand( "clear", ClearCommand );

	// Convars
	// AddConvar( "test", 2 );
	// AddConvar( "something", 20 );
	// AddConvar( "some_other_thing", 1337 );
}
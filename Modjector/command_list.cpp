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
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo( console, &screen );
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition( console, topLeft );
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
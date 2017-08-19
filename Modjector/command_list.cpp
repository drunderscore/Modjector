#include "common.h"
#include "commands.h"

// Default commands. Try not to overwrite them and please keep them.

void ListCommand( std::vector<std::string> args )
{
	fprintf( GetConsoleOutput(), "There are %d commands and %d convars available.\n", GetCommands().size(), GetConvars().size() );
	for( const auto &myPair : GetCommands() )
		fprintf( GetConsoleOutput(), "%s\n", myPair.first.c_str() );
	for( auto &myPair : GetConvars() )
		if( myPair.second.GetValue().compare( myPair.second.GetDefaultValue() ) == 0 )
			fprintf( GetConsoleOutput(), "\"%s\" = \"%s\"\n", myPair.first.c_str(), myPair.second.GetValue().c_str() );
		else
			fprintf( GetConsoleOutput(), "\"%s\" = \"%s\" (def. \"%s\")\n", myPair.first.c_str(), myPair.second.GetValue().c_str(), myPair.second.GetDefaultValue().c_str() );
	return;
}

void ClearCommand( std::vector<std::string> args )
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo( console, &screen );
	FillConsoleOutputCharacterA( console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written );
	FillConsoleOutputAttribute( console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written );
	SetConsoleCursorPosition( console, topLeft );
	return;
}

void RegisterConsoleCommands()
{
	// Commands
	AddCommand( "list", ListCommand );
	AddCommand( "clear", ClearCommand );

	// Convars
	AddConvar( "test_mod_class", "CTestMod" );
	AddConvar( "some_other_data", "20" );
	AddConvar( "some_float_value", "3.14159" );
	AddConvar( "lol_player_baseaddress", "0xdeadbeef" );
}
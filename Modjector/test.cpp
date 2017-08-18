#include "common.h"
#include "test.h"
#include "main.h"

void CTestMod::Main()
{
	fprintf( GetConsoleOutput(), "This is the main for mod %s, and it's pretty cool. 5 + 5 is %d\n", GetName().c_str(), 5 + 5 );
}

void CTestMod::Think()
{
	if( GetAsyncKeyState( VK_SPACE ) )
		fprintf( GetConsoleOutput(), "Nice spacing.\n" );
	if( GetAsyncKeyState( 'B' ) )
		fprintf( GetConsoleOutput(), "On nice key you got there, B.\n" );
}
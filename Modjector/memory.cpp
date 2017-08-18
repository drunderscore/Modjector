#include "common.h"
#include "memory.h"
#include "commands.h"

template<typename T>
T ReadMemory( LPCVOID addr )
{
	T val;
	ReadProcessMemory( GetCurrentProcess(), addr, &val, sizeof( val ), NULL );
	return val;
}

void ReadMemoryCommand( std::vector<std::string> args )
{
	if( args.size() < 3 )
	{
		fprintf( GetConsoleOutput(), "read_memory <addr> <ubyte, int, uint, float, double, string> [hex true/false]\n" );
		return;
	}
	bool outputHex = false;
	if( args.size() >= 4 )
		outputHex = args[3].compare( "true" ) == 0;
	std::string type = args[2];
	if( type.compare( "ubyte" ) != 0 && type.compare( "int" ) != 0 && type.compare( "uint" ) != 0 && type.compare( "double" ) != 0 && type.compare( "float" ) != 0 && type.compare( "string" ) != 0 )
	{
		fprintf( GetConsoleOutput(), "Invalid type %s\n", type.c_str() );
		return;
	}
	try
	{
		unsigned int addr = std::stoul( args[1], nullptr, 16 );
		// TOOD: Does this have to be an if chain?
		if( type.compare( "ubyte" ) == 0 )
		{
			byte val = ReadMemory<byte>( (LPCVOID)addr );
			if( outputHex )
				fprintf( GetConsoleOutput(), "(%s) Value in %s is %x\n", type.c_str(), args[1].c_str(), val );
			else
				fprintf( GetConsoleOutput(), "(%s) Value in %s is %d\n", type.c_str(), args[1].c_str(), val );
		}
		else if( type.compare( "int" ) == 0 )
		{
			int val = ReadMemory<int>( (LPCVOID)addr );
			if( outputHex )
				fprintf( GetConsoleOutput(), "(%s) Value in %s is %x\n", type.c_str(), args[1].c_str(), val );
			else
				fprintf( GetConsoleOutput(), "(%s) Value in %s is %d\n", type.c_str(), args[1].c_str(), val );
		}
		else if( type.compare( "uint" ) == 0 )
		{
			UINT val = ReadMemory<UINT>( (LPCVOID)addr );
			if( outputHex )
				fprintf( GetConsoleOutput(), "(%s) Value in %s is %x\n", type.c_str(), args[1].c_str(), val );
			else
				fprintf( GetConsoleOutput(), "(%s) Value in %s is %d\n", type.c_str(), args[1].c_str(), val );
		}
		else if( type.compare( "float" ) == 0 )
		{
			float val = ReadMemory<float>( (LPCVOID)addr );
			fprintf( GetConsoleOutput(), "(%s) Value in %s is %f\n", type.c_str(), args[1].c_str(), val );
		}
		else if( type.compare( "double" ) == 0 )
		{
			double val = ReadMemory<double>( (LPCVOID)addr );
			fprintf( GetConsoleOutput(), "(%s) Value in %s is %f\n", type.c_str(), args[1].c_str(), val );
		}
		else if( type.compare( "string" ) == 0 )
		{
			char val[2048];
			ReadProcessMemory( GetCurrentProcess(), (LPCVOID)addr, &val, 2048, NULL );
			fprintf( GetConsoleOutput(), "(%s) Value in %s is %s\n", type.c_str(), args[1].c_str(), val );
		}
	}
	catch( std::invalid_argument )
	{
		fprintf( GetConsoleOutput(), "Invalid address %s (format)\n", args[1].c_str() );
		return;
	}
	return;
}

void CMemoryMod::Main()
{
	fprintf( GetConsoleOutput(), "The PID of this process is %d. The base address for this proecss is %x\n", (int)GetCurrentProcessId(), GetModuleHandleA( NULL ) );
	// TOOD: This is register AFTER the Commands mod is registers. Not a huge problem, but perferably have this not happen.
	AddCommand( "read_memory", ReadMemoryCommand );
}

void CMemoryMod::Think()
{

}

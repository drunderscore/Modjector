#include "common.h"
#include "memory.h"
#include "commands.h"

template<typename T>
T ReadMemory( int addr )
{
	T val;
	ReadProcessMemory( GetCurrentProcess(), (LPCVOID)addr, &val, sizeof( val ), NULL );
	return val;
}

template<typename T>
T ReadOffset( int offset )
{
	return ReadMemory<T>( (int)GetModuleHandleA( NULL ) + offset );
}

void ReadMemoryCommand( std::vector<std::string> args )
{
	if( args.size() < 3 )
	{
		fprintf( GetConsoleOutput(), "mem_read <addr> <ubyte, int, uint, float, double, string> [hex true/false]\n" );
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
			byte val = ReadMemory<byte>( addr );
			if( outputHex )
				fprintf( GetConsoleOutput(), "(%s) Value in %s is %x\n", type.c_str(), args[1].c_str(), val );
			else
				fprintf( GetConsoleOutput(), "(%s) Value in %s is %d\n", type.c_str(), args[1].c_str(), val );
		}
		else if( type.compare( "int" ) == 0 )
		{
			int val = ReadMemory<int>( addr );
			if( outputHex )
				fprintf( GetConsoleOutput(), "(%s) Value in %s is %x\n", type.c_str(), args[1].c_str(), val );
			else
				fprintf( GetConsoleOutput(), "(%s) Value in %s is %d\n", type.c_str(), args[1].c_str(), val );
		}
		else if( type.compare( "uint" ) == 0 )
		{
			UINT val = ReadMemory<UINT>( addr );
			if( outputHex )
				fprintf( GetConsoleOutput(), "(%s) Value in %s is %x\n", type.c_str(), args[1].c_str(), val );
			else
				fprintf( GetConsoleOutput(), "(%s) Value in %s is %d\n", type.c_str(), args[1].c_str(), val );
		}
		else if( type.compare( "float" ) == 0 )
		{
			float val = ReadMemory<float>( addr );
			fprintf( GetConsoleOutput(), "(%s) Value in %s is %f\n", type.c_str(), args[1].c_str(), val );
		}
		else if( type.compare( "double" ) == 0 )
		{
			double val = ReadMemory<double>( addr );
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

void ReadMemoryOffsetCommand( std::vector<std::string> args )
{
	if( args.size() < 3 )
	{
		fprintf( GetConsoleOutput(), "mem_read_offset <offset> <ubyte, int, uint, float, double, string> [hex true/false]\n" );
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
		unsigned int otherOffset = std::stoul( GetConvars()["mem_offset_address"].GetValue(), nullptr, 16 );
		// TOOD: Does this have to be an if chain?
		if( type.compare( "ubyte" ) == 0 )
		{
			byte val = ReadOffset<byte>( addr + otherOffset );
			if( outputHex )
				fprintf( GetConsoleOutput(), "(%s) Value in (%x + %x) + %s is %x\n", type.c_str(), (int)GetModuleHandleA( NULL ), otherOffset, args[1].c_str(), val );
			else
				fprintf( GetConsoleOutput(), "(%s) Value in (%x + %x) + %s is %d\n", type.c_str(), (int)GetModuleHandleA( NULL ), otherOffset, args[1].c_str(), val );
		}
		else if( type.compare( "int" ) == 0 )
		{
			int val = ReadOffset<int>( addr + otherOffset );
			if( outputHex )
				fprintf( GetConsoleOutput(), "(%s) Value in (%x + %x) + %s is %x\n", type.c_str(), (int)GetModuleHandleA( NULL ), otherOffset, args[1].c_str(), val );
			else
				fprintf( GetConsoleOutput(), "(%s) Value in (%x + %x) + %s is %d\n", type.c_str(), (int)GetModuleHandleA( NULL ), otherOffset, args[1].c_str(), val );
		}
		else if( type.compare( "uint" ) == 0 )
		{
			UINT val = ReadOffset<UINT>( addr + otherOffset );
			if( outputHex )
				fprintf( GetConsoleOutput(), "(%s) Value in (%x + %x) + %s is %x\n", type.c_str(), (int)GetModuleHandleA( NULL ), otherOffset, args[1].c_str(), val );
			else
				fprintf( GetConsoleOutput(), "(%s) Value in (%x + %x) + %s is %d\n", type.c_str(), (int)GetModuleHandleA( NULL ), otherOffset, args[1].c_str(), val );
		}
		else if( type.compare( "float" ) == 0 )
		{
			float val = ReadOffset<float>( addr + otherOffset );
			fprintf( GetConsoleOutput(), "(%s) Value in (%x + %x) + %s is %f\n", type.c_str(), (int)GetModuleHandleA( NULL ), otherOffset, args[1].c_str(), val );
		}
		else if( type.compare( "double" ) == 0 )
		{
			double val = ReadOffset<double>( addr + otherOffset );
			fprintf( GetConsoleOutput(), "(%s) Value in (%x + %x) + %s is %f\n", type.c_str(), (int)GetModuleHandleA( NULL ), otherOffset, args[1].c_str(), val );
		}
		else if( type.compare( "string" ) == 0 )
		{
			char val[2048];
			ReadProcessMemory( GetCurrentProcess(), GetModuleHandleA( NULL ) + addr + otherOffset, &val, 2048, NULL );
			fprintf( GetConsoleOutput(), "(%s) Value in (%x + %x) + %s is %s\n", type.c_str(), (int)GetModuleHandleA( NULL ), otherOffset, args[1].c_str(), val );
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
	fprintf( GetConsoleOutput(), "The PID of this process is %d. The base address for this proecss is %x\n", (int)GetCurrentProcessId(), (int)GetModuleHandleA( NULL ) );
	// TOOD: This is register AFTER the Commands mod is registers. Not a huge problem, but perferably have this not happen.
	AddConvar( "mem_offset_address", "0" );
	AddCommand( "mem_read", ReadMemoryCommand );
	AddCommand( "mem_read_offset", ReadMemoryCommand );
}

void CMemoryMod::Think()
{

}

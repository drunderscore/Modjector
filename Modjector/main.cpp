#include "common.h"
#include "mod.h"
#include "commands.h"

std::vector<CMod*> pMods = std::vector<CMod*>();
FILE *pConsoleFile;
FILE *pConsoleFileIn;

FILE *GetConsoleOutput() { return pConsoleFile; }
FILE *GetConsoleInput() { return pConsoleFileIn; }

void AddMods()
{
	// TODO: Create a better way to add mods. This is good enough for now.
	pMods.push_back( new CCommandsMod() );
}

void __stdcall main()
{
	AddMods();
	if( !AllocConsole() )
	{
		// If we have no console, then we most certainly may have problems later with nullptr and mods flat out not working.
		MessageBoxA( NULL, "Unable to create console window.", "Error", MB_OK | MB_ICONERROR );
		exit( 1 );
	}
	freopen_s( &pConsoleFile, "CONOUT$", "w", stdout );
	freopen_s( &pConsoleFileIn, "CONIN$", "r", stdin );
	std::cout.clear();
	std::cin.clear();
	fprintf( GetConsoleOutput(), "Console initalized.\n" );
	for each(CMod *mod in pMods)
	{
		DWORD thrdId;
		fprintf( GetConsoleOutput(), "Loading mod %s\n", mod->GetName().c_str() );
		CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)StartMod, mod, 0, &thrdId );
		fprintf( GetConsoleOutput(), "Mod started in thread %d\n", (int)thrdId );
	}
	fprintf( GetConsoleOutput(), "Loaded %d mods.\n", pMods.size() );
}

BOOL APIENTRY DllMain( HINSTANCE hInst, DWORD reason, LPVOID lpvReserved )
{
	switch( reason )
	{
	case DLL_PROCESS_ATTACH:
		CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)main, NULL, 0, NULL );
		return TRUE;
	case DLL_PROCESS_DETACH:
		// TODO: We should be closing the file here.
		return TRUE;
	default:
		break;
	}
}
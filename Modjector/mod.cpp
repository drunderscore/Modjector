#include "common.h"
#include "mod.h"

void CMod::Start()
{
	Main();
	while( true )
	{
		Sleep( 0 );
		Think();
	}
}
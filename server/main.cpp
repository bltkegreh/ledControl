#include "ledServer.h"

int main()
{
	LedServer ledServer;
	if(ledServer.init())
	{
		ledServer.run();
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

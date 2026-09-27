#include <window.h>


int main()
{
	if (makeWindow(800, 600) < 0)
	{
		return -1;
	}

	while (windowLoop())
	{
		// Generic processing happens until window closes
		continue;
	}

	return 0;		
}
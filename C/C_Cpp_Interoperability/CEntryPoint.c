
#include "./CodeInteroperability.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	void* entry_point = CreateCppEntryPoint();
	if (entry_point == NULL)
		wprintf(L"Could not create C++ code\n");

	RunCppEntryPoint(entry_point);
	DestroyCppEntryPoint(entry_point);

	wprintf(L"\n\nPress any key to continue!\n");
	getchar();

	return 0;
}

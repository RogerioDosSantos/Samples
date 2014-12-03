//Program used for the CMake Tutorial

#include <stdio.h>
#include <wchar.h>
#include <string>

#include <cstdlib> //strol

//#include "./TutorialConfig.h"

void CommandList()
{
	//	wprintf(L"CMake Tutorial (Version %d.%d.%d)\n", Tutorial_VERSION_MAJOR, Tutorial_VERSION_MINOR, Tutorial_VERSION_PATCH);
	wprintf(L"*** Command List\n");

	wprintf(L"0 - Exit\n");

	wprintf(L"\n");
}

bool ExecuteCommand(unsigned int command)
{
	switch (command)
	{
	default:
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	wchar_t command[3] = { L'\0', L'\0', L'\0' };
	while (command[0] != L'Y' && command[0] != L'y')
	{		
		wprintf(L"*** CMake Tutorial Program Example:\n");
		wprintf(L"Enter the desired example code number or ? for a code list: ");
		//wscanf_s(L"%s", &command[0], 3);
		wscanf(L"%s", &command[0]);
		wprintf(L"\n\n");
		
		int example_id = -1;
		try
		{
			//example_id = std::stoi(command);
			example_id = 0;
		}
		catch (...)
		{
			example_id = 0;
		}

		if (!ExecuteCommand(example_id))
		{
			if (command[0] == L'0')
			{
				command[0] = L'Y';
				continue;
			}

			if (command[0] != L'?')
			{
				wprintf(L"The command %s is invalid!\n\n", command);
				command[0] = L'\0';
				continue;
			}

			CommandList();
			continue;
		}

		wprintf(L"\n\n");
	}

	return 0;
}
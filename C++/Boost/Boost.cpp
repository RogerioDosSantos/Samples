//Boost Example Application Entrypoint

#include <stdio.h>
#include <wchar.h>
#include <string> 

#include "./Timer.h"
#include "./Thread.h"
#include "./Serialization.h"

using namespace boost_example;

void CommandList()
{
	wprintf(L"*** Command List\n");

	wprintf(L"0 - Exit\n");
	wprintf(L"1 - Timer\n");
	wprintf(L"2 - Thread\n");
	wprintf(L"3 - Serialization\n");

	wprintf(L"\n");
}

bool ExecuteCommand(unsigned int command)
{
	switch (command)
	{
	case 1:
		Timer();
		break;
	case 2:
		Thread();
		break;
	case 3:
		Serialization();
		break;
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
		wprintf(L"*** Boost Example:\n");
		wprintf(L"Enter the desired example code number or ? for a code list: ");
		wscanf_s(L"%s", &command[0], 3);
		wprintf(L"\n\n");
		
		int example_id = -1;
		try
		{
			example_id = std::stoi(command);
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

		while (command[0] != L'Y' && command[0] != L'y' && command[0] != L'N' && command[0] != L'n')
		{
			wprintf(L"\n\nWould you like to exit? (Y/N)\n");
			wscanf_s(L"%s", &command[0], 3);
		}
	}

	return 0;
}
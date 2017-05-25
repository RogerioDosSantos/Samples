
#include <stdio.h>
#include <wchar.h>
#include <string>

// #include <windows.h> //Used to create a standard window
#include <afxwin.h> //Used to create a MFC window

#ifndef nullptr
#define nullptr NULL
#endif // nullptr

void CommandList()
{
    wprintf(L"*** Command List\n");

    wprintf(L"0 - Exit\n");
    wprintf(L"1 - Display Compilation Platform Information\n");
    wprintf(L"2 - Create a Window\n");
    wprintf(L"3 - Create a Window using MFC\n");
    wprintf(L"\n");
}

bool DisplayCompilationPlatformInformation()
{
    int platform_full_version = 0;
#ifdef _MSC_FULL_VER
    platform_full_version = _MSC_FULL_VER;
#else
    return false;
#endif  // _MSC_FULL_VER

    wprintf(L" - Platform Toolset Number: %d", platform_full_version);
    switch (platform_full_version)
    {
    case 160040219:
        wprintf(L"\n - Platform Toolset Name: Microsoft Visual Studio 2010 (v100)");
        break;
    case 170060315:
        wprintf(L"\n - Platform Toolset Name: Microsoft Visual Studio 2012 (v110)");
        break;
    case 170061030:
        wprintf(L"\n - Platform Toolset Name: Microsoft Visual Studio 2012 (v110_xp)");
        break;
    case 180020617:
        wprintf(L"\n - Platform Toolset Name: Microsoft Visual Studio 2013 (v120)");
        break;
    case 180040629:
        wprintf(L"\n - Platform Toolset Name: Microsoft Visual Studio 2013 (v120_xp)");
        break;
    case 170051025:
        wprintf(L"\n - Platform Toolset Name: Microsoft Visual Studio 2012 (v120_CTP_Nov2012)");
        break;
    case 1:
        wprintf(L"\n - Platform Toolset Name: Microsoft Visual Studio 2015 (v140)");
        break;
    case 190024215:
        wprintf(L"\n - Platform Toolset Name: Microsoft Visual Studio 2015 (v140_xp)");
        break;
    case 191025019:
        wprintf(L"\n - Platform Toolset Name: Microsoft Visual Studio 2017 (v141_xp)");
        break;
    // case 191025019:
    //     wprintf(L"\n - Platform Toolset Name: Microsoft Visual Studio 2017 (v141)");
    //     break;
    default:
        wprintf(L"\n - Platform Toolset Name: Unknown");
    }

    return true;
}

 LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
 {
     switch (message)
     {
     case WM_DESTROY:
         wprintf(L"\n - Destroying Window");
         PostQuitMessage(0);
         return 0L;
     case WM_LBUTTONDOWN:
         wprintf(L"\n - Mouse: Left button down");
         break;
     default:
         break;
     }

     return DefWindowProc(hWnd, message, wParam, lParam);
 }

 bool CreateMainWindow()
 {
     wprintf(L"Creating a Window:");

     std::wstring class_name(L"WindowsSampleWindow");
     WNDCLASSEX window_class;
     memset(&window_class, 0, sizeof(WNDCLASSEX));
     window_class.cbSize = sizeof(WNDCLASSEX);
     window_class.style = CS_DBLCLKS;
     window_class.lpfnWndProc = WindowProcedure;
     window_class.cbClsExtra = 0;
     window_class.cbWndExtra = 0;
     window_class.hInstance = GetModuleHandle(nullptr);
     window_class.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
     window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
     window_class.hbrBackground = HBRUSH(COLOR_WINDOW + 1);
     window_class.lpszMenuName = L'\0';
     window_class.lpszClassName = class_name.c_str();
     window_class.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

     if (!RegisterClassEx(&window_class))
     {
         wprintf(L"\n - Error: Could not Register the Window Class!");
         return false;
     }

     HWND window = CreateWindowEx(0, class_name.c_str(), L"Windows Sampler", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
         CW_USEDEFAULT, 0, 0, GetModuleHandle(nullptr), 0);

     if (!window)
     {
         wprintf(L"\n - Error: Could not create Window!");
         return false;
     }

     ShowWindow(window, SW_SHOWDEFAULT);
     MSG message;
     while (GetMessage(&message, 0, 0, 0))
     {
         DispatchMessage(&message);
     }

     return true;
 }

 bool CreateMainWindowMFC()
 {
     wprintf(L"Creating a Window using MFC:");

     std::wstring class_name(L"WindowsSampleWindow");
     WNDCLASS window_class;
     memset(&window_class, 0, sizeof(WNDCLASS));
     window_class.style = CS_DBLCLKS;
     window_class.lpfnWndProc = WindowProcedure;
     window_class.cbClsExtra = 0;
     window_class.cbWndExtra = 0;
     window_class.hInstance = GetModuleHandle(nullptr);
     window_class.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
     window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
     window_class.hbrBackground = HBRUSH(COLOR_WINDOW + 1);
     window_class.lpszMenuName = L'\0';
     window_class.lpszClassName = class_name.c_str();
     // window_class.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

     if (!AfxRegisterClass(&window_class))
     {
         wprintf(L"\n - Error: Could not Register the Window Class!");
         return false;
     }

     HWND window = CreateWindowEx(0, class_name.c_str(), L"Windows Sampler MFC", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
         CW_USEDEFAULT, 0, 0, GetModuleHandle(nullptr), 0);

     if (!window)
     {
         wprintf(L"\n - Error: Could not create Window!");
         return false;
     }

     ShowWindow(window, SW_SHOWDEFAULT);
     MSG message;
     while (GetMessage(&message, 0, 0, 0))
     {
         DispatchMessage(&message);
     }

     return true;
 }

bool ExecuteCommand(unsigned int command)
{
    switch (command)
    {
    case 1:
        return DisplayCompilationPlatformInformation();
     case 2:
         return CreateMainWindow();
     case 3:
         return CreateMainWindowMFC();
    default:
        return false;
    }

    return true;
}

int main()
{
    wchar_t command[3] = {L'\0', L'\0', L'\0'};
    while (command[0] != L'Y' && command[0] != L'y')
    {
        wprintf(L"*** Windows Sampler:\n");
        wprintf(L"Enter the desired command or ? for a command list: ");
        wscanf_s(L"%s", &command[0], 3);
        wprintf(L"\n\n");

        int command_id = -1;
        try
        {
            command_id = std::stoi(command);
        }
        catch (...)
        {
            command_id = 0;
        }

        if (!ExecuteCommand(command_id))
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

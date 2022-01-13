#include <Syringe.h>

bool __stdcall DllMain(HANDLE hInstance, DWORD dwReason, LPVOID v)
{
	return true;
}


#include <Dbghelp.h>
#include <tlhelp32.h>
#include <cstdio>

bool DetachFromDebugger()
{
	auto GetDebuggerProcessId = [](DWORD dwSelfProcessId) -> DWORD
	{
		DWORD dwParentProcessId = -1;
		HANDLE hSnapshot = CreateToolhelp32Snapshot(2, 0);
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		Process32First(hSnapshot, &pe32);
		do
		{
			if (pe32.th32ProcessID == dwSelfProcessId)
			{
				dwParentProcessId = pe32.th32ParentProcessID;
				break;
			}
		} while (Process32Next(hSnapshot, &pe32));
		CloseHandle(hSnapshot);
		return dwParentProcessId;
	};

	HMODULE hModule = LoadLibrary("ntdll.dll");
	if (hModule != NULL)
	{
		auto const NtRemoveProcessDebug =
			(NTSTATUS(__stdcall*)(HANDLE, HANDLE))GetProcAddress(hModule, "NtRemoveProcessDebug");
		auto const NtSetInformationDebugObject =
			(NTSTATUS(__stdcall*)(HANDLE, ULONG, PVOID, ULONG, PULONG))GetProcAddress(hModule, "NtSetInformationDebugObject");
		auto const NtQueryInformationProcess =
			(NTSTATUS(__stdcall*)(HANDLE, ULONG, PVOID, ULONG, PULONG))GetProcAddress(hModule, "NtQueryInformationProcess");
		auto const NtClose =
			(NTSTATUS(__stdcall*)(HANDLE))GetProcAddress(hModule, "NtClose");

		HANDLE hDebug;
		HANDLE hCurrentProcess = GetCurrentProcess();
		NTSTATUS status = NtQueryInformationProcess(hCurrentProcess, 30, &hDebug, sizeof(HANDLE), 0);
		if (0 <= status)
		{
			ULONG killProcessOnExit = FALSE;
			status = NtSetInformationDebugObject(
				hDebug,
				1,
				&killProcessOnExit,
				sizeof(ULONG),
				NULL
			);
			if (0 <= status)
			{
				const auto pid = GetDebuggerProcessId(GetProcessId(hCurrentProcess));
				status = NtRemoveProcessDebug(hCurrentProcess, hDebug);
				if (0 <= status)
				{
					char buffer[0x200];
					sprintf_s(buffer, "taskkill /F /PID %d", pid);
					WinExec(buffer, SW_HIDE);
					return true;
				}
			}
			NtClose(hDebug);
		}
		FreeLibrary(hModule);
	}

	return false;
}

DEFINE_HOOK(0x7CD810, ExeRun, 0x9)
{
	if (DetachFromDebugger())
	{
		MessageBoxW(NULL,
			L"You can now attach a debugger.\n\n"

			L"Press OK to continue YR execution.",
			L"Debugger Notice", MB_OK);
	}
	else
	{
		MessageBoxW(NULL,
			L"You can now attach a debugger.\n\n"

			L"To attach a debugger find the YR process in Process Hacker "
			L"/ Visual Studio processes window and detach debuggers from it, "
			L"then you can attach your own debugger. After this you should "
			L"terminate Syringe.exe because it won't automatically exit when YR is closed.\n\n"

			L"Press OK to continue YR execution.",
			L"Debugger Notice", MB_OK);
	}

	return 0;
}
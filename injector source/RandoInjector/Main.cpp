#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

// Change "MY_DLL_NAME.dll" to your dll name
#define DLL_NAME "xyz.dll"

// And you need:
// 1. change all bytes(0x00, 0x01, 0x03....) in define "JUNKS" to random bytes
// 2. change size this block by add new bytes
#define JUNKS \
__asm _emit 0x96 \
__asm _emit 0x64 \
__asm _emit 0x43 \
__asm _emit 0x47 \
__asm _emit 0x96 \
__asm _emit 0x64 \
__asm _emit 0x43 \
__asm _emit 0x47 \
__asm _emit 0x96 \
__asm _emit 0x64 \
__asm _emit 0x43 \
__asm _emit 0x47 \
__asm _emit 0x64 \
__asm _emit 0x21 \
__asm _emit 0x01 \
__asm _emit 0x11 \
__asm _emit 0x87 \
__asm _emit 0x96 \
__asm _emit 0x64 \
__asm _emit 0x43 \
__asm _emit 0x45 \
__asm _emit 0x55 \
__asm _emit 0x15 \
__asm _emit 0x68 \
__asm _emit 0x25 \
__asm _emit 0x15 \
__asm _emit 0x88 \
__asm _emit 0x76 \
__asm _emit 0x43 \
__asm _emit 0x96 \
__asm _emit 0x66 \
__asm _emit 0x36 \
__asm _emit 0x45 \
__asm _emit 0x45 \
__asm _emit 0x68 \
__asm _emit 0x12 \
__asm _emit 0x04 \
__asm _emit 0x68 \
__asm _emit 0x64 \
__asm _emit 0x43 \
__asm _emit 0x47 \
__asm _emit 0x15 \
__asm _emit 0x15 \
__asm _emit 0x12 \
__asm _emit 0x84 \
__asm _emit 0x45 \
__asm _emit 0x95 \


// Don't change this!
#define _JUNK_BLOCK(s) __asm jmp s JUNKS __asm s:


/////////////////////////////////////////////////////////////////////////////////////
//                                 INJECTOR CODE                                   //
/////////////////////////////////////////////////////////////////////////////////////

DWORD Process(char* ProcessName)
{
	_JUNK_BLOCK(jmp_label1)
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	
	_JUNK_BLOCK(jmp_label2)
	PROCESSENTRY32 ProcEntry;
	
	_JUNK_BLOCK(jmp_label3)
	ProcEntry.dwSize = sizeof(ProcEntry);
	
	_JUNK_BLOCK(jmp_label4)
	do
	{
		_JUNK_BLOCK(jmp_label5)
		if (!strcmp(ProcEntry.szExeFile, ProcessName))
		{
			_JUNK_BLOCK(jmp_label6)
			DWORD dwPID = ProcEntry.th32ProcessID;
			
			_JUNK_BLOCK(jmp_label7)
			CloseHandle(hPID);
			
			_JUNK_BLOCK(jmp_label8)
			return dwPID;
		}
		
		_JUNK_BLOCK(jmp_label9)
	}
	while (Process32Next(hPID, &ProcEntry));
	
	_JUNK_BLOCK(jmp_label10)
}

int main()
{
	_JUNK_BLOCK(jmp_label11)
	DWORD dwProcess;
	
	_JUNK_BLOCK(jmp_label12)
	char myDLL[MAX_PATH];
	
	_JUNK_BLOCK(jmp_label13)
	GetFullPathName(DLL_NAME, MAX_PATH, myDLL, 0);
	
	_JUNK_BLOCK(jmp_label4)
	dwProcess = Process("csgo.exe");
	
	_JUNK_BLOCK(jmp_label15)
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, dwProcess);
	
	_JUNK_BLOCK(jmp_label16)
	LPVOID allocatedMem = VirtualAllocEx(hProcess, NULL, sizeof(myDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	
	_JUNK_BLOCK(jmp_label17)
	WriteProcessMemory(hProcess, allocatedMem, myDLL, sizeof(myDLL), NULL);
	
	_JUNK_BLOCK(jmp_label18)
	CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocatedMem, 0, 0);
	
	_JUNK_BLOCK(jmp_label19)
	CloseHandle(hProcess);
	
	_JUNK_BLOCK(jmp_label20)
	return 0;
	
	_JUNK_BLOCK(jmp_label21)
}
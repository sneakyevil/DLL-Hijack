#pragma once
#include <windows.h>
#include <dpapi.h>

namespace DPApiHijack
{
	#if _WIN64
	#define DPAPI_CALL_CONVENTION __fastcall
	#else
	#define DPAPI_CALL_CONVENTION __stdcall
	#endif

	FARPROC m_fCryptProtectDataNoUI = 0;
	BOOL DPAPI_CALL_CONVENTION CryptProtectDataNoUI_(DATA_BLOB* pDataIn, LPCWSTR szDataDescr, DATA_BLOB* pOptionalEntropy, PVOID pvReserved, CRYPTPROTECT_PROMPTSTRUCT* pPromptStruct, DWORD dwFlags, const BYTE* pbOptionalPassword, DWORD cbOptionalPassword, DATA_BLOB* pDataOut)
	{
		return reinterpret_cast<BOOL(DPAPI_CALL_CONVENTION*)(DATA_BLOB*, LPCWSTR, DATA_BLOB*, PVOID, CRYPTPROTECT_PROMPTSTRUCT*, DWORD, const BYTE*, DWORD, DATA_BLOB*)>(m_fCryptProtectDataNoUI)(pDataIn, szDataDescr, pOptionalEntropy, pvReserved, pPromptStruct, dwFlags, pbOptionalPassword, cbOptionalPassword, pDataOut);
	}
	
	FARPROC m_fCryptProtectMemory = 0;
	BOOL DPAPI_CALL_CONVENTION CryptProtectMemory_(LPVOID pDataIn, DWORD cbDataIn, DWORD dwFlags)
	{
		return reinterpret_cast<BOOL(DPAPI_CALL_CONVENTION*)(LPVOID, DWORD, DWORD)>(m_fCryptProtectMemory)(pDataIn, cbDataIn, dwFlags);
	}

	FARPROC m_fCryptResetMachineCredentials = 0;
	DWORD DPAPI_CALL_CONVENTION CryptResetMachineCredentials_(char c1)
	{
		return reinterpret_cast<DWORD(DPAPI_CALL_CONVENTION*)(char)>(m_fCryptProtectMemory)(c1);
	}

	FARPROC m_fCryptUnprotectDataNoUI = 0;
	BOOL DPAPI_CALL_CONVENTION CryptUnprotectDataNoUI_(DATA_BLOB* pDataIn, LPWSTR* ppszDataDescr, DATA_BLOB* pOptionalEntropy, PVOID pvReserved, CRYPTPROTECT_PROMPTSTRUCT* pPromptStruct, DWORD dwFlags, const BYTE* pbOptionalPassword, DWORD cbOptionalPassword, DATA_BLOB* pDataOut)
	{
		return reinterpret_cast<BOOL(DPAPI_CALL_CONVENTION*)(DATA_BLOB*, LPWSTR*, DATA_BLOB*, PVOID, CRYPTPROTECT_PROMPTSTRUCT*, DWORD, const BYTE*, DWORD, DATA_BLOB*)>(m_fCryptUnprotectDataNoUI)(pDataIn, ppszDataDescr, pOptionalEntropy, pvReserved, pPromptStruct, dwFlags, pbOptionalPassword, cbOptionalPassword, pDataOut);
	}

	FARPROC m_fCryptUnprotectMemory = 0;
	BOOL DPAPI_CALL_CONVENTION CryptUnprotectMemory_(LPVOID pDataIn, DWORD cbDataIn, DWORD dwFlags)
	{
		return reinterpret_cast<BOOL(DPAPI_CALL_CONVENTION*)(LPVOID, DWORD, DWORD)>(m_fCryptUnprotectMemory)(pDataIn, cbDataIn, dwFlags);
	}

	FARPROC m_fCryptUpdateProtectedState = 0;
	BOOL DPAPI_CALL_CONVENTION CryptUpdateProtectedState_(PSID pOldSid, LPCWSTR pwszOldPassword, DWORD dwFlags, DWORD* pdwSuccessCount, DWORD* pdwFailureCount)
	{
		return reinterpret_cast<BOOL(DPAPI_CALL_CONVENTION*)(PSID, LPCWSTR, DWORD, DWORD*, DWORD*)>(m_fCryptUpdateProtectedState)(pOldSid, pwszOldPassword, dwFlags, pdwSuccessCount, pdwFailureCount);
	}

	FARPROC m_fiCryptIdentifyProtection = 0;
	void* DPAPI_CALL_CONVENTION iCryptIdentifyProtection_(void* p1, void* p2, unsigned int u3, void* p4, void* p5)
	{
		return reinterpret_cast<void*(DPAPI_CALL_CONVENTION*)(void*, void*, unsigned int, void*, void*)>(m_fiCryptIdentifyProtection)(p1, p2, u3, p4, p5);
	}

	void Initialize()
	{
		char m_cSystemDirectory[MAX_PATH] = { '\0' };
		if (GetSystemDirectoryA(m_cSystemDirectory, sizeof(m_cSystemDirectory)) == 0)
			return;

		if (strcat_s(m_cSystemDirectory, sizeof(m_cSystemDirectory), "\\dpapi.dll"))
			return;

		HMODULE m_hModule = LoadLibraryA(m_cSystemDirectory);
		if (!m_hModule)
			return;

		m_fCryptProtectDataNoUI			= GetProcAddress(m_hModule, reinterpret_cast<LPCSTR>(1));
		m_fCryptProtectMemory			= GetProcAddress(m_hModule, reinterpret_cast<LPCSTR>(2));
		m_fCryptResetMachineCredentials = GetProcAddress(m_hModule, reinterpret_cast<LPCSTR>(3));
		m_fCryptUnprotectDataNoUI		= GetProcAddress(m_hModule, reinterpret_cast<LPCSTR>(4));
		m_fCryptUnprotectMemory			= GetProcAddress(m_hModule, reinterpret_cast<LPCSTR>(5));
		m_fCryptUpdateProtectedState	= GetProcAddress(m_hModule, reinterpret_cast<LPCSTR>(6));
		m_fiCryptIdentifyProtection		= GetProcAddress(m_hModule, reinterpret_cast<LPCSTR>(7));
	}
}

namespace sneakyevil_DllHijack
{
	void Initialize()
	{
		DPApiHijack::Initialize();
	}
}

#pragma comment(linker, "/export:CryptProtectDataNoUI@1=CryptProtectDataNoUI_,@1")
#pragma comment(linker, "/export:CryptProtectMemory@2=CryptProtectMemory_,@2")
#pragma comment(linker, "/export:CryptResetMachineCredentials@3=CryptResetMachineCredentials_,@3")
#pragma comment(linker, "/export:CryptUnprotectDataNoUI@4=CryptUnprotectDataNoUI_,@4")
#pragma comment(linker, "/export:CryptUnprotectMemory@5=CryptUnprotectMemory_,@5")
#pragma comment(linker, "/export:CryptUpdateProtectedState@6=CryptUpdateProtectedState_,@6")
#pragma comment(linker, "/export:iCryptIdentifyProtection@7=iCryptIdentifyProtection_,@7")
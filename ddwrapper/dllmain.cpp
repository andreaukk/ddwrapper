// dllmain.cpp: definisce il punto di ingresso per l'applicazione DLL.
#include "stdafx.h"
#include "ddwrapper.h"

FILE *logFile;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		fopen_s(&logFile, "log.txt","w");
		char sysPath[100];
		GetSystemDirectoryA(sysPath,90);
		fprintf(logFile, "Loadyng system ddraw.dll from %s\n", sysPath);
		strcat_s(sysPath, "\\ddraw.dll");
		sysDDraw = LoadLibraryA(sysPath);

		if (sysDDraw != NULL)
		{
			fprintf(logFile, "Success loading dll. Initializing hooks\n");
			InitApiHooks();
		}
		else 
		{
			int e = GetLastError();

			fprintf(logFile, "Loading dll failed with error %i\n", e);
		}
		break;
	}
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		FreeLibrary(sysDDraw);
		fclose(logFile);
        break;
    }
    return TRUE;
}

void InitApiHooks()
{

	pDirectDrawCreate = (wDirectDrawCreate) GetProcAddress(sysDDraw, "DirectDrawCreate");
	pDirectDrawCreateEx = (wDirectDrawCreateEx) GetProcAddress(sysDDraw, "DirectDrawCreateEx");
	pDirectDrawCreateClipper = (wDirectDrawCreateClipper) GetProcAddress(sysDDraw, "DirectDrawCreateClipper");
	pDirectDrawEnumerateA = (wDirectDrawEnumerateA) GetProcAddress(sysDDraw, "DirectDrawEnumerateA");
	pDirectDrawEnumerateExA = (wDirectDrawEnumerateExA) GetProcAddress(sysDDraw, "DirectDrawEnumerateExA");
	pDirectDrawEnumerateExW = (wDirectDrawEnumerateExW) GetProcAddress(sysDDraw, "DirectDrawEnumerateExW");
	pDirectDrawEnumerateW = (wDirectDrawEnumerateW) GetProcAddress(sysDDraw, "DirectDrawEnumerateW");
	pD3DParseUnknownCommand = (wD3DParseUnknownCommand)GetProcAddress (sysDDraw, "D3DParseUnknownCommand");
	pDllGetClassObject = (wDllGetClassObject) GetProcAddress(sysDDraw, "DllGetClassObject");
	pDllCanUnloadNow = (wDllCanUnloadNow) GetProcAddress(sysDDraw, "DllCanUnloadNow");
	pAcquireDDThreadLock = (wAcquireDDThreadLock) GetProcAddress(sysDDraw, "AcquireDDThreadLock");
	pReleaseDDThreadLock = (wReleaseDDThreadLock) GetProcAddress(sysDDraw, "ReleaseDDThreadLock");
	pGetOLEThunkData = (wGetOLEThunkData) GetProcAddress(sysDDraw, "GetOLEThunkData");
	pSetAppCompatData = (wSetAppCompatData) GetProcAddress(sysDDraw, "SetAppCompatData");
	pCompleteCreateSysmemSurface = (wCompleteCreateSysmemSurface) GetProcAddress(sysDDraw, "CompleteCreateSysmemSurface");
	pDDGetAttachedSurfaceLcl = (wDDGetAttachedSurfaceLcl) GetProcAddress(sysDDraw, "DDGetAttachedSurfaceLcl");
	pDDInternalLock = (wDDInternalLock) GetProcAddress(sysDDraw, "DDInternalLock");
	pDDInternalUnlock = (wDDInternalUnlock) GetProcAddress(sysDDraw, "DDInternalUnlock");
	pDSoundHelp = (wDSoundHelp) GetProcAddress(sysDDraw, "DSoundHelp");
	pGetDDSurfaceLocal = (wGetDDSurfaceLocal) GetProcAddress(sysDDraw, "GetDDSurfaceLocal");
	pGetSurfaceFromDC = (wGetSurfaceFromDC_export) GetProcAddress(sysDDraw, "GetSurfaceFromDC");
	pRegisterSpecialCase = (wRegisterSpecialCase) GetProcAddress(sysDDraw, "RegisterSpecialCase");

}

HRESULT __stdcall DirectDrawCreate(GUID* lpGUID, LPDIRECTDRAW* lpDD, IUnknown* lpUnknown)
{
	LPDIRECTDRAW original;
	HRESULT ret = pDirectDrawCreate(lpGUID, &original, lpUnknown);
	ret = DirectDrawWrapper::CreateInstance(original,(LPVOID*) lpDD);
	((DirectDrawWrapper*)*lpDD)->SetLogFile(logFile);
	return ret;
}

HRESULT __stdcall DirectDrawCreateEx(GUID* lpGUID, LPVOID* lpDD, REFIID id, IUnknown* pUnknown)
{
	return pDirectDrawCreateEx(lpGUID, lpDD, id, pUnknown);
}

HRESULT __stdcall DirectDrawEnumerateA(LPDDENUMCALLBACK lpCallback, LPVOID lpContext)
{
	return pDirectDrawEnumerateA(lpCallback, lpContext);
}

HRESULT __stdcall DirectDrawEnumerateW(LPDDENUMCALLBACK lpCallback, LPVOID lpContext)
{
	return pDirectDrawEnumerateW(lpCallback, lpContext);
}

HRESULT __stdcall DirectDrawEnumerateExA(LPDDENUMCALLBACK lpCallback, LPVOID lpContext, DWORD dwFlags)
{
	return pDirectDrawEnumerateExA(lpCallback, lpContext, dwFlags);
}

HRESULT __stdcall DirectDrawEnumerateExW(LPDDENUMCALLBACK lpCallback, LPVOID lpContext, DWORD dwFlags)
{
	return pDirectDrawEnumerateExW(lpCallback, lpContext, dwFlags);
}

HRESULT __stdcall DirectDrawCreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR *lpDDClipper, IUnknown FAR *pUnknown)
{
	return pDirectDrawCreateClipper(dwFlags, lpDDClipper, pUnknown);
}

HRESULT __stdcall DllGetClassObject(REFCLSID sid, REFIID id, LPVOID* ppv)
{
	return pDllGetClassObject(sid, id, ppv);
}

HRESULT __stdcall DllCanUnloadNow()
{
	return pDllCanUnloadNow();
}

HRESULT __stdcall D3DParseUnknownCommand(LPVOID lpCmd, LPVOID *lpRetCmd)
{
	return pD3DParseUnknownCommand(lpCmd, lpRetCmd);
}

DWORD __stdcall AcquireDDThreadLock()
{
	return pAcquireDDThreadLock();
}

DWORD __stdcall ReleaseDDThreadLock()
{
	return pReleaseDDThreadLock();
}

DWORD __stdcall GetOLEThunkData(DWORD dwIndex)
{
	return pGetOLEThunkData(dwIndex);
}

DWORD __stdcall SetAppCompatData(DWORD dwIndex, DWORD dwData)
{
	return pSetAppCompatData(dwIndex, dwData);
}

DWORD __stdcall CompleteCreateSysmemSurface(DWORD dw)
{
	return pCompleteCreateSysmemSurface(dw);
}

DWORD __stdcall DDGetAttachedSurfaceLcl(DWORD dw1, DWORD dw2, DWORD dw3)
{
	return pDDGetAttachedSurfaceLcl(dw1, dw2, dw3);
}

DWORD __stdcall DDInternalLock(DWORD dw1, DWORD dw2)
{
	return pDDInternalLock(dw1, dw2);
}

DWORD __stdcall DDInternalUnlock(DWORD dw)
{
	return pDDInternalUnlock(dw);
}

DWORD __stdcall DSoundHelp(DWORD dw1, DWORD dw2, DWORD dw3)
{
	return pDSoundHelp(dw1, dw2, dw3);
}

DWORD __stdcall GetDDSurfaceLocal(DWORD dw1, DWORD dw2, DWORD dw3)
{
	return pGetDDSurfaceLocal(dw1, dw2, dw3);
}

DWORD __stdcall GetSurfaceFromDC_export(DWORD dw1, DWORD dw2, DWORD dw3)
{
	return pGetSurfaceFromDC(dw1, dw2, dw3);
}

DWORD __stdcall RegisterSpecialCase(DWORD dw1, DWORD dw2, DWORD dw3, DWORD dw4)
{
	return pRegisterSpecialCase(dw1, dw2, dw3, dw4);
}
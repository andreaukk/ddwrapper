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
		//sostituire con GetSystemDirectory
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

//Set DLL Api Hooks
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

/*
Couldn't find a CLSID for a DirectDrawSurface object, hence vtable hooks
*/
HRESULT InitSurfaceHooks(IDirectDrawSurface* surface)
{
	if (initializedSurfaceHooks)
		return S_OK;

	fprintf(logFile, "Initializing DDSurface hooks\n");
	DWORD dwOld = 0;
	if (!::VirtualProtect((LPVOID)(surface), sizeof(LONG_PTR), PAGE_EXECUTE_READWRITE, &dwOld))
		return E_FAIL;
	SetComHook(surface, (PVOID)DDSurfaceAddAttachedSurface, (PVOID*)&pAddAttachedSurface, 3);
	SetComHook(surface, (PVOID)DDSurfaceAddOverlayDirtyRect, (PVOID*)&pAddOverlayDirtyRect, 4);
	SetComHook(surface, (PVOID)DDSurfaceBlt, (PVOID*)&pBlt, 5);
	SetComHook(surface, (PVOID)DDSurfaceBltBatch, (PVOID*)&pBltBatch, 6);
	SetComHook(surface, (PVOID)DDSurfaceBltFast, (PVOID*)&pBltFast, 7);
	SetComHook(surface, (PVOID)DDSurfaceDeleteAttachedSurface, (PVOID*)&pDeleteAttachedSurface, 8);
	SetComHook(surface, (PVOID)DDSurfaceEnumAttachedSurfaces, (PVOID*)&pEnumAttachedSurfaces, 9);
	SetComHook(surface, (PVOID)DDSurfaceEnumOverlayZOrders, (PVOID*)&pEnumOverlayZOrders, 10);
	SetComHook(surface, (PVOID)DDSurfaceFlip, (PVOID*)&pFlip, 11);
	SetComHook(surface, (PVOID)DDSurfaceGetAttachedSurface, (PVOID*)&pGetAttachedSurface, 12);
	SetComHook(surface, (PVOID)DDSurfaceGetBltStatus, (PVOID*)&pGetBltStatus, 13);
	SetComHook(surface, (PVOID)DDSurfaceGetCaps, (PVOID*)&pGetCaps, 14);
	SetComHook(surface, (PVOID)DDSurfaceGetClipper, (PVOID*)&pGetClipper, 15);
	SetComHook(surface, (PVOID)DDSurfaceGetColorKey, (PVOID*)&pGetColorKey, 16);
	SetComHook(surface, (PVOID)DDSurfaceGetDC, (PVOID*)&pGetDC, 17);
	SetComHook(surface, (PVOID)DDSurfaceGetFlipStatus, (PVOID*)&pGetFlipStatus, 18);
	SetComHook(surface, (PVOID)DDSurfaceGetOverlayPosition, (PVOID*)&pGetOverlayPosition, 19);
	SetComHook(surface, (PVOID)DDSurfaceGetPalette, (PVOID*)&pGetPalette, 20);
	SetComHook(surface, (PVOID)DDSurfaceGetPixelFormat, (PVOID*)&pGetPixelFormat, 21);
	SetComHook(surface, (PVOID)DDSurfaceGetSurfaceDesc, (PVOID*)&pGetSurfaceDesc, 22);
	SetComHook(surface, (PVOID)DDSurfaceInitialize, (PVOID*)&pInitialize, 23);
	SetComHook(surface, (PVOID)DDSurfaceIsLost, (PVOID*)&pIsLost, 24);
	SetComHook(surface, (PVOID)DDSurfaceLock, (PVOID*)&pLock, 25);
	SetComHook(surface, (PVOID)DDSurfaceReleaseDC, (PVOID*)&pReleaseDC, 26);
	SetComHook(surface, (PVOID)DDSurfaceRestore, (PVOID*)&pRestore, 27);
	SetComHook(surface, (PVOID)DDSurfaceSetClipper, (PVOID*)&pSetClipper, 28);
	SetComHook(surface, (PVOID)DDSurfaceSetColorKey, (PVOID*)&pSetColorKey, 29);
	SetComHook(surface, (PVOID)DDSurfaceSetOverlayPosition, (PVOID*)&pSetOverlayPosition, 30);
	SetComHook(surface, (PVOID)DDSurfaceSetPalette, (PVOID*)&pSetPalette, 31);
	SetComHook(surface, (PVOID)DDSurfaceUnlock, (PVOID*)&pUnlock, 32);
	SetComHook(surface, (PVOID)DDSurfaceUpdateOverlay, (PVOID*)&pUpdateOverlay, 33);
	SetComHook(surface, (PVOID)DDSurfaceUpdateOverlayDisplay, (PVOID*)&pUpdateOverlayDisplay, 34);
	SetComHook(surface, (PVOID)DDSurfaceUpdateOverlayZOrder, (PVOID*)&pUpdateOverlayZOrder, 35);
	SetComHook(surface, (PVOID)DDSurfaceGetDDInterface, (PVOID*)&pGetDDInterface, 36);
	SetComHook(surface, (PVOID)DDSurfacePageLock, (PVOID*)&pPageLock, 37);
	SetComHook(surface, (PVOID)DDSurfacePageUnlock, (PVOID*)&pPageUnlock, 38);
	SetComHook(surface, (PVOID)DDSurfaceSetSurfaceDesc, (PVOID*)&pSetSurfaceDesc, 39);
	SetComHook(surface, (PVOID)DDSurfaceSetPrivateData, (PVOID*)&pSetPrivateData, 40);
	SetComHook(surface, (PVOID)DDSurfaceGetPrivateData, (PVOID*)&pGetPrivateData, 41);
	SetComHook(surface, (PVOID)DDSurfaceFreePrivateData, (PVOID*)&pFreePrivateData, 42);
	SetComHook(surface, (PVOID)DDSurfaceGetUniquenessValue, (PVOID*)&pGetUniquenessValue, 43);
	SetComHook(surface, (PVOID)DDSurfaceChangeUniquenessValue, (PVOID*)&pChangeUniquenessValue, 44);
	initializedSurfaceHooks = true;
	return S_OK;
}

HRESULT SetComHook(IUnknown* original, PVOID wrapperFunct, PVOID* wrappedFunct, DWORD vtableIndex)
{
	LPVOID* vtable = *(PVOID**)original;
	if (vtable[vtableIndex] == wrapperFunct)
		return S_OK;
	*wrappedFunct = vtable[vtableIndex];
	vtable[vtableIndex] = wrapperFunct;
	return S_OK;
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



HRESULT __stdcall DDSurfaceAddAttachedSurface(IDirectDrawSurface* surface, LPDIRECTDRAWSURFACE lpDDSurface)
{
	fprintf(logFile, "Called AddAttachedSurface\n");
	return pAddAttachedSurface(surface, lpDDSurface);
}

HRESULT __stdcall DDSurfaceAddOverlayDirtyRect(IDirectDrawSurface* surface, LPRECT lpRect)
{
	fprintf(logFile, "Called AddOverlayDirtyRect\n");
	return pAddOverlayDirtyRect(surface, lpRect);
}

HRESULT __stdcall DDSurfaceBlt(IDirectDrawSurface* surface, LPRECT lpDestRect, LPDIRECTDRAWSURFACE lpDDSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpBltFx)
{
	fprintf(logFile, "Called Blt\n", dwFlags);
	return pBlt(surface, lpDestRect, lpDDSurface, lpSrcRect, dwFlags, lpBltFx);
}

HRESULT __stdcall DDSurfaceBltBatch(IDirectDrawSurface* surface, LPDDBLTBATCH lpBltBatch, DWORD dwCount, DWORD dwFlags)
{
	fprintf(logFile, "Called BltBatch\n");
	return pBltBatch(surface, lpBltBatch, dwCount, dwFlags);
}

HRESULT __stdcall DDSurfaceBltFast(IDirectDrawSurface* surface, DWORD dwX, DWORD dwY, LPDIRECTDRAWSURFACE lpDDSurface, LPRECT srcRect, DWORD dwFlags)
{
	fprintf(logFile, "Called BltFast\n");
	return pBltFast(surface, dwX, dwY, lpDDSurface, srcRect, dwFlags);
}

HRESULT __stdcall DDSurfaceChangeUniquenessValue(IDirectDrawSurface* surface)
{
	fprintf(logFile, "Called ChangeUniquenessValue\n");
	return pChangeUniquenessValue(surface);
}

HRESULT __stdcall DDSurfaceDeleteAttachedSurface(IDirectDrawSurface* surface, DWORD dwFlags, LPDIRECTDRAWSURFACE lpAttachedSurface)
{
	fprintf(logFile, "Called DeleteAttachedSurface\n");
	return pDeleteAttachedSurface(surface, dwFlags, lpAttachedSurface);
}

HRESULT __stdcall DDSurfaceEnumAttachedSurfaces(IDirectDrawSurface* surface, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpCallback)
{
	fprintf(logFile, "Called EnumAttachedSurfaces\n");
	return pEnumAttachedSurfaces(surface, lpContext, lpCallback);
}

HRESULT __stdcall DDSurfaceEnumOverlayZOrders(IDirectDrawSurface* surface, DWORD dwFlags, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpCallback)
{
	fprintf(logFile, "Called EnumOverlayZOrders\n");
	return pEnumOverlayZOrders(surface, dwFlags, lpContext, lpCallback);
}

HRESULT __stdcall DDSurfaceFlip(IDirectDrawSurface* surface, LPDIRECTDRAWSURFACE lpDDTargetOverride, DWORD dwFlags)
{
	fprintf(logFile, "Called Flip\n");
	return pFlip(surface, lpDDTargetOverride, dwFlags);
}

HRESULT __stdcall DDSurfaceFreePrivateData(IDirectDrawSurface* surface, REFGUID guidTag)
{
	fprintf(logFile, "Called FreePrivateData\n");
	return pFreePrivateData(surface, guidTag);
}

HRESULT __stdcall DDSurfaceGetAttachedSurface(IDirectDrawSurface* surface, LPDDSCAPS lpCaps, LPDIRECTDRAWSURFACE *lplpAttachedSurface)
{
	fprintf(logFile, "Called GetAttachedSurface\n");
	return pGetAttachedSurface(surface, lpCaps, lplpAttachedSurface);
}

HRESULT __stdcall DDSurfaceGetBltStatus(IDirectDrawSurface* surface, DWORD dwFlags)
{
	fprintf(logFile, "Called GetBltStatus\n");
	return pGetBltStatus(surface, dwFlags);
}

HRESULT __stdcall DDSurfaceGetCaps(IDirectDrawSurface* surface, LPDDSCAPS lpDDSCaps)
{
	fprintf(logFile, "Called GetCaps\n");
	return pGetCaps(surface, lpDDSCaps);
}

HRESULT __stdcall DDSurfaceGetClipper(IDirectDrawSurface* surface, LPDIRECTDRAWCLIPPER *lplpDDClipper)
{
	fprintf(logFile, "Called GetClipper\n");
	return pGetClipper(surface, lplpDDClipper);
}

HRESULT __stdcall DDSurfaceGetColorKey(IDirectDrawSurface* surface, DWORD dwFlags, LPDDCOLORKEY lpDDColorKey)
{
	fprintf(logFile, "Called GetColorKey\n");
	return pGetColorKey(surface, dwFlags, lpDDColorKey);
}

HRESULT __stdcall DDSurfaceGetDC(IDirectDrawSurface* surface, HDC *lphDC)
{
	fprintf(logFile, "Called GetDC\n");
	return pGetDC(surface, lphDC);
}

HRESULT __stdcall DDSurfaceGetDDInterface(IDirectDrawSurface* surface, LPVOID *lplpDD)
{
	fprintf(logFile, "Called GetDDInterface\n");
	return pGetDDInterface(surface, lplpDD);
}

HRESULT __stdcall DDSurfaceGetFlipStatus(IDirectDrawSurface* surface, DWORD dwFlags)
{
	fprintf(logFile, "Called GetFlipStatus\n");
	return pGetFlipStatus(surface, dwFlags);
}

HRESULT __stdcall DDSurfaceGetOverlayPosition(IDirectDrawSurface* surface, LPLONG lplX, LPLONG lplY)
{
	fprintf(logFile, "Called GetOverlayPosition\n");
	return pGetOverlayPosition(surface, lplX, lplY);
}

HRESULT __stdcall DDSurfaceGetPalette(IDirectDrawSurface* surface, LPDIRECTDRAWPALETTE  *lplpDDPalette)
{
	fprintf(logFile, "Called GetPalette\n");
	return pGetPalette(surface, lplpDDPalette);
}

HRESULT __stdcall DDSurfaceGetPixelFormat(IDirectDrawSurface* surface, LPDDPIXELFORMAT lpDDPixelFormat)
{
	fprintf(logFile, "Called GetPixelFormat\n");
	return pGetPixelFormat(surface, lpDDPixelFormat);
}

HRESULT __stdcall DDSurfaceGetPrivateData(IDirectDrawSurface* surface, REFGUID guidTag, LPVOID  lpBuffer, LPDWORD lpcbBufferSize)
{
	fprintf(logFile, "Called GetPrivateData\n");
	return pGetPrivateData(surface, guidTag, lpBuffer, lpcbBufferSize);
}

HRESULT __stdcall DDSurfaceGetSurfaceDesc(IDirectDrawSurface* surface, LPDDSURFACEDESC lpDDSurfaceDesc)
{
	fprintf(logFile, "Called GetSurfaceDesc\n");
	return pGetSurfaceDesc(surface, lpDDSurfaceDesc);
}

HRESULT __stdcall DDSurfaceGetUniquenessValue(IDirectDrawSurface* surface, LPDWORD lpValue)
{
	fprintf(logFile, "Called GetUniquenessValue\n");
	return pGetUniquenessValue(surface, lpValue);
}

HRESULT __stdcall DDSurfaceInitialize(IDirectDrawSurface* surface, LPDIRECTDRAW lpDD, LPDDSURFACEDESC lpDDSurfaceDesc)
{
	fprintf(logFile, "Called Initialize\n");
	return pInitialize(surface, lpDD, lpDDSurfaceDesc);
}

HRESULT __stdcall DDSurfaceIsLost(IDirectDrawSurface* surface)
{
	fprintf(logFile, "Called IsLost\n");
	return pIsLost(surface);
}

HRESULT __stdcall DDSurfaceLock(IDirectDrawSurface* surface, LPRECT lpDestRect, LPDDSURFACEDESC lpDDSurfaceDesc, DWORD  dwFlags, HANDLE hEvent)
{
	fprintf(logFile, "Called Lock\n");
	return pLock(surface, lpDestRect, lpDDSurfaceDesc, dwFlags, hEvent);
}

HRESULT __stdcall DDSurfacePageLock(IDirectDrawSurface* surface, DWORD dwFlags)
{
	fprintf(logFile, "Called PageLock\n");
	return pPageLock(surface, dwFlags);
}

HRESULT __stdcall DDSurfacePageUnlock(IDirectDrawSurface* surface, DWORD dwFlags)
{
	fprintf(logFile, "Called PageUnlock\n");
	return pPageUnlock(surface, dwFlags);
}

HRESULT __stdcall DDSurfaceReleaseDC(IDirectDrawSurface* surface, HDC hDC)
{
	fprintf(logFile, "Called ReleaseDC\n");
	return pReleaseDC(surface, hDC);
}

HRESULT __stdcall DDSurfaceRestore(IDirectDrawSurface* surface)
{
	fprintf(logFile, "Called Restore\n");
	return pRestore(surface);
}

HRESULT __stdcall DDSurfaceSetClipper(IDirectDrawSurface* surface, LPDIRECTDRAWCLIPPER lpDDClipper)
{
	fprintf(logFile, "Called SetClipper\n");
	return pSetClipper(surface, lpDDClipper);
}

HRESULT __stdcall DDSurfaceSetColorKey(IDirectDrawSurface* surface, DWORD dwFlags, LPDDCOLORKEY lpDDColorKey)
{
	fprintf(logFile, "Called SetColorKey\n");
	return pSetColorKey(surface, dwFlags, lpDDColorKey);
}

HRESULT __stdcall DDSurfaceSetOverlayPosition(IDirectDrawSurface* surface, LONG lX, LONG lY)
{
	fprintf(logFile, "Called SetOverlayPosition\n");
	return pSetOverlayPosition(surface, lX, lY);
}

HRESULT __stdcall DDSurfaceSetPalette(IDirectDrawSurface* surface, LPDIRECTDRAWPALETTE lpDDPalette)
{
	fprintf(logFile, "Called SetPalette\n");
	return pSetPalette(surface, lpDDPalette);
}

HRESULT __stdcall DDSurfaceSetPrivateData(IDirectDrawSurface* surface, REFGUID guidTag, LPVOID  lpData, DWORD   cbSize, DWORD   dwFlags)
{
	fprintf(logFile, "Called SetPrivateData\n");
	return pSetPrivateData(surface, guidTag, lpData, cbSize, dwFlags);
}

HRESULT __stdcall DDSurfaceSetSurfaceDesc(IDirectDrawSurface* surface, LPDDSURFACEDESC lpDDsd2, DWORD dwFlags)
{
	fprintf(logFile, "Called SetSurfaceDesc\n");
	return pSetSurfaceDesc(surface, lpDDsd2, dwFlags);
}

HRESULT __stdcall DDSurfaceUnlock(IDirectDrawSurface* surface, LPVOID lpRect)
{
	fprintf(logFile, "Called Unlock\n");
	return pUnlock(surface, lpRect);
}

HRESULT __stdcall DDSurfaceUpdateOverlay(IDirectDrawSurface* surface, LPRECT lpSrcRect, LPDIRECTDRAWSURFACE lpDDDestSurface, LPRECT lpDestRect, DWORD dwFlags, LPDDOVERLAYFX lpDDOverlayFx)
{
	fprintf(logFile, "Called UpdateOverlay\n");
	return pUpdateOverlay(surface, lpSrcRect, lpDDDestSurface, lpDestRect, dwFlags, lpDDOverlayFx);
}

HRESULT __stdcall DDSurfaceUpdateOverlayDisplay(IDirectDrawSurface* surface, DWORD dwFlags)
{
	fprintf(logFile, "Called UpdateOverlayDisplay\n");
	return pUpdateOverlayDisplay(surface, dwFlags);
}

HRESULT __stdcall DDSurfaceUpdateOverlayZOrder(IDirectDrawSurface* surface, DWORD dwFlags, LPDIRECTDRAWSURFACE lpDDSReference)
{
	fprintf(logFile, "Called UpdateOverlayZOrder\n");
	return pUpdateOverlayZOrder(surface, dwFlags, lpDDSReference);
}

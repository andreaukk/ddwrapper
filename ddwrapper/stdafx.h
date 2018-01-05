// stdafx.h : file di inclusione per file di inclusione di sistema standard
// o file di inclusione specifici del progetto utilizzati di frequente, ma
// modificati raramente
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Escludere gli elementi utilizzati di rado dalle intestazioni di Windows
// File di intestazione di Windows:
#include <windows.h>
#include <ddraw.h>
#include <atldef.h>
#include <atlbase.h>
#include <atlcom.h>
#include "stdio.h"

class ATL_NO_VTABLE DirectDrawWrapper :
	public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>,
	public ATL::CComCoClass<DirectDrawWrapper, &CLSID_DirectDraw7>,
	public IDirectDraw
{

public:
	DirectDrawWrapper();

	DECLARE_NO_REGISTRY()

	BEGIN_COM_MAP(DirectDrawWrapper)
		COM_INTERFACE_ENTRY_IID(IID_IDirectDraw, IDirectDraw)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

public:
	HRESULT FinalConstruct();
	void FinalRelease();

public:
	HRESULT static CreateInstance(IUnknown* original, void **ppvObject);

public:
	HRESULT __stdcall Compact();
	HRESULT __stdcall CreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER *lpDDClipper, IUnknown *pUnk);
	HRESULT __stdcall CreatePalette(DWORD dwFlags, LPPALETTEENTRY lpDDColor,LPDIRECTDRAWPALETTE *lpDDPalette, IUnknown *pUnk);
	HRESULT __stdcall CreateSurface(LPDDSURFACEDESC lpDDSurfDesc, LPDIRECTDRAWSURFACE *lpDDSurface, IUnknown *pUnk);
	HRESULT __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE lpDDSurface, LPDIRECTDRAWSURFACE *lplpDDSurface);
	HRESULT __stdcall EnumDisplayModes(DWORD dwFlags, LPDDSURFACEDESC lpDDSD2, LPVOID lpContext, LPDDENUMMODESCALLBACK lpEnumModeCallback);
	HRESULT __stdcall EnumSurfaces(DWORD dwFlags, LPDDSURFACEDESC lpDDSD2, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpEnumSurfCallback);
	//HRESULT __stdcall EvaluateMode(DWORD dwFlags, DWORD *pSecUntilTimeout);
	HRESULT __stdcall FlipToGDISurface();
	//HRESULT __stdcall GetAvailableVidMem(LPDDSCAPS2 lpDDSCaps, LPDWORD lpdwTotal, LPDWORD lpdwFree);
	HRESULT __stdcall GetCaps(LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps);
	//HRESULT __stdcall GetDeviceIdentifier(LPDDDEVICEIDENTIFIER2 lpddi, DWORD dwFlags);
	HRESULT __stdcall GetDisplayMode(LPDDSURFACEDESC lpDDSurf);
	HRESULT __stdcall GetFourCCCodes(LPDWORD lpNumCodes, LPDWORD lpCodes);
	HRESULT __stdcall GetGDISurface(LPDIRECTDRAWSURFACE *lplpGDIDDSurf);
	HRESULT __stdcall GetMonitorFrequency(LPDWORD lpdwFreq);
	HRESULT __stdcall GetScanLine(LPDWORD lpdwScanLine);
	//HRESULT __stdcall GetSurfaceFromDC(HDC hdc, LPDIRECTDRAWSURFACE *lpDDS);
	HRESULT __stdcall GetVerticalBlankStatus(LPBOOL lpVB);
	HRESULT __stdcall Initialize(GUID *lpGUID);
	//HRESULT __stdcall RestoreAllSurfaces();
	HRESULT __stdcall RestoreDisplayMode();
	HRESULT __stdcall SetCooperativeLevel(HWND hwnd, DWORD dwFlags);
	HRESULT __stdcall SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBPP);
	//HRESULT __stdcall StartModeTest(LPSIZE lpModesToTest, DWORD dwNumEntries, DWORD dwFlags);
	//HRESULT __stdcall TestCooperativeLevel();
	HRESULT __stdcall WaitForVerticalBlank(DWORD dwFlags, HANDLE hEvent);

public:
	void SetLogFile(FILE* log);
	


private:
	ATL::CComPtr<IDirectDraw> dd7; 
	FILE* logFile;

};


void InitApiHooks();



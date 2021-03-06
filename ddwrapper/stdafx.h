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

/* DirectDrawSurface wrapper functions declarations*/
HRESULT __stdcall DDSurfaceAddAttachedSurface(IDirectDrawSurface* surface, LPDIRECTDRAWSURFACE lpDDSurface);
HRESULT __stdcall DDSurfaceAddOverlayDirtyRect(IDirectDrawSurface* surface, LPRECT lpRect);
HRESULT __stdcall DDSurfaceBlt(IDirectDrawSurface* surface, LPRECT lpDestRect, LPDIRECTDRAWSURFACE lpDDSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpBltFx);
HRESULT __stdcall DDSurfaceBltBatch(IDirectDrawSurface* surface, LPDDBLTBATCH lpBltBatch, DWORD dwCount, DWORD dwFlags);
HRESULT __stdcall DDSurfaceBltFast(IDirectDrawSurface* surface, DWORD dwX, DWORD dwY, LPDIRECTDRAWSURFACE lpDDSurface, LPRECT srcRect, DWORD dwFlags);
HRESULT __stdcall DDSurfaceChangeUniquenessValue(IDirectDrawSurface* surface);
HRESULT __stdcall DDSurfaceDeleteAttachedSurface(IDirectDrawSurface* surface, DWORD dwFlags, LPDIRECTDRAWSURFACE lpAttachedSurface);
HRESULT __stdcall DDSurfaceEnumAttachedSurfaces(IDirectDrawSurface* surface, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpCallback);
HRESULT __stdcall DDSurfaceEnumOverlayZOrders(IDirectDrawSurface* surface, DWORD dwFlags, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpCallback);
HRESULT __stdcall DDSurfaceFlip(IDirectDrawSurface* surface, LPDIRECTDRAWSURFACE lpDDTargetOverride, DWORD dwFlags);
HRESULT __stdcall DDSurfaceFreePrivateData(IDirectDrawSurface* surface, REFGUID guidTag);
HRESULT __stdcall DDSurfaceGetAttachedSurface(IDirectDrawSurface* surface, LPDDSCAPS lpCaps, LPDIRECTDRAWSURFACE *lplpAttachedSurface);
HRESULT __stdcall DDSurfaceGetBltStatus(IDirectDrawSurface* surface, DWORD dwFlags);
HRESULT __stdcall DDSurfaceGetCaps(IDirectDrawSurface* surface, LPDDSCAPS lpDDSCaps);
HRESULT __stdcall DDSurfaceGetClipper(IDirectDrawSurface* surface, LPDIRECTDRAWCLIPPER *lplpDDClipper);
HRESULT __stdcall DDSurfaceGetColorKey(IDirectDrawSurface* surface, DWORD dwFlags, LPDDCOLORKEY lpDDColorKey);
HRESULT __stdcall DDSurfaceGetDC(IDirectDrawSurface* surface, HDC *lphDC);
HRESULT __stdcall DDSurfaceGetDDInterface(IDirectDrawSurface* surface, LPVOID *lplpDD);
HRESULT __stdcall DDSurfaceGetFlipStatus(IDirectDrawSurface* surface, DWORD dwFlags);
HRESULT __stdcall DDSurfaceGetOverlayPosition(IDirectDrawSurface* surface, LPLONG lplX, LPLONG lplY);
HRESULT __stdcall DDSurfaceGetPalette(IDirectDrawSurface* surface, LPDIRECTDRAWPALETTE  *lplpDDPalette);
HRESULT __stdcall DDSurfaceGetPixelFormat(IDirectDrawSurface* surface, LPDDPIXELFORMAT lpDDPixelFormat);
HRESULT __stdcall DDSurfaceGetPrivateData(IDirectDrawSurface* surface, REFGUID guidTag, LPVOID  lpBuffer, LPDWORD lpcbBufferSize);
HRESULT __stdcall DDSurfaceGetSurfaceDesc(IDirectDrawSurface* surface, LPDDSURFACEDESC lpDDSurfaceDesc);
HRESULT __stdcall DDSurfaceGetUniquenessValue(IDirectDrawSurface* surface, LPDWORD lpValue);
HRESULT __stdcall DDSurfaceInitialize(IDirectDrawSurface* surface, LPDIRECTDRAW lpDD, LPDDSURFACEDESC lpDDSurfaceDesc);
HRESULT __stdcall DDSurfaceIsLost(IDirectDrawSurface* surface);
HRESULT __stdcall DDSurfaceLock(IDirectDrawSurface* surface, LPRECT lpDestRect, LPDDSURFACEDESC lpDDSurfaceDesc, DWORD  dwFlags, HANDLE hEvent);
HRESULT __stdcall DDSurfacePageLock(IDirectDrawSurface* surface, DWORD dwFlags);
HRESULT __stdcall DDSurfacePageUnlock(IDirectDrawSurface* surface, DWORD dwFlags);
HRESULT __stdcall DDSurfaceReleaseDC(IDirectDrawSurface* surface, HDC hDC);
HRESULT __stdcall DDSurfaceRestore(IDirectDrawSurface* surface);
HRESULT __stdcall DDSurfaceSetClipper(IDirectDrawSurface* surface, LPDIRECTDRAWCLIPPER lpDDClipper);
HRESULT __stdcall DDSurfaceSetColorKey(IDirectDrawSurface* surface, DWORD dwFlags, LPDDCOLORKEY lpDDColorKey);
HRESULT __stdcall DDSurfaceSetOverlayPosition(IDirectDrawSurface* surface, LONG lX, LONG lY);
HRESULT __stdcall DDSurfaceSetPalette(IDirectDrawSurface* surface, LPDIRECTDRAWPALETTE lpDDPalette);
HRESULT __stdcall DDSurfaceSetPrivateData(IDirectDrawSurface* surface, REFGUID guidTag, LPVOID  lpData, DWORD cbSize, DWORD dwFlags);
HRESULT __stdcall DDSurfaceSetSurfaceDesc(IDirectDrawSurface* surface, LPDDSURFACEDESC lpDDsd2, DWORD dwFlags);
HRESULT __stdcall DDSurfaceUnlock(IDirectDrawSurface* surface, LPVOID lpRect);
HRESULT __stdcall DDSurfaceUpdateOverlay(IDirectDrawSurface* surface, LPRECT lpSrcRect, LPDIRECTDRAWSURFACE lpDDDestSurface, LPRECT lpDestRect, DWORD dwFlags, LPDDOVERLAYFX lpDDOverlayFx);
HRESULT __stdcall DDSurfaceUpdateOverlayDisplay(IDirectDrawSurface* surface, DWORD dwFlags);
HRESULT __stdcall DDSurfaceUpdateOverlayZOrder(IDirectDrawSurface* surface, DWORD dwFlags, LPDIRECTDRAWSURFACE lpDDSReference);

/*Hook Init Functions*/
void InitApiHooks();
HRESULT SetComHook(IUnknown* original, PVOID wrapperFunct, PVOID* wrappedFunct, DWORD vtableIndex);
HRESULT InitSurfaceHooks(IDirectDrawSurface* surface);


// TODO: fare riferimento qui alle intestazioni aggiuntive richieste dal programma

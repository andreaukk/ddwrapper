// ddwrapper.cpp: definisce le funzioni esportate per l'applicazione DLL.
//

#include "stdafx.h"

//Empty constructor
DirectDrawWrapper::DirectDrawWrapper(){}

//CComObjectRootEx Functions
HRESULT DirectDrawWrapper::FinalConstruct()
{
	return S_OK;
}

void DirectDrawWrapper::FinalRelease()
{
	return;
}


//CComCoClass Functions
HRESULT DirectDrawWrapper::CreateInstance(IUnknown *pUnk, void **ppvObject)
{
	ATL::CComObjectNoLock<DirectDrawWrapper>* self = new ATL::CComObjectNoLock<DirectDrawWrapper>;
	self->SetVoid(NULL);
	self->InternalFinalConstructAddRef();
	HRESULT hr = self->_AtlInitialConstruct();
	if (SUCCEEDED(hr))
		hr = self->FinalConstruct();
	if (SUCCEEDED(hr))
		hr = self ->_AtlFinalConstruct();
	if (SUCCEEDED(hr))
		hr = pUnk->QueryInterface(IID_IDirectDraw,(void**)&self->dd7);
	if (SUCCEEDED(hr))
		hr = self->QueryInterface(IID_IDirectDraw, ppvObject);
	if (hr != S_OK)
		delete self;
	return hr;
}


//IDirectDraw7 functions
HRESULT __stdcall DirectDrawWrapper::Compact()
{
	return this->dd7->Compact();
}

HRESULT __stdcall DirectDrawWrapper::CreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER *lpDDClipper, IUnknown *pUnk)
{
	fprintf(this->logFile, "Called CreateClipper flags:%d\n", dwFlags);
	return this->dd7->CreateClipper( dwFlags, lpDDClipper, pUnk);
}

HRESULT __stdcall DirectDrawWrapper::CreatePalette(DWORD dwFlags, LPPALETTEENTRY lpDDColor, LPDIRECTDRAWPALETTE *lpDDPalette, IUnknown *pUnk)
{
	fprintf(this->logFile, "Called CreatePalette flags:%d\n", dwFlags);
	return this->dd7->CreatePalette(dwFlags, lpDDColor, lpDDPalette, pUnk);
}

HRESULT __stdcall DirectDrawWrapper::CreateSurface(LPDDSURFACEDESC lpDDSurfDesc, LPDIRECTDRAWSURFACE *lpDDSurface, IUnknown *pUnk)
{
	//hook methods to IDirectDrawSurface
	fprintf(this->logFile, "Called CreateSurface\n");
	HRESULT hr = this->dd7->CreateSurface(lpDDSurfDesc, lpDDSurface, pUnk);
	InitSurfaceHooks(*lpDDSurface);
	return hr;
}

HRESULT __stdcall DirectDrawWrapper::DuplicateSurface(LPDIRECTDRAWSURFACE lpDDSurface, LPDIRECTDRAWSURFACE *lplpDDSurface)
{
	fprintf(this->logFile, "Called DuplicateSurface\n");
	return this->dd7->DuplicateSurface(lpDDSurface, lplpDDSurface);
}

HRESULT __stdcall DirectDrawWrapper::EnumDisplayModes(DWORD dwFlags, LPDDSURFACEDESC lpDDSD2, LPVOID lpContext, LPDDENUMMODESCALLBACK lpEnumModeCallback)
{
	fprintf(this->logFile, "Called EnumDisplayModes flags:%d\n", dwFlags);
	return this->dd7->EnumDisplayModes(dwFlags, lpDDSD2, lpContext, lpEnumModeCallback);
}

HRESULT __stdcall DirectDrawWrapper::EnumSurfaces(DWORD dwFlags, LPDDSURFACEDESC lpDDSD2, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpEnumSurfCallback)
{
	fprintf(this->logFile, "Called EnumSurfaces flags:%d\n", dwFlags);
	return this->dd7->EnumSurfaces(dwFlags, lpDDSD2, lpContext, lpEnumSurfCallback);
}
/*
HRESULT __stdcall DirectDrawWrapper::EvaluateMode(DWORD dwFlags, DWORD *pSecUntilTimeout)
{
	return this->dd7->EvaluateMode(dwFlags, pSecUntilTimeout);
}*/

HRESULT __stdcall DirectDrawWrapper::FlipToGDISurface()
{
	fprintf(this->logFile, "Called FlipToGDISurface\n");
	return this->dd7->FlipToGDISurface();
}
/*
HRESULT __stdcall DirectDrawWrapper::GetAvailableVidMem(LPDDSCAPS2 lpDDSCaps, LPDWORD lpdwTotal, LPDWORD lpdwFree)
{
	return this->dd7->GetAvailableVidMem(lpDDSCaps, lpdwTotal, lpdwFree);
}*/

HRESULT __stdcall DirectDrawWrapper::GetCaps(LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps)
{
	fprintf(this->logFile, "Called GetCaps\n");
	return this->dd7->GetCaps(lpDDDriverCaps, lpDDHELCaps);
}
/*
HRESULT __stdcall DirectDrawWrapper::GetDeviceIdentifier(LPDDDEVICEIDENTIFIER2 lpddi, DWORD dwFlags)
{
	return this->dd7->GetDeviceIdentifier(lpddi, dwFlags);
}*/

HRESULT __stdcall DirectDrawWrapper::GetDisplayMode(LPDDSURFACEDESC lpDDSurf)
{
	fprintf(this->logFile, "Called GetDisplayMode\n");
	return this->dd7->GetDisplayMode(lpDDSurf);
}

HRESULT __stdcall DirectDrawWrapper::GetFourCCCodes(LPDWORD lpNumCodes, LPDWORD lpCodes)
{
	fprintf(this->logFile, "Called GetFourCCCodes\n");
	return this->dd7->GetFourCCCodes(lpNumCodes, lpCodes);
}

HRESULT __stdcall DirectDrawWrapper::GetGDISurface(LPDIRECTDRAWSURFACE *lplpGDIDDSurf)
{
	fprintf(this->logFile, "Called GetGDISurface\n");
	return this->dd7->GetGDISurface(lplpGDIDDSurf);
}

HRESULT __stdcall DirectDrawWrapper::GetMonitorFrequency(LPDWORD lpdwFreq)
{
	fprintf(this->logFile, "Called GetMonitorFrequency\n");
	return this->dd7->GetMonitorFrequency(lpdwFreq);
}

HRESULT __stdcall DirectDrawWrapper::GetScanLine(LPDWORD lpdwScanLine)
{
	fprintf(this->logFile, "Called GetScanLine\n");
	return this->dd7->GetScanLine(lpdwScanLine);
}
/*
HRESULT __stdcall DirectDrawWrapper::GetSurfaceFromDC(HDC hdc, LPDIRECTDRAWSURFACE7 *lpDDS)
{
	return this->dd7->GetSurfaceFromDC(hdc, lpDDS);
}*/

HRESULT __stdcall DirectDrawWrapper::GetVerticalBlankStatus(LPBOOL lpVB)
{
	fprintf(this->logFile, "Called GetVerticalBlankStatus\n");
	return this->dd7->GetVerticalBlankStatus(lpVB);
}

HRESULT __stdcall DirectDrawWrapper::Initialize(GUID *lpGUID)
{
	fprintf(this->logFile, "Called Initialize\n");
	return this->dd7->Initialize(lpGUID);
}
/*
HRESULT __stdcall DirectDrawWrapper::RestoreAllSurfaces()
{
	return this->dd7->RestoreAllSurfaces();
}
*/
HRESULT __stdcall DirectDrawWrapper::RestoreDisplayMode()
{
	fprintf(this->logFile, "Called RestoreDisplayMode\n");
	return this->dd7->RestoreDisplayMode();
}

HRESULT __stdcall DirectDrawWrapper::SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
{
	fprintf(this->logFile, "Called SetCooperativeLevel flags:%d\n", dwFlags);
	return this->dd7->SetCooperativeLevel(hwnd, dwFlags);
}

HRESULT __stdcall DirectDrawWrapper::SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBPP)
{
	fprintf(this->logFile, "Called SetDisplayMode w:%d h:%d bpp:%d\n", dwWidth, dwHeight, dwBPP);
	return this->dd7->SetDisplayMode(dwWidth, dwHeight, dwBPP);
}

/*
HRESULT __stdcall DirectDrawWrapper::StartModeTest(LPSIZE lpModesToTest, DWORD dwNumEntries, DWORD dwFlags)
{
	return this->dd7->StartModeTest(lpModesToTest, dwNumEntries, dwFlags);
}

HRESULT __stdcall DirectDrawWrapper::TestCooperativeLevel()
{
	return this->dd7->TestCooperativeLevel();
}*/

HRESULT __stdcall DirectDrawWrapper::WaitForVerticalBlank(DWORD dwFlags, HANDLE hEvent)
{
	fprintf(this->logFile, "Called WaitForVerticalVblank\n");
	return this->dd7->WaitForVerticalBlank(dwFlags, hEvent);
}

void DirectDrawWrapper::SetLogFile(FILE* log)
{
	this->logFile = log;
}
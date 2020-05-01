// LoadDll
// Copyright(C)2006 Tonny Petersen (tsp@person.dk) 
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA, or visit
// http://www.gnu.org/copyleft/gpl.html .

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include "avs_headers\avisynth.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

void __cdecl UnloadDll(void* hinst,IScriptEnvironment* env)
{
	if(hinst)
		FreeLibrary(static_cast<HMODULE>(hinst)); 
}

AVSValue __cdecl LoadDll(AVSValue args, void* user_data, IScriptEnvironment* env){
	HMODULE hinst=0;
	hinst=LoadLibrary(args[0].AsString());
	env->AtExit(UnloadDll,hinst);
	return hinst!=NULL;
}

const AVS_Linkage *AVS_linkage = 0;
extern "C" __declspec(dllexport) const char* __stdcall AvisynthPluginInit3(IScriptEnvironment* env, const AVS_Linkage* const vectors) {
	AVS_linkage = vectors;
	env->AddFunction("loaddll", "s", LoadDll, 0);
	return "loaddll 1.0";
}

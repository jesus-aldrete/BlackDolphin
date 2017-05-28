/*

Copyright 2017 Jesús E. Aldréte Hernández

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

//---------------------------------------------------------------------------

#include <fmx.h>
#ifdef _WIN32
#include <tchar.h>
#include <wGeneral.h>
#endif
#pragma hdrstop
#include <System.StartUpCopy.hpp>
//---------------------------------------------------------------------------
USEFORM("f01_Main.cpp", f01Main);
//---------------------------------------------------------------------------
HCURSOR gdragCursor  = NULL;
HCURSOR genterCursor = NULL;
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		if ( ParamStr(1) != "/C" ) {
			STARTUPINFO         sti = {0}; sti.cb = sizeof(sti);
			PROCESS_INFORMATION pri = {0};

			if (
				CreateProcess( NULL, ( ParamStr(0) + ".bat" ).w_str(), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &sti, &pri )
			) return 0;
		}

		Application->Initialize();
		Application->CreateForm(__classid(Tf01Main), &f01Main);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

﻿/*

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

#ifndef SfieldHPP
#define SfieldHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.Generics.Collections.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Generics.Defaults.hpp>	// Pascal unit
#include <System.Types.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sfield
{
//-- type declarations -------------------------------------------------------
template<typename T> class DELPHICLASS sField__1;
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION sField__1 : public System::Generics::Collections::TList__1<T>
{
	typedef System::Generics::Collections::TList__1<T> inherited;

public:
	__fastcall sField__1(void);
	__fastcall virtual ~sField__1(void);
	static void __fastcall Cleanup(sField__1<T>* &L);
};


class DELPHICLASS sFieldByt;
class PASCALIMPLEMENTATION sFieldByt : public sField__1<System::Byte>
{
	typedef sField__1<System::Byte> inherited;

public:
	/* {sField}sField<System_Byte>.Create */ inline __fastcall sFieldByt(void) : sField__1<System::Byte>() { }
	/* {sField}sField<System_Byte>.Destroy */ inline __fastcall virtual ~sFieldByt(void) { }

};


class DELPHICLASS sFieldInt;
class PASCALIMPLEMENTATION sFieldInt : public sField__1<int>
{
	typedef sField__1<int> inherited;

public:
	/* {sField}sField<System_Integer>.Create */ inline __fastcall sFieldInt(void) : sField__1<int>() { }
	/* {sField}sField<System_Integer>.Destroy */ inline __fastcall virtual ~sFieldInt(void) { }

};


class DELPHICLASS sFieldDou;
class PASCALIMPLEMENTATION sFieldDou : public sField__1<double>
{
	typedef sField__1<double> inherited;

public:
	/* {sField}sField<System_Double>.Create */ inline __fastcall sFieldDou(void) : sField__1<double>() { }
	/* {sField}sField<System_Double>.Destroy */ inline __fastcall virtual ~sFieldDou(void) { }

};


class DELPHICLASS sFieldStr;
class PASCALIMPLEMENTATION sFieldStr : public sField__1<System::UnicodeString>
{
	typedef sField__1<System::UnicodeString> inherited;

public:
	/* {sField}sField<System_string>.Create */ inline __fastcall sFieldStr(void) : sField__1<System::UnicodeString>() { }
	/* {sField}sField<System_string>.Destroy */ inline __fastcall virtual ~sFieldStr(void) { }

};


class DELPHICLASS sFieldAns;
class PASCALIMPLEMENTATION sFieldAns : public sField__1<System::AnsiString>
{
	typedef sField__1<System::AnsiString> inherited;

public:
	/* {sField}sField<System_AnsiString>.Create */ inline __fastcall sFieldAns(void) : sField__1<System::AnsiString>() { }
	/* {sField}sField<System_AnsiString>.Destroy */ inline __fastcall virtual ~sFieldAns(void) { }

};


class DELPHICLASS sFieldUTF;
class PASCALIMPLEMENTATION sFieldUTF : public sField__1<System::UTF8String>
{
	typedef sField__1<System::UTF8String> inherited;

public:
	/* {sField}sField<System_UTF8String>.Create */ inline __fastcall sFieldUTF(void) : sField__1<System::UTF8String>() { }
	/* {sField}sField<System_UTF8String>.Destroy */ inline __fastcall virtual ~sFieldUTF(void) { }

};


class DELPHICLASS sFieldI64;
class PASCALIMPLEMENTATION sFieldI64 : public sField__1<__int64>
{
	typedef sField__1<__int64> inherited;

public:
	/* {sField}sField<System_Int64>.Create */ inline __fastcall sFieldI64(void) : sField__1<__int64>() { }
	/* {sField}sField<System_Int64>.Destroy */ inline __fastcall virtual ~sFieldI64(void) { }

};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sfield */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SFIELD)
using namespace Sfield;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SfieldHPP

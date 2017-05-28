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

#pragma hdrstop
#include "p02_Options.h"
#include "f01_Main.h"
#pragma package(smart_init)


// Otros ####################################################################
/*Definiciones*/
#define HLoader i64[0]
//###########################################################################


// class pOtions : public cBase //###########################################
/*Creacion - controles - private*/
void pOptions::CreateThis  () {
	_rback         = new TRectangle( this );
	_rback->Parent = this;
	_rback->Align  = AL::Contents;
	_rback->StrK   = BK::None;
	_rback->FilC   = colorBlack;
 };
void pOptions::CreateNumber() {
	_lnum         = new TLayout( this );
	_lnum->Parent = this;
	_lnum->PosY   = 1000;
	_lnum->Align  = AL::Top;
	_lnum->Height = 50;
	_lnum->MarT   = 10;
	_lnum->MarL   = 10;

	_tnum                = new TText( this );
	_tnum->Parent        = _lnum;
	_tnum->PosY          = 1000;
	_tnum->Align         = AL::Top;
	_tnum->Height        = 20;
	_tnum->Color         = colorWhite;
	_tnum->Text          = "Número de elementos de las JumpList";
	_tnum->FonS          = fontSize;
	_tnum->FonF          = fontFamily;
	_tnum->HorzTextAlign = TA::Leading;

	_lnue         = new TLayout( this );
	_lnue->Parent = _lnum;
	_lnue->PosY   = 1000;
	_lnue->Align  = AL::Top;
	_lnue->Height = 20;

	_pnu1              = new TPath( this );
	_pnu1->Parent      = _lnue;
	_pnu1->PosX        = 1000;
	_pnu1->Align       = AL::Left;
	_pnu1->Width       = _pnu1->Height;
	_pnu1->StrK        = BK::None;
	_pnu1->FilC        = colorGray1;
	_pnu1->DatD        = "M50,50 M0,0 M2.6,25 47.4,50 47.4,0 z";
	_pnu1->OnMouseDown = moudw_button;

	_rnue         = new TRectangle( this );
	_rnue->Parent = _lnue;
	_rnue->PosX   = 1000;
	_rnue->Align  = AL::Left;
	_rnue->Width  = 15;
	_rnue->StrK   = BK::None;
	_rnue->FilC   = colorGray1;
	_rnue->MarL   = 5;
	_rnue->MarR   = 5;

	_fnue         = new fLine( this );
	_fnue->Parent = _rnue;
	_fnue->Align  = AL::Contents;
	_fnue->Color  = colorWhite;
	_fnue->Fill   = colorHigh;

	_pnu2              = new TPath( this );
	_pnu2->Parent      = _lnue;
	_pnu2->PosX        = 1000;
	_pnu2->Align       = AL::Left;
	_pnu2->Width       = _pnu2->Height;
	_pnu2->StrK        = BK::None;
	_pnu2->FilC        = colorGray1;
	_pnu2->DatD        = "M0,0 M50,50 M47.4,25 2.6,0 2.6,50 z";
	_pnu2->OnMouseDown = moudw_button;
 };
void pOptions::CreateIcon  () {
	_lico         = new TLayout( this );
	_lico->Parent = this;
	_lico->Align  = AL::Client;
	MarG( _lico, 10 );

	_tico                = new TText( this );
	_tico->Parent        = _lico;
	_tico->PosY          = 1000;
	_tico->Align         = AL::Top;
	_tico->Height        = 20;
	_tico->Color         = colorWhite;
	_tico->Text          = "Icono";
	_tico->FonS          = fontSize;
	_tico->FonF          = fontFamily;
	_tico->HorzTextAlign = TA::Leading;

	_iico             = new TImage( this );
	_iico->Parent     = _lico;
	_iico->Align      = AL::Client;
	_iico->MarT       = 5;
	_iico->OnDblClick = dblcl_icon;
 };

/*Creacion - public*/
__fastcall pOptions::pOptions( TComponent *owner ) : cBase(owner) {
	CreateThis  ();
	CreateNumber();
	CreateIcon  ();
 };
//###########################################################################


/*Hilos - private*/
void __fastcall pOptions::thini_save( wThread *hil ) {
	if ( _change == ouNumber || _change == ouAll ) {
		/*Save Number*/
		int        num = sai( _fnue->Text );
		wRegistry *reg = new wRegistry;

		reg->HKey = HKEY_CURRENT_USER;
		reg->Pass = KEY_READ | KEY_WRITE;
		reg->Key  = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced";

		if ( reg->OpenKey( false ) ) {
			reg->Int( "JumpListItems_Maximum", num );
			reg->Int( "Start_JumpListItems"  , num );
		}

		delete reg;
	}

	if ( _change == ouIcon || _change == ouAll ) {
		/*Save Image*/
		if ( _pathIcon != "" ) {
			String pat = ParamStr( 0 );

			DeleteFile( pat + ".borrar" );
			MoveFile( pat.w_str(), ( pat + ".borrar" ).w_str() );
			CopyFile( ( pat + ".borrar" ).w_str(), pat.w_str(), false );

			if ( !ChangeIconExe( _pathIcon.w_str(), pat.w_str(), L"MAINICON", false ) )
				MoveFile( ( pat + ".borrar" ).w_str(), pat.w_str() );

			DeleteFile( pat + ".borrar" );

			//Recargar Explorer
			SHChangeNotify( SHCNE_ASSOCCHANGED, SHCNF_IDLIST, null, null );
		}
	}
 };
void __fastcall pOptions::thfin_save( wThread *hil ) {
	((Tf01Main*)Owner       )->ActiveMenu( true );
	((fLoader *)hil->HLoader)->HideL( true );
 };
//###########################################################################


/*Eventos - private*/
void __fastcall pOptions::moudw_button( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	varPom;
	double tma = TTime( 0, 0, 0, 100 ).Val;
	TTime  ti1 = Time() - TTime( 0, 0, 0, 200 );

	do {
		if ( ( Time() - ti1 ).Val >= tma ) {
			ti1 = Time();

			int num = sai( _fnue->Text );

			if ( sender == _pnu1 ) num--; else num++;

			if ( num > 50 ) num = 50;
			if ( num < 1  ) num = 1 ;

			_fnue->Text = (String)num;

			_change = _change == ouNone ? ouNumber : ouAll;

		}

		Application->ProcessMessages();
	}
	while ( whileDown );
 };

void __fastcall pOptions::dblcl_icon( TObject *sender ) {
	wDialog *
	dig         = new wDialog;
	dig->Filter = "*.ico|Archivo de icono";
	dig->Index  = 0;

	if ( dig->RunOP() )
		ChangeIcon( dig->Path );

	delete dig;
 };

void __fastcall pOptions::loini_save( TObject *sender ) {
	_rback->Opacity = 0;
	_lnum ->Opacity = 0;
	_lico ->Opacity = 0;

	wThread*
	hil           = new wThread;
	hil->onThread = thini_save;
	hil->onFinal  = thfin_save;
	hil->HLoader  = (__int64)sender;
	hil->Play();
 };
void __fastcall pOptions::lofin_save( TObject *sender ) {
	_rback->Opacity = 1;
	_lnum ->Opacity = 1;
	_lico ->Opacity = 1;

	this->Visible = false;
 };
void __fastcall pOptions::anfin_save( fAnim   *sender ) {
	lofin_save( null );
 };
//###########################################################################


/*Metodos - public*/
pOptions *pOptions::Load() {
	_change = ouNone;

	/*Load Number*/
	int num = 0;

	wRegistry *
	reg       = new wRegistry;
	reg->HKey = HKEY_CURRENT_USER;
	reg->Pass = KEY_READ;
	reg->Key  = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced";

	if ( reg->OpenKey( false ) ) {
		num = reg->DefInt( "JumpListItems_Maximum", snan );

		if ( num == snan )
			num = reg->DefInt( "Start_JumpListItems", snan );
	}

	_fnue->Text = (String)num;

	delete reg;

	/*Load Image*/
	TMemoryStream *mem = GetIconStream( ParamStr( 0 ), 0 );
	if ( mem->Size ) { mem->Position = 0; _iico->Bitmap->LoadFromStream( mem ); }
	delete mem;

	return this;
 };
pOptions *pOptions::Save() {
	if ( _change == ouNone ) {
		fAnim::Opacity( (TShape*)this, "close"+(String)(int)this, 0.5, 0, sfExponentialOut, anfin_save );
	}
	else {
		((Tf01Main*)Owner)->ActiveMenu( false );

		fLoader*
		loa         = new fLoader( this );
		loa->Parent = this;
		loa->Align  = AL::Contents;
		loa->Color  = colorHigh;
		loa->Fill   = colorBlack;
		loa->onShow = loini_save;
		loa->onHide = lofin_save;
		loa->ShowL( true );
	}

	return this;
 };
//###########################################################################


/*Funciones - public*/
void pOptions::ChangeIcon( String path ) {
	_pathIcon = path;

	_iico->Bitmap->LoadFromFile( path );

	_change = _change == ouNone ? ouIcon : ouAll;
 };
//###########################################################################

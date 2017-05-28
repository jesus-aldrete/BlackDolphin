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

#include <fmx.h>
#pragma hdrstop
#include "f01_Main.h"
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource "_BlackDolphin.res"
Tf01Main *f01Main;



//Otros #####################################################################
/*Definiciones*/
#define widthForm  350
#define heightForm 450
//###########################################################################



// class Tf01Main : public TForm //##########################################
/*Creacion - private*/
void Tf01Main::CreatePanel( TLayout *parent, cBase *panel ) {
	panel->Parent  = parent;
	panel->Align   = AL::Contents;
	panel->Visible = false;
 };

void Tf01Main::CreateThis  () {
	this->Width    = widthForm;
	this->Height   = heightForm;
	this->OnResize = resiz_this;

	_lback         = new TLayout( this );
	_lback->Parent = this;
	_lback->Align  = AL::Contents;
	MarG( _lback, 10 );

	_rback              = new TRectangle( this );
	_rback->Parent      = _lback;
	_rback->Align       = AL::Contents;
	_rback->StrK        = BK::None;
	_rback->FilC        = colorBlack;
	_rback->TagFloat    = dzZone;
	_rback->OnMouseDown = moudw_rback;

	_eshadow            = new TShadowEffect( this );
	_eshadow->Parent    = _rback;
	_eshadow->Direction = 0.001;
	_eshadow->Distance  = 0.001;
	_eshadow->Opacity   = 1;
	_eshadow->Softness  = 0.2;

	_cresize              = new TCircle( this );
	_cresize->Parent      = this;
	_cresize->Width       = 10;
	_cresize->Height      = 10;
	_cresize->FilC        = colorHigh;
	_cresize->StrC        = colorBlack;
	_cresize->PosY        = this->Height - _cresize->Height - 5;
	_cresize->PosX        = this->Width  - _cresize->Width  - 5;
	_cresize->Cursor      = crSizeNWSE;
	_cresize->OnMouseDown = moudw_cresize;
 };
void Tf01Main::CreateMenu  () {
	_cmenu               = new cMenu( this );
	_cmenu->Parent       = _lback;
	_cmenu->Align        = AL::MostLeft;
	_cmenu->Width        = 30;
	_cmenu->onClickPanel = panel_cmenu;
	_cmenu->onClickFiles = files_cmenu;
	_cmenu->Open();
 };
void Tf01Main::CreatePanels() {
	_lpanels         = new TLayout( this );
	_lpanels->Parent = _lback;
	_lpanels->Align  = AL::Client;

	_plinks   = new pLinks  ( this ); CreatePanel( _lpanels, _plinks   ); _plinks->Open()->Render();
	_poptions = new pOptions( this ); CreatePanel( _lpanels, _poptions );
 };

/*Creacion - public*/
__fastcall Tf01Main:: Tf01Main( TComponent *owner ) : TForm(owner) {
	_panel       = null;
	this->OnShow = showw_this;
 };
__fastcall Tf01Main::~Tf01Main(                   ) {
	if ( FileExists( ParamStr( 0 ) + ".borrar" ) ) {
		wStream *mem = new wStream;
		String   cad = AccentABat( ParamStr( 0 ) );

		mem->OnlyStr(
			">nul ping -n 2 localhost"         "\n"
			"Erase \"" + cad + ".borrar\""     "\n"
			"Erase \"" + cad + ".borrar.bat\"" "\n"
		);

		mem->Save( ParamStr( 0 ) + ".borrar.bat" );

		delete mem;

		WinExec( AnsiString( ParamStr( 0 ) + ".borrar.bat" ).c_str(), SW_HIDE );
	}
 };
//###########################################################################


/*Eventos - private*/
void __fastcall Tf01Main::showw_this( TObject *sender ) {
	GetHandle( GetActiveWindow() );

	CreateThis  ();
	CreateMenu  ();
	CreatePanels();

	this->Top  = ( Screen->WorkAreaHeight - this->Height ) / 2;
	this->Left = ( Screen->WorkAreaWidth  - this->Width  ) / 2;

	new wDragDrop( GetHandle(), drini_this, drove_this, drdro_this, (sfDrag)null );

	ShowPanel( _plinks );
 };
void __fastcall Tf01Main::resiz_this( TObject *sender ) {
	_cresize->PosY = this->Height - _cresize->Height - 5;
	_cresize->PosX = this->Width  - _cresize->Width  - 5;
 };

void __fastcall Tf01Main::drini_this( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept ) {
	_dragTimer = Time();
	_dragInter = TTime( 0, 0, 0, 150 ).Val;
	_dragDelay = 0;

	GetWindowRect( GetHandle(),&_dragFormR );
 };
void __fastcall Tf01Main::drove_this( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept ) {
	if ( files.Size ) {
		 accept  = true;
		 effects = DROPEFFECT_LINK;
	}
	else {
		IControl   *con = ObjectAtPoint( TPoint( point.x, point.y ) );
		TFmxObject *obj = con ? con->GetObjectW() : NULL;

		accept = obj && obj->TagFloat > dzNone;

		if ( accept ) {
			if ( point.y - _dragFormR.top < 30 ) {
				if ( ( Time() - _dragTimer ).Val >= _dragInter ) {
					_dragTimer = Time();

					if ( _dragDelay < 3 ) _dragDelay++;
					else _plinks->Up();
				}
			}
			else if ( point.y > _dragFormR.top + _dragFormR.Height() - 30 ) {
				if ( ( Time() - _dragTimer ).Val >= _dragInter ) {
					_dragTimer = Time();

					if ( _dragDelay < 3 ) _dragDelay++;
					else _plinks->Down();
				}
			}
			else _dragDelay = 0;
		}
	}
 };
void __fastcall Tf01Main::drdro_this( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept ) {
	if ( accept ) _plinks->Drop( texts, files, point, effects, accept );
 };

void __fastcall Tf01Main::panel_cmenu( TObject *sender ) {
	TLayout *lay = (TLayout*)sender;

	if      ( lay->TagString == "_pgroup"   ) _plinks->Insert( snan, "1,titulo" )->Load()->Last()->Render();
	else if ( lay->TagString == "_plink"    ) _plinks->Insert( snan, "0,titulo" )->Load()->Last()->Render();
	else if ( lay->TagString == "_poptions" ) ButtonOptions( lay->Tag == 1 );
	else if ( lay->TagString == "_prefresh" ) _plinks->CreateJumpList( _cmenu->Work() );
	else if ( lay->TagString == "_pdelete"  ) _plinks->DeleteJumpList(                );
 };
void __fastcall Tf01Main::files_cmenu( TObject *sender ) {
	TLayout *lay = (TLayout*)sender;

	if      ( lay->TagString == "_lsave"    ) { _cmenu->Save(); _plinks->Save(); }
	else if ( lay->TagString == "_lgarbage" ) _plinks->Open()->Load()->Render();
 };

void __fastcall Tf01Main::moudw_rback  ( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	SendMessage( GetHandle(), WM_LBUTTONUP    , 0        , 0 );
	SendMessage( GetHandle(), WM_NCLBUTTONDOWN, HTCAPTION, 0 );
 };
void __fastcall Tf01Main::moudw_cresize( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	ChangeCursor( LoadCursor( null, IDC_SIZENWSE ) );

	varPom;
	float px1 = pom.x - fom.left - x, py1 = pom.y - fom.top  - y;
	float px2, py2;
	float wid = fom.Width(), hei = fom.Height();
	HWND  han = GetHandle();

	while ( whileDown ) {
		GetCursorPos( &pom );

		px2 = wid + ( pom.x - fom.left - x - px1 ); if ( px2 < widthForm  ) px2 = widthForm ;
		py2 = hei + ( pom.y - fom.top  - y - py1 ); if ( py2 < heightForm ) py2 = heightForm;

		SetWindowPos( han, null, 0, 0, px2, py2, SWP_NOOWNERZORDER | SWP_NOMOVE );

		Application->ProcessMessages();
	}

	RestoreCursor();
 };

void __fastcall Tf01Main::anifi_panels( fAnim *sender ) {
	sender->parent->Visible = false;
 };
//###########################################################################


/*Metodos - public*/
void __fastcall Tf01Main::ActiveMenu   ( bool active ) {
	_cmenu->Active( active );
 };
void __fastcall Tf01Main::ButtonOptions( bool show   ) {
	if ( show ) {
		_poptions->Opacity = 0;
		_poptions->Visible = true;

		_poptions->Load();

		fAnim::Opacity( (TShape*)_poptions, "close"+(String)(int)_poptions, 0.5, 1, sfExponentialOut );
	}
	else _poptions->Save();
 };
//###########################################################################


/*Funciones - private*/
void Tf01Main::ShowPanel( cBase *panel ) {
	if ( _panel == null ) {
		 panel->Opacity = 0;
		 panel->Visible = true;
		_panel          = panel;

		AnimO( panel, 0.5, 1, sfCircularOut );
	}
	else if ( _panel != panel ) {
		panel->Opacity = 1;
		panel->Visible = true;
		panel->SendToBack();

		fAnim::Opacity( (TShape*)_panel, (String)(int)_panel, 0.3, 0, sfCircularOut, anifi_panels );

		_panel = panel;
	}
 };
//###########################################################################
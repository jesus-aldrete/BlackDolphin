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
#include "c03_Edit.h"
#pragma package(smart_init)

// Otros ####################################################################
/*Definiciones*/
#define widthTitle 80
//###########################################################################


// class cEdit : public cBase //#############################################
/*Creacion - Controles - private*/
void cEdit::CreateEdit  ( TLayout **lay, TText **tex, TRectangle **lin, String title ) {
	(*lay)         = new TLayout( this );
	(*lay)->Parent = _rcont;
	(*lay)->PosY   = 1000;
	(*lay)->Align  = AL::Top;
	(*lay)->Height = 20;
	(*lay)->MarT   = 5;

	(*tex)                = new TText( this );
	(*tex)->Parent        = (*lay);
	(*tex)->Align         = AL::Left;
	(*tex)->FonS          = fontSize;
	(*tex)->FonF          = fontFamily;
	(*tex)->Color         = colorGray3;
	(*tex)->Width         = widthTitle;
	(*tex)->MarR          = 5;
	(*tex)->Text          = title;
	(*tex)->HorzTextAlign = TA::Trailing;

	(*lin)          = new TRectangle( this );
	(*lin)->Parent  = (*lay);
	(*lin)->PosX    = 1000;
	(*lin)->Align   = AL::Left;
	(*lin)->Width   = 1;
	(*lin)->StrK    = BK::None;
	(*lin)->FilC    = colorGray3;
	(*lin)->Opacity = 0.6;
 };
void cEdit::CreateLine  ( TLayout  *lay, fLine **lin                                 ) {
	(*lin)              = new fLine( this );
	(*lin)->Parent      = lay;
	(*lin)->Align       = AL::Client;
	(*lin)->MarL        = 5;
	(*lin)->Color       = colorWhite;
	(*lin)->Fill        = colorHigh;
	(*lin)->onKeyChange = chang_item;
 };
void cEdit::CreateButton( TLayout  *lay, TRectangle **rec, TPath **path, String data ) {
	(*rec)               = new TRectangle( this );
	(*rec)->Parent       = lay;
	(*rec)->PosX         = 1000;
	(*rec)->Align        = AL::Right;
	(*rec)->Width        = lay->Height;
	(*rec)->StrK         = BK::None;
	(*rec)->FilC         = colorGray1;
	(*rec)->OnClick      = click_item;
	(*rec)->OnMouseEnter = mouen_item;
	(*rec)->OnMouseLeave = moule_item;

	(*path)             = new TPath( null );
	(*path)->Parent     = (*rec);
	(*path)->Align      = AL::Contents;
	(*path)->StrK       = BK::None;
	(*path)->FilC       = colorGray3;
	(*path)->HitTest    = false;
	(*path)->Data->Data = data;
	MarG( (*path), 4 );

	(*rec)->TagObject = (*path);
 };

void cEdit::CreateThis () {
	this->OnResize = resiz_this;

	_rback          = new TRectangle( this );
	_rback->Parent  = this;
	_rback->Align   = AL::Contents;
	_rback->StrK    = BK::None;
	_rback->FilC    = colorBlack;
	_rback->Opacity = 0.9;
	_rback->OnClick = click_rback;

	_rcont         = new TRectangle( this );
	_rcont->Parent = this;
	_rcont->Align  = AL::Horizontal;
	_rcont->StrK   = BK::None;
	_rcont->FilC   = colorGray1;
	_rcont->Height = ( 6 * 25 ) + 5;
	_rcont->MarL   = 5;
	_rcont->MarR   = 5;

	_eshad            = new TShadowEffect( this );
	_eshad->Parent    = _rcont;
	_eshad->Direction = 0.002;
	_eshad->Distance  = 0.002;
	_eshad->Opacity   = 0.2;
	_eshad->Softness  = 0.3;
 };
void cEdit::CreateTitle() {
	CreateEdit( &_ltitle, &_ttitle, &_rtitle, "Titulo" );
	CreateLine( _ltitle, &_ftitle );
 };
void cEdit::CreateIcon () {
	CreateEdit( &_licon, &_ticon, &_ricon, "Icono" );

	_bicon         = new TImage( this );
	_bicon->Parent = _licon;
	_bicon->PosX   = 1000;
	_bicon->Align  = AL::Left;
	_bicon->Width  = _licon->Height;
	_bicon->MarL   = 5;
	_bicon->MarR   = -3;

	CreateLine  (  _licon, &_ficon );
	CreateButton(  _licon, &_dicon, &_picon, "M0,0 M50,50 M28.8,50V39.1c0-1,0.2-1.9,0.6-2.8c0.4-0.8,0.9-1.6,1.5-2.3c0.7-0.7,1.4-1.2,2.3-1.5 c0.9-0.4,1.8-0.6,2.8-0.6h10.9c0,0,0,0,0,0V3.1c0-1.7-1.4-3.1-3.1-3.1H6.2C4.5,0,3.1,1.4,3.1,3.1v43.7c0,1.7,1.4,3.1,3.1,3.1 L28.8,50C28.8,50,28.8,50,28.8,50z M32.8,39.1V50l14.1-14.1H35.9C34.2,35.9,32.8,37.3,32.8,39.1z" );
 };
void cEdit::CreatePath () {
	CreateEdit  ( &_lpath, &_tpath, &_rpath, "Ruta" );
	CreateLine  (  _lpath, &_fpath );
	CreateButton(  _lpath, &_dpat1, &_ppat1, "M0,0 M50,50 M46.9,14.2H3.1c-1.7,0-3.1,1.4-3.1,3.1v26.8c0,1.7,1.4,3.1,3.1,3.1h43.8c1.7,0,3.1-1.4,3.1-3.1 V17.4C50,15.6,48.6,14.2,46.9,14.2z M0.4,10.8c0.9-0.4,1.8-0.6,2.8-0.6h43.8c1,0,1.9,0.2,2.8,0.6c0.1,0.1,0.2,0.1,0.4,0.2V9 c0-1.7-1.4-3.1-3.1-3.1H18.8c0-1.7-1.4-3.1-3.1-3.1H3.1C1.4,2.8,0,4.2,0,5.9V11C0.1,10.9,0.2,10.8,0.4,10.8z" );
	CreateButton(  _lpath, &_dpat2, &_ppat2, "M0,0 M50,50 M28.8,50V39.1c0-1,0.2-1.9,0.6-2.8c0.4-0.8,0.9-1.6,1.5-2.3c0.7-0.7,1.4-1.2,2.3-1.5 c0.9-0.4,1.8-0.6,2.8-0.6h10.9c0,0,0,0,0,0V3.1c0-1.7-1.4-3.1-3.1-3.1H6.2C4.5,0,3.1,1.4,3.1,3.1v43.7c0,1.7,1.4,3.1,3.1,3.1 L28.8,50C28.8,50,28.8,50,28.8,50z M32.8,39.1V50l14.1-14.1H35.9C34.2,35.9,32.8,37.3,32.8,39.1z" );
 };
void cEdit::CreateParam() {
	CreateEdit( &_lparam, &_tparam, &_rparam, "Parametros" );
	CreateLine(  _lparam, &_fparam );
 };
void cEdit::CreateRun  () {
	CreateEdit( &_lrun, &_trun, &_rrun, "Ejecutar" );
	CreateEdit( &_lruc, &_truc, &_rruc, "" );
	CreateLine(  _lruc, &_frun );

	_cruc          = new TRectangle( this );
	_cruc->Parent  = _lrun;
	_cruc->PosX    = 1000;
	_cruc->Align   = AL::Left;
	_cruc->MarT    = 3;
	_cruc->MarB    = 3;
	_cruc->MarL    = 5;
	_cruc->Width   = _lruc->Height - 6;
	_cruc->StrC    = colorGray2;
	_cruc->OnClick = check_item;
 };

/*Creacion - public*/
__fastcall cEdit::cEdit( TComponent *owner ) : cBase(owner) {
	_link = null;

	CreateThis ();
	CreateTitle();
 };
//###########################################################################


/*Propiedades - private*/
void cEdit::WTop ( float  top  ) {
	_top = top;

	if ( _top > this->Height - _rcont->Height ) _top = this->Height - _rcont->Height;
	if ( _top < 0                             ) _top = 0;

	_rcont->PosY = _top;
 };
void cEdit::WLink( cLink *link ) {
	if ( _link ) return;

	_link = link;

	_ftitle->Text = link->title;
	_ftitle->Select( link->title.Length(), snan );
	_ftitle->Render( true );
	_ftitle->SetFocus();

	if ( _link->type != 1 ) {
		CreateIcon ();
		CreatePath ();
		CreateParam();
		CreateRun  ();

		_ficon ->Text = link->icon;
		_fpath ->Text = link->path;
		_fparam->Text = link->params;
		_frun  ->Text = link->exe;

		_cruc->Tag  = link->run;
		_cruc->FilC = link->run > 0 ? colorHigh : colorBlack;

		LoadIconPath( link->icon, _bicon->Bitmap );
	}
	else {
		_rcont->Height = 30;
		_ttitle->Width = 50;
	}

	this->Opacity = 0;

	AnimO( this, 0.5, 1, sfExponentialOut );
 };
//###########################################################################


/*Eventos - private*/
void __fastcall cEdit::resiz_this( TObject *sender ) {
	float top = _top;

	if ( top > this->Height - _rcont->Height ) top = this->Height - _rcont->Height;
	if ( top < 0                             ) top = 0;

	_rcont->PosY = top;
 };

void __fastcall cEdit::click_rback( TObject *sender ) {
	TRectangle *
	zon          = new TRectangle( this );
	zon->Parent  = this;
	zon->Align   = AL::Contents;
	zon->Opacity = 0.001;

	if ( Point ) (*Point) = null;

	fAnim::Opacity( (TShape*)this, "close"+(String)(int)this, 0.5, 0, sfExponentialOut, finan_rback );
 };
void __fastcall cEdit::finan_rback( fAnim   *sender ) {
	delete this;
 };

void __fastcall cEdit::chang_item( TObject *sender ) {
	if ( !_link ) return;

	if      ( sender == _ftitle ) _link->title  = _ftitle->Text;
	else if ( sender == _ficon  ) _link->icon   = _ficon ->Text;
	else if ( sender == _fpath  ) _link->path   = _fpath ->Text;
	else if ( sender == _fparam ) _link->params = _fparam->Text;
	else if ( sender == _frun   ) _link->exe    = _frun  ->Text;

	if ( sender == _ftitle ) {
		if ( _link->ttitle )
			_link->ttitle->Text = _link->title;
	}
	else if ( sender == _ficon ) {
		LoadIconPath( _ficon->Text, _bicon->Bitmap );

		if ( _link->iicon )
			LoadIconPath( _ficon->Text, _link->iicon->Bitmap );
	}
 };
void __fastcall cEdit::click_item( TObject *sender ) {
	wDialog *dig = new wDialog;

	if      ( sender == _dicon && dig->RunOP() ) { _ficon->Text = dig->Path; chang_item( _ficon ); }
	else if ( sender == _dpat1 && dig->RunDI() ) { _fpath->Text = dig->Path; chang_item( _fpath ); }
	else if ( sender == _dpat2 && dig->RunOP() ) { _fpath->Text = dig->Path; chang_item( _fpath ); }

	delete dig;
 };
void __fastcall cEdit::mouen_item( TObject *sender ) {
	TRectangle *rec = (TRectangle*)sender;
	TPath      *pat = (TPath     *)rec->TagObject;

	AnimFC( rec, 0.5, colorGray3, sfExponentialOut );
	AnimFC( pat, 0.5, colorGray1, sfExponentialOut );
 };
void __fastcall cEdit::moule_item( TObject *sender ) {
	TRectangle *rec = (TRectangle*)sender;
	TPath      *pat = (TPath     *)rec->TagObject;

	AnimFC( rec, 0.5, colorGray1, sfExponentialOut );
	AnimFC( pat, 0.5, colorGray3, sfExponentialOut );
 };
void __fastcall cEdit::check_item( TObject *sender ) {
	if ( !_link || !_link->rback ) return;

	TRectangle *rec = (TRectangle*)sender;

	AnimFC( rec, 0.5, rec->Tag > 0 ? colorBlack : colorHigh, sfExponentialOut );

	rec->Tag           = rec->Tag > 0 ? 0 : 1;
	_link->run         = rec->Tag > 0 ? 1 : 0;
	_link->rback->FilC = rec->Tag > 0 ? colorGray2 : colorGray1;
 };
//###########################################################################
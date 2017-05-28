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
#include "p01_Links.h"
#pragma package(smart_init)



//Otros #####################################################################
/*Definiciones*/
#define heightItem 30
#define marginItem 1

#define playAll SetTimeout  ("dbldown"+String((int)this),0.25,timer_dbldown);_dbldown=true;
#define stopAll StopInterval("dbldown"+String((int)this));_dbldown=false;
//###########################################################################



//class pLinks : public cBase //#############################################
/*Creacion - controles - private*/
void pLinks::CreateThis () {
	this->OnResize     = resiz_this;
	this->OnMouseWheel = mouwh_this;

	_rback          = new TRectangle( this );
	_rback->Parent  = this;
	_rback->Align   = AL::Contents;
	_rback->StrK    = BK::None;
	_rback->FilC    = colorBlack;
	_rback->HitTest = false;
 };
void pLinks::CreateItems() {
	_lcont               = new TLayout( this );
	_lcont->Parent       = this;
	_lcont->Align        = AL::Contents;
	_lcont->ClipChildren = true;

	_litems         = new TLayout( this );
	_litems->Parent = _lcont;
	_litems->Align  = AL::Contents;
	_litems->PosY   = 0;

	_rscroll         = new TRectangle( this );
	_rscroll->Parent = _lcont;
	_rscroll->Width  = 3;
	_rscroll->Height = 30;
	_rscroll->PosY   = 0;
	_rscroll->PosX   = this->Width - _rscroll->Width;
	_rscroll->StrK   = BK::None;
	_rscroll->FilC   = colorHigh;
 };

/*Creacion - public*/
__fastcall pLinks::pLinks( TComponent *owner ) : cBase(owner) {
	_position = 0;
	_dbldown  = false;

	CreateThis ();
	CreateItems();
 };
//###########################################################################


/*Intervalos - public*/
void __fastcall pLinks::timer_scroll ( TObject *sender ) {
	AnimO( _rscroll, 0.5, 0.2, sfExponentialOut );
 };
void __fastcall pLinks::timer_dbldown( TObject *sender ) {
	_dbldown = false;
 };
//###########################################################################


/*Eventos - private*/
void __fastcall pLinks::resiz_this( TObject *sender                                                   ) {
	_rscroll->PosX = this->Width - _rscroll->Width;

	Render();
 };
void __fastcall pLinks::mouwh_this( TObject *sender, TShiftState shift, int wheelDelta, bool &handled ) {
	if ( _edit ) return;

	_position-= wheelDelta;

	Render();
 };

void __fastcall pLinks::moudw_item( TObject *sender, TMouseButton button, TShiftState shift, float x, float y ) {
	TRectangle *rec = (TRectangle*)sender;

	if ( !_dbldown ) {
		varPom; playAll;
		float px1 = pom.x, py1 = pom.y;

		while ( whileDown ) {
			GetCursorPos( &pom );

			if (
				( px1 > pom.x + toleranceDrag || px1 < pom.x - toleranceDrag ) ||
				( py1 > pom.y + toleranceDrag || py1 < pom.y - toleranceDrag )
			) {
				stopAll;

                if ( rec->Tag < 0 || rec->Tag >= _plinks.Size ) return;

				SHDRAGIMAGE *img = BMPaDBM( rec->MakeScreenshot(), x, y );
				cLink       *lin = (cLink*)rec->TagObject;
				String       cad =
					(String)lin->type   + "¦" +
					(String)lin->title  + "¦" +
					(String)lin->icon   + "¦" +
					(String)lin->path   + "¦" +
					(String)lin->params + "¦" +
					(String)lin->exe    + "¦" +
					(String)lin->run
				 ;

				cad          = StringReplace( cad, ",", "\\,", TReplaceFlags() << rfReplaceAll );
				cad          = StringReplace( cad, "¦", ","  , TReplaceFlags() << rfReplaceAll );
				rec->Opacity = 0.2;

				wDragDrop::DoDragText( DROPEFFECT_MOVE, true, img, 2, cad, (String)(int)rec );

				delete img;

				rec->Opacity = 1;

				return;
			}

			Application->ProcessMessages();
		}
	}
	else {
		stopAll;
		cLink*
		lin           = (cLink*)rec->TagObject;
		_edit         = new cEdit( null );
		_edit->Point  = &_edit;
		_edit->Parent = this;
		_edit->Align  = AL::Contents;
		_edit->Link   = lin;
		_edit->Top    = lin->rback->AbsoluteRect.Top - 10;
	}
 };
void __fastcall pLinks::close_item( TObject *sender                                                           ) {
	TRectangle *rec = (TRectangle*)sender;

	fAnim::Stop( (String)(int)rec );

	this->Delete( rec->Tag )->Load()->Render();
 };
void __fastcall pLinks::mouen_item( TObject *sender                                                           ) {
	TRectangle *rec = (TRectangle*)sender;

	AnimFC( rec, 0.5, colorGray3, sfExponentialOut );
 };
void __fastcall pLinks::moule_item( TObject *sender                                                           ) {
	TRectangle *rec = (TRectangle*)sender;

	AnimFC( rec, 0.5, colorClose, sfExponentialOut );
 };
//###########################################################################


/*Metodos - public*/
void pLinks::Up  () {
	_position-= heightItem;

	Render();
 };
void pLinks::Down() {
	_position+= heightItem;

	Render();
 };

pLinks *pLinks::Drop( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept ) {
	if ( files.Size ) {
		for ( int i = 0; i < files.Size; i++ ) {
			if ( ExtractFileExt( files[i] ).LowerCase() == ".lnk" ) {
				TInfoLink *lnk = new TInfoLink;
				String     tit = StringReplace( ExtractFileName( files[i] ), ".lnk", "", TReplaceFlags() << rfReplaceAll );
				String     ico = "";

				SolveLink( files[i].Value, lnk );

				if ( lnk->PathIcon == "" ) ico = GetPathIcon( lnk->Destiny ); else ico = lnk->PathIcon + "|" + String( lnk->IndexIcon );

				String
				cad = "0¦" + tit + "¦" + ico + "¦" + lnk->Destiny + "¦" + lnk->Arguments + "¦¦";
				cad = StringReplace( cad, ",", "\\,", TReplaceFlags() << rfReplaceAll );
				cad = StringReplace( cad, "¦", ","  , TReplaceFlags() << rfReplaceAll );

				this->Insert( snan, cad );

				delete lnk;
			}
			else if ( FileExist( files[i] ) || DirectoryExists( files[i] ) ) {
				String
				cad = "0¦" + ExtractFileName( files[i] ) + "¦" + GetPathIcon( files[i] ) + "¦" + files[i].Value + "¦¦¦";
				cad = StringReplace( cad, ",", "\\,", TReplaceFlags() << rfReplaceAll );
				cad = StringReplace( cad, "¦", ","  , TReplaceFlags() << rfReplaceAll );

				this->Insert( snan, cad );
			}
		}

		this->Load()->Last()->Render();
	}
	else {
		IControl   *con = ObjectAtPoint( TPoint( point.x, point.y ) );
		TFmxObject *obj = con ? con->GetObjectW() : NULL;
		TRectangle *rec = (TRectangle*)sai( texts[1] );

		if ( texts.Size > 1 ) {
			if ( rec ) {
				if ( !obj || obj == _litems ) this->Delete( rec->Tag )->Insert( snan    , texts[0].Value )->Load()->Render();
				else                          this->Delete( rec->Tag )->Insert( obj->Tag, texts[0].Value )->Load()->Render();
			}
		}
		else {
			if ( !obj || obj == _litems ) this->Insert( snan    , texts[0].Value )->Load()->Render();
			else                          this->Insert( obj->Tag, texts[0].Value )->Load()->Render();
		}
	}

	return this;
 };

pLinks *pLinks::Open  (                        ) {
	this->Clear( true );

	TIniFile *ini = new TIniFile( fileName );
	int       num = ini->ReadInteger( "general", "number", 0 );

	for ( int i = 0; i < num; i++ ) {
		cLink *lin  = new cLink; _plinks+= (int)lin;
		lin->index  = i;
		lin->type   = ini->ReadInteger( "_itype" , String(i), 0  );
		lin->icon   = ini->ReadString ( "_sicon" , String(i), "" );
		lin->title  = ini->ReadString ( "_stitle", String(i), "" );
		lin->path   = ini->ReadString ( "_spath" , String(i), "" );
		lin->params = ini->ReadString ( "_sparam", String(i), "" );
		lin->run    = ini->ReadInteger( "_irun"  , String(i), 0  );
		lin->exe    = ini->ReadString ( "_srun"  , String(i), "" );
		CreateLink( lin );
	}

	delete ini;
	return this;
 };
pLinks *pLinks::Save  (                        ) {
	DeleteFile( ParamStr( 0 ) + ".bat" );

	TIniFile *ini = new TIniFile( fileName );
	int       num = _plinks.Size;
	String    exe = "";
	String    par = "";

	ini->WriteInteger( "general", "number", num );

	for ( int i = 0; i < num; i++ ) {
		cLink *lin = (cLink*)_plinks[i].Value;

		ini->WriteInteger( "_itype" , String(i), lin->type   );
		ini->WriteString ( "_stitle", String(i), lin->title  );
		ini->WriteString ( "_sicon" , String(i), lin->icon   );
		ini->WriteString ( "_spath" , String(i), lin->path   );
		ini->WriteString ( "_sparam", String(i), lin->params );
		ini->WriteString ( "_srun"  , String(i), lin->exe    );
		ini->WriteInteger( "_irun"  , String(i), lin->run    );

		if ( lin->run == 1 ) {
			exe+= "\nSTART \"\" \"" + lin->path + "\"";

			if ( lin->exe != "" )
				exe+= " \"" + lin->exe + "\"";
        }
	}

	delete ini;

	if ( exe != "" ) {
		wStream *mem = new wStream;

		mem->OnlyStr( AccentABat( exe ) );
		mem->Save( ParamStr( 0 ) + ".bat" );

		delete mem;
	}

	return this;
 };
pLinks *pLinks::Load  (                        ) {
	for ( int i = 0; i < _plinks.Size; i++ ) {
		cLink *lin = (cLink*)_plinks[i].Value;

		lin->Delete();
		lin->index = i;
		CreateLink( lin );
	}

	return this;
 };
pLinks *pLinks::Last  (                        ) {
	float max, map, hei = this->Height;

	max       = _plinks.Size * ( heightItem + marginItem );
	map       = max - hei;
	_position = map;

	return this;
 };
pLinks *pLinks::Clear ( bool all               ) {
	for ( int i = 0; i < _plinks.Size; i++ )
		if ( all ) delete (cLink*)_plinks[i].Value;
		else             ((cLink*)_plinks[i].Value)->Delete();

	if ( all )
		_plinks.Clear();

	return this;
 };
pLinks *pLinks::Delete( int index              ) {
	if ( index < 0 || index >= _plinks.Size ) return this;

	delete (cLink*)_plinks[index].Value;

	_plinks-= index;

	return this;
 };
pLinks *pLinks::Insert( int index, String data ) {
	/*0¦title 4¦P:\AND\BlackCoral - Sistemas\1.ico¦path4¦param4¦run4¦0¦40102256¦*/
	data+= ",";

	cLink   *lin = new cLink;
	wchar_t *cad = data.w_str();
	int      len = data.Length();
	int      pos = 0;
	int      sta = 0;
	String   tem = "";

	for ( ;pos<len; pos++ ) {
		if ( cad[pos]=='\\' && pos+1<len && cad[pos+1]==',' ) {
			tem+= ",";
			pos++;
		}
		else if ( cad[pos]==',' ) {
			if      ( sta == 0 ) lin->type   = sai( tem );
			else if ( sta == 1 ) lin->title  = tem;
			else if ( sta == 2 ) lin->icon   = tem;
			else if ( sta == 3 ) lin->path   = tem;
			else if ( sta == 4 ) lin->params = tem;
			else if ( sta == 5 ) lin->exe    = tem;
			else if ( sta == 6 ) lin->run    = sai( tem );

			sta++;
			tem = "";
		}
		else tem+= cad[pos];
	}

	_plinks( index == snan ? _plinks.Size : index, (int)lin );

	return this;
 };
pLinks *pLinks::Render(                        ) {
	StopInterval( "scroll"+(String)(int)this );

	float max, map, msp, hei = this->Height, num = _plinks.Size;

	max = num * ( heightItem + marginItem );
	map = max - hei;

	if ( _position > map ) _position = map;
	if ( _position < 0   ) _position = 0  ;

	_litems ->MarT   = -_position;
	_rscroll->Height = max <= 0 ? 0 : ( hei * hei ) / max;

	if ( _rscroll->Height > hei || _rscroll->Height == 0 ) _rscroll->Visible = false;
	else {
		_rscroll->Visible = true;

		if ( _rscroll->Height < heightItem ) _rscroll->Height = heightItem;

		msp            = hei - _rscroll->Height;
		_rscroll->PosY = map <= 0 ? 0 : ( _position * msp ) / map;

		//Ver Scroll
		AnimO( _rscroll, 0.5, 1, sfExponentialOut );
		SetTimeout( "scroll"+(String)(int)this, 0.5, timer_scroll );
	}

	return this;
 };

void pLinks::CreateJumpList( bool work ) {
	wTaskBar *bar = new wTaskBar;
	cLink    *lin ;
	String    cat = "";
	String    ico = "";
	int       ind;

	for ( int i = 0; i < _plinks.Size; i++ ) {
		lin = (cLink*)_plinks[i].Value;

		if ( lin->type == 1 ) cat = lin->title;
		else if ( cat != "" ) {
			ico = GetPathIcon( lin->icon );
			ind = 0;

			if ( ico.Pos( "|" ) ) {
				ind = sai( ico.SubString( ico.Pos( "|" ) + 1, ico.Length() ) );
				ico = ico.SubString( 1, ico.Pos( "|" ) - 1 );
			}

			bar->AddLink( cat, lin->title, lin->path, lin->params, ico, ind );
		}
	}

	if ( work )
		bar->AddLink( "[tareas]", "Configurar opciones", ParamStr( 0 ), "/C", ParamStr( 0 ), 1 );

    bar->CreateJump();

	delete bar;
 };
void pLinks::DeleteJumpList(           ) {
	wTaskBar::DeleteJump();
 };
//###########################################################################


/*Funciones - private*/
void pLinks::CreateLink( cLink *lin ) {
	TRectangle*
	rec              = new TRectangle( null );
	rec->Parent      = _litems;
	rec->PosY        = ( lin->index * ( heightItem + marginItem ) );
	rec->Align       = AL::Top;
	rec->Height      = heightItem;
	rec->StrK        = BK::None;
	rec->FilC         = lin->run == 1 ? colorGray2 : colorGray1;
	rec->MarB        = marginItem;
	rec->MarL        = lin->type == 1 ? 0 : 10;
	rec->Tag         = lin->index;
	rec->TagObject   = (TObject*)lin;
	rec->TagFloat    = dzZone;
	rec->OnMouseDown = moudw_item;

	TRectangle*
	clo               = new TRectangle( null );
	clo->Parent       = rec;
	clo->Align        = AL::MostLeft;
	clo->Width        = 10;
	clo->StrK         = BK::None;
	clo->FilC         = colorClose;
	clo->Tag          = lin->index;
	clo->TagObject    = (TObject*)lin;
	clo->OnClick      = close_item;
	clo->OnMouseEnter = mouen_item;
	clo->OnMouseLeave = moule_item;

	TText*
	tex                = new TText( null );
	tex->Parent        = rec;
	tex->Align         = AL::VertCenter;
	tex->Height        = 20;
	tex->Color         = colorWhite;
	tex->Text          = lin->title;
	tex->MarL          = 8;
	tex->FonS          = fontSize;
	tex->FonF          = fontFamily;
	tex->HitTest       = false;
	tex->WordWrap      = false;
	tex->HorzTextAlign = TA::Leading;

	if ( lin->type != 1 ) {
		TImage*
		img          = new TImage( null );
		img->Parent  = rec;
		img->Align   = AL::Left;
		img->Width   = 25;
		img->MarR    = 5;
		img->MarL    = 5;
		img->HitTest = false;
		LoadIconPath( lin->icon, img->Bitmap );

		lin->iicon = img;
    }

	lin->rback  = rec;
	lin->rclose = clo;
	lin->ttitle = tex;
 };
//###########################################################################

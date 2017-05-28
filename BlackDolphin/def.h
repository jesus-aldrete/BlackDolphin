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

#ifndef defH
#define defH

#include <FMX.Layouts.hpp>
#include <sGeneral.h>
#include <wGeneral.h>
#include <fGeneral.h>
#include <wDragDrop.h>
#include <wThread.h>
#include <wDialog.h>
#include <wStream.h>
#include <wTaskBar.h>
#include <fAnim.h>
#include <fLine.h>
#include <fLoader.h>
#include <Vcl.Graphics.hpp>

/*Definiciones*/
#define colorBlack 0xFF353535
#define colorGray1 0xFF434343
#define colorGray2 0xFF555555
#define colorGray3 0xFF707071
#define colorWhite 0xFFB3B3B3
#define colorHigh  0xFF6DD068
#define colorClose 0xFF4C4C4D

#define toleranceDrag 5
#define widthLetter   float wil;TBitmap*bmp=new TBitmap;bmp->Canvas->Font->Family=fontFamily;bmp->Canvas->Font->Size=fontSize;wil=bmp->Canvas->TextWidth("00")-bmp->Canvas->TextWidth("0");delete bmp;

#define fileName ParamStr(0) + ".ini"

/*Enumeraciones*/
enum geDragZone    { dzNone, dzZone };
enum gOptionsUpdate{ ouNone, ouNumber, ouIcon, ouAll };

/*Clases*/
class cLink {
	public:
		cLink() {
			rback  = null;
			rclose = null;
			ttitle = null;
			iicon  = null;
		 };
		~cLink() {
			this->Delete();
		 };
		void Delete() {
			if ( iicon  ) delete iicon ; iicon  = null;
			if ( ttitle ) delete ttitle; ttitle = null;
			if ( rclose ) delete rclose; rclose = null;
			if ( rback  ) delete rback ; rback  = null;
		 };

		int    type;
		String icon;
		String title;
		String path;
		String params;
		int    run;
		String exe;

		int index;

		TRectangle *rback;
		TRectangle *rclose;
		TText      *ttitle;
		TImage     *iicon;
 };

/*Funciones*/
void ChangeCursor ( HICON cursor ) {
	if ( !cursor ) return;

	extern HCURSOR gdragCursor ;
	extern HCURSOR genterCursor;

	gdragCursor = CopyIcon( cursor );

	SetSystemCursor( gdragCursor, OCR_NORMAL );
 };
void RestoreCursor(              ) {
	extern HCURSOR gdragCursor ;
	extern HCURSOR genterCursor;

	if ( genterCursor ) SetSystemCursor( genterCursor, OCR_NORMAL );
	else                SystemParametersInfo( SPI_SETCURSORS, 0, NULL, 0 );

	DestroyIcon( gdragCursor );

	gdragCursor = null;
 };

void LoadIconPath( String path, Fmx::Graphics::TBitmap *icon ) {
	String pat = path;

	icon->Clear( 0 );

	if ( path != "" && path != "*" && icon ) {
		int   ind = 0;
		HICON hic;

		pat = GetPathIcon( path );

		if ( pat.Pos( "|" ) ) {
			ind = sai( pat.SubString( pat.Pos( "|" ) + 1, pat.Length() ) );
			pat = pat.SubString( 1, pat.Pos( "|" ) - 1 );
		}

		icon->Clear( 0 );

		if ( FileExists( pat ) ) {
			HICON hic = null;

			ExtractIconEx( pat.w_str(), ind, &hic, null, 1 );

			if ( hic ) {
				TIcon         *ico = new TIcon;
				TMemoryStream *mem = new TMemoryStream;

				ico->Handle = hic;
				ico->SaveToStream( mem );
				delete ico;

				mem->Position = 0;
				icon->LoadFromStream( mem );
				delete mem;
			}
		}
	}
 };
#endif

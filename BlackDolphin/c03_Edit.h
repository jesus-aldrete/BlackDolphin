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

#ifndef c03_EditH
#define c03_EditH

#include "c01_base.h"

class cEdit : public cBase {
	/*Variables*/public:
	cEdit **Point;

	/*Variables - Propiedades*/private:
	float  _top ;
	cLink *_link;

	/*Variables - Contorles*/private:
	TRectangle    *_rback;
	TRectangle    *_rcont;
	TShadowEffect *_eshad;

	TLayout    *_ltitle;
	TText      *_ttitle;
	TRectangle *_rtitle;
	fLine      *_ftitle;

	TLayout    *_licon;
	TText      *_ticon;
	TRectangle *_ricon;
	fLine      *_ficon;
	TRectangle *_dicon;
	TPath      *_picon;
	TImage     *_bicon;

	TLayout    *_lpath;
	TText      *_tpath;
	TRectangle *_rpath;
	fLine      *_fpath;
	TRectangle *_dpat1;
	TPath      *_ppat1;
	TRectangle *_dpat2;
	TPath      *_ppat2;

	TLayout    *_lparam;
	TText      *_tparam;
	TRectangle *_rparam;
	fLine      *_fparam;

	TLayout    *_lrun;
	TText      *_trun;
	TRectangle *_rrun;
	fLine      *_frun;

	TLayout    *_lruc;
	TText      *_truc;
	TRectangle *_rruc;
	TRectangle *_cruc;
	//###########################################################################


	/*Creacion - Controles*/private:
	void CreateEdit  ( TLayout **lay, TText **tex, TRectangle **lin, String title );
	void CreateLine  ( TLayout  *lay, fLine **lin                                 );
	void CreateButton( TLayout  *lay, TRectangle **rec, TPath **path, String data );

	void CreateThis ();
	void CreateTitle();
	void CreateIcon ();
	void CreatePath ();
	void CreateParam();
	void CreateRun  ();

	/*Creacion*/public:
	__fastcall cEdit( TComponent *owner );
	//###########################################################################


	/*Propiedades*/private:
	void WTop ( float  top  );
	void WLink( cLink *link );

	/*Propiedades*/public:
	__property float  Top  = { read=_top , write=WTop  };
	__property cLink *Link = { read=_link, write=WLink };
	//###########################################################################


	/*Eventos - private*/
	void __fastcall resiz_this( TObject *sender );

	void __fastcall click_rback( TObject *sender );
	void __fastcall finan_rback( fAnim   *sender );

	void __fastcall chang_item( TObject *sender );
	void __fastcall click_item( TObject *sender );
	void __fastcall mouen_item( TObject *sender );
	void __fastcall moule_item( TObject *sender );
	void __fastcall check_item( TObject *sender );
	//###########################################################################
 };

#endif

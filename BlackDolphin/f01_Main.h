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

#ifndef f01_MainH
#define f01_MainH
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>

#include "def.h"
#include "c01_Base.h"
#include "c02_Menu.h"
#include "p01_Links.h"
#include "p02_Options.h"

class Tf01Main : public TForm {__published:/**/
	/*Variables*/private:
	double _dragInter;
	TTime  _dragTimer;
	int    _dragDelay;
	TRect  _dragFormR;

	/*Variables - controles*/private:
	TLayout       *_lback;
	TRectangle    *_rback;
	TShadowEffect *_eshadow;
	TCircle       *_cresize;

	cMenu *_cmenu;

	TLayout  *_lpanels;
	cBase    *_panel;
	pLinks   *_plinks;
	pOptions *_poptions;
	//###########################################################################


	/*Creacion - controles*/private:
	void CreatePanel( TLayout *parent, cBase *panel );

	void CreateThis  ();
	void CreateMenu  ();
	void CreatePanels();

	/*Creacion*/public:
	__fastcall  Tf01Main( TComponent *owner );
	__fastcall ~Tf01Main(                   );
	//###########################################################################


	/*Eventos*/private:
	void __fastcall showw_this( TObject *sender );
	void __fastcall resiz_this( TObject *sender );

	void __fastcall drini_this( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );
	void __fastcall drove_this( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );
	void __fastcall drdro_this( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );

	void __fastcall panel_cmenu( TObject *sender );
	void __fastcall files_cmenu( TObject *sender );

	void __fastcall moudw_rback  ( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );
	void __fastcall moudw_cresize( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );

	void __fastcall anifi_panels( fAnim *sender );
	//###########################################################################


	/*Metodos*/public:
	void __fastcall ActiveMenu   ( bool active );
	void __fastcall ButtonOptions( bool show   );
	//###########################################################################


	/*Funciones*/private:
	void ShowPanel( cBase *panel );
	//###########################################################################
 };

extern PACKAGE Tf01Main *f01Main;
#endif

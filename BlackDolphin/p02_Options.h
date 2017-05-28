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

#ifndef p02_OptionsH
#define p02_OptionsH

#include "c01_base.h"

class pOptions : public cBase {
	/*Variables*/private:
	gOptionsUpdate _change  ;
	String         _pathIcon;

	/*Variables - Controles*/private:
	TRectangle *_rback;

	TLayout    *_lnum;
	TText      *_tnum;
	TLayout    *_lnue;
	TPath      *_pnu1;
	TPath      *_pnu2;
	TRectangle *_rnue;
	fLine      *_fnue;

	TLayout *_lico;
	TText   *_tico;
	TImage  *_iico;
	//###########################################################################


	/*Creacion - controles*/private:
	void CreateThis  ();
	void CreateNumber();
	void CreateIcon  ();

	/*Creacion*/public:
	__fastcall pOptions( TComponent *owner );
	//###########################################################################


	/*Hilos - private*/
	void __fastcall thini_save( wThread *hil );
	void __fastcall thfin_save( wThread *hil );
	//###########################################################################


	/*Eventos*/private:
	void __fastcall moudw_button( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );

	void __fastcall dblcl_icon( TObject *sender );

	void __fastcall loini_save( TObject *sender );
	void __fastcall lofin_save( TObject *sender );
	void __fastcall anfin_save( fAnim   *sender );
	//###########################################################################


	/*Metodos*/public:
	pOptions *Load();
	pOptions *Save();
	//###########################################################################


	/*Funciones*/public:
	void ChangeIcon( String path );
	//###########################################################################
 };

#endif

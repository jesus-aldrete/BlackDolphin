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

#ifndef p01_LinksH
#define p01_LinksH

#include "c01_base.h"
#include "c03_Edit.h"

class pLinks : public cBase {
	/*Variables*/private:
	float _position;

	sIField _plinks;

	bool _dbldown;

	cEdit *_edit;

	/*Variables - controles*/private:
	TRectangle *_rback;

	TLayout    *_lcont;
	TLayout    *_litems;
	TRectangle *_rscroll;
	//###########################################################################


	/*Creacion - controles*/private:
	void CreateThis ();
	void CreateItems();

	/*Creacion*/public:
	__fastcall pLinks( TComponent *owner );
	//###########################################################################


	/*Intervalos*/public:
	void __fastcall timer_scroll ( TObject *sender );
	void __fastcall timer_dbldown( TObject *sender );
	//###########################################################################


	/*Eventos*/private:
	void __fastcall resiz_this( TObject *sender                                                   );
	void __fastcall mouwh_this( TObject *sender, TShiftState shift, int wheelDelta, bool &handled );

	void __fastcall moudw_item( TObject *sender, TMouseButton button, TShiftState shift, float x, float y );
	void __fastcall close_item( TObject *sender                                                           );
	void __fastcall mouen_item( TObject *sender                                                           );
	void __fastcall moule_item( TObject *sender                                                           );
	//###########################################################################


	/*Metodos*/public:
	void Up  ();
	void Down();

	pLinks *Drop( sSField texts, sSField files, POINTL point, DWORD &effects, bool &accept );

	pLinks *Open  (                        );
	pLinks *Save  (                        );
	pLinks *Load  (                        );
	pLinks *Last  (                        );
	pLinks *Clear ( bool all               );
	pLinks *Delete( int index              );
	pLinks *Insert( int index, String data );
	pLinks *Render(                        );

	void CreateJumpList( bool work );
	void DeleteJumpList(           );
	//###########################################################################


	/*Funciones*/private:
	void CreateLink( cLink *lin );
	//###########################################################################
 };

#endif

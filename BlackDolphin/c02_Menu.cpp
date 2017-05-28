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
#include "c02_Menu.h"
#pragma package(smart_init)

// class cMenu : public cBase //#############################################
/*Creacion - controles - private*/
void cMenu::CreateButton( TLayout *parent, TLayout **button, TNotifyEvent onclick, String id, String data ) {
	(*button)               = new TLayout( this );
	(*button)->Parent       = parent;
	(*button)->PosY         = parent->Height + 1000;
	(*button)->Align        = AL::Top;
	(*button)->Height       = 18;
	(*button)->HitTest      = true;
	(*button)->TagString    = id;
	(*button)->OnClick      = onclick;
	(*button)->OnMouseEnter = mouen_this;
	(*button)->OnMouseLeave = moule_this;

	TRectangle *
	rec          = new TRectangle( this );
	rec->Parent  = (*button);
	rec->Align   = AL::Contents;
	rec->StrK    = BK::None;
	rec->FilC    = colorBlack;
	rec->HitTest = false;

	TPath *
	pat             = new TPath( this );
	pat->Parent     = (*button);
	pat->Align      = AL::Center;
	pat->Height     = 13;
	pat->Width      = 13;
	pat->StrK       = BK::None;
	pat->FilC       = colorGray3;
	pat->HitTest    = false;
	pat->Data->Data = data;


	pat      ->TagObject = rec;
	(*button)->TagObject = pat;
 };

void cMenu::CreateThis  () {
	this->CanFocus = true;
 };
void cMenu::CreateSystem() {
	_system         = new TLayout( this );
	_system->Parent = this;
	_system->Align  = AL::Top;
	_system->MarT   = 5;

	CreateButton( _system, &_lclose   , click_lclose   , "_lclose"   , "M15,2.1 12.9,0 7.5,5.4 2.1,0 0,2.1 5.4,7.5 0,12.9 2.1,15 7.5,9.6 12.9,15 15,12.9 9.6,7.5z M0,0 M15,15" );
	CreateButton( _system, &_lminimize, click_lminimize, "_lminimize", "M0,6.3 15,6.3 15,8.8 0,8.8z M0,0 M15,15" );
	CreateButton( _system, &_lpin     , click_lpin     , "_lpin"     , "M9,8.9 9,3.1 6,3.1 6,8.9 0,8.9 0,11.9 15,11.9 15,8.9z M0,0 M15,15" );

	_system->Height = 18 * 3;
 };
void cMenu::CreatePanels() {
	_panels         = new TLayout( this );
	_panels->Parent = this;
	_panels->Align  = AL::VertCenter;

	CreateButton( _panels, &_pgroup  , click_panel   , "_pgroup"  , "M0,0 M50,50 M48.4,7.8h-5.5V2.3c0-0.9-0.7-1.6-1.6-1.6h-4.3c-0.9,0-1.6,0.7-1.6,1.6v5.5H30 c-0.9,0-1.6,0.7-1.6,1.6v4.3c0,0.9,0.7,1.6,1.6,1.6h5.5v5.5c0,0.9,0.7,1.6,1.6,1.6h4.3c0.9,0,1.6-0.7,1.6-1.6v-5.5h5.5 c0.9,0,1.6-0.7,1.6-1.6V9.3C50,8.5,49.3,7.8,48.4,7.8z M31.5,31.3l-5.4-8.6l-4.7,2.9l0.2-0.9l-8.3-2.1l-2.4,9.8l2.8,0.7v7.6h8.6v-0.5l5.3,1.7l3.1-9.7 l-0.6-0.2L31.5,31.3z M21,30.8h-0.9l0.2-1L21,30.8z M41.4,24.2h-4.3c-1.9,0-3.5-1.6-3.5-3.5v-3.6H30c-1.9,0-3.5-1.6-3.5-3.5v-4H12.4 c-1.3,0-2.4,0.7-2.4,1.6v2.2H0v35.9h42.4V24C42.1,24.1,41.7,24.2,41.4,24.2z M32.5,33l-3.7,11.5l-5.3-1.7H11.7v-8L8.6,34l3.3-13.6 l10.3,2.5l4.6-2.9L34.2,32L32.5,33z" );
	CreateButton( _panels, &_plink   , click_panel   , "_plink"   , "M0,0 M50,50 M50,9.5v4.3c0,0.9-0.7,1.6-1.6,1.6h-5.5v5.5c0,0.9-0.7,1.6-1.6,1.6h-4.3c-0.9,0-1.6-0.7-1.6-1.6 v-5.5H30c-0.9,0-1.6-0.7-1.6-1.6V9.5c0-0.9,0.7-1.6,1.6-1.6h5.5V2.4c0-0.9,0.7-1.6,1.6-1.6h4.3c0.9,0,1.6,0.7,1.6,1.6v5.5h5.5 C49.3,7.9,50,8.6,50,9.5z M26.5,10.1H1.4c-0.8,0-1.4,0.6-1.4,1.4V20l0.1,0c0,0,0.9,0,2,0h16.3c1,0,3.3-0.2,4.2-0.4 c0.1-0.2,0.2-0.6,0.2-1v-3.4c0-2.1,1.7-3.8,3.8-3.8V10.1z M18,39.9c0,0-3.1,1.9-5.9,2c0,0,9.5,3.8,12.3,7.2c0,0-1.1-8.8,2.5-13.8c0,0-3,1.4-4.8,2.3 c0,0-10.1-24.2-22,2.7C0,40.3,7.7,22.8,18,39.9z M11.4,43.7c-0.8-0.3-1.3-1.2-1.2-2.1c0.2-0.9,0.9-1.6,1.8-1.6c1,0,1,0,1,0 c1.2-0.4,0.2-3-2.2-5.6c0,0,0,0-2,0c-3.4,0-6.3,4.9-7.2,6.8c-0.3,0.7-0.3,0.7-0.3,0.7C0.6,42.1,0,43.5,0,45s0.2,3,0.3,3.4 s5.7,0.7,11.2,0.7h0.1c5.5,0,6.7-1.9,2.7-4.3C14.4,44.9,14.4,44.9,11.4,43.7z M41.7,24.3c-0.2,0-1.3,0-2.5,0s-2.9-0.4-3.9-0.8S33.6,20,33.6,19s-0.8-1.8-1.8-1.8 c-1,0-2.6-0.4-3.5-0.8c-1-0.4-1.7-2.8-1.7-2.9s-0.4-0.2-0.9-0.2c-0.5,0-0.9,1.6-0.9,3.6s-0.4,3.9-1,4.3c-0.5,0.4-7.9,0.7-13.4,0.7 h-0.1c-5.5,0-10,0-10,0S0,25.1,0,28.9s2.7,3.4,5.9-1.1c0,0,1.5-2.1,5.8-2.1c3.2,0,6.2,2,9,5.8c0.9,1.3,0.9,1.3,0.9,1.3 c0.7,1.3,2.6,1.6,4.3,0.9c0,0,0,0,0.1,0c0.8-0.4,1.7-0.2,2.3,0.5c0.6,0.7,0.6,1.6,0.1,2.3C25.9,40,25.9,40,25.9,40 c0.2,4.8,0.4,8.8,0.4,8.9c0,0.1,3.3,0.2,7.3,0.2s7.6-0.1,8-0.3c0.4-0.2,0.8-5.6,0.8-11.1v-3.5C42.4,28.7,41.9,24.3,41.7,24.3z" );
	CreateButton( _panels, &_prefresh, click_panel   , "_prefresh", "M0,0 M50,50 M50,47.1H0v-6.6h50V47.1z M0.2,46.9h49.7v-6.3H0.2V46.9z M0.1,40.6V47h49.8v-6.4H0.1z M28.3,46.3h-6.5v-5h6.5V46.3z M37.3,40.1H13.4c-0.3,0-0.6-0.3-0.6-0.6v-36c0-0.3,0.3-0.6,0.6-0.6h23.9c0.3,0,0.6,0.3,0.6,0.6 v36C37.9,39.8,37.6,40.1,37.3,40.1z M13.4,3.1c-0.2,0-0.4,0.2-0.4,0.4v36c0,0.2,0.2,0.4,0.4,0.4h23.9c0.2,0,0.4-0.2,0.4-0.4v-36 c0-0.2-0.2-0.4-0.4-0.4H13.4z M37.3,3H13.4c-0.3,0-0.5,0.2-0.5,0.5v36c0,0.3,0.2,0.5,0.5,0.5h23.9c0.3,0,0.5-0.2,0.5-0.5v-36 C37.8,3.2,37.6,3,37.3,3z M37.2,39c0,0.3-0.2,0.5-0.5,0.5H13.9c-0.3,0-0.5-0.2-0.5-0.5V4c0-0.3,0.2-0.5,0.5-0.5h22.8 c0.3,0,0.5,0.2,0.5,0.5V39z M36.6,19.5L35,11.8l-1.7,1.7c-4.4-4.4-11.5-4.4-15.9,0c-1.9,1.9-3,4.3-3.2,6.7l3.7,0.3 c0.2-1.6,0.9-3.2,2.2-4.5c2.9-2.9,7.7-2.9,10.6,0l-1.7,1.7L36.6,19.5z M36.5,22.7l-3.7-0.3c-0.2,1.6-0.9,3.2-2.2,4.5c-2.9,2.9-7.7,2.9-10.6,0l1.7-1.7l-7.7-1.6 l1.6,7.7l1.7-1.7c4.4,4.4,11.5,4.4,15.9,0C35.2,27.6,36.2,25.2,36.5,22.7z" );
	CreateButton( _panels, &_pdelete , click_panel   , "_pdelete" , "M0,0 M50,50 M16.1,25.2h18.5c0.9,0,1.6-0.7,1.6-1.6v-4.3c0-0.9-0.7-1.6-1.6-1.6H16.1 c-0.9,0-1.6,0.7-1.6,1.6v4.3C14.6,24.5,15.3,25.2,16.1,25.2z M50,47.1H0v-6.6h50V47.1z M0.2,46.9h49.7v-6.3H0.2V46.9z M0.1,40.6V47h49.8v-6.4H0.1z M28.3,46.3h-6.5v-5h6.5V46.3z M37.3,40.1H13.4c-0.3,0-0.6-0.3-0.6-0.6v-36c0-0.3,0.3-0.6,0.6-0.6h23.9 c0.3,0,0.6,0.3,0.6,0.6v36C37.9,39.8,37.6,40.1,37.3,40.1z M13.4,3.1c-0.2,0-0.4,0.2-0.4,0.4v36c0,0.2,0.2,0.4,0.4,0.4h23.9 c0.2,0,0.4-0.2,0.4-0.4v-36c0-0.2-0.2-0.4-0.4-0.4H13.4z M37.3,3H13.4c-0.3,0-0.5,0.2-0.5,0.5v36c0,0.3,0.2,0.5,0.5,0.5h23.9c0.3,0,0.5-0.2,0.5-0.5 v-36C37.8,3.2,37.6,3,37.3,3z M37.2,39c0,0.3-0.2,0.5-0.5,0.5H13.9c-0.3,0-0.5-0.2-0.5-0.5V4c0-0.3,0.2-0.5,0.5-0.5h22.8 c0.3,0,0.5,0.2,0.5,0.5V39z" );
	CreateButton( _panels, &_pview   , click_lview   , "_pview"   , "M0,0 M50,50 M45.1,14.7l2.2,0.4l0.8-4.2l-2.3-0.4c-0.1-1.2-0.4-2.3-0.9-3.4l1.7-1.5L44,2.3l-1.8,1.5 c-0.9-0.7-2-1.2-3.2-1.5V0h-4.3v2.3c-1.7,0.4-3.2,1.3-4.3,2.5l-2-1.1l-2.2,3.7l2,1.1c-0.2,0.8-0.4,1.6-0.4,2.5c0,0.3,0,0.7,0.1,1 l-2.1,0.8l1.5,4.1l2.1-0.8c0.7,1,1.5,1.8,2.5,2.5l-0.8,2.1l4.1,1.5l0.8-2.1c0.3,0,0.6,0.1,1,0.1c0.9,0,1.7-0.1,2.5-0.4l1.1,2 l3.7-2.2l-1.1-2C44,16.7,44.7,15.8,45.1,14.7z M36.9,14.6c-1.9,0-3.5-1.6-3.5-3.5c0-1.9,1.6-3.5,3.5-3.5c1.9,0,3.5,1.6,3.5,3.5 C40.4,13,38.8,14.6,36.9,14.6z M36.3,24.6l-7.7-2.8l1-2.6c-0.3-0.3-0.6-0.5-0.8-0.8l-2.6,1l-2.8-7.7l2.6-1 c0-0.4,0-0.8,0.1-1.2l-2.4-1.4l0.3-0.5H2.8c-0.5,0-1,0.4-1,1v40.2c0,0.6,0.4,1.2,1,1.2h33c0.5,0,1-0.6,1-1.2V23.2L36.3,24.6z" );
	CreateButton( _panels, &_poptions, click_loptions, "_poptions", "M0,0 M50,50 M43.3,33.1l5,0.9l1.7-9.6l-5-0.9c-0.2-2.7-0.9-5.3-2-7.6l3.9-3.3l-6.2-7.5l-3.9,3.3 c-2.1-1.5-4.5-2.7-7.1-3.3V0H20v5.2c-3.8,0.9-7.1,2.9-9.7,5.7L5.9,8.2l-4.8,8.4l4.4,2.6c-0.5,1.8-0.8,3.7-0.8,5.7 c0,0.7,0,1.5,0.1,2.2L0,28.9L3.3,38l4.8-1.8c1.5,2.2,3.3,4.1,5.5,5.6l-1.7,4.8l9.1,3.3l1.7-4.8c0.7,0.1,1.4,0.1,2.2,0.1 c2,0,3.8-0.3,5.6-0.8l2.6,4.5l8.4-4.9l-2.6-4.5C40.7,37.8,42.2,35.6,43.3,33.1z M24.8,32.9c-4.3,0-7.9-3.6-7.9-7.9 c0-4.4,3.5-7.9,7.9-7.9c4.4,0,7.9,3.6,7.9,7.9C32.7,29.3,29.2,32.9,24.8,32.9z" );

	_panels->Height = 18 * 6;
 };
void cMenu::CreateFiles () {
	_file         = new TLayout( this );
	_file->Parent = this;
	_file->Align  = AL::Bottom;
	_file->MarB   = 5;

	//CreateButton( _file, &_lopen   , click_files, "_lopen"   , "M10.3,4.3C10.3,4.3,10.3,4.3,10.3,4.3c-0.3,0-0.6,0-0.8-0.3C9.2,3.8,9.2,3.4,9.2,3.2V0H1.9 C1.6,0,1.3,0.3,1.3,0.6v13.8c0,0.3,0.3,0.6,0.6,0.6h11.2c0.3,0,0.6-0.3,0.6-0.6v-10L10.3,4.3z M11.7,13.8c-1-1.3-4.6-2.7-4.6-2.7 c1,0,2.2-0.8,2.2-0.8c-3.8-6.4-6.7-0.1-6.8,0.2c0,0,0,0,0,0c0,0,0,0,0,0c4.5-10.2,8.3-1,8.3-1c0.7-0.3,1.8-0.9,1.8-0.9 C11.2,10.5,11.7,13.8,11.7,13.8z M9.8,0v3.2c0,0,0,0.3,0.1,0.4c0.1,0.1,0.4,0.1,0.4,0.1l3.4,0L9.8,0z M0,0 M15,15" );
	CreateButton( _file, &_lsave   , click_files, "_lsave"   , "M14.7,0.1H0.4C0.2,0.1,0,0.2,0,0.5v12.6l1.2,1.7h13.5c0.2,0,0.3-0.3,0.3-0.5V0.5 C15,0.2,14.9,0.1,14.7,0.1z M0.8,1.4H0.2V0.7h0.7V1.4z M11.6,14.7H3.5c-0.4,0-0.4,0-0.4-0.3V9.8c0-0.3,0.3-0.6,0.7-0.6h7.3 c0.4,0,0.7,0.3,0.7,0.6v4.6C11.9,14.7,12,14.7,11.6,14.7z M13.4,8.2H1.7V0.5h11.7V8.2z M14.9,1.2h-0.5V0.6h0.5V1.2z M12.7,7.8H2.3V1h10.4v0.6c0,0,0,0,0,0c0,0,0,0,0,0V7.8z M4.6,10.1c-0.3,0-0.7,0.1-0.7,0.3v3.3c0,0.2,0.1,0.3,0.4,0.3h4.3v-4H4.6z M0,0 M15,15" );
	//CreateButton( _file, &_lsaveAs , click_files, "_lsaveAs" , "M14.7,0.1H0.4C0.2,0.1,0,0.2,0,0.5v12.6l1.2,1.7h13.5c0.2,0,0.3-0.3,0.3-0.5V0.5 C15,0.2,14.9,0.1,14.7,0.1z M0.8,1.4H0.2V0.7h0.7V1.4z M11.6,14.7H3.5c-0.4,0-0.4,0-0.4-0.3V9.8c0-0.3,0.3-0.6,0.7-0.6h7.3 c0.4,0,0.7,0.3,0.7,0.6v4.6C11.9,14.7,12,14.7,11.6,14.7z M13.4,8.2H1.7V0.5h11.7V8.2z M14.9,1.2h-0.5V0.6h0.5V1.2z M4.6,10.1c-0.3,0-0.7,0.1-0.7,0.3v3.3c0,0.2,0.1,0.3,0.4,0.3h4.3v-4H4.6z M2.4,1.8 7.5,6.9 12.6,1.8z M0,0 M15,15" );
	CreateButton( _file, &_lgarbage, click_files, "_lgarbage", "M0,0 M50,50 M19.3,28.7l0.3,0.1l-1.4-2.5l-2.5,0l0.2,0.1l-2.1,4l2.5,4.3c0.2-0.4,0.5-1,0.9-2l0.2-0.4l0,0 c0.5-0.9,1-1.9,1.6-3.1L19.3,28.7z M23.9,20c-0.2-0.3-0.6-0.9-1.2-1.7c-0.6-0.4-1.2-0.6-1.6-0.6c-0.6,0-0.8,0.3-0.8,0.4l0,0l0,0 l-2.5,4.4l3.5,1.8L23.9,20z M25.4,19.6C25.4,19.6,25.4,19.6,25.4,19.6l0.3,0.4l0,0c0.6,0.8,1.2,1.8,1.9,2.9l0.3,0.5 l-0.2,0.2l2.9,0.1l1.2-2.1l-0.2,0.1l-2.4-3.8h-5C24.4,18.1,24.8,18.7,25.4,19.6L25.4,19.6z M18.4,33.7c-0.2,0.4-0.5,1-0.8,1.8c0,1.2,0.2,1.7,0.5,1.9c0.2,0.3,0.5,0.3,0.6,0.3l0,0l0,0 l5.1-0.1l-0.2-3.9L18.4,33.7z M32,33.4L32,33.4c-1,0.1-2.2,0.1-3.4,0.1l-0.6,0l-0.1-0.3l-1.5,2.5l1.2,2.1l0-0.2l4.5-0.2 l2.5-4.3c-0.4,0-1.1,0.1-2.2,0.2L32,33.4z M36.2,29.6L36.2,29.6l-2.6-4.4l-3.3,2.1l2.6,4.5c0.4,0,1.1-0.1,2-0.2c1-0.6,1.4-1.1,1.4-1.4 C36.3,29.9,36.2,29.7,36.2,29.6L36.2,29.6z M29.1,32.1c0.7,0,1.4-0.1,2.1-0.1l-2.9-5.1l2.8-1.7L24,25l1.9-1.8c-0.4-0.6-0.8-1.2-1.1-1.8 l-3,5.1l-2.6-1.3l3.3,6l-2.5-0.7c-0.4,0.7-0.7,1.3-1,1.9l5.9,0l0.1,2.8l3.4-5.6L29.1,32.1z M44.7,3.1c0,0.9-0.6,1.7-1.4,1.7H6.7C6,4.8,5.3,4,5.3,3.1V1.7C5.3,0.7,6,0,6.7,0h36.6 c0.8,0,1.4,0.7,1.4,1.7V3.1z M46,3.5h-0.8c-0.2,1-1,1.8-1.9,1.8H6.7c-1,0-1.8-0.8-1.9-1.8H4c-0.9,0-1.6,0.7-1.6,1.7v1.5 c0,0.9,0.7,1.7,1.6,1.7h42c0.9,0,1.6-0.7,1.6-1.7V5.2C47.6,4.3,46.9,3.5,46,3.5z M4.2,8.9l4.3,39.5c0,0.9,0.6,1.7,1.4,1.7h30.3c0.8,0,1.4-0.7,1.4-1.7l4.3-39.5H4.2z M37.7,30.6 c-0.1,0.3-0.2,0.6-0.4,0.9l0,0L33,38.9l-4,0.2l-0.4,3.4l-3.5-6l0.1,2.7l-6.5,0.1c0,0-0.1,0-0.1,0c-0.3,0-1-0.1-1.7-0.7 c-0.2-0.2-0.3-0.4-0.5-0.7l0,0l-4.3-7.5l1.9-3.6l-2.8-2l7.4,0l-2.9-1.5l3.2-5.7c0.2-0.5,0.9-1.3,2.1-1.3c0.1,0,0.1,0,0.2,0l0,0h8.6 l2.1,3.4l3.1-1.4l-3.8,6.5l2.6-1.7l3.3,5.6C37.5,29,37.9,29.7,37.7,30.6z" );

	_file->Height = 18 * 2;
 };

/*Creacion - public*/
__fastcall cMenu::cMenu( TComponent *owner ) : cBase(owner) {
	CreateThis  ();
	CreateSystem();
	CreatePanels();
	CreateFiles ();
 };
//###########################################################################


/*Intervalos - private*/
void __fastcall cMenu::timer_refresh( TObject *sender ) {
	_prefresh->Tag = 0;

	moule_this( _prefresh );
 };
void __fastcall cMenu::timer_delete ( TObject *sender ) {
	_pdelete->Tag = 0;

	moule_this( _pdelete );
 };
void __fastcall cMenu::timer_save   ( TObject *sender ) {
	_lsave->Tag = 0;

	moule_this( _lsave );
 };
void __fastcall cMenu::timer_garbage( TObject *sender ) {
	_lgarbage->Tag = 0;

	moule_this( _lgarbage );
 };
//###########################################################################


/*Eventos - private*/
void __fastcall cMenu::mouen_this( TObject *sender ) {
	TLayout *lay = (TLayout*)sender;
	TPath   *pat = (TPath  *)lay->TagObject;

	if ( lay->Tag != 1 )
		AnimFC( pat, 1, colorHigh, sfExponentialOut );
 };
void __fastcall cMenu::moule_this( TObject *sender ) {
	TLayout *lay = (TLayout*)sender;
	TPath   *pat = (TPath  *)lay->TagObject;

	if ( lay->Tag != 1 )
		AnimFC( pat, 1, colorGray3, sfExponentialOut );
 };

void __fastcall cMenu::click_lclose   ( TObject *sender ) {
	Application->Terminate();
 };
void __fastcall cMenu::click_lminimize( TObject *sender ) {
	((TPath*)_lminimize->TagObject)->FilC = colorGray3;

	ShowWindow( GetHandle(), SW_MINIMIZE );
 };
void __fastcall cMenu::click_lpin     ( TObject *sender ) {
	_lpin->Tag = _lpin->Tag == 1 ? 0 : 1;

	SetWindowPos( GetHandle(), _lpin->Tag == 1 ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
 };

void __fastcall cMenu::click_lview   ( TObject *sender ) {
	_pview->Tag = _pview->Tag == 1 ? 0 : 1;

	//ColorButton( _lview, true );

	if ( onClickPanel ) onClickPanel( sender );
 };
void __fastcall cMenu::click_loptions( TObject *sender ) {
	_poptions->Tag = _poptions->Tag == 1 ? 0 : 1;

	ColorButton( _poptions, true );

	if ( onClickPanel ) onClickPanel( sender );
 };

void __fastcall cMenu::click_panel( TObject *sender ) {
	if      ( sender == _prefresh ) { _prefresh->Tag = 1; SetTimeout( "cMenuBRefresh", 2, timer_refresh ); }
	else if ( sender == _pdelete  ) { _pdelete ->Tag = 1; SetTimeout( "cMenuBDelete" , 2, timer_delete  ); }

	if ( onClickPanel ) onClickPanel( sender );
 };
void __fastcall cMenu::click_files( TObject *sender ) {
	if      ( sender == _lsave    ) { _lsave   ->Tag = 1; SetTimeout( "cMenuBSave"   , 2, timer_save    ); }
	else if ( sender == _lgarbage ) { _lgarbage->Tag = 1; SetTimeout( "cMenuBGarbage", 2, timer_garbage ); }

	if ( onClickFiles ) onClickFiles( sender );
 };
//###########################################################################


/*Metodos - public*/
void cMenu::ClickButton( String id   ) {
	if      ( id == "_lclose"    ) click_panel( _lclose    );
	else if ( id == "_lminimize" ) click_panel( _lminimize );
	else if ( id == "_lpin"      ) click_panel( _lpin      );

	else if ( id == "_pgroup  " ) click_panel( _pgroup   );
	else if ( id == "_plink   " ) click_panel( _plink    );
	else if ( id == "_prefresh" ) click_panel( _prefresh );
	else if ( id == "_pdelete " ) click_panel( _pdelete  );
	else if ( id == "_pview   " ) click_panel( _pview    );
	else if ( id == "_poptions" ) click_panel( _poptions );

	else if ( id == "_lopen"    ) click_panel( _lopen    );
	else if ( id == "_lsave"    ) click_panel( _lsave    );
	else if ( id == "_lsaveAs"  ) click_panel( _lsaveAs  );
	else if ( id == "_lgarbage" ) click_panel( _lgarbage );
 };
void cMenu::Active     ( bool active ) {
	_panels->Enabled = active;
	_file  ->Enabled = active;

	_panels->Opacity = active ? 1 : 0.4;
	_file  ->Opacity = active ? 1 : 0.4;
 };

cMenu *cMenu::Open() {
	TIniFile *ini = new TIniFile( fileName );

	if ( ini->ReadBool( "general", "configuracion", false ) ) {
		mouen_this( _pview );

		_pview->Tag = 1;
	}

	delete ini;
	return this;
 };
cMenu *cMenu::Save() {
	TIniFile *ini = new TIniFile( fileName );

    ini->WriteBool( "general", "configuracion", _pview->Tag == 1 );

	delete ini;
	return this;
 };
cMenu *cMenu::High() {
	StopInterval( "cMenuBRefresh" );
	StopInterval( "cMenuBDelete"  );
	StopInterval( "cMenuBSave"    );
	StopInterval( "cMenuBGarbage" );

	_prefresh->Tag = 0;
	_pdelete ->Tag = 0;
	_lsave   ->Tag = 0;
	_lgarbage->Tag = 0;

	moule_this( _prefresh );
	moule_this( _pdelete  );
	moule_this( _lsave    );
	moule_this( _lgarbage );

	return this;
 };
bool   cMenu::Work() {
	return _pview->Tag == 1;
 };
//###########################################################################


/*Funciones - private*/
void cMenu::ColorButton( TLayout *layout, bool buttonBlack ) {
	TPath      *pat = (TPath     *)layout->TagObject;
	TRectangle *rec = (TRectangle*)pat   ->TagObject;

	if ( layout->Tag == 1 ) {
		AnimFC( pat, 0.5, colorBlack, sfCircularOut );
		AnimFC( rec, 0.5, colorHigh , sfCircularOut );
	}
	else {
		AnimFC( pat, 0.5, buttonBlack ? colorHigh : colorGray3, sfCircularOut );
		AnimFC( rec, 0.5, colorBlack                          , sfCircularOut );
	}
 };
//###########################################################################
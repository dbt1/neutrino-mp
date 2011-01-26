/*
	Mediaplayer selection menu - Neutrino-GUI

	Copyright (C) 2001 Steffen Hehn 'McClean'
	and some other guys
	Homepage: http://dbox.cyberphoria.org/

	Copyright (C) 2011 T. Graf 'dbt'
	Homepage: http://www.dbox2-tuning.net/

	License: GPL

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include "gui/mediaplayer.h"

#include <global.h>
#include <neutrino.h>

#include "gui/audioplayer.h"
#include "gui/movieplayer.h"
#include "gui/pictureviewer.h"
#include "gui/upnpbrowser.h"

#include <gui/widget/icons.h>

#include <driver/screen_max.h>

#include <system/debug.h>



CMediaPlayerMenu::CMediaPlayerMenu()
{
	frameBuffer = CFrameBuffer::getInstance();

	width = w_max (40, 10); //%
	hheight = g_Font[SNeutrinoSettings::FONT_TYPE_MENU_TITLE]->getHeight();
	mheight = g_Font[SNeutrinoSettings::FONT_TYPE_MENU]->getHeight();
	height 	= hheight+13*mheight+ 10;
	selected = -1;
	x	= getScreenStartX (width);
	y	= getScreenStartY (height);
}

CMediaPlayerMenu::~CMediaPlayerMenu()
{

}

int CMediaPlayerMenu::exec(CMenuTarget* parent, const std::string &/*actionKey*/)
{
	dprintf(DEBUG_DEBUG, "init mediaplayer menu\n");
	int   res = menu_return::RETURN_REPAINT;

	if (parent)
		parent->hide();
	
	showMenu();
	
	return res;
}

void CMediaPlayerMenu::hide()
{
	frameBuffer->paintBackgroundBoxRel(x,y, width, height);
}

//show selectable mediaplayer items
void CMediaPlayerMenu::showMenu()
{
	//menue init
	CMenuWidget *media = new CMenuWidget(LOCALE_MAINMENU_MEDIA, NEUTRINO_ICON_MULTIMEDIA, width);

	media->setSelected(selected);
	media->addIntroItems();
	
	//audio player
	media->addItem(new CMenuForwarder(LOCALE_MAINMENU_AUDIOPLAYER, true, NULL, new CAudioPlayerGui(), NULL, CRCInput::RC_red, NEUTRINO_ICON_BUTTON_RED));

	//internet player
	media->addItem(new CMenuForwarder(LOCALE_INETRADIO_NAME, true, NULL, new CAudioPlayerGui(true), NULL, CRCInput::RC_green, NEUTRINO_ICON_BUTTON_GREEN));
	
	//movieplayer
	CMenuWidget *moviePlayer = new CMenuWidget(LOCALE_MAINMENU_MOVIEPLAYER, NEUTRINO_ICON_MULTIMEDIA, width);
	showMoviePlayer(moviePlayer);
	media->addItem(new CMenuForwarder(LOCALE_MAINMENU_MOVIEPLAYER, true, NULL, moviePlayer, NULL, CRCInput::RC_yellow, NEUTRINO_ICON_BUTTON_YELLOW));
	
	//pictureviewer
	media->addItem(new CMenuForwarder(LOCALE_MAINMENU_PICTUREVIEWER, true, NULL, new CPictureViewerGui(), NULL, CRCInput::RC_blue, NEUTRINO_ICON_BUTTON_BLUE));
	
	//upnp browser
	media->addItem(new CMenuForwarder(LOCALE_UPNPBROWSER_HEAD, true, NULL, new CUpnpBrowserGui(), NULL, CRCInput::RC_0, NEUTRINO_ICON_BUTTON_0));
	
	media->exec(NULL, "");
	media->hide();
	selected = media->getSelected();
	delete media;
}

//show movieplayer submenu with selectable items for moviebrowser or filebrowser
void CMediaPlayerMenu::showMoviePlayer(CMenuWidget *moviePlayer)
{ 
	CMoviePlayerGui *movieplayer_gui = new CMoviePlayerGui();
		
	moviePlayer->addIntroItems();
	moviePlayer->addItem(new CMenuForwarder(LOCALE_MOVIEBROWSER_HEAD, true, NULL, movieplayer_gui, "tsmoviebrowser", CRCInput::RC_red, NEUTRINO_ICON_BUTTON_RED));
	moviePlayer->addItem(new CMenuForwarder(LOCALE_MOVIEPLAYER_FILEPLAYBACK, true, NULL, movieplayer_gui, "fileplayback", CRCInput::RC_green, NEUTRINO_ICON_BUTTON_GREEN));
	
// #if 0
// 	//moviePlayer->addItem(new CMenuForwarder(LOCALE_MOVIEPLAYER_PESPLAYBACK, true, NULL, moviePlayerGui, "pesplayback"));
// 	//moviePlayer->addItem(new CMenuForwarder(LOCALE_MOVIEPLAYER_TSPLAYBACK_PC, true, NULL, moviePlayerGui, "tsplayback_pc"));
// 	moviePlayer->addItem(new CLockedMenuForwarder(LOCALE_MOVIEBROWSER_HEAD, g_settings.parentallock_pincode, false, true, NULL, moviePlayerGui, "tsmoviebrowser"));
// 	moviePlayer->addItem(new CLockedMenuForwarder(LOCALE_MOVIEPLAYER_TSPLAYBACK, g_settings.parentallock_pincode, false, true, NULL, moviePlayerGui, "tsplayback", CRCInput::RC_green, NEUTRINO_ICON_BUTTON_GREEN));
// 
// 	moviePlayer->addItem(new CLockedMenuForwarder(LOCALE_MOVIEPLAYER_BOOKMARK, g_settings.parentallock_pincode, false, true, NULL, moviePlayerGui, "bookmarkplayback"));
// 	moviePlayer->addItem(GenericMenuSeparator);
// 	moviePlayer->addItem(new CMenuForwarder(LOCALE_MOVIEPLAYER_FILEPLAYBACK, true, NULL, moviePlayerGui, "fileplayback", CRCInput::RC_red, NEUTRINO_ICON_BUTTON_RED));
// 	moviePlayer->addItem(new CMenuForwarder(LOCALE_MOVIEPLAYER_DVDPLAYBACK, true, NULL, moviePlayerGui, "dvdplayback", CRCInput::RC_yellow, NEUTRINO_ICON_BUTTON_YELLOW));
// 	moviePlayer->addItem(new CMenuForwarder(LOCALE_MOVIEPLAYER_VCDPLAYBACK, true, NULL, moviePlayerGui, "vcdplayback", CRCInput::RC_blue, NEUTRINO_ICON_BUTTON_BLUE));
// 	moviePlayer->addItem(GenericMenuSeparatorLine);
// 	moviePlayer->addItem(new CMenuForwarder(LOCALE_MAINMENU_SETTINGS, true, NULL, &streamingSettings, NULL, CRCInput::RC_help, NEUTRINO_ICON_BUTTON_HELP_SMALL));
// 	moviePlayer->addItem(new CMenuForwarder(LOCALE_NFSMENU_HEAD, true, NULL, new CNFSSmallMenu(), NULL, CRCInput::RC_setup, NEUTRINO_ICON_BUTTON_DBOX_SMALL));
// #endif
}
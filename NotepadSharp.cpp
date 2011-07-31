//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "stdio.h"
#include "tchar.h"
#include "PluginDefinition.h"

#define SC_UPDATE_SELECTION 0x2

extern FuncItem funcItem[nbFunc];
extern NppData nppData;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  reasonForCall, 
                       LPVOID lpReserved )
{
    switch (reasonForCall)
    {
      case DLL_PROCESS_ATTACH:
        pluginInit(hModule);
        break;

      case DLL_PROCESS_DETACH:
        pluginCleanUp();
        break;

      case DLL_THREAD_ATTACH:
        break;

      case DLL_THREAD_DETACH:
        break;
    }

    return TRUE;
}


extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
	nppData = notpadPlusData;
	commandMenuInit();
}

extern "C" __declspec(dllexport) const TCHAR * getName()
{
	return NPP_PLUGIN_NAME;
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
{
	*nbF = nbFunc;
	return funcItem;
}

int fire_enter;
int curly_brace;

char hex[] = {"0123456789AaBbCcDdEeFf#\r\n\t"};

extern "C" __declspec(dllexport) void beNotified(SCNotification *notifyCode)
{
    switch (notifyCode->nmhdr.code) 
    {
        case SCN_CHARADDED:
            if (notifyCode->ch == '\n' || notifyCode->ch == '\r')
            {
                if (fire_enter == 0) {
                    fire_enter = 1;
                }
            }
            else if (notifyCode->ch == '}')
            {
                curly_brace = 1;
            }
            else if (notifyCode->ch == ' ' || notifyCode->ch == '=')
            {
                EMBED_code();
            }
            else if (notifyCode->ch == 64)
            {
                docblock_keywords();
            }
            
            if (notifyCode->ch == 'd' || notifyCode->ch == 'e' || notifyCode->ch == 'f')
            {
                RubyExtra(notifyCode->ch);
            }

            char character[2];
            sprintf(character, "%c", notifyCode->ch);

            if (strstr(hex, character))
            {
                peek_hex_color();
            }
            character[0] = '\0';
            break;
        case SCN_UPDATEUI:
            if (SC_PERFORMED_USER && fire_enter)
            {
                Newline();
                fire_enter = 0;
            }

            if (curly_brace == 1)
            {
                indentEndingCurlyBrace();
                curly_brace = 0;
            }

            if (notifyCode->updated == SC_UPDATE_V_SCROLL) {
                peek_hex_color();
            }
            
            break;
        case SCN_MODIFIED:
            if (notifyCode->modificationType & SC_MOD_DELETETEXT)
            {
                //peek_hex_color();
            }
            break;
        case NPPN_LANGCHANGED:
            peek_hex_color();
            break;
        case NPPN_FILEBEFORECLOSE :
            get_all_files();
            break;

        case NPPN_FILECLOSED:
            find_missing();
            break;
        case NPPN_BUFFERACTIVATED:
            peek_hex_color();
            break;
        case NPPN_SHUTDOWN:
        {
            commandMenuCleanUp();
        }
        break;

        default:
            return;
    }
}


// Here you can process the Npp Messages 
// I will make the messages accessible little by little, according to the need of plugin development.
// Please let me know if you need to access to some messages :
// http://sourceforge.net/forum/forum.php?forum_id=482781
//
extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam)
{/*
	if (Message == WM_MOVE)
	{
		::MessageBox(NULL, "move", "", MB_OK);
	}
*/
	return TRUE;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode()
{
    return TRUE;
}
#endif //UNICODE

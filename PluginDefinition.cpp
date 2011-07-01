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
#include "menuCmdID.h"
#include "Version.h"

// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE hModule)
{
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );


    /**
     * Delete current line on CTRL+SHIFT+D
     */
    ShortcutKey *D_key = new ShortcutKey;
    D_key->_isAlt      = false;
    D_key->_isCtrl     = true;
    D_key->_isShift    = true;
    D_key->_key        = 0x44; // D
    setCommand(0, TEXT("Delete current line"), delete_current_line, D_key, false);


    ShortcutKey *T_key = new ShortcutKey;
    T_key->_isAlt      = false;
    T_key->_isCtrl     = true;
    T_key->_isShift    = true;
    T_key->_key        = 0x54; // T
    setCommand(1, TEXT("Undo close tab"), undo_closed_tab, T_key, false);

    ShortcutKey *I_key = new ShortcutKey;
    I_key->_isAlt      = false;
    I_key->_isCtrl     = true;
    I_key->_isShift    = true;
    I_key->_key        = 0x49 ; // I
    //setCommand(2, TEXT("INSERT ALL FILES LIST"), closed_file_list, I_key, false);


    ShortcutKey *LEFT_key = new ShortcutKey;
    LEFT_key->_isAlt      = true;
    LEFT_key->_isCtrl     = false;
    LEFT_key->_isShift    = false;
    LEFT_key->_key        = VK_LEFT ; // LEFT
    setCommand(3, TEXT("Tab left"), buffer_left, LEFT_key, false);

    ShortcutKey *RIGHT_key = new ShortcutKey;
    RIGHT_key->_isAlt      = true;
    RIGHT_key->_isCtrl     = false;
    RIGHT_key->_isShift    = false;
    RIGHT_key->_key        = VK_RIGHT ; // RIGHT
    setCommand(4, TEXT("Tab right"), buffer_right, RIGHT_key, false);

    ShortcutKey *W_key = new ShortcutKey;
    W_key->_isAlt      = true;
    W_key->_isCtrl     = true;
    W_key->_isShift    = false;
    W_key->_key        = 0x57; // W
    setCommand(6, TEXT("Wrap selection with tag"), wrap_with_tag, W_key, false);

    ShortcutKey *period = new ShortcutKey;
    period->_isAlt      = false;
    period->_isCtrl     = true;
    period->_isShift    = false;
    period->_key        = 0xBE;// VK_OEM_PERIOD  0xBE  "." any country/region
    setCommand(7, TEXT("Close last open tag"), end_tag, period, false);

    setCommand(9, TEXT("URLencode selection"), url_encode_selection, NULL, false);
    setCommand(10, TEXT("URLdecode selection"), url_decode_selection, NULL, false);

    ShortcutKey *C_key = new ShortcutKey;
    C_key->_isAlt      = false;
    C_key->_isCtrl     = true;
    C_key->_isShift    = true;
    C_key->_key        = 0x43; // C
    setCommand(12, TEXT("Column ruler"), ruler, C_key, false);

    setCommand(14, TEXT("Features"), show_features, NULL, false);
    setCommand(15, TEXT("About"), show_about, NULL, false);

    //ShortcutKey *ESC_key = new ShortcutKey;
    //ESC_key->_isAlt      = false;
    //ESC_key->_isCtrl     = false;
    //ESC_key->_isShift    = false;
    //ESC_key->_key        = 0x1B; // ESC
    //setCommand(16, TEXT("ESC"), style, ESC_key, false);

}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}

//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//

void show_features()
{
    ::MessageBox(nppData._nppHandle, FEATURES, TEXT("Notepad#"), MB_OK);
}

void show_about()
{
    ::MessageBox(nppData._nppHandle, ABOUT, TEXT("Notepad#"), MB_OK);
}

void Newline()
{
    HWND curScintilla = getCurrentScintilla();

    int lang = -100;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&lang);

    int position    = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    int line_number = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, position, 0);

    char line[9999];
    ::SendMessage(curScintilla, SCI_GETLINE, line_number - 1 , (LPARAM)&line);
    
    trim_left(line);

    switch (lang)
    {
        case L_C:
        case L_CPP:
            cStyleComment(curScintilla, line);
            indentAfterCurlyBrace(curScintilla, line_number - 1);
            break;
        case L_CSS:
            if (cStyleComment(curScintilla, line) == 0
             && indentAfterCurlyBrace(curScintilla, line_number - 1) == 0)
            {

            }
            break;
        case L_JS:
            if (cStyleComment(curScintilla, line) == 0
             && indentAfterCurlyBrace(curScintilla, line_number - 1) == 0)
            {

            }
            break;
        case L_PHP:
            if ( cStyleComment(curScintilla, line) == 0
              && poundComment(curScintilla, line) == 0
              && indentAfterCurlyBrace(curScintilla, line_number - 1) == 0)
            {
                XHTMLindent(curScintilla, position, line_number - 1);
            }
            break;
        case L_HTML:
        case L_XML:
            XHTMLindent(curScintilla, position, line_number - 1);
            break;
        case L_RUBY:
            if (poundComment(curScintilla, line) == 0)
            {
                Ruby_Newline(curScintilla);
            }
            break;
        case L_TXT:
            auto_numbering();
            break;
    }
}

int indentAfterCurlyBrace(HWND &curScintilla, int line_number)
{
    ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

    int ret = 0;

    int save_position = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);

    char selection[9999];
    int line_start = ::SendMessage(curScintilla, SCI_POSITIONFROMLINE, line_number, 0);
    int line_end   = ::SendMessage(curScintilla, SCI_GETLINEENDPOSITION, line_number, 0);
    ::SendMessage(curScintilla, SCI_SETSEL, line_start, line_end);
    ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&selection);

    char *lastchar;
    lastchar = substr(selection, strlen(selection) - 1, strlen(selection));

    char nextchar[1];
    ::SendMessage(curScintilla, SCI_SETSEL, save_position, save_position + 1);
    ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&nextchar);

    ::SendMessage(curScintilla, SCI_SETSEL, save_position, save_position);

    if (strstr(lastchar, "{"))
    {
        ret = 1;
        if (strstr(nextchar, "}"))
        {
            ::SendMessage(curScintilla, SCI_NEWLINE , 0, 0 );
            ::SendMessage(curScintilla, SCI_SETSEL, save_position, save_position);
        }

        ::SendMessage(curScintilla, SCI_TAB , 0, 0 );
    }

    ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);

    return ret;
}

void indentEndingCurlyBrace()
{
    int lang = -100;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&lang);

    if (!( lang == L_C
       || lang == L_CPP
       || lang == L_JS
       || lang == L_PHP
       || lang == L_CSS))
    {
        return;
    }

    HWND curScintilla = getCurrentScintilla();

    int save_position = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    int save_line     = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, save_position, 0);

    int line_start = ::SendMessage(curScintilla, SCI_POSITIONFROMLINE, save_line, 0);
    int line_end   = ::SendMessage(curScintilla, SCI_GETLINEENDPOSITION, save_line, 0);

    char line_contents[9999];
    ::SendMessage(curScintilla, SCI_SETSEL, line_start, line_end);
    ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&line_contents);
    ::SendMessage(curScintilla, SCI_SETSEL, save_position, save_position);

    // IF THERE ARE OTHER CHARACTERS
    if (strlen(trim(line_contents)) > 1)
    {
        return;
    }

    ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

    // FIND MATCHING BRACE INDENTATION
    ::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_SEARCH_GOTOMATCHINGBRACE);

    int opening_brace_position = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    int opening_brace_line     = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, opening_brace_position, 0);

    int brace_indent = ::SendMessage(curScintilla, SCI_GETLINEINDENTATION, opening_brace_line, 0);

    // RETURN TO SAVED POSITION
    ::SendMessage(curScintilla, SCI_SETSEL, save_position, save_position);
    // SET THE MATCHING BRACE INDENTATION
    ::SendMessage(curScintilla, SCI_SETLINEINDENTATION, save_line, brace_indent);

    ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
}

int poundComment(HWND &curScintilla, char *line)
{
    int ret = 0;
    char comment[2];
    strncpy(comment, line, 2);
    if (strstr(comment, "# "))
    {
        ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

        ret = 1;
        int pos  = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
        ::SendMessage(curScintilla, SCI_INSERTTEXT, pos, (LPARAM)"# " );
        int next = pos + 2;
        ::SendMessage(curScintilla, SCI_SETSEL, next, next);

        ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);

        auto_numbering();
    }

    return ret;
}

void style()
{
    HWND curScintilla = getCurrentScintilla();


    ::SendMessage(curScintilla, SCI_SETSEL, 0, 0);

    ::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);
    ::SendMessage(curScintilla, SCI_SEARCHNEXT, SCFIND_REGEXP, (LPARAM)"@\\w+");

    int selection_start = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
    int selection_end = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);

    //::SendMessage(curScintilla, SCI_STYLESETFONT, 2, (LPARAM) "Times New Roman");
    //::SendMessage(curScintilla, SCI_STYLESETSIZE, 2, (LPARAM)14);
    //::SendMessage(curScintilla, SCI_STYLESETITALIC, 2, (LPARAM)true);
    
    //::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)"1270");

    //::SendMessage(curScintilla, SCI_STARTSTYLING, 0, (LPARAM)0xff);
    //::SendMessage(curScintilla, SCI_STARTSTYLING, 0, (LPARAM)2);

    //::SendMessage(curScintilla, SCI_SETSTYLING, 1, 1);
    //::SendMessage(curScintilla, SCI_SETSTYLING, 1, 2);
    //::SendMessage(curScintilla, SCI_SETSTYLING, 1, 1);
    //::SendMessage(curScintilla, SCI_SETSTYLING, 1, 2);

    //::SendMessage(curScintilla, SCI_SETSTYLING, 2, 1);
    //::SendMessage(curScintilla, SCI_SETSTYLING, 2, 2);





    ::SendMessage(curScintilla, SCI_SETSEL, 0, 0);
    int len =  selection_end - selection_start;

    //SCI_STYLESETITALIC(int styleNumber, bool italic)
    ::SendMessage(curScintilla, SCI_STYLESETITALIC, 9999, (LPARAM)true);
    //SCI_STYLESETBOLD(int styleNumber, bool bold)
    ::SendMessage(curScintilla, SCI_STYLESETBOLD, 9999, (LPARAM)true);
    
    //SCI_STARTSTYLING(int pos, int mask)
    ::SendMessage(curScintilla, SCI_STARTSTYLING, 0, (LPARAM)31);

    ::SendMessage(curScintilla, SCI_SETSTYLING, 10, (LPARAM)9999);

    //while (len)
    //{
    //    ::SendMessage(curScintilla, SCI_SETSTYLING, 1, (LPARAM)9999);
    //    len--;
    //}
    //::SendMessage(curScintilla, SCI_SETSTYLING, selection_start - 150, (LPARAM)9999);



    //SCI_SETSTYLINGEX(int length, const char *styles)
    //::SendMessage(curScintilla, SCI_SETSTYLINGEX, 31, (LPARAM)STYLE_DEFAULT);

    //SCI_AUTOCSHOW(int lenEntered, const char *list)
    //::SendMessage(curScintilla, SCI_AUTOCSHOW, 1, (LPARAM)"@access @author @copyright");

    //int konj = '@';
    //char buff[200];
    //sprintf(buff, "%d", selection_start);
    //::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)buff);
}

int cStyleComment(HWND &curScintilla, char *line)
{
    int ret = 0;
    char comment[2];
    strncpy(comment, line, 2);
    
    if (strstr(comment,"* ") && ! strstr(line, "*/") )
    {
        ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

        ret = 1;
        int pos  = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
        ::SendMessage(curScintilla, SCI_INSERTTEXT, pos, (LPARAM)"* " );
        int next = pos + 2;
        ::SendMessage(curScintilla, SCI_SETSEL, next, next);

        ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
        auto_numbering();
    }
    else if (strstr(comment, "/*") && ! strstr(line, "*/") )
    {
        ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

        ret = 2;
        int pos = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
        ::SendMessage(curScintilla, SCI_INSERTTEXT, pos, (LPARAM)" * " );
        int next = pos + 3;
        ::SendMessage(curScintilla, SCI_SETSEL, next, next);

        ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
        auto_numbering();
    }
    else if (strstr(comment, "*/"))
    {
        ret = 3;
        ::SendMessage(curScintilla, SCI_DELETEBACK, 0, 0);
    }
    return ret;
}

void XHTMLindent(HWND &curScintilla, int position, int line_number)
{

    ::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);
    //::SendMessage(curScintilla, SCI_SEARCHPREV, SCFIND_REGEXP, (LPARAM)"<[^?][^\\/]+>$");
    ::SendMessage(curScintilla, SCI_SEARCHPREV, SCFIND_REGEXP, (LPARAM)"<[\\w\\/]+[\\w\\W\\b\\B]+?>\\s*$");

    char selection[9999];
    ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&selection);
    int selection_end = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);

    int line_end = ::SendMessage(curScintilla, SCI_GETLINEENDPOSITION, line_number, 0);

    // FALLBACK TO SIMPLE REGEX
    //if (selection_end != line_end)
    //{
    //    ::SendMessage(curScintilla, SCI_SETSEL, position, position);
    //    ::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);
    //    ::SendMessage(curScintilla, SCI_SEARCHPREV, SCFIND_REGEXP, (LPARAM)"<[\\w\\W\\b\\B]+?>");
    //    ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&selection);
    //    selection_end = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);
    //}

    char not_allowed[] = "!?%/";

    if (strstr(not_allowed, substr(selection, 1,1)))
    {
        ::SendMessage(curScintilla, SCI_SETSEL, position, position);
        return;
    }
    else if (selection[strlen(selection) - 2] == '/')
    {
        ::SendMessage(curScintilla, SCI_SETSEL, position, position);
        return;
    }
    
    ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

    char tag[30];
    create_ending_tag(tag);

    if (selection_end == line_end)
    {
        ::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);
        ::SendMessage(curScintilla, SCI_SEARCHNEXT, 0, (LPARAM)tag);

        int selection_start = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
        ::SendMessage(curScintilla, SCI_SETSEL, position, position);

        if (selection_start == position)
        {
            ::SendMessage(curScintilla, SCI_NEWLINE , 0, 0 );
            ::SendMessage(curScintilla, SCI_SETSEL, position, position);
        }

        ::SendMessage(curScintilla, SCI_TAB , 0, 0 );
    }
    else {
        ::SendMessage(curScintilla, SCI_SETSEL, position, position);
    }

    ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
}

char* create_ending_tag(char *tag)
{
    HWND curScintilla = getCurrentScintilla();
    char selection[9999];
    ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&selection);
    int tag_i = 2;
    int selection_i = 1;
    tag[0] = '<';
    tag[1] = '/';
    while (tag_i < 30) {
        if (selection[selection_i] == ' ' || selection[selection_i] == '>') {
            break;
        } else {
            tag[tag_i] = selection[selection_i];
            tag_i++;
            selection_i++;
        }
    }
    tag[tag_i] = '>';
    tag[tag_i+1] = '\0';

    return tag;
}

void end_tag()
{
    HWND curScintilla = getCurrentScintilla();

    ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

    int save_position = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    int save_line     = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, save_position, 0);

    char line[9999];

    ::SendMessage(curScintilla, SCI_GETCURLINE, 9999, (LPARAM)&line);

    int trim_line = strlen(trim(line));

    int matching_tag_indentation;
    int tag_line;
    
    int end = 0;
    char selection[9999];

    int last_search = 0;

    int i = 1;

    char not_allowed[] = "!?%/";

    do {
        ::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);

        //::SendMessage(curScintilla, SCI_SEARCHPREV, SCFIND_REGEXP, (LPARAM)"<[\\w\\W\\b\\B]+?>");
        /**
         * Scintillas regex engine is not very friendly
         */
        ::SendMessage(curScintilla, SCI_SEARCHPREV, SCFIND_REGEXP, (LPARAM)"<[\\w\\/][\\w\\W\\b\\B]*?>");

        end = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);
        ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&selection);

        if (end == last_search)
        {
            ::SendMessage(curScintilla, SCI_SETSEL, end, end);
            break;
        }
        last_search = end;

        if (selection[1] == '/')
        {
            i++;
        }
        else if (strstr(not_allowed, substr(selection, 1,1)))
        {
            continue;
        }
        else if (selection[strlen(selection) - 2] == '/')
        {
            continue;
        }
        else {
            i--;
        }
    }
    while (i);

    // FIXES PROBLEM WITH LAST TAG REPEATION
    int tag_selection_start = ::SendMessage(curScintilla, SCI_GETSELECTIONNSTART, 0, 0);
    int tag_selection_end   = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);

    if ( tag_selection_start != tag_selection_end )
    {
        char tag[30];
        create_ending_tag(tag);

        int taglen = strlen(tag);

        if (trim_line < 1)
        {
            tag_line = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, tag_selection_start, 0);
            matching_tag_indentation = ::SendMessage(curScintilla, SCI_GETLINEINDENTATION, tag_line, 0);
        }

        ::SendMessage(curScintilla, SCI_INSERTTEXT, save_position, (LPARAM)tag );
        ::SendMessage(curScintilla, SCI_SETSEL, save_position + taglen, save_position + taglen);

        if (trim_line < 1)
        {
            ::SendMessage(curScintilla, SCI_SETLINEINDENTATION, save_line, matching_tag_indentation);
        }
    }
    else
    {
        ::SendMessage(curScintilla, SCI_SETSEL, save_position , save_position );
    }
    
    ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
}

void delete_current_line()
{
    HWND curScintilla = getCurrentScintilla();

    ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

    int position = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    int line     = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, position, 0);
    int column   = ::SendMessage(curScintilla, SCI_GETCOLUMN, position, 0);

    int line_start  = ::SendMessage(curScintilla, SCI_POSITIONFROMLINE, line, 0);
    int line_length = ::SendMessage(curScintilla, SCI_LINELENGTH, line, 0);

    ::SendMessage(curScintilla, SCI_SETSEL, line_start, line_start + line_length);
    ::SendMessage(curScintilla, SCI_DELETEBACK, 0, 0);
    
    int restore_column = ::SendMessage(curScintilla, SCI_FINDCOLUMN, line, column);
    ::SendMessage(curScintilla, SCI_SETSEL, restore_column, restore_column);
    
    ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
}

char closed_files[300][MAX_PATH] = {};
int closed_files_index = 0;

void undo_closed_tab()
{
    int i = closed_files_index - 1;
    
    if (strlen(closed_files[i]))
    {
        HWND curScintilla = getCurrentScintilla(); 

        TCHAR path[MAX_PATH];

        int len = MultiByteToWideChar ((int)::SendMessage(curScintilla, SCI_GETCODEPAGE, 0, 0), 0, closed_files[i], -1, NULL, 0);

        MultiByteToWideChar ((int)::SendMessage(curScintilla, SCI_GETCODEPAGE, 0, 0), 0, closed_files[i], -1, path, len);
    
        ::SendMessage(nppData._nppHandle, NPPM_DOOPEN, 0, (LPARAM)path);
        closed_files[i][0] = '\0';
    }

    closed_files_index--;

    if (closed_files_index < 1)
    {
        closed_files_index = 0;
    }
}

char all_files[300][MAX_PATH] = {};
int all_files_index = 0;

void get_all_files()
{
    HWND curScintilla = getCurrentScintilla();
    
    int position = 0;
    int buffer;

    TCHAR full_file_path[MAX_PATH];
    char path_text[MAX_PATH];

    int loop = 30;

    while (loop)
    {
        buffer = ::SendMessage(nppData._nppHandle, NPPM_GETBUFFERIDFROMPOS, position, (LPARAM)MAIN_VIEW);

        ::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID, buffer, (LPARAM)full_file_path);

        WideCharToMultiByte((int)::SendMessage(curScintilla, SCI_GETCODEPAGE, 0, 0), 0, full_file_path, -1, path_text, MAX_PATH, NULL, NULL);

        if (strstr(all_files[all_files_index - 1], path_text))
        {
            all_files[all_files_index][0] = '\0';
            break;
        }

        //::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)getEOL());
        //::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)path_text );

        strcpy(all_files[all_files_index], path_text);
        position++;
        loop--;
        all_files_index++;
    }

}

char now_files[300][MAX_PATH] = {};
int now_files_index = 0;

void get_files_now()
{
    HWND curScintilla = getCurrentScintilla();
    
    int position = 0;
    int buffer;

    TCHAR full_file_path[MAX_PATH];
    char path_text[MAX_PATH];

    int loop = 30;

    while (loop)
    {
        buffer = ::SendMessage(nppData._nppHandle, NPPM_GETBUFFERIDFROMPOS, position, (LPARAM)MAIN_VIEW);

        ::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID, buffer, (LPARAM)full_file_path);

        WideCharToMultiByte((int)::SendMessage(curScintilla, SCI_GETCODEPAGE, 0, 0), 0, full_file_path, -1, path_text, MAX_PATH, NULL, NULL);

        if (strstr(now_files[now_files_index - 1], path_text))
        {
            now_files[now_files_index][0] = '\0';
            break;
        }

        strcpy(now_files[now_files_index], path_text);
        position++;
        loop--;
        now_files_index++;
    }
}

void find_missing()
{
    HWND curScintilla = getCurrentScintilla();
    
    get_files_now();

    int has = 0;

    int i;
    int j;

    int all_files_loop = all_files_index + 1;
    int now_files_loop = now_files_index + 1;
    
    now_files_index = 0;

    for(i = 0; i < all_files_loop; i++)
    {
        if (strlen(all_files[i]) < 1)
        {
            break;
        }
        
        has = 0;

        for (j = 0; j < now_files_loop; j++)
        {
            if (strlen(now_files[j]) < 1)
            {
                break;
            }

            if (strstr(all_files[i], now_files[j]))
            {
                has = 1;
            }
        }

        if (has == 0)
        {
            strcpy(closed_files[closed_files_index], all_files[i]);
            closed_files_index++;
        }
    }

    //insertList();
    //::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)getEOL());
    //closed_file_list();

    all_files_index = 0;
}

void closed_file_list()
{
    HWND curScintilla = getCurrentScintilla();
    for (int i = 0; i < 30; i++)
    {
        if (strlen(closed_files[i]) < 1)
        {
            break;
        }

        ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)getEOL());
        ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)closed_files[i]);
    }
    ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)getEOL());
    ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)"CLOSED FILES LIST");
}

void insertList()
{
    HWND curScintilla = getCurrentScintilla();
    for (int i = 0; i < 30; i++)
    {
        if (strlen(all_files[i]))
        {
            ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)getEOL());
            ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)all_files[i]);
        }
        else {
            break;
        }
    }
    ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)getEOL());
    ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)"FILES BEFORE CLOSE");

    ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)getEOL());

    for (int i = 0; i < 30; i++)
    {
        if (strlen(now_files[i]))
        {
            ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)getEOL());
            ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)now_files[i]);
        }
        else {
            break;
        }
    }
    ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)getEOL());
    ::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)"FILES AFTER CLOSE");
}

void buffer_left()
{
    HWND curScintilla = getCurrentScintilla();

    int buffer;
    int pos;

    buffer = ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTBUFFERID, 0, 0);
    pos = ::SendMessage(nppData._nppHandle, NPPM_GETPOSFROMBUFFERID , buffer, 0);

    pos--;

    int left_buffer = ::SendMessage(nppData._nppHandle, NPPM_GETBUFFERIDFROMPOS , pos, 0);

    TCHAR full_file_path[MAX_PATH];
    char path_text[MAX_PATH];

    ::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID, left_buffer, (LPARAM)full_file_path);

    WideCharToMultiByte((int)::SendMessage(curScintilla, SCI_GETCODEPAGE, 0, 0), 0, full_file_path, -1, path_text, MAX_PATH, NULL, NULL);

    ::SendMessage(nppData._nppHandle, NPPM_SWITCHTOFILE , 0, (LPARAM)full_file_path);
}

void buffer_right()
{
    HWND curScintilla = getCurrentScintilla();

    int buffer;
    int pos;

    buffer = ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTBUFFERID, 0, 0);
    pos = ::SendMessage(nppData._nppHandle, NPPM_GETPOSFROMBUFFERID , buffer, 0);

    pos++;

    int left_buffer = ::SendMessage(nppData._nppHandle, NPPM_GETBUFFERIDFROMPOS , pos, 0);

    TCHAR full_file_path[MAX_PATH];
    char path_text[MAX_PATH];

    ::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID, left_buffer, (LPARAM)full_file_path);

    WideCharToMultiByte((int)::SendMessage(curScintilla, SCI_GETCODEPAGE, 0, 0), 0, full_file_path, -1, path_text, MAX_PATH, NULL, NULL);

    ::SendMessage(nppData._nppHandle, NPPM_SWITCHTOFILE , 0, (LPARAM)full_file_path);
}

void wrap_with_tag()
{
    HWND curScintilla = getCurrentScintilla();

    int selection_start = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
    int selection_end   = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);

    ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

    ::SendMessage(curScintilla, SCI_INSERTTEXT, selection_end, (LPARAM)"</p>");
    ::SendMessage(curScintilla, SCI_INSERTTEXT, selection_start, (LPARAM)"<p>");

    ::SendMessage(curScintilla, SCI_SETSELECTION, selection_end + 5, selection_end + 6);
    ::SendMessage(curScintilla, SCI_ADDSELECTION, selection_start + 1, selection_start + 2);

    ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
}

void url_encode_selection()
{
    HWND curScintilla = getCurrentScintilla();

    int selection_start = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
    int selection_end   = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);

    if (selection_start != selection_end)
    {
        ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

        char selection[9999];
        ::SendMessage(curScintilla, SCI_GETSELTEXT , 0, (LPARAM)selection);
        ::SendMessage(curScintilla, SCI_DELETEBACK , 0, 0);

        char *encoded = url_encode(selection);

        ::SendMessage(curScintilla, SCI_INSERTTEXT, selection_start, (LPARAM)encoded);
        
        ::SendMessage(curScintilla, SCI_SETSEL , selection_start + strlen(encoded), selection_start + strlen(encoded));

        free(encoded);
        
        ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
    }
}

void url_decode_selection()
{
    HWND curScintilla = getCurrentScintilla();

    int selection_start = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
    int selection_end   = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);

    if (selection_start != selection_end)
    {
        ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

        char selection[9999];
        ::SendMessage(curScintilla, SCI_GETSELTEXT , 0, (LPARAM)selection);
        ::SendMessage(curScintilla, SCI_DELETEBACK , 0, 0);

        char *encoded = url_decode(selection);

        ::SendMessage(curScintilla, SCI_INSERTTEXT, selection_start, (LPARAM)encoded);

        ::SendMessage(curScintilla, SCI_SETSEL , selection_start + strlen(encoded), selection_start + strlen(encoded));

        free(encoded);

        ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
    }
}

/**
 * Url encode/decode functions from http://www.geekhideout.com/urlcode.shtml
 * Why reinvent the wheel?
 */
char from_hex(char ch)
{
  return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

char to_hex(char code)
{
  static char hex[] = "0123456789abcdef";
  return hex[code & 15];
}

char *url_encode(char *str)
{
  char *pstr = str, *buf = (char *) malloc(strlen(str) * 3 + 1), *pbuf = buf;
  while (*pstr) {
    if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~') 
      *pbuf++ = *pstr;
    else if (*pstr == ' ') 
      *pbuf++ = '+';
    else 
      *pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
    pstr++;
  }
  *pbuf = '\0';
  return buf;
}

char *url_decode(char *str)
{
  char *pstr = str, *buf = (char *) malloc(strlen(str) + 1), *pbuf = buf;
  while (*pstr) {
    if (*pstr == '%') {
      if (pstr[1] && pstr[2]) {
        *pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);
        pstr += 2;
      }
    } else if (*pstr == '+') { 
      *pbuf++ = ' ';
    } else {
      *pbuf++ = *pstr;
    }
    pstr++;
  }
  *pbuf = '\0';
  return buf;
}


void EMBED_code()
{
    HWND curScintilla = getCurrentScintilla();
    TCHAR full_file_path[MAX_PATH];
    char path_text[MAX_PATH];

    int current_buffer = ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTBUFFERID, 0, 0);
    
    ::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID, current_buffer, (LPARAM)full_file_path);

    WideCharToMultiByte((int)::SendMessage(curScintilla, SCI_GETCODEPAGE, 0, 0), 0, full_file_path, -1, path_text, MAX_PATH, NULL, NULL);


    if (strstr(path_text, ".erb"))
    {
        int pos         = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
        int line_number = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, pos, 0);

        char line[9999];

        int line_end = ::SendMessage(curScintilla, SCI_GETLINEENDPOSITION, line_number, 0);
        ::SendMessage(curScintilla, SCI_SETSEL, pos, line_end);
        ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&line);
        ::SendMessage(curScintilla, SCI_SETSEL, pos, pos);
        
        if (strstr(line, "%>"))
        {
            return;
        }

        char check[4];
        ::SendMessage(curScintilla, SCI_SETSEL, pos, pos - 3);
        ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&check);
        ::SendMessage(curScintilla, SCI_SETSEL, pos, pos );

        if (strstr(check, "<% "))
        {
            ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);
            ::SendMessage(curScintilla, SCI_INSERTTEXT, pos, (LPARAM)" %>");
            ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
        }
        else if (strstr(check, "<%="))
        {
            ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);
            ::SendMessage(curScintilla, SCI_INSERTTEXT, pos, (LPARAM)"  %>");
            ::SendMessage(curScintilla, SCI_SETSEL, pos + 1, pos + 1 );
            ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
        }
    }
    else if (strstr(path_text, ".php")
          || strstr(path_text, ".html"))
    {
        int pos         = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
        int line_number = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, pos, 0);

        char line[9999];

        int line_end = ::SendMessage(curScintilla, SCI_GETLINEENDPOSITION, line_number, 0);
        ::SendMessage(curScintilla, SCI_SETSEL, pos, line_end);
        ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&line);
        ::SendMessage(curScintilla, SCI_SETSEL, pos, pos);

        if (strstr(line, "?>"))
        {
            return;
        }
        
        char check[4];
        ::SendMessage(curScintilla, SCI_SETSEL, pos, pos - 3);
        ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&check);
        ::SendMessage(curScintilla, SCI_SETSEL, pos, pos );

        if (strstr(check, "<? "))
        {
            ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);
            ::SendMessage(curScintilla, SCI_INSERTTEXT, pos, (LPARAM)" ?>");
            ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
        }
        else if (strstr(check, "<?="))
        {
            ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);
            ::SendMessage(curScintilla, SCI_INSERTTEXT, pos, (LPARAM)"  ?>");
            ::SendMessage(curScintilla, SCI_SETSEL, pos + 1, pos + 1 );
            ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
        }
    }
}

int ruler_check = 0;

void ruler()
{
    HWND curScintilla = getCurrentScintilla();

    if (ruler_check == 0)
    {
        int position    = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
        int line_number = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, position, 0);

        ::SendMessage(curScintilla, SCI_ANNOTATIONSETTEXT, line_number, (LPARAM)"--- 0 ---|--- 10---|--- 20---|--- 30---|--- 40---|--- 50---|--- 60---|--- 70---|--- 80---|--- 90---|---100---|---110---|---120---|---130---|---140---|---150---|---160---|---170---|---180---|---190---|\n\
123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|");
        /**
         * #define STYLE_DEFAULT 32
         * #define STYLE_LINENUMBER 33
         * #define STYLE_BRACELIGHT 34
         * #define STYLE_BRACEBAD 35
         * #define STYLE_CONTROLCHAR 36
         * #define STYLE_INDENTGUIDE 37
         * #define STYLE_CALLTIP 38
         */
        ::SendMessage(curScintilla, SCI_ANNOTATIONSETSTYLE, line_number, STYLE_CALLTIP);
        ::SendMessage(curScintilla, SCI_ANNOTATIONSETVISIBLE, line_number, 0);
        ruler_check = 1;
    }
    else
    {
        ::SendMessage(curScintilla, SCI_ANNOTATIONCLEARALL, 0, 0);
        ruler_check = 0;
    }
}

int auto_numbering()
{
    HWND curScintilla = getCurrentScintilla();
    
    ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

    int ret = 0;

    int save_position    = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    int save_line_number = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, save_position, 0);
    
    /**
     * The /^[\s\#\*]*[0-9]+[.]/ regex does not match good when using SEARCHPREV
     * so we're using SEARCHNEXT from line start position
     */
    int line_start       = ::SendMessage(curScintilla, SCI_POSITIONFROMLINE, save_line_number - 1, 0);
    ::SendMessage(curScintilla, SCI_SETSEL , line_start , line_start);

    ::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);
    ::SendMessage(curScintilla, SCI_SEARCHNEXT , SCFIND_REGEXP, (LPARAM)"^[\\s\\#\\*]*[0-9]+[.\\)-]");

    int search_position_start = ::SendMessage(curScintilla, SCI_GETSELECTIONNSTART, 0, 0);
    int search_position_end   = ::SendMessage(curScintilla, SCI_GETSELECTIONEND , 0, 0);

    if (search_position_start != search_position_end)
    {
        int search_line_number = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, search_position_start, 0);

        if ((save_line_number - 1) == search_line_number)
        {
            ret = 1;

            char selection[9999];
            ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&selection);

            trim(selection);

            int last = strlen(selection);

            // FIND LAST SPACE
            while(last)
            { 
                if (isspace(selection[last])) { last++; break; }
                else { last--; }
            }

            // FIND FIRST SPACE
            int first = 0;
            int slen = strlen(selection);
            while (first < slen)
            {
                if (isspace(selection[first])) break;
                else first++;
            }

            char *only_number = substr(selection, last , slen - 2);

            int num = 1;
            sscanf(only_number, "%d", &num);

            num++;            
            char buff[100];
            sprintf(buff, "%d", num);

            //strcat(buff, ". ");

            // ADD LAST CHARACTER
            strcat(buff, substr(selection, slen - 1, slen));
            strcat(buff, " ");

            ::SendMessage(curScintilla, SCI_INSERTTEXT, save_position, (LPARAM) buff );
            
            int new_position = save_position + strlen(buff);
            
            if (strstr(selection, "#") || strstr(selection, "*"))
            {
                first++;

                //char trace[100];
                //sprintf(trace, "%d|%s|%d", first, selection, last);
                //::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM) trace );

                if (first < last )
                {
                    last--;

                    char *white_space = substr(selection, first , last );
                    ::SendMessage(curScintilla, SCI_INSERTTEXT, save_position, (LPARAM) white_space );
                    new_position = new_position + strlen(white_space);
                }
            }
            

            ::SendMessage(curScintilla, SCI_SETSEL, new_position, new_position);
        }
        else
        {
            ret = 2;
            ::SendMessage(curScintilla, SCI_SETSEL , save_position, save_position);
        }
    }
    else
    {
        ::SendMessage(curScintilla, SCI_SETSEL , save_position, save_position);
    }

    ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);

    return ret;
}

void docblock_keywords()
{
    int lang = -100;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&lang);

    if (!( lang == L_C
       || lang == L_CPP
       || lang == L_JS
       || lang == L_PHP
       || lang == L_CSS))
    {
        return;
    }

    HWND curScintilla = getCurrentScintilla();

    int save_position = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);

    ::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);
    ::SendMessage(curScintilla, SCI_SEARCHPREV, SCFIND_REGEXP, (LPARAM)"^\\s+\\*\\s\\@");

    int selection_start = ::SendMessage(curScintilla, SCI_GETSELECTIONNSTART, 0, 0);
    int selection_end   = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);

    ::SendMessage(curScintilla, SCI_SETSEL, save_position, save_position);

    if (selection_start != selection_end && selection_end == save_position)
    {
        ::SendMessage(curScintilla, SCI_AUTOCSETSEPARATOR, (LPARAM)'|', 0);
        ::SendMessage(curScintilla, SCI_AUTOCSHOW, 1, (LPARAM)"@access  |@author  |@copyright  |@example  |@global  |@license  |@link  |@name  |@package  |@param  |@return  |@see  |@static  |@subpackage  |@todo  |@var  |@version  ");
    }
}

void Ruby_Newline(HWND &curScintilla)
{
    int lang = -100;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&lang);

    if (lang != L_RUBY)
    {
        return;
    }

    int save_position = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    int save_line     = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, save_position, 0);

    int line_start = ::SendMessage(curScintilla, SCI_POSITIONFROMLINE, save_line - 1, 0);
    int line_end   = ::SendMessage(curScintilla, SCI_GETLINEENDPOSITION, save_line - 1, 0);

    char line[9999];
    ::SendMessage(curScintilla, SCI_SETSEL, line_start, line_end);
    ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&line);
    ::SendMessage(curScintilla, SCI_SETSEL, save_position, save_position);

    trim(line);

    if (strlen(line) < 2) return;

    char seven[8];
    strncpy(seven, line, 7);

    char six[7];
    strncpy(six, line, 6);

    char five[6];
    strncpy(five, line, 5);

    char four[5];
    strncpy(four, line, 4);

    char tree[4];
    strncpy(tree, line, 3);

    char *end = substr(line, strlen(line) - 2, strlen(line));

    if (strstr(seven, "private")

     || strstr(six, "module")
     || strstr(six, "unless")
     || strstr(six, "ensure")

     || strstr(five, "class")
     || strstr(five, "elsif")
     || strstr(five, "begin")

     || strstr(four, "def ")
     || strstr(four, "else")

     || strstr(tree, "if ")

     || strstr(line, " do |")
     || strstr(line, "do|")

     || strstr(end, "do")
        )
    {
        ::SendMessage(curScintilla, SCI_TAB , 0, 0 );
    }
}

void RubyExtra(int character)
{
    int lang = -100;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&lang);

    if (lang != L_RUBY)
    {
        return;
    }


    HWND curScintilla = getCurrentScintilla();

    int save_position = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    int save_line     = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, save_position, 0);

    int save_line_start = ::SendMessage(curScintilla, SCI_POSITIONFROMLINE , save_line, 0);
    int save_line_end   = ::SendMessage(curScintilla, SCI_GETLINEENDPOSITION , save_line, 0);

    ::SendMessage(curScintilla, SCI_SETSEL, save_line_start, save_line_end);

    char content[9999];

    ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&content);
    ::SendMessage(curScintilla, SCI_SETSEL, save_position, save_position);

    trim(content);

    char *cmp;
    int check_len = -1;

    if (character == 'd') {
        cmp = "end";
        check_len = 3;
    }
    else if (character == 'e') {
        if (strcmp(content, "else") == 0 && strlen(content) == 4) {
            cmp = "else";
            check_len = 4;
        }
        else {
            cmp = "ensure";
            check_len = 6;
        }
    }
    else if (character == 'f') {
        cmp = "elsif";
        check_len = 5;
    }
    else {
        return;
    }

    if (strcmp(content, cmp) == 0 && strlen(content) == check_len)
    {
        int fold_line = ::SendMessage(curScintilla, SCI_GETFOLDPARENT, save_line, 0);
        //int fold_pos  = ::SendMessage(curScintilla, SCI_POSITIONFROMLINE, fold_line, 0);

        int match_indent = ::SendMessage(curScintilla, SCI_GETLINEINDENTATION, fold_line, 0);
        ::SendMessage(curScintilla, SCI_SETLINEINDENTATION, save_line, match_indent);

        if (::SendMessage(curScintilla, SCI_AUTOCACTIVE, 0, 0))
        {
            ::SendMessage(curScintilla, SCI_AUTOCCANCEL, 0, 0);
            ::SendMessage(curScintilla, SCI_AUTOCSHOW, 1, (LPARAM)"#fix_autocomplete");
        }
    }
}

/**
 * HELPER FUNCTIONS
 */
HWND getCurrentScintilla()
{
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return NULL;
    if (which == 0)
    {
        return nppData._scintillaMainHandle;
    }
    else
    {
        return nppData._scintillaSecondHandle;
    }
    return nppData._scintillaMainHandle;
}

char* getEOL()
{
    int eol = ::SendMessage( getCurrentScintilla() , SCI_GETEOLMODE, 0,0);

    char *ENDL;

    if (eol == 0)
        ENDL = "\r\n";
    else if (eol == 1)
        ENDL = "\r";
    else/* == 2 */
        ENDL = "\n";

    return ENDL;
}

char* trim_left(char *s)
{
    char *cp1;                              // for parsing the whole s
    char *cp2;                              // for shifting & padding

    // skip leading spaces, shift remaining chars
    for (cp1=s; isspace(*cp1); cp1++ )      // skip leading spaces, via cp1
        ;
    for (cp2=s; *cp1; cp1++, cp2++)         // shift left remaining chars, via cp2
        *cp2 = *cp1;
    *cp2-- = 0;                             // mark new end of string for s

    // replace trailing spaces with '\0'
    //while ( cp2 > s && isspace(*cp2) )
    //    *cp2-- = 0;                         // pad with '\0's

    return s;
}

char* trim(char *s)
{
    char *cp1;                              // for parsing the whole s
    char *cp2;                              // for shifting & padding

    // skip leading spaces, shift remaining chars
    for (cp1=s; isspace(*cp1); cp1++ )      // skip leading spaces, via cp1
        ;
    for (cp2=s; *cp1; cp1++, cp2++)         // shift left remaining chars, via cp2
        *cp2 = *cp1;
    *cp2-- = 0;                             // mark new end of string for s

    // replace trailing spaces with '\0'
    while ( cp2 > s && isspace(*cp2) )
        *cp2-- = 0;                         // pad with '\0's

    return s;
}

char* substr(char* string, int begin, int end)
{
    char* temp = (char *) malloc(sizeof(char)*(end-begin+1));
    if(temp != NULL)
    {
        strncpy(temp,string+begin,end-begin+1);
        temp[end-begin+1] = '\0';
    }
    return temp;
}



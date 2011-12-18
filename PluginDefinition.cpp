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

    ShortcutKey *ctrlv = new ShortcutKey;
    ctrlv->_isAlt      = false;
    ctrlv->_isCtrl     = true;
    ctrlv->_isShift    = false;
    ctrlv->_key        = 0x56; // V
    setCommand(1, TEXT("Paste indented"), paste_indented, ctrlv, false);

    ShortcutKey *T_key = new ShortcutKey;
    T_key->_isAlt      = false;
    T_key->_isCtrl     = true;
    T_key->_isShift    = true;
    T_key->_key        = 0x54; // T
    setCommand(2, TEXT("Undo close tab"), undo_closed_tab, T_key, false);

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
    setCommand(4, TEXT("Tab left"), buffer_left, LEFT_key, false);

    ShortcutKey *RIGHT_key = new ShortcutKey;
    RIGHT_key->_isAlt      = true;
    RIGHT_key->_isCtrl     = false;
    RIGHT_key->_isShift    = false;
    RIGHT_key->_key        = VK_RIGHT ; // RIGHT
    setCommand(5, TEXT("Tab right"), buffer_right, RIGHT_key, false);

    ShortcutKey *W_key = new ShortcutKey;
    W_key->_isAlt      = true;
    W_key->_isCtrl     = true;
    W_key->_isShift    = false;
    W_key->_key        = 0x57; // W
    setCommand(7, TEXT("Wrap selection with tag"), wrap_with_tag, W_key, false);

    ShortcutKey *period = new ShortcutKey;
    period->_isAlt      = false;
    period->_isCtrl     = true;
    period->_isShift    = false;
    period->_key        = 0xBE;// VK_OEM_PERIOD  0xBE  "." any country/region
    setCommand(8, TEXT("Close last open tag"), end_tag, period, false);

    setCommand(10, TEXT("URL encode selection"), url_encode_selection, NULL, false);
    setCommand(11, TEXT("URL decode selection"), url_decode_selection, NULL, false);

    ShortcutKey *C_key = new ShortcutKey;
    C_key->_isAlt      = false;
    C_key->_isCtrl     = true;
    C_key->_isShift    = true;
    C_key->_key        = 0x43; // C
    setCommand(13, TEXT("Column ruler"), ruler, C_key, false);

    setCommand(15, TEXT("Leading TABS to Spaces"), tabs_to_spaces, NULL, false);
    setCommand(16, TEXT("Leading Spaces to TABS"), spaces_to_tabs, NULL, false);

    setCommand(18, TEXT("Features"), show_features, NULL, false);
    setCommand(19, TEXT("About"), show_about, NULL, false);

	ShortcutKey *L_key = new ShortcutKey;
    L_key->_isAlt      = true;
    L_key->_isCtrl     = false;
    L_key->_isShift    = false;
    L_key->_key        = 0x49; // L
    setCommand(20, TEXT("Select string"), select_string, L_key, false);

    ::SendMessage(getCurrentScintilla(), SCI_SETENDATLASTLINE , (WPARAM)false, (LPARAM)false);
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
    HWND curScintilla = getCurrentScintilla();
    char about[9999];
    strcpy(about, "");
    strcat(about , "Notepad#\r\n\
Version: ");
    strcat(about , VERSION_TEXT);
    strcat(about, "\
\r\nSource code: https://github.com/jvdanilo/NotepadSharp \r\n\
\r\n\
This plugin implements all the features I wanted to see in Notepad++ for years, plus some more\r\n\
\r\n\
jvdanilo");

    TCHAR about_wide[MAX_PATH];

    int len = MultiByteToWideChar ((int)::SendMessage(curScintilla, SCI_GETCODEPAGE, 0, 0), 0, about, -1, NULL, 0);

    MultiByteToWideChar ((int)::SendMessage(curScintilla, SCI_GETCODEPAGE, 0, 0), 0, about, -1, about_wide, len);

    ::MessageBox(nppData._nppHandle, about_wide, TEXT("Notepad#"), MB_OK);

}

void Newline()
{
    HWND curScintilla = getCurrentScintilla();

    int lang = -100;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&lang);

    int position    = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    int line_number = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, position, 0);

    //int indent = ::SendMessage(curScintilla, SCI_GETLINEINDENTATION, line_number - 1, 0);
    //::SendMessage(curScintilla, SCI_SETLINEINDENTATION, line_number, indent);
    
    //copyindent(curScintilla, line_number - 1, position);
    position   = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    line_number = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, position, 0);

    char line[9999];
    ::SendMessage(curScintilla, SCI_GETLINE, line_number - 1 , (LPARAM)line);
    
    trim_left(line);

    switch (lang)
    {
        case L_C:
        case L_CPP:
            cStyleComment(curScintilla, line, line_number);
            indentAfterCurlyBrace(curScintilla, line_number - 1);
            break;
        case L_CSS:
            if (cStyleComment(curScintilla, line, line_number) == 0
             && indentAfterCurlyBrace(curScintilla, line_number - 1) == 0)
            {

            }
            break;
        case L_JS:
            if (cStyleComment(curScintilla, line, line_number) == 0
             && indentAfterCurlyBrace(curScintilla, line_number - 1) == 0)
            {
            }
            break;
        case L_PHP:
            if ( cStyleComment(curScintilla, line, line_number) == 0
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

    // FIND MATCHING BRACE INDENTATION
    int opening_brace_position = ::SendMessage(curScintilla, SCI_BRACEMATCH, save_position - 1, 0);

    if (opening_brace_position == -1)
    {
        return;
    }

    ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

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

int cStyleComment(HWND &curScintilla, char *line, int line_number)
{
    int ret = 0;
    char comment[2];
    strncpy(comment, line, 2);
	comment[2] = '\0';

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
	else
    {
		char check_line[9999];
		::SendMessage(curScintilla, SCI_GETLINE, line_number - 1, (LPARAM)check_line);

		int check_line_end = ::SendMessage(curScintilla, SCI_LINELENGTH, line_number - 1, 0);

		check_line[check_line_end] = '\0';

		if (check_line[0] != '*' && strlen(trim(check_line)) == 2)
		{
			ret = 3;
			strncpy(comment, trim(check_line), 2);

			if (comment[0] == '*' && comment[1] == '/') {
				ret = 4;
				::SendMessage(curScintilla, SCI_DELETEBACK, 0, 0);
			}
		}
    }

    return ret;
}

void XHTMLindent(HWND &curScintilla, int position, int line_number)
{

    ::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);
    //::SendMessage(curScintilla, SCI_SEARCHPREV, SCFIND_REGEXP, (LPARAM)"<[^?][^\\/]+>$");
    ::SendMessage(curScintilla, SCI_SEARCHPREV, SCFIND_REGEXP, (LPARAM)"<[\\w\\/]+[\\w\\W\\b\\B]*?>\\s*$");

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

	int html_comment = 9;

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

		if (
			::SendMessage(curScintilla, SCI_GETSTYLEAT, ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0) + 1, 0) == html_comment
		) {
			continue;
		}
        else if (end == last_search)
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


    int position = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    int line     = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, position, 0);
    int column   = ::SendMessage(curScintilla, SCI_GETCOLUMN, position, 0);
	int lines    = ::SendMessage(curScintilla, SCI_GETLINECOUNT, 0, 0);

    if (line == (lines - 1)) {
		//SCI_GETLINEENDPOSITION(int line)
		int line_start = ::SendMessage(curScintilla, SCI_POSITIONFROMLINE, line, 0);
		int line_end   = ::SendMessage(curScintilla, SCI_GETLINEENDPOSITION, line, 0);

		if (line_start != line_end)
		{
			::SendMessage(curScintilla, SCI_SETSELECTIONSTART, line_start, 0);
			::SendMessage(curScintilla, SCI_SETSELECTIONEND, line_end, 0);	
			::SendMessage(curScintilla, SCI_DELETEBACK, 0, 0);
		}

        return;
    }

    ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

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

/*
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
*/

void buffer_left()
{
    HWND curScintilla = getCurrentScintilla();

    int buffer;
    int pos;

    buffer = ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTBUFFERID, 0, 0);
    pos    = ::SendMessage(nppData._nppHandle, NPPM_GETPOSFROMBUFFERID , buffer, 0);

	int which;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);

    pos--;

	if (which == 1) {
		pos = pos - 1073741823 - 1;
	}

    int left_buffer = ::SendMessage(nppData._nppHandle, NPPM_GETBUFFERIDFROMPOS , pos, which );

	//if (left_buffer == 0)
	//{
	//	::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)"INVALID");
	//}

    TCHAR full_file_path[MAX_PATH];
    char path_text[MAX_PATH];

    ::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID, left_buffer, (LPARAM)full_file_path);

    WideCharToMultiByte((int)::SendMessage(curScintilla, SCI_GETCODEPAGE, 0, 0), 0, full_file_path, -1, path_text, MAX_PATH, NULL, NULL);

    ::SendMessage(nppData._nppHandle, NPPM_SWITCHTOFILE , 0, (LPARAM)full_file_path);
}
/*
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
*/
void buffer_right()
{
    HWND curScintilla = getCurrentScintilla();

    int buffer;
    int pos;

    buffer = ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTBUFFERID, 0, 0);
    pos = ::SendMessage(nppData._nppHandle, NPPM_GETPOSFROMBUFFERID , buffer, 0);

    pos++;
	
	int which;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
	
	if (which == 1) {
		pos = pos - 1073741823 - 1;
	}

    int right_buffer = ::SendMessage(nppData._nppHandle, NPPM_GETBUFFERIDFROMPOS , pos, which);

	//if (right_buffer == 0)
	//{
		//::SendMessage(curScintilla, SCI_INSERTTEXT, 0, (LPARAM)"INVALID");
	//}


    TCHAR full_file_path[MAX_PATH];
    char path_text[MAX_PATH];

    ::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID, right_buffer, (LPARAM)full_file_path);

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

void clear_hex_indicators()
{
    HWND curScintilla = getCurrentScintilla();
    
    int length = ::SendMessage(curScintilla, SCI_GETTEXT, 0, 0);
    int i = 1;
    while (i <= 20) {
        ::SendMessage(curScintilla, SCI_SETINDICATORCURRENT, i, 0);
        ::SendMessage(curScintilla, SCI_INDICATORCLEARRANGE, 0, length);
        i++;
    }
}

//void clear_hex_indicators()
//{
//    HWND curScintilla = getCurrentScintilla();
//    
//    int first_visible_line = ::SendMessage(curScintilla, SCI_GETFIRSTVISIBLELINE, 0, 0);
//	int first_line_pos     = ::SendMessage(curScintilla, SCI_POSITIONFROMLINE, first_visible_line, 0);
//
//    int length = ::SendMessage(curScintilla, SCI_GETTEXT, 0, 0);
//
//   int i = 1;
//    while (i <= 20) {
//        ::SendMessage(curScintilla, SCI_SETINDICATORCURRENT, i, 0);
//        ::SendMessage(curScintilla, SCI_INDICATORCLEARRANGE, first_line_pos, length);
//        i++;
//    }
//}


void peek_hex_color()
{
    int lang = -100;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&lang);
    
    clear_hex_indicators();

    if (lang != L_CSS) {
        return;
    }

    HWND curScintilla = getCurrentScintilla();

    int save_caret_start = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
    int save_caret_end = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);

    //SCI_GETFIRSTVISIBLELINE first line is 0
    int first_visible_line = ::SendMessage(curScintilla, SCI_GETFIRSTVISIBLELINE, 0, 0);
    
    int first_line_position = ::SendMessage(curScintilla, SCI_POSITIONFROMLINE, first_visible_line, 0);
    ::SendMessage(curScintilla, SCI_SETANCHOR, first_line_position, 0);
    ::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);


    char found[9999];
    strcpy(found, "");

    int i = 1;
    int indicator;

    int set_colors = 0;


    while (i <= 20)
    {
        ::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);
        ::SendMessage(curScintilla, SCI_SEARCHNEXT, SCFIND_REGEXP, (LPARAM)"#[0-9AaBbCcDdEeFf]+");

        int selection_start = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
        int selection_end   = ::SendMessage(curScintilla, SCI_GETSELECTIONEND , 0, 0);

        int selection_length = selection_end - selection_start;

        if (selection_start == selection_end)
        {
            break;
        }
        else if (selection_length > 0 && selection_length != 4 && selection_length != 7)
        {
            ::SendMessage(curScintilla, SCI_SETSELECTIONSTART, selection_end, 0);
            ::SendMessage(curScintilla, SCI_SETSELECTIONEND, selection_end, 0);

            ::SendMessage(curScintilla, SCI_SETANCHOR, selection_end, 0);
            //i++;
            continue;
        }

        int hex_length;

        char selection[6];
        ::SendMessage(curScintilla, SCI_GETSELTEXT , 0, (LPARAM)&selection);

        ::SendMessage(curScintilla, SCI_SETSELECTIONSTART, selection_end, 0);
        ::SendMessage(curScintilla, SCI_SETSELECTIONEND, selection_end, 0);

        ::SendMessage(curScintilla, SCI_SETANCHOR, selection_end, 0);

        char hex[6];
        strcpy(hex, substr(selection,1, strlen(selection)));

        if (strlen(hex) == 3)
        {
            hex[0] = selection[1];
            hex[1] = selection[1];
            hex[2] = selection[2];
            hex[3] = selection[2];
            hex[4] = selection[3];
            hex[5] = selection[3];
            hex[6] = '\0';

            hex_length = 3;
        }
        else {
            hex_length = 6;
        }

        // Reverse RGB to BGR which Scintilla uses
        char reverse[6];
        reverse[0] = toupper(hex[4]);
        reverse[1] = toupper(hex[5]);
        reverse[2] = toupper(hex[2]);
        reverse[3] = toupper(hex[3]);
        reverse[4] = toupper(hex[0]);
        reverse[5] = toupper(hex[1]);
        reverse[6] = '\0';

        indicator = i;
        
        char search[9];
        strcpy(search, "|");
        strcat(search, reverse);

        if (strstr(found, search)) {
            i--;
            int j = 0;
            while (j <= set_colors) {
                if (htoi(reverse) == ::SendMessage(curScintilla, SCI_INDICGETFORE, j, 0))
                {
                    indicator = j;
                    break;
                }
                else {
                    j++;
                }
            }
        }
        else {
            strcat(found, search);
            set_colors++;
        }

        ::SendMessage(curScintilla, SCI_INDICSETSTYLE, indicator, INDIC_ROUNDBOX);

        ::SendMessage(curScintilla, SCI_INDICSETUNDER, indicator, (LPARAM)true);
        ::SendMessage(curScintilla, SCI_INDICSETFORE, indicator, (LPARAM)htoi(reverse));
        ::SendMessage(curScintilla, SCI_INDICSETALPHA, indicator, (LPARAM)255);

        ::SendMessage(curScintilla, SCI_SETINDICATORCURRENT, indicator, 0);
        ::SendMessage(curScintilla, SCI_INDICATORFILLRANGE, selection_start + 1, hex_length);

        i++;
    }

    ::SendMessage(curScintilla, SCI_SETSELECTIONSTART, save_caret_start, 0);
    ::SendMessage(curScintilla, SCI_SETSELECTIONEND, save_caret_end, 0);

}

long htoi (char s[])
{

    char *p = &s[strlen(s)-1];
    long deci = 0, dig = 0;
    int pos = 0;

    while (p >= s) {

        if ((dig = hchartoi(*p, pos)) < 0 ) {
            printf("Error\n");
            return -1;

        }
        deci += dig;
        --p;
        ++pos;

    }
    return deci;
}

/* convert hex char to decimal value */
long hchartoi (char hexdig, int pos)
{

    char hexdigits[] = "0123456789ABCDEF";
    char *p = &hexdigits[0];
    long deci = 0;
    int i;

    while (*p != toupper(hexdig) && deci < 16) {

        ++p;
        ++deci;

    }
    if (*p == toupper(hexdig)) {
       for (i = 0; i < pos; i++)
           deci *= 16;
       return deci;

    }
    return -1;
}

void spaces_to_tabs()
{
	spaces_tabs(true);
}

void tabs_to_spaces()
{
	spaces_tabs(false);
}

void spaces_tabs(bool tabs)
{
    HWND curScintilla = getCurrentScintilla();

	::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

	int setting = ::SendMessage(curScintilla, SCI_GETUSETABS, 0, 0);
	int lines = ::SendMessage(curScintilla, SCI_GETLINECOUNT, 0, 0);

	//SCI_SETUSETABS(bool useTabs)
	::SendMessage(curScintilla, SCI_SETUSETABS, ((tabs) ? true : false), 0);

	while (lines) {
		int indentation = ::SendMessage(curScintilla, SCI_GETLINEINDENTATION, lines, 0);
		::SendMessage(curScintilla, SCI_SETLINEINDENTATION, lines, 1);
		::SendMessage(curScintilla, SCI_SETLINEINDENTATION, lines, indentation);

		lines--;
	}

	// Restore setting
	::SendMessage(curScintilla, SCI_SETUSETABS, setting, 0);

    ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
}

void paste_indented()
{
    HWND curScintilla = getCurrentScintilla();
	
	::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);

	int save_position = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    int save_line     = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, save_position, 0);

    ::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND , 0, (LPARAM)IDM_EDIT_PASTE);

	int position = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
    int line     = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, position, 0);

	if (save_line != line)
	{
		int lang = -100;
		::SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&lang);

		int tab_width;
		int loop;

		switch(lang) {
			case L_C:
			case L_CPP:
			case L_CSS:
			case L_JS:
			case L_PHP:
			case L_HTML:
			case L_XML:
				tab_width = ::SendMessage(curScintilla, SCI_GETTABWIDTH, 0, 0);

				loop = save_line;
		
				while (loop <= line)
				{
					int fold_parent = ::SendMessage(curScintilla, SCI_GETFOLDPARENT, loop, 0);

					if (fold_parent == -1) break;

					int parent_indent = ::SendMessage(curScintilla, SCI_GETLINEINDENTATION, fold_parent, 0);
					// Dont move this line, it redraws the screen
					int last_child    = ::SendMessage(curScintilla, SCI_GETLASTCHILD, fold_parent , -1);

					if (fold_parent == 0) {
						::SendMessage(curScintilla, SCI_SETLINEINDENTATION , loop, 0);
					}
					else {
						char line_contents[9999];
						::SendMessage(curScintilla, SCI_GETLINE, loop, (LPARAM)line_contents);
						char check[2];
						char check2[6];

						strncpy(check, trim_left(line_contents), 2);
						strncpy(check2, trim_left(line_contents), 6);

						if (strstr(check, "* ") || strstr(check, "*/")) {
							::SendMessage(curScintilla, SCI_SETLINEINDENTATION , loop, parent_indent + 1);
						}
						else if (loop == last_child || strstr(check2, "} else")) {
							::SendMessage(curScintilla, SCI_SETLINEINDENTATION , loop, parent_indent);
						}
						else {
							::SendMessage(curScintilla, SCI_SETLINEINDENTATION , loop, parent_indent + tab_width);
						}
					}

					loop++;
				}
			break;
			case L_RUBY:
				tab_width = ::SendMessage(curScintilla, SCI_GETTABWIDTH, 0, 0);

				loop = save_line;
		
				while (loop <= line)
				{
					int fold_parent = ::SendMessage(curScintilla, SCI_GETFOLDPARENT, loop, 0);

					if (fold_parent == -1) break;

					int parent_indent = ::SendMessage(curScintilla, SCI_GETLINEINDENTATION, fold_parent, 0);
					// Dont move this line, it redraws the screen
					int last_child    = ::SendMessage(curScintilla, SCI_GETLASTCHILD, fold_parent , -1);

					if (fold_parent == 0) {
						::SendMessage(curScintilla, SCI_SETLINEINDENTATION , loop, 0);
					}
					else {
						char line_contents[9999];
						::SendMessage(curScintilla, SCI_GETLINE, loop, (LPARAM)line_contents);
						char check_else[4];
						char check_elsif[5];

						strncpy(check_else, trim_left(line_contents), 4);
						strncpy(check_elsif, trim_left(line_contents), 5);

						if (loop == last_child
						 || strstr(check_else, "else")
						 || strstr(check_elsif, "elsif")
						) {
							::SendMessage(curScintilla, SCI_SETLINEINDENTATION , loop, parent_indent);
						}
						else {
							::SendMessage(curScintilla, SCI_SETLINEINDENTATION , loop, parent_indent + tab_width);
						}
					}

					loop++;
				}
			break;
		}

	}
	
	::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
}

void watch_dblclick(int position, int line) {
    HWND curScintilla = getCurrentScintilla();

	int comment = 9;
	
	int save_selection_start = (int) ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
	int save_selection_end   = (int) ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);

	int start = (int) ::SendMessage(curScintilla, SCI_WORDSTARTPOSITION, position, (LPARAM)true);
	int word_end = (int) ::SendMessage(curScintilla, SCI_WORDENDPOSITION, position, (LPARAM)true);

	int character = (int) ::SendMessage(curScintilla, SCI_GETCHARAT, start - 1 , 0);

	bool run = false;
	bool starting = false;

	if (::SendMessage(curScintilla, SCI_GETSTYLEAT, start + 1, 0) == comment) {
		return;
	}

	if (character == '<') {
		run = true;
		starting = true;
		::SendMessage(curScintilla, SCI_SETSELECTIONSTART, start - 1, 0);
		::SendMessage(curScintilla, SCI_SETSELECTIONEND, start - 1, 0);
	}
	else if (character == '/' && '<' == (int) ::SendMessage(curScintilla, SCI_GETCHARAT, start - 2 , 0) ) {
		run = true;
		starting = false;
		::SendMessage(curScintilla, SCI_SETSELECTIONSTART, start - 2, 0);
		::SendMessage(curScintilla, SCI_SETSELECTIONEND, start - 2, 0);
	}
	
	if ( ! run) return;
	
    char selection[9999];

    ::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);
	::SendMessage(curScintilla, SCI_SEARCHNEXT , SCFIND_REGEXP, (LPARAM)"<[\\w\\/][\\w\\W\\b\\B]*?>");
	::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&selection);
	
	if (selection[strlen(selection) - 2] == '/') {
		::SendMessage(curScintilla, SCI_SETSELECTIONSTART, save_selection_start, 0);
		::SendMessage(curScintilla, SCI_SETSELECTIONEND, save_selection_end, 0);
		return;
	}

	selection[0] = '\0';

	int end = 0;
    int last_search = 0;

	int i = 1;

	if (starting) {
		end = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);
	}

	int first_selection_start = start;
	int first_selection_end = first_selection_end = word_end;

	do {
		if (starting) {
			::SendMessage(curScintilla, SCI_SETSELECTIONSTART, end, 0);
			::SendMessage(curScintilla, SCI_SETSELECTIONEND, end, 0);
		}

		::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);
		::SendMessage(
			curScintilla,
			(starting) ? SCI_SEARCHNEXT : SCI_SEARCHPREV,
			SCFIND_REGEXP,
			(LPARAM)"<[\\w\\/][\\w\\W\\b\\B]*?>"
		);

		end = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);
		::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)&selection);
			
		if (end == last_search) {
			::SendMessage(curScintilla, SCI_SETSELECTIONSTART, end, 0);
			::SendMessage(curScintilla, SCI_SETSELECTIONEND, end, 0);
			break;
		}
			
		last_search = end;

		if (
			::SendMessage(curScintilla, SCI_GETSTYLEAT, ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0) + 1, 0) == comment
		) {
			continue;
		}
		else if (selection[1] == '/') {
			(starting) ? i-- : i++;
		}
		else if (selection[strlen(selection) - 2] == '/') {
			continue;
		}
		else {
			(starting) ? i++ : i--;
		}
	}
	while (i);

	if (starting) {
		int selection_start = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
		int selection_end   = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);
		
		::SendMessage(curScintilla, SCI_SETSELECTION, selection_start + 2, selection_end - 1);
		::SendMessage(curScintilla, SCI_ADDSELECTION, first_selection_start, first_selection_end);
	}
	else {
		::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);
		::SendMessage(curScintilla, SCI_SEARCHNEXT, SCFIND_REGEXP, (LPARAM)"<[\\w]*?");

		int selection_start = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
		int selection_end   = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);
		
		::SendMessage(curScintilla, SCI_SETSELECTION, first_selection_start, first_selection_end);
		::SendMessage(curScintilla, SCI_ADDSELECTION, selection_start + 1, selection_end);
	}
}

bool is_string_style(int style) {
	bool ret = false;

	int lang = -100;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&lang);

	switch(lang) {
		case L_CPP:
			if (style == 6) {
				ret = true;
			}
		case L_HTML:
			if (style == 6) {
				ret = true;
			}
			break;
		case L_JS:
			if (style == 6
			 || style == 49
			 || style == 48
			) {
				ret = true;
			}
			break;
	}
	return ret;
}

void select_string() {
    HWND curScintilla = getCurrentScintilla();

	//int string_style = 6;
	
    int position = ::SendMessage(curScintilla, SCI_GETCURRENTPOS, 0, 0);
	::SendMessage(curScintilla, SCI_SETSEL, position + 1, position + 1);

	int selection_start = 0;
	int selection_end = 0;

	int style_one;

	int i = 2;
	while (1) {
		::SendMessage(curScintilla, SCI_SEARCHANCHOR, 0, 0);
		::SendMessage(curScintilla, SCI_SEARCHNEXT , SCFIND_REGEXP, (LPARAM)"['\"]");

		selection_start = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
		selection_end   = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);

		if ( selection_start == selection_end ) return;

		style_one = ::SendMessage(curScintilla, SCI_GETSTYLEAT, selection_start + 1, 0);

		//char buff[100];
		//sprintf(buff, "%d", style_one);
        //::SendMessage(curScintilla, SCI_INSERTTEXT, ::SendMessage(curScintilla, SCI_GETLENGTH, 0, 0 ), (LPARAM)buff );
		//return;

		//if (style_one == string_style) {
		if (is_string_style(style_one)) {
			break;
		}
		else {
			::SendMessage(curScintilla, SCI_SETSEL, selection_start + 1, selection_start + 1);
		}
		//return;
	}

	//return;

	int original_start = selection_start;
	int style;

	int character = 0;
	int prev = 0;
	while (1) {
		selection_start++;

		style = ::SendMessage(curScintilla, SCI_GETSTYLEAT, selection_start, 0);
		prev = ::SendMessage(curScintilla, SCI_GETCHARAT, selection_start - 1, 0);
		character = ::SendMessage(curScintilla, SCI_GETCHARAT, selection_start, 0);

		//if (character == '"' && style == string_style) {
		if (prev != '\\' && (character == '"' || character == '\'') && is_string_style(style)) {
			break;
		}
	}
	
	::SendMessage(curScintilla, SCI_SETSEL, original_start + 1, selection_start);
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

int strpos(char *haystack, char *needle)
{
   char *p = strstr(haystack, needle);
   if (p)
      return p - haystack;
   return -1;   // Not found = -1.
}

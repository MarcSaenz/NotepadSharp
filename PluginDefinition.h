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

#ifndef PLUGINDEFINITION_H
#define PLUGINDEFINITION_H

//
// All difinitions of plugin interface
//
#include "PluginInterface.h"

//-------------------------------------//
//-- STEP 1. DEFINE YOUR PLUGIN NAME --//
//-------------------------------------//
// Here define your plugin name
//
const TCHAR NPP_PLUGIN_NAME[] = TEXT("Notepad#");

//-----------------------------------------------//
//-- STEP 2. DEFINE YOUR PLUGIN COMMAND NUMBER --//
//-----------------------------------------------//
//
// Here define the number of your plugin commands
//
const int nbFunc = 20;


//
// Initialization of your plugin data
// It will be called while plugin loading
//
void pluginInit(HANDLE hModule);

//
// Cleaning of your plugin
// It will be called while plugin unloading
//
void pluginCleanUp();

//
//Initialization of your plugin commands
//
void commandMenuInit();

//
//Clean up your plugin commands allocation (if any)
//
void commandMenuCleanUp();

//
// Function which sets your command 
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk = NULL, bool check0nInit = false);

//
// Your plugin command functions
//

void show_features();
void show_about();

// Commenting helpers
void Newline();
int poundComment(HWND &curScintilla, char *line);
int cStyleComment(HWND &curScintilla, char *line, int line_number);

// Cyrly brace indentation
int indentAfterCurlyBrace(HWND &curScintilla, int line_number);
void indentEndingCurlyBrace();

// XML/HTML tags indentation
char* create_ending_tag(char *tag);
void XHTMLindent(HWND &curScintilla, int position, int line_number);

void delete_current_line();

// Switching buffers
void buffer_left();
void buffer_right();

// Undo closed files functions
void get_all_files();
void get_files_now();
void find_missing();
void undo_closed_tab();

void closed_file_list();
void insertList();

void wrap_with_tag();
void end_tag();

// Url encode/decode selection
void url_encode_selection();
void url_decode_selection();
char from_hex(char ch);
char to_hex(char code);
char *url_encode(char *str);
char *url_decode(char *str);

// Helpers for embeded code like php and ruby
void EMBED_code();

void ruler();

int auto_numbering();

void Ruby_Newline(HWND &curScintilla);
void RubyExtra(int character);

void docblock_keywords();

// Peek HEX/CSS colors
void peek_hex_color();
void clear_hex_indicators();
long htoi (char s[]);
long hchartoi (char hexdig, int pos);

// Convert TABS to SPACES and reverse
void spaces_to_tabs();
void tabs_to_spaces();
void spaces_tabs(bool tabs);

void paste_indented();

// dblclick tag select
void watch_dblclick(int position, int line);

bool is_string_style(int style);
void select_string();

// Heper functions
HWND getCurrentScintilla();
char* getEOL();
char* trim_left(char *s);
char* trim(char *s);
char* substr(char* string, int begin, int end);
int strpos(char *haystack, char *needle);

#endif //PLUGINDEFINITION_H

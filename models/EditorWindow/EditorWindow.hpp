#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Buffer.H>
#include <cstring>
#include <string>
#include <iostream>
#include <FL/Fl_File_Chooser.H> 

// Classe da janela do editor
class EditorWindow : public Fl_Double_Window {
public:
    EditorWindow(int W, int H, const char* title);
    ~EditorWindow();

    Fl_Window *replace_dlg;
    Fl_Input *replace_find;
    Fl_Input *replace_with;
    Fl_Button *replace_all;
    Fl_Return_Button *replace_next;
    Fl_Button *replace_cancel;

    Fl_Text_Editor *editor;
    char search[256];
};

void load_file(char*, int);

extern Fl_Text_Buffer *textbuf;
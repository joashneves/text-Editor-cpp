#include <iostream>
#include <Fl/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Menu_Item.H>

using namespace std;

int changed = 0;
char filename[256] = "";
Fl_Text_Buffer *textbuffer = new Fl_Text_Buffer();

class EditorWindow : public Fl_Double_Window{
public:
  EditorWindow(int witdh, int height, const char *t);
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


w->editor = new Fl_Text_Editor(0, 30, 640, 370);
w->editor->buffer(textitems);

textbuf->

Fl_Menu_Item menuItems[] = {
    {"&File", 0, 0, 0, FL_SUBMENU},
    {"&New File...", 0, (Fl_Callback *)new_cd},
    {"&Open File...", FL_CTRL + 'o', (Fl_Callback *)open_cd},
    {"&Insert File...", FL_CTRL + 'i', (Fl_Callback *)insert_cd, 0, FL_MENU_DIVIDER},
    {"&Save File", FL_CTRL + 's', (Fl_Callback *)save_cd},
    {"&Save File &As...", FL_CTRL + FL_SHIFT + 's', (Fl_Callback *)saveas_cd, 0, FL_MENU_DIVIDER},
    {"New &View", FL_ALT + 'v', (Fl_Callback *)view_cd, 0 },
    {"&Close View", FL_CTRL + 'w', (Fl_Callback *)close_cd, 0, FL_MENU_DIVIDER},
    {"E&xit", FL_CTRL + 'q', (Fl_Callback *)quit_cd, 0},
    {0},
    {"&Editor", 0,0,0, FL_SUBMENU}
  };

void new_cd(Fl_Widget*, void*){}  
void open_cd(Fl_Widget*, void*){}  
void insert_cd(Fl_Widget*, void*){}  
void save_cd(Fl_Widget*, void*){}  
void saveas_cd(Fl_Widget*, void*){}  
void view_cd(Fl_Widget*, void*){}  
void close_cd(Fl_Widget*, void*){}  
void quit_cd(Fl_Widget*, void*){}  

Fl_Menu_Bar *m = new Fl_Menu_Bar(0,0,640,30);
m->copy(menuItems);


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

int changed = 0;
Fl_Text_Buffer *textbuf = new Fl_Text_Buffer();

// Função de callback para mudança no texto
void changed_cb(int, int nInserted, int nDeleted,int, const char*, void* v) {
  if ((nInserted || nDeleted)) changed = 1;
  EditorWindow *w = (EditorWindow *)v;
  
  w->editor->show_insert_position();
  std::cout << nInserted << '\n';
}

// Callbacks de menu vazios por enquanto
void new_cb(Fl_Widget*, void*) {}
void open_cb(Fl_Widget*, void*) {}
void insert_cb(Fl_Widget*, void*) {}
void save_cb(Fl_Widget*, void*) {}
void saveas_cb(Fl_Widget*, void*) {}
void view_cb(Fl_Widget*, void*) {}
void close_cb(Fl_Widget*, void*) {}
void quit_cb(Fl_Widget*, void*) { exit(0); }
void undo_cb(Fl_Widget*, void*) {}

void cut_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  Fl_Text_Editor::kf_cut(0, e->editor);
}

void copy_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  Fl_Text_Editor::kf_copy(0, e->editor);
}
void paste_cb(Fl_Widget*, void*) {}

void delete_cb(Fl_Widget*, void* v) {
  textbuf->remove_selection();
}

void find2_cb(Fl_Widget* w, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  if (e->search[0] == '\0') {
    // Search string is blank; get a new one...
    find2_cb(w, v);
    return;
  }

  int pos = e->editor->insert_position();
  int found = textbuf->search_forward(pos, e->search, &pos);
  if (found) {
    // Found a match; select and update the position...
    textbuf->select(pos, pos+strlen(e->search));
    e->editor->insert_position(pos+strlen(e->search));
    e->editor->show_insert_position();
  }
  else fl_alert("No occurrences of \'%s\' found!", e->search);
}

void find_cb(Fl_Widget* w, void* v) {
EditorWindow* e = (EditorWindow*)v;
const char *val;

val = fl_input("Search String:", e->search);
if (val != NULL) {
// User entered a string - go find it!
strcpy(e->search, val);
find2_cb(w, v);
}


int pos = e->editor->insert_position();
int found = textbuf->search_forward(pos, e->search, &pos);
if (found) {
// Found a match; select and update the position...
textbuf->select(pos, pos+strlen(e->search));
e->editor->insert_position(pos+strlen(e->search));
e->editor->show_insert_position();
}
else fl_alert("No occurrences of \'%s\' found!", e->search);
}
void replace_cb(Fl_Widget*, void*) {}
void replace2_cb(Fl_Widget*, void*) {}

EditorWindow::EditorWindow(int W, int H, const char* title) : Fl_Double_Window(W, H, title) {
    editor = new Fl_Text_Editor(0, 30, W, H - 30);
    editor->buffer(textbuf);
    editor->textfont(FL_COURIER);
    editor->textcolor(FL_BLUE);

    replace_dlg = new Fl_Window(300, 105, "Replace");
    replace_find = new Fl_Input(70, 10, 200, 25, "Find:");
    replace_with = new Fl_Input(70, 40, 200, 25, "Replace:");
    replace_all = new Fl_Button(10, 70, 90, 25, "Replace All");
    replace_next = new Fl_Return_Button(105, 70, 120, 25, "Replace Next");
    replace_cancel = new Fl_Button(230, 70, 60, 25, "Cancel");
    replace_dlg->end();

    end();
}

EditorWindow::~EditorWindow() {
    delete textbuf;
}

int main() {
    EditorWindow *window = new EditorWindow(680, 440, "Editor de texto");

    // Menu
    Fl_Menu_Item menuitems[] = {
        { "&File", 0, 0, 0, FL_SUBMENU },
            { "&New File", 0, new_cb },
            { "&Open File...", FL_CTRL + 'o', open_cb },
            { "&Insert File...", FL_COMMAND + 'i', insert_cb, 0, FL_MENU_DIVIDER },
            { "&Save File", FL_COMMAND + 's', save_cb },
            { "Save File &As...", FL_COMMAND + FL_SHIFT + 's', saveas_cb, 0, FL_MENU_DIVIDER },
            { "New &View", FL_ALT + 'v', view_cb },
            { "&Close View", FL_COMMAND + 'w', close_cb, 0, FL_MENU_DIVIDER },
            { "E&xit", FL_COMMAND + 'q', quit_cb },
            { 0 },

        { "&Edit", 0, 0, 0, FL_SUBMENU },
            { "&Undo", FL_COMMAND + 'z', undo_cb, 0, FL_MENU_DIVIDER },
            { "Cu&t", FL_COMMAND + 'x', cut_cb },
            { "&Copy", FL_COMMAND + 'c', copy_cb },
            { "&Paste", FL_COMMAND + 'v', paste_cb },
            { "&Delete", 0, delete_cb },
            { 0 },

        { "&Search", 0, 0, 0, FL_SUBMENU },
            { "&Find...", FL_COMMAND + 'f', find_cb },
            { "F&ind Again", FL_COMMAND + 'g', find2_cb },
            { "&Replace...", FL_COMMAND + 'r', replace_cb },
            { "Re&place Again", FL_COMMAND + 't', replace2_cb },
            { 0 },

        { 0 }
    };

    Fl_Menu_Bar *menu = new Fl_Menu_Bar(0, 0, 680, 30);
    menu->copy(menuitems);

    textbuf->add_modify_callback(changed_cb, window);
    textbuf->call_modify_callbacks();

    window->show();
    return Fl::run();
}

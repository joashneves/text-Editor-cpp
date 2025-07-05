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

int changed = 0;
Fl_Text_Buffer *textbuf = new Fl_Text_Buffer();
char filename[256] = "";
char title[256] = "";

// Função de callback para mudança no texto
void changed_cb(int, int nInserted, int nDeleted,int, const char*, void* v) {
  if ((nInserted || nDeleted)) changed = 1;
  EditorWindow *w = (EditorWindow *)v;
  
  w->editor->show_insert_position();
  std::cout << nInserted << '\n';
}

void save_file(char *newfile){
  if (textbuf->savefile(newfile)){
    fl_alert("Erro ao salvar o arquivo \'%s\' :\n%s", newfile, strerror(errno));
  }
  else {
    strcpy(filename, newfile);
  }
  changed = 0;
  textbuf->call_modify_callbacks();
}

void saveas_cb(void){
  char *newfile;
  newfile = fl_file_chooser("Salva arquivo? ", "*", filename);
  if (newfile != NULL) save_file(newfile);
}

void save_cb(void) {
  if(filename[0] == '\0'){
    saveas_cb();
    return;
  }
  else save_file(filename);
}

int check_save(void){
  if(!changed) return 1;
  int r = fl_choice("O arquivo não foi salvo \n Voce gostaria de salva-lo?", "Cancelar", "Salvar", "Descartar");
  if (r == 1){
    save_cb();
    return !changed;
  }
  return (r == 2) ? 1 : 0;
}

// Callbacks de menu vazios por enquanto
void new_cb(Fl_Widget*, void*) {
  if(!check_save()) return;
  filename[0] = '\0';
  textbuf->select(0, textbuf->length());
  textbuf->remove_selection();
  changed = 0;
  textbuf->call_modify_callbacks();
}

int loading = 0;
void load_file(char *newfile, int ipos){
  loading =1;
  int insert = (ipos != -1);
  changed = insert;
  if(!insert) strcpy(filename, "");
  int r;
  if(!insert) r = textbuf->loadfile(newfile);
  if(r){
    fl_alert("Erro ao carregar o arquivo \'%s\' : \n%s.", newfile, strerror(errno));
  }else{
    if(!insert) strcpy(filename, newfile);
  }
  loading = 0;
  textbuf->call_modify_callbacks();
}


void open_cb(Fl_Widget*, void*) {
  if(!check_save()) return;

  char *newfile = fl_file_chooser("Abrir arquivo?", "*", filename);
  if(newfile != NULL) load_file(newfile, -1);
}

void replace_cb(Fl_Widget*, void* v){
  EditorWindow* e= (EditorWindow*)v;
  e->replace_dlg->show();
}
void replace2_cb(Fl_Widget*, void* v){
  EditorWindow* e = (EditorWindow*)v;
  const char *find = e->replace_find->value();
  const char *replace = e->replace_with->value();

  if(find[0] == '\0'){
    e->replace_dlg->show();
    return;
  }
  e->replace_dlg->hide();
  int pos = e->editor->insert_position();
  int found = textbuf->search_forward(pos, find, &pos);

  if(found){
    textbuf->select(pos, pos+strlen(find));
    textbuf->remove_selection();
    textbuf->insert(pos, replace);
    textbuf->select(pos, pos+strlen(replace));
    e->editor->insert_position(pos+strlen(replace));
    e->editor->show_insert_position();
  }
  else fl_alert("No occurrences of \'%s\' found!", find);
}

void replall_cd(Fl_Widget*, void* v){
  EditorWindow* e = (EditorWindow*)v;
  const char *find = e->replace_find->value();
  const char *replace = e->replace_with->value();

  find = e->replace_find->value();
  if(find[0] == '\0'){
    e->replace_dlg->show();
    return;
  }
  e->replace_dlg->hide();
  e->editor->insert_position(0);
  int times = 0;
  for (int found = 1; found;){
    int pos = e->editor->insert_position();
    found = textbuf->search_forward(pos, find, &pos);
    if(found){
      textbuf->select(pos, pos+strlen(find));
      textbuf->remove_selection();
      e->editor->insert_position(pos+strlen(replace));
      e->editor->show_insert_position();
      times++;
    }
  }
  if(time){
    fl_message("Replaced %d ocurrences.", times);
  }else{
    fl_alert("NO OCCURRENCES OF \'%s\' found!", find);
  }
}

void replcan_cb(Fl_Widget*, void* v){
  EditorWindow* e = (EditorWindow*)v;
  e->replace_dlg->hide();
}

void insert_cb(Fl_Widget*, void*) {}

void view_cb(Fl_Widget*, void*) {}
void close_cb(Fl_Widget*, void*) {}
void quit_cb(Fl_Widget*, void*) { 
  if(changed && check_save()) return;

  exit(0);
 }

void undo_cb(Fl_Widget*, void*) {}

void cut_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  Fl_Text_Editor::kf_cut(0, e->editor);
}

void copy_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  Fl_Text_Editor::kf_copy(0, e->editor);
}
void paste_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  Fl_Text_Editor::kf_paste(0, e->editor);
}

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
void set_title(Fl_Window* w){
  if(filename[0] == '\0'){
    strcpy(title, "Untitled");
  }
  else{
    char *slash;
    slash = strrchr(filename, '/');
    #ifdef WIN32
    if(slash == NULL)slash = strrchr(filename, '\\');
    #endif
    if(slash != NULL) strcpy(title, slash + 1);
    else strcpy(title, filename); 
  }
  if (changed) strcat(title, " (Modificado)");
  w->label(title);
}


Fl_Menu_Item menuitems[] = {
  { "&File",              0, 0, 0, FL_SUBMENU },
    { "&New File",        0, (Fl_Callback *)new_cb },
    { "&Open File...",    FL_COMMAND + 'o', (Fl_Callback *)open_cb },
    { "&Insert File...",  FL_COMMAND + 'i', (Fl_Callback *)insert_cb, 0, FL_MENU_DIVIDER },
    { "&Save File",       FL_COMMAND + 's', (Fl_Callback *)save_cb },
    { "Save File &As...", FL_COMMAND + FL_SHIFT + 's', (Fl_Callback *)saveas_cb, 0, FL_MENU_DIVIDER },
    { "New &View", FL_ALT + 'v', (Fl_Callback *)view_cb, 0 },
    { "&Close View", FL_COMMAND + 'w', (Fl_Callback *)close_cb, 0, FL_MENU_DIVIDER },
    { "E&xit", FL_COMMAND + 'q', (Fl_Callback *)quit_cb, 0 },
    { 0 },

  { "&Edit", 0, 0, 0, FL_SUBMENU },
    { "&Undo",       FL_COMMAND + 'z', (Fl_Callback *)undo_cb, 0, FL_MENU_DIVIDER },
    { "Cu&t",        FL_COMMAND + 'x', (Fl_Callback *)cut_cb },
    { "&Copy",       FL_COMMAND + 'c', (Fl_Callback *)copy_cb },
    { "&Paste",      FL_COMMAND + 'v', (Fl_Callback *)paste_cb },
    { "&Delete",     0, (Fl_Callback *)delete_cb },
    { 0 },

  { "&Search", 0, 0, 0, FL_SUBMENU },
    { "&Find...",       FL_COMMAND + 'f', (Fl_Callback *)find_cb },
    { "F&ind Again",    FL_COMMAND + 'g', find2_cb },
    { "&Replace...",    FL_COMMAND + 'r', replace_cb },
    { "Re&place Again", FL_COMMAND + 't', replace2_cb },
    { 0 },

  { 0 }
};


EditorWindow::EditorWindow(int W, int H, const char* title) : Fl_Double_Window(W, H, title) {
    editor = new Fl_Text_Editor(0, 30, W, H - 30);
    editor->buffer(textbuf);
    editor->textfont(FL_COURIER);
    editor->textcolor(FL_BLUE);

      Fl_Menu_Bar *m = new Fl_Menu_Bar(0,0,640,30);
  m->copy(menuitems);

  
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

int main(int argc, char **argv) {

  textbuf = new Fl_Text_Buffer;

  EditorWindow* window = new EditorWindow(640, 400, "Text Editor");
  
  
  window->show(1, argv);

  if (argc > 1) load_file(argv[1], -1);

  return Fl::run();
}
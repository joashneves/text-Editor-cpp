#pragma once

// Inclusões de cabeçalhos da biblioteca FLTK e da biblioteca padrão C++.
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

/**
 * @class EditorWindow
 * @brief Representa a janela principal do editor de texto.
 *
 * Herda de Fl_Double_Window para fornecer uma interface gráfica com buffer duplo,
 * o que melhora a renderização e reduz o flickering.
 */
class EditorWindow : public Fl_Double_Window {
public:
    /**
     * @brief Construtor da classe EditorWindow.
     * 
     * @param W Largura da janela.
     * @param H Altura da janela.
     * @param title Título da janela.
     */
    EditorWindow(int W, int H, const char* title);

    /**
     * @brief Destrutor da classe EditorWindow.
     */
    ~EditorWindow();

    // Widgets para a funcionalidade de "Substituir"
    Fl_Window *replace_dlg;       // Janela de diálogo para substituir texto.
    Fl_Input *replace_find;       // Campo de entrada para o texto a ser encontrado.
    Fl_Input *replace_with;       // Campo de entrada para o texto de substituição.
    Fl_Button *replace_all;       // Botão para substituir todas as ocorrências.
    Fl_Return_Button *replace_next; // Botão para substituir a próxima ocorrência.
    Fl_Button *replace_cancel;    // Botão para cancelar a operação de substituição.

    // Widget principal do editor de texto.
    Fl_Text_Editor *editor;

    // Buffer para armazenar o texto da busca.
    std::string search;
};

// Declaração de função externa para carregar um arquivo.
void load_file(const char*, int);

// Declaração de um buffer de texto externo, usado para armazenar o conteúdo do editor.
extern Fl_Text_Buffer *textbuf;

void find_cb(Fl_Widget* w, void* v);

void delete_cb(Fl_Widget*, void* v);
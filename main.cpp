// main.cpp
#include "textEditor.h"
#include <FL/Fl.H>

int main(int argc, char **argv) {
    Fl_Window *window = new_view();
    window->show(argc, argv);
    return Fl::run();
}
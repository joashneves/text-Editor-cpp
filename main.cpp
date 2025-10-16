#include <models/EditorWindow/EditorWindow.hpp>

int main(int argc, char **argv)
{
  // cria Editor
  EditorWindow *window = new EditorWindow(640, 400, "Text Editor");

  window->show(1, argv);

  if (argc > 1)
    load_file(argv[1], -1);

  return Fl::run();
}
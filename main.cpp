// Inclusão do cabeçalho da classe da janela do editor.
#include <models/EditorWindow/EditorWindow.hpp>

/**
 * @brief Função principal do programa.
 * 
 * @param argc Número de argumentos da linha de comando.
 * @param argv Vetor de argumentos da linha de comando.
 * @return int Código de status de saída.
 */
int main(int argc, char **argv)
{
  // Cria uma nova instância da janela do editor com dimensões 640x400.
  EditorWindow *window = new EditorWindow(640, 400, "Text Editor");

  // Exibe a janela.
  window->show(1, argv);

  // Se um nome de arquivo foi passado como argumento na linha de comando,
  // carrega o conteúdo desse arquivo no editor.
  if (argc > 1)
    load_file(argv[1], -1);

  // Inicia o loop de eventos do FLTK, que aguarda por interações do usuário.
  return Fl::run();
}

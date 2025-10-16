# Editor de Texto Simples em C++

Um editor de texto básico desenvolvido em C++ com a biblioteca gráfica [FLTK](https://www.fltk.org/).

## Funcionalidades

*   **Gerenciamento de Arquivos:**
    *   Criar novo arquivo
    *   Abrir arquivo existente
    *   Salvar arquivo
    *   Salvar como...
*   **Edição de Texto:**
    *   Recortar, copiar e colar
    *   Desfazer (funcionalidade a ser implementada)
    *   Excluir seleção
*   **Busca e Substituição:**
    *   Encontrar texto no documento
    *   Substituir ocorrências de texto

## Pré-requisitos

Para compilar e executar este projeto, você precisa ter a biblioteca FLTK instalada.

### Instalação do FLTK

**Em sistemas baseados em Debian/Ubuntu:**
```bash
sudo apt-get update
sudo apt-get install libfltk1.3-dev
```

**Em macOS (usando Homebrew):**
```bash
brew install fltk
```

## Compilação

O projeto utiliza um `Makefile` para simplificar o processo de compilação. Para compilar, execute o seguinte comando no terminal:

```bash
make
```

Isso irá gerar um executável chamado `text_editor`.

## Uso

Para iniciar o editor de texto, execute o seguinte comando:

```bash
./text_editor
```

Você também pode abrir um arquivo diretamente pela linha de comando:

```bash
./text_editor nome_do_arquivo.txt
```

## Limpeza

Para remover os arquivos de objeto e o executável gerados durante a compilação, execute:

```bash
make clean
```
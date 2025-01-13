# Atividade em C-EDB2
## Projeto 2 Jogo de Caça-Palavras

- **Para cada pasta há um arquivo classe correspondente e sua main.**

## Sobre o jogo

**O objetivo deste projeto é implementar um jogo de caça-palavras na linguagem C, utilizando uma Árvore AVL para armazenar palavras encontradas 
e uma Árvore Digital (Trie) para validar palavras possíveis. O projeto será
modularizado, dividido em múltiplos arquivos para facilitar o entendimento
e manutenção. A busca pelas palavras será feita automaticamente pelo programa, verificando todas as direções possíveis no tabuleiro.**

## Discentes

- **Elon Arkell Freire Bezerra**
- **Vinicius Alexandre Melo**

## Docente

- **Einstein Gomes dos Santos**

## Configuração e execução

**Baixe todos os arquivos (Exceto o READ.me)**:

**Instale as ferramentas essenciais para C, análogo as variáveis de ambiente**:

- **Dica: Atualize os repositórios de pacotes caso esteja no Linux (pelo terminal), caso esteja no Windows é necessário instalar o MinGW (pelo próprio navegador):**
```bash
  sudo apt update
```
**Após todo o processo, rode o programa pelo Linux**
```bash
  make all
```
**Caso esteja no Windows, abra no terminal a pasta do projeto (localizado onde foi instalado) e utilize tais comandos**
```bash
  gcc -c main.c avl.c trie.c jogo.c
  gcc -o prog main.o avl.o trie.o jogo.o
  ./prog
```
**Referência do Projeto:**
```bash
  Alguns códigos foram baseados nos slides disponíveis no sigaa pelo Docente Einstein Gomes dos Santos.
  Outra fonte de aprendizado sobre Árvore AVL foi o canal do YouTube Programação Descomplicada: https://www.youtube.com/watch?v=F7_Daymw-WM
  E sobre Árvore Trie no canal Computação com Prof. Foleis: https://youtu.be/Spmw4hTo7ek
```


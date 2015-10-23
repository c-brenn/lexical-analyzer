#include "analyzer.c"

int main(int argc, char ** argv) {
  for(int i = 1; i < argc; i++) {
    analyze_lexeme(argv[i]);
  }
}

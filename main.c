#include "analyzer.c"

int main(int argc, char ** argv) {
  int error_input_count = 10;
  char * error_inputs[10] = {
    "179",
    "-2803",
    "-0",
    "4bc9h",
    "172371b",
    "bb",
    "-000001",
    "+123b",
    "-12h",
    "-120-3"
  };
  for(int i = 1; i < argc; i++) {
    analyze_lexeme(argv[i]);
  }
}

#include "analyzer.c"

int main() {
  int input_count = 7;
  char * inputs[7] = {
    "179",
    "-2803",
    "-0",
    "4bc9h",
    "172371b",
    "bb",
    "-000001"
  };
  for(int i = 0; i < input_count; i++) {
    analyze_lexeme(inputs[i]);
  }
}

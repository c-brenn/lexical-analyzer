#include "analyzer.c"
#include "test_inputs.h"

void analyze_test_inputs() {
  int length = sizeof(inputs) / sizeof(char *);
  for(int i = 0; i < length; i++){
    printf("--- %s ---\n", reasons[i]);
    analyze_lexeme(inputs[i]);
  }
}

int main(int argc, char ** argv) {
  for(int i = 1; i < argc; i++) {
    if(strcmp(argv[i], "--test-inputs") == 0) {
      analyze_test_inputs();
    } else {
      analyze_lexeme(argv[i]);
    }
  }
}


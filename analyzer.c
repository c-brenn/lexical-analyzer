#include "transition_functions.h"

analyzer_state * new_analyzer_state() {
  analyzer_state * this = malloc(sizeof(analyzer_state));
  this->sign = 1;
  this->digit_count = 0;
  this->current_char = '+';
  this->current_state = start;
  this->digits = malloc(sizeof(int) * MAX_OCT_DIGITS);
  this->value = 0;
  return this;
}

void free_analyzer_state(analyzer_state * this) {
  free(this->digits);
  free(this);
}

void analyze_lexeme(char * lexeme) {
  printf("Lexeme(%s) ->", lexeme);

  analyzer_state * astate = new_analyzer_state();
  bool done = false;
  int index = 0;
  while(!done) {
    char current_char = lexeme[index];
    input current_input_type = char_to_input(current_char);
    transition current_transition = transition_table[astate->current_state][current_input_type];
    astate->current_char = current_char;
    if(current_transition.transition_function != NULL) {
      current_transition.transition_function(astate);
    }
    if(astate->current_state != reject) {
      astate->current_state = current_transition.next_state;
    }
    done = (astate->current_state == reject || astate->current_state == accept);
    index++;
  }

  if(astate->current_state == accept) {
    char * base = (astate->base == 8)? "Octal" : (astate->base == 10)? "Decimal" : "Hexadecimal";
    printf("Lexical Token(%s Constant, %d)\n", base, astate->value);
  }
}

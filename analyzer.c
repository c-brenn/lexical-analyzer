#include "transition_functions.h"

analyzer_state * new_analyzer_state() {
  analyzer_state * this = malloc(sizeof(analyzer_state));
  this->sign = 1;
  this->digit_count = 0;
  this->current_char = '+';
  this->current_state = start;
  this->digits = malloc(sizeof(int) * MAX_OCTAL_DIGITS);
  return this;
}

void analyze_lexeme(char * lexeme) {
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
    astate->current_state = current_transition.next_state;
    done = (astate->current_state == reject || astate->current_state == accept);
    index++;
  }
}

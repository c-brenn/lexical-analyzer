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
  printf("Lexeme(%s) -> ", lexeme);

  analyzer_state * astate = new_analyzer_state();
  bool done = false;
  int index = 0;
  while(!done) {

    char current_char = lexeme[index];
    input current_input_type = char_to_input(current_char); // translate char to class of input
    transition current_transition = transition_table[astate->current_state][current_input_type]; // look up next state and transition function
    astate->current_char = current_char; // set the current char so it can be used in transition functions

    // call the transition function if it is not a "no op"
    if(current_transition.transition_function != NULL) {
      current_transition.transition_function(astate);
    }
    // transition to the next state unless we have just rejected the lexeme
    if(astate->current_state != reject) {
      astate->current_state = current_transition.next_state;
    }
    // check to see if we have accepted/rejected the lexeme and should exit
    done = (astate->current_state == reject || astate->current_state == accept);
    index++;
  }

  // print an appropriate message depending on whether the lexeme was accepted or not
  if(astate->current_state == accept) {
    char * base = (astate->base == 8)? "Octal" : (astate->base == 10)? "Decimal" : "Hexadecimal";
    printf("Lexical Token(%s Constant, %d)\n", base, astate->value);
  } else {
    printf("ERROR: %s\n", astate->error_string);
  }
  // free the memory used by the analyzer struct
  free_analyzer_state(astate);
}

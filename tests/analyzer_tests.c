#include "minunit.h"
#include "../analyzer.c"


int tests_run = 0;

static char * test_new_analyzer_state() {
  analyzer_state * astate = new_analyzer_state();
  mu_assert("error, sign not initialized to 1", astate->sign == 1);
  mu_assert("error, char not initialized to +", astate->current_char == '+');
  mu_assert("error, digit_count not initialized to 0", astate->digit_count == 0);
  mu_assert("error, state not initialized to start state", astate->current_state == start);
  mu_assert("error, true is not true!", true);
  return 0;
}

static char * all_tests() {
  mu_run_test(test_new_analyzer_state);
  return 0;
}

int main(int argc, char **argv) {
  char *result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  }
  else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);
  return result != 0;
}

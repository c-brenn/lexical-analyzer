#include <stdio.h>
#include "minunit.h"
#include "../analyzer.c"

int tests_run = 0;

static char * test_true() {
  mu_assert("error, true is not true!", true);
  return 0;
}

static char * test_false() {
  mu_assert("error, true is not true!", !false);
  return 0;
}

static char * test_set_sign() {
  analyzer_state * astate = new_analyzer_state();
  astate->current_char = '+';
  set_sign(astate);
  mu_assert("error, set sign does not set the sign!", astate->sign == 1);
  astate->current_char = '-';
  set_sign(astate);
  mu_assert("error, set sign does not set the sign!", astate->sign == -1);
  return 0;
}

static char * all_tests() {
  mu_run_test(test_true);
  mu_run_test(test_false);
  mu_run_test(test_set_sign);
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

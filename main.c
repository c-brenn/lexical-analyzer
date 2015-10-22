#include "analyzer.c"

int main() {
  char * test_oct = "123b";
  char * test_dec = "1234";
  char * test_hex = "123afh";
  char * fuck = "12ab";
  analyze_lexeme(test_oct);
  analyze_lexeme(test_dec);
  analyze_lexeme(test_hex);
  analyze_lexeme(fuck);
}

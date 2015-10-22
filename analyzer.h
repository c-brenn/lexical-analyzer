typedef enum {
  false = 0,
  true = 1
} bool;

typedef enum {
  start = 0,
  signed_value,
  slz,
  lz,
  oct,
  dec,
  sdec,
  hex,
  b,
  h,
  accept,
  reject
} state;

typedef enum {
  sign = 0,
  zero,
  octal_digit,
  decimal_digit,
  hex_digit,
  b_digit,
  h_digit,
  end_symbol,
  invalid
} input;

typedef struct {
  int sign;
  int digit_count;
  state current_state;
  char current_char;
  input current_input;
  int * digits;
  int value;
  int base;
} analyzer_state;

typedef struct {
  state next_state;
  void (*transition_function)(analyzer_state * this);
} transition;

#define MAX_OCT_DIGITS 11
#define MAX_DEC_DIGITS 10
#define MAX_HEX_DIGITS 8

analyzer_state * new_analyzer_state();
void analyze_lexeme(char * lexeme);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyzer.h"

char tolower(char c) {
  return (c <= 'Z' && c >= 'A') ? c + 32 : c;
}
void set_sign(analyzer_state * this) {
  if(this->current_char == '+' || this->current_char == '0') {
    this->sign = 1;
  } else {
    this->sign = -1;
  }
}

int char_to_int(char digit) {
  digit = tolower(digit);
  if(digit >= 'a' && digit <= 'f') {
    return digit - 'a' + 10;
  } else {
    return digit - '0';
  }
}

input char_to_input(char c) {
  c = tolower(c);
  if(c == 'b') {
    return b_digit;
  } else if(c == '0') {
    return zero;
  } else if (c >= '1' && c <= '7') {
    return octal_digit;
  } else if(c == '8' || c == '9') {
    return decimal_digit;
  } else if(c >= 'a' && c <= 'f') {
    return hex_digit;
  } else if(c == 'h') {
    return h_digit;
  } else if( c== '-' || c == '+') {
    return sign;
  } else if(c == '\0') {
    return end_symbol;
  } else {
    return invalid;
  }
}

void add_digit(analyzer_state * this) {
  this->digits[this->digit_count] = char_to_int(this->current_char);
  this->digit_count++;
}

void add_b(analyzer_state * this) {
  this->digits[this->digit_count] = char_to_int('b');
  this->digit_count++;
}

void add_digit_b(analyzer_state * this) {
  add_b(this);
  add_digit(this);
}

int get_value(int * digits, int digit_count, int base) {
  int sum = 0;
  for(int i = 0; i < digit_count; i++) {
    if(base == 16) {
      sum = sum << 4;
      sum += digits[i];
    } else if(base == 8) {
      sum = sum  << 3;
      sum += digits[i];
    } else {
      sum *= 10;
      sum += digits[i];
    }
  }
  return sum;
}

void accept_oct(analyzer_state * this) {
  this->base = 8;
  if(this->digit_count < MAX_OCT_DIGITS || (this->digit_count == MAX_OCT_DIGITS && this->digits[0] <= 3)) {
    this->value = get_value(this->digits, this->digit_count, this->base);
  } else {
    this->current_state = reject;
    printf("Too many digits for Octal constant.\n");
  }
}

bool will_not_overflow_dec(int digit_count, int * digits, int sign) {
  if(digit_count < MAX_DEC_DIGITS) {
    return true;
  } else if(digit_count == MAX_DEC_DIGITS) {
    char dec_string[digit_count];
    for(int i = 0; i < digit_count; i++) {
      dec_string[i] = (char)('0' + digits[i]);
    }
    if(sign == 1) {
      return strcmp(dec_string, "2147483647") <= 0;
    } else {
      return strcmp(dec_string, "2147483648") <= 0;
    }
  } else {
    return false;
  }
}

void accept_decimal(analyzer_state * this) {
  this->base = 10;
  if(will_not_overflow_dec(this->digit_count, this->digits, this->sign)) {
    this->value = this->sign * get_value(this->digits, this->digit_count, this->base);
  } else {
    this->current_state = reject;
    printf("Too many digits for Decimal constant.\n");
  }
}

void accept_hex(analyzer_state * this) {
  this->base = 16;
  if(this->digit_count <= MAX_HEX_DIGITS) {
    this->value = get_value(this->digits, this->digit_count, this->base);
  } else {
    this->current_state = reject;
    printf("Too many digits for Hex constant\n");
  }
}

void reject_lex(analyzer_state * this) {
  printf("rejected for some reason\n");
}

transition transition_table[10][8] =
{
/*        ||     +|-  ||  0  ||  1-7  ||  8-9  ||  a-f  ||  a-f  ||  b|B  ||  h|H  ||  -|           */
/* =======|| ===============================================================================================================================================*/
/* 0 start|| */ {{signed_value, &set_sign}, {lz, NULL}, {oct, &add_digit}, {dec, &add_digit}, {hex, &add_digit}, {hex, &add_digit}, {reject, &reject_lex}, {reject, &reject_lex}},
/* 1 sign || */ {{reject, &reject_lex}, {slz, NULL}, {sdec, &add_digit}, {sdec, &add_digit}, {reject, &reject_lex}, {reject, &reject_lex},{reject, &reject_lex}, {reject, &reject_lex}},
/* 2 slz  || */ {{reject, &reject_lex}, {slz, NULL}, {sdec, &add_digit},{sdec, &add_digit}, {reject, &reject_lex}, {reject, &reject_lex},{reject, &reject_lex}, {accept, &accept_decimal}},
/* 3 lz   || */ {{reject, &reject_lex}, {lz, NULL}, {oct, &add_digit}, {dec, &add_digit}, {hex, &add_digit}, {b, NULL}, {h, NULL}, {accept, &accept_decimal}},
/* 4 oct  || */ {{reject, &reject_lex}, {oct, &add_digit}, {oct, &add_digit}, {dec, &add_digit}, {hex, &add_digit}, {b, NULL}, {h, NULL}, {accept, &accept_decimal}},
/* 5 dec  || */ {{reject, &reject_lex}, {dec, &add_digit}, {dec, &add_digit}, {dec, &add_digit}, {hex, &add_digit}, {hex, &add_digit}, {h, NULL}, {accept, &accept_decimal}},
/* 6 sdec || */ {{reject, &reject_lex}, {sdec, &add_digit}, {sdec, &add_digit}, {sdec, &add_digit}, {reject, &reject_lex}, {reject, &reject_lex}, {reject, &reject_lex}, {accept, &accept_decimal}},
/* 7 hex  || */ {{reject, &reject_lex}, {hex, &add_digit}, {hex, &add_digit}, {hex, &add_digit}, {hex, &add_digit}, {hex, &add_digit}, {h, NULL}, {reject, &reject_lex}},
/* 8 b    || */ {{reject, &reject_lex}, {hex, &add_digit_b}, {hex, &add_digit_b}, {hex, &add_digit_b}, {hex, &add_digit_b}, {hex, &add_digit_b}, {h, &add_b}, {accept, &accept_oct}},
/* 9 h    || */ {{reject, &reject_lex}, {reject, &reject_lex}, {reject, &reject_lex}, {reject, &reject_lex}, {reject, &reject_lex}, {reject, &reject_lex}, {reject, &reject_lex}, {accept, &accept_hex}}
};


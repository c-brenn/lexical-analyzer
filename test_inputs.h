static char * inputs[] = {
  "0", // decimal zero
  "-0", // signed decimal zer
  "0b", // octal 0
  "0h", // hex 0
  "1234", // valid decimal
  "-1234", // valid signed decimal
  "000123", // valid decimal with leading zeros
  "-000034",// valid signed decimal with leading zeros
  "12b", // valid octal
  "0002b", // valid octal with leading zeros
  "37777777777b", // valid octal that produces a negative decimal value
  "1289abfh", // valid hexadecimal
  "00123afh", // valid hexadecimal with leading zeros
  "ffffffffh", // valid hexadecimal that prodcuces a negative decimal value
  "2147483647", // max int
  "2147483648", // decimal that would overflow
  "-2147483648", // min int
  "-2147483649", // negative decimal that would overflow
  "123456789h" , // hexadecimal that would overflow
  "40000000000b", // octal that would overflow
  "123llasdd", // lexeme with invalid characters
  "+123+234", // extra sign
  "+123b", // invalid - signed octal
  "-1234h", // invalid - signed hexadecimal
  "", // empty lexeme
  "b", // empty octal
  "h", // empty hex
};

static char * reasons[] = {
  "decimal zero",
  "signed decimal zero",
  "octal zero",
  "hex 0",
  "valid decimal",
  "valid signed decimal",
  "valid decimal with leading zeros",
  "valid signed decimal with leading zeros",
  "valid octal",
  "valid octal with leading zeros",
  "valid octal that produces a negative decimal value",
  "valid hexadecimal",
  "valid hexadecimal with leading zeros",
  "valid hexadecimal that prodcuces a negative decimal value",
  "max int",
  "decimal that would overflow",
  "min int",
  "negative decimal that would overflow",
  "hexadecimal that would overflow",
  "octal that would overflow",
  "lexeme with invalid characters",
  "extra sign",
  "invalid - signed octal",
  "invalid - signed hexadecimal",
  "empty lexeme",
  "empty octal",
  "empty hex"
};

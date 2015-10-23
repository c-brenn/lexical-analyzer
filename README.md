### Lexical Analyzer  

A solution to one of my assignments from a compiler design module in college.  

It reads in some octal, hex or decimal lexemes and prints out their decimal value if they are valid or gives you some reasons why they aren't valid.

## Run it

Compile `main.c`  
You can pass it lexemes like this:  
`./main.out 1234 1234 1234 ...`  

You can see it handle the test inputs from `test_inputs.h` by passing the `--test-inputs` flag:  
`./main.out --test-inputs`


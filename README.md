# Running Lex Files

This README provides instructions on how to compile and run Lex (Flex) files using different methods. Choose the method that works best for your system and preferences.

## Method 1: Using Flex and gcc with -lfl

This method uses Flex to generate the C file and gcc to compile it, linking with the Flex library.

```bash
flex filename.l
gcc lex.yy.c -o lexer -lfl
./lexer
```

## Method 2: Using Lex and gcc with -ll

This method is similar to Method 1 but uses the traditional Lex command and links with the Lex library.

```bash
lex filename.l
gcc lex.yy.c -o lexer -ll
./lexer
```

## Method 3: Using Flex and gcc without specifying the library

This method doesn't explicitly link to the Flex library, which might work on some systems.

```bash
flex filename.l
gcc lex.yy.c
./a.out
```

## Method 4: Using a build script

This method uses a shell script to automate the build process.

1. Create a file named `build.sh` with the following content:

```bash
#!/bin/bash
flex "$1"
gcc lex.yy.c -o lexer -lfl
./lexer
```

2. Make the script executable (you only need to do this once):

```bash
chmod +x build.sh
```

3. Run the script with your Lex file as an argument:

```bash
./build.sh filename.l
```

## Troubleshooting

- If you encounter "undefined reference to `yywrap`" error, you can either:
  1. Add `%option noyywrap` at the top of your Lex file, or
  2. Define `yywrap()` in your Lex file:
     ```c
     int yywrap() { return 1; }
     ```
- If you get "cannot find -lfl" or "cannot find -ll" errors, you may need to install the Flex development libraries. On Ubuntu or Debian, you can do this with:
  ```bash
  sudo apt-get install libfl-dev
  ```

## Note

Make sure you have Flex (or Lex) and gcc installed on your system before attempting to compile Lex files.

For more information on Flex, visit the [official Flex documentation](https://github.com/westes/flex).

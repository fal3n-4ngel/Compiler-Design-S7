# KTU S7 Compiler Design - Lab
2024-25

## Compiling and Running C Programs

### Standard Method
1. Compile the C program:
   ```bash
   gcc filename.c -o program_name
   ```
2. Run the compiled program:
   ```bash
   ./program_name
   ```

### For NixOS Users
1. Enter a nix-shell with gcc:
   ```bash
   nix-shell -p gcc
   ```
2. Compile and run as normal:
   ```bash
   gcc filename.c -o program_name
   ./program_name
   ```

## Running Lex Files

### Method 1: Using Flex and gcc with -lfl
```bash
flex filename.l
gcc lex.yy.c -o lexer -lfl
./lexer
```

### Method 2: Using Lex and gcc with -ll
```bash
lex filename.l
gcc lex.yy.c -o lexer -ll
./lexer
```

### Method 3: Using Flex and gcc without specifying the library
```bash
flex filename.l
gcc lex.yy.c
./a.out
```

### Method 4: Using a build script
1. Create a file named `build.sh` with the following content:
   ```bash
   #!/bin/bash
   flex "$1"
   gcc lex.yy.c -o lexer -lfl
   ./lexer
   ```
2. Make the script executable:
   ```bash
   chmod +x build.sh
   ```
3. Run the script:
   ```bash
   ./build.sh filename.l
   ```

### For NixOS Users
1. Add flex and bison to your configuration file:
   ```nix
   environment.systemPackages = with pkgs; [
     flex
     bison
   ];
   ```
2. Rebuild your system:
   ```bash
   sudo nixos-rebuild switch
   ```
3. Use nix-shell to run the files:
   ```bash
   nix-shell -p flex
   flex lex.l
   gcc lex.yy.c -o lexer -lfl
   ./lexer
   ```

## Troubleshooting
- For "undefined reference to `yywrap`" error:
  1. Add `%option noyywrap` at the top of your Lex file, or
  2. Define `yywrap()` in your Lex file:
     ```c
     int yywrap() { return 1; }
     ```
- For "cannot find -lfl" or "cannot find -ll" errors on Ubuntu or Debian:
  ```bash
  sudo apt-get install libfl-dev
  ```

## Note
Ensure you have Flex (or Lex) and gcc installed on your system before compiling Lex files or C programs.

For more information on Flex, visit the [official Flex documentation](https://github.com/westes/flex).
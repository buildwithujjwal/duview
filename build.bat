@echo off
C:\msys64\msys2_shell.cmd -defterm -here -no-start -ucrt64 -c "gcc -Wall src/main.c src/tree.c src/sort.c src/terminal.c src/ui.c -o duview"
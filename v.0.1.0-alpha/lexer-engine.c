#include <locale.h>
#include <stdio.h>

#include "function-declaration.txt"

int main(int argc, char *argv[])
{
    setlocale(0, "");
    printf(" Количество аргументов: %d", argc);
    for (int i = 0; i < argc; i++) printf("\n Имя аргумента %d: %s", i, argv[i]);
    return 0;
}

void compilation()
{
    // ... //
}
void execution()
{
    // ... //
}
#include <locale.h>
#include <stdio.h>

#include "function-declaration.txt"

#define ln_() putchar('\n')

int main(int argc, char *argv[])
{
    setlocale(0, "");
    printf(" Количество аргументов: %d", argc);
    for (int i = 0; i < argc; i++) printf("\n Имя аргумента %d: %s", i, argv[i]);
    ln_();
    
    FILE *file = fopen(argv[1], "rb");
    if (file != NULL)
    {
        printf(" Не удалось открыть файл <%s> на чтение", argv[1]);
    }
    fclose(file);
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
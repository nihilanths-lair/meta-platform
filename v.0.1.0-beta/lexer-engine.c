#include <locale.h>
#include <stdio.h>

#include "function-declaration.txt"

#define ln_() putchar('\n')

int main(int argc, char *argv[])
{
    setlocale(0, "");
    printf(" Количество аргументов: %d", argc);
    for (int i = 0; i < argc; i++)
    {
        ln_();
        printf(" Имя аргумента %d: %s", i, argv[i]);
    }
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        ln_();
        printf(" Не удалось открыть файл <%s>", argv[1]);
        return 0;
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
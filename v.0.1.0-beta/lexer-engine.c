#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "function-declaration.txt"

#define ln_() putchar('\n')
#define x_ {
#define _x }

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
    // I и II (считывание всего текста целиком в память или сканирование текста прямо в файле)
    switch (1) x_
    case 1: // Загрузка всего текста с файла прямо в память, вся работа идёт только строго в памяти
    {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);
        ln_(); printf(" file_size: %lu", file_size);
        unsigned char *text = (unsigned char *) malloc(file_size);
        size_t text_size = fread(text, sizeof (char), file_size, file);
        ln_(); printf(" text_size: %llu", text_size);
        ln_(); for (int i = 0; i < file_size; i++) putchar(text[i]);
        ln_();
        for (int i = 0, j, t1 = 0, t2 = 0; i < file_size; i++)
        {
            j = i;
            while (i < file_size)
            {
                if (text[i] == '\r' && text[i+1] == '\n') break; // Если среда Windows
                printf(" %2c", text[i]);
                i++;
            }
            putchar('\t');
            while (j < file_size)
            {
                if (text[j] == '\r' && text[j+1] == '\n') // Если среда Windows
                {
                    printf(" %02X", text[j]);
                    j++;
                    printf(" %02X", text[j]);
                    j++;
                    ln_();
                    break;
                }
                printf(" %02X", text[j]);
                j++;
            }
        }
        execution();
    }
    case 2: // Сканирование файла, без полной загрузки в память
    {
        // ... //
    }
    _x
    fclose(file);
    return 0;
}
void compilation()
{
    // ... //
}
void execution()
{
    switch (1) x_ // String-matching
    case 1:
    {
        // ... //
    }
    _x
}
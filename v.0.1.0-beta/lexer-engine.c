#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "function-declaration.txt"

#define ln_(arg) for (int _ln = 0; _ln < arg; _ln++) putchar('\n')
#define sp_(arg) for (int _sp = 0; _sp < arg; _sp++) putchar(' ')

#define x_ {
#define _x }

#define anonymous_scope_(arg) { arg }

int main(int argc, char *argv[])
{
    setlocale(0, "");
    // Передаем весь блок инструкций прямо внутрь макроса
    anonymous_scope_(
        int x = 5;
        int y = 10;
        printf("Сумма: %d\n", x + y);
    )
    // Здесь переменные x и y больше не существуют
    printf(" Количество аргументов: %d", argc);
    for (int i = 0; i < argc; i++)
    {
        ln_(1);
        printf(" Имя аргумента %d: %s", i, argv[i]);
    }
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        ln_(1);
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
        ln_(1);
        printf(" file_size: %lu", file_size);
        unsigned char *text = (unsigned char *) malloc(file_size);
        size_t text_size = fread(text, sizeof (char), file_size, file);
        ln_(1);
        printf(" text_size: %llu", text_size);
        ln_(1);
        anonymous_scope_(
            int string_length = 0;
            int max_string_length = 0;
            for (int current_pos = 0; current_pos < file_size; )
            {
                if (text[current_pos] == '\r' && text[current_pos+1] == '\n') // Если среда Windows
                {
                    current_pos += 2;
                    string_length += 2;
                    if (string_length > max_string_length)
                    {
                        max_string_length = string_length;
                        string_length = 0;
                        printf("\n max_string_length: %u", max_string_length);
                    }
                    continue;
                }
                current_pos++;
                string_length++;
            }
            printf("\n checkpoint: max_string_length: %u", max_string_length);
            ln_(1);
            for (int current_pos = 0, j; current_pos < file_size; )
            {
                j = current_pos;
                while (current_pos < file_size) // Графа исходного кода как есть
                {
                    if (text[current_pos] == '\r' && text[current_pos+1] == '\n') // Если среда Windows
                    {
                        current_pos += 2;
                        //string_length += 2;
                        break;
                    }
                    printf("%c", text[current_pos]);
                    current_pos++;
                    string_length++;
                }
                sp_(max_string_length - string_length - 2 + 8); // Выравнивание между первой и второй графой
                string_length = 0;
                current_pos = j;
                while (current_pos < file_size) // Графа исходного кода в HEX-представлении
                {
                    if (text[current_pos] == '\r' && text[current_pos+1] == '\n') // Если среда Windows
                    {
                        sp_(1);
                        printf("%02X %02X", text[current_pos], text[current_pos+1]); // Напечатали 0D (CR) и 0A (LF)
                        current_pos += 2;
                        ln_(1);
                        break; // Вышли из цикла HEX-строки!
                    }
                    printf(" %02X", text[current_pos]);
                    current_pos++;
                }
                //ln_(1);
            }
        )
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
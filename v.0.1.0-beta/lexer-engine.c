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
    const unsigned char fch[256] =
    {
        // 0x00 - 0x1F (32 управляющих символа, замененные пробелами 0x20)
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',

        // 0x20 - 0x2F (Пробел, !, ", #, $, %, &, ', (, ), *, +, ,, -, ., /)
        ' ', 33, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
        // 0x30 - 0x3F (Цифры 0-9 и знаки :, ;, <, =, >, ?)
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
        // 0x40 - 0x4F (@ и заглавная латиница A-O)
        0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
        // 0x50 - 0x5F (Заглавная латиница P-Z и знаки [, \, ], ^, _, `)
        0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
        // 0x60 - 0x6F (` и строчная латиница a-o)
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
        // 0x70 - 0x7F (Строчная латиница p-z, знаки {, |, }, ~, а 0x7F глушим пробелом)
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x20,

        // 0x80 - 0x9F (32 пробела расширенной CP1251)
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',

        // 0xA0 - 0xAF (Пробелы, на индексе 0xA8 стоит заглавная 'Ё')
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'Ё', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        // 0xB0 - 0xBF (Пробелы, на индексе 0xB8 стоит строчная 'ё')
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'ё', ' ', ' ', ' ', ' ', ' ', ' ', ' ',

        // 0xC0 - 0xDF (Заглавная кириллица А-Я в кодах Windows-1251)
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
        0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,

        // 0xE0 - 0xFF (Строчная кириллица а-я в кодах Windows-1251)
        0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
        0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
    };
    #define fch_(arg) fch[arg]
    /*
    // Передаем весь блок инструкций прямо внутрь макроса
    anonymous_scope_(
        int x = 5;
        int y = 10;
        printf("Сумма: %d\n", x + y);
    )
    // Здесь переменные x и y больше не существуют
    */
    printf(" Количество аргументов: %d", argc);
    for (int i = 0; i < argc; i++)
    {
        ln_(1);
        printf(" Имя аргумента %d: %s", i+1, argv[i]);
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
        printf(" Размер файла (байт): %lu", file_size);
        unsigned char *text = (unsigned char *) malloc(file_size);
        size_t text_size = fread(text, sizeof (char), file_size, file);
        if (file_size == text_size) printf("\n Количество считанных байт: %llu", text_size);
        ln_(1);
        anonymous_scope_(
            // === ШАГ 1: Оптимизированный расчет длины без лишних тактов ===
            int string_length = 0;
            int max_string_length = 0;
            int current_pos;
            for (current_pos = 0; current_pos < file_size; current_pos++)
            {
                if (text[current_pos] == '\r' && text[current_pos+1] == '\n') // Если среда Windows
                {
                    if (string_length > max_string_length)
                    {
                        max_string_length = string_length;
                        printf("\n max_string_length: %u", max_string_length);
                    }
                    string_length = 0; // Сбросили счетчик текущей строки
                    current_pos++;     // Пропустили \n
                    continue;          // Никаких проверок, сразу уходим на следующий шаг
                }
                string_length++;
            }
            // === ИЗОЛИРОВАННЫЙ БЛОК ХВОСТА (Выполняется строго 1 раз за жизнь программы) ===
            // Сюда мы гарантированно приземляемся, когда цикл закрылся сам.
            // Если файл закончился без \r\n, в string_length останется «хвост» последней строки.
            if (string_length > 0) { if (string_length > max_string_length) max_string_length = string_length; }
            printf("\n checkpoint: max_string_length (only print chars): %u\n", max_string_length);
            ln_(1);
            int j;
            // === ШАГ 2: Вывод двух граф с ровным выравниванием ===
            for (current_pos = 0; current_pos < file_size; )
            {
                j = current_pos;
                string_length = 0; // Сбрасываем перед каждой строкой
                // 1. Графа исходного кода
                while (current_pos < file_size)
                {
                    if (text[current_pos] == '\r' && text[current_pos+1] == '\n') // Если среда Windows
                    {
                        current_pos += 2;
                        //string_length += 2;
                        break;
                    }
                    printf("%c", fch_(text[current_pos]));
                    current_pos++;
                    string_length++;
                }
                // НОВАЯ ИСПРАВЛЕННАЯ ФОРМУЛА:
                // Мы просто берем разницу между самой длинной строкой и текущей, 
                // и добавляем фиксированный красивый отступ (например, 8 пробелов)
                sp_(max_string_length - string_length + 8); // Выравнивание между первой и второй графой
                //string_length = 0;
                current_pos = j;
                // 2. Графа HEX-представления
                while (current_pos < file_size)
                {
                    if (text[current_pos] == '\r' && text[current_pos+1] == '\n') // Если среда Windows
                    {
                        //sp_(1);
                        // Выводим перенос строки в HEX
                        printf(" %02X %02X\n", text[current_pos], text[current_pos+1]); // Напечатали 0D (CR) и 0A (LF)
                        current_pos += 2;
                        //ln_(1);
                        break; // Вышли из цикла HEX-строки!
                    }
                    //sp_(1);
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
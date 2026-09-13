#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "function-declaration.txt"

#define ln_(arg) for (int _ln = 0; _ln < arg; _ln++) putchar('\n')
#define sp_(arg) for (int _sp = 0; _sp < arg; _sp++) putchar(' ')

#define x_ {
#define _x }

#define anonymous_scope_(arg) { arg }

#define fch_(arg) fch[arg]

int main(int argc, char *argv[])
{
    setlocale(0, "");
    const unsigned char fch[256] =
    {
        // 0x00 - 0x1F: 32 пустых управляющих символа (заменены пробелами)
        "                                "

        // 0x20 - 0x7F: Пробел, знаки, латиница. Опасные ", \, ' пишем через HEX
        " !\"#$%&'\x27()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\x5C]^_`abcdefghijklmnopqrstuvwxyz{|}~"

        // 0x80 - 0xBF: 64 байта расширенной CP1251 (заменили пробелами, кроме ё/Ё)
        // Чтобы буквы 'ё' и 'Ё' не съехали из-за UTF-8, пишем их строго в CP1251 кодах:
        // \xA8 = 'Ё' (индекс 168), \xB8 = 'ё' (индекс 184)
        "                                " // 0x80 - 0x9F (32 пробела)
        "        \xA8       "               // 0xA0 - 0xAF (0xA8 на своем месте)
        "        \xB8       ",              // 0xB0 - 0xBF (0xB8 на своем месте)

        // 0xC0 - 0xFF: Вся кириллица А-Я и а-я (64 байта)
        // Чтобы она занимала по 1 байту на знак, ваш файл .c ДОЛЖЕН быть сохранен в кодировке CP1251!
        // 0xC0 - 0xDF: Заглавная кириллица А-Я (32 байта в кодах Windows-1251)
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
        0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,

        // 0xE0 - 0xFF: Строчная кириллица а-я (32 байта в кодах Windows-1251)
        0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
        0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
    };
    // Передаем весь блок инструкций прямо внутрь макроса
    anonymous_scope_(
        int x = 5;
        int y = 10;
        printf("Сумма: %d\n", x + y);
    )
    // Здесь переменные x и y больше не существуют
    /*
    for (int i = 0; i < 256; i++) ascii[i] = i;
    ascii['\0'] = ' '; // 0
    for (int i = 1; i <= 6; i++) ascii[i] = ' '; // Глушим нижний диапазон 1-6
    ascii['\a'] = ' '; // 7
    ascii['\b'] = ' '; // 8
    ascii['\t'] = ' '; // 9
    ascii['\n'] = ' '; // 10
    ascii['\v'] = ' '; // 11
    ascii['\f'] = ' '; // 12
    ascii['\r'] = ' '; // 13
    for (int i = 14; i <= 26; i++) ascii[i] = ' '; // Глушим нижний диапазон 14-26
    ascii['\e'] = ' '; // 27
    for (int i = 28; i <= 31; i++) ascii[i] = ' '; // Глушим нижний диапазон 28-31
    for (int i = 0x7F; i <= 159; i++) ascii[i] = ' '; // Глушим 127 и верхний управляющий диапазон C1 (128 - 159)
    for (int i = 161; i <= 167; i++) ascii[i] = ' '; // Глушим символы-призраки
    for (int i = 169; i <= 183; i++) ascii[i] = ' ';
    for (int i = 185; i <= 191; i++) ascii[i] = ' ';
    for (int i = 0; i < 256; i++) printf("%c", ascii[i]);
    ln_(1);
    */
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
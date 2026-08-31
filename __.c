#include <stdio.h>
#include <locale.h>

// Макрос принимает имя переменной (i) и количество повторений (N)
#define loop_(n) for (int _itr = 0; _itr < n; _itr++)

char ascii[256];

char cache[0x100];

int main()
{
    setlocale(0, "");
    loop_(256) ascii[_itr] = _itr;
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
    loop_(256) printf("\n №%-3d | %02X | %03d | %c", _itr+1, _itr, _itr, ascii[_itr]);
    char opcode[256] =
    {
        [0] = ' '
    };
    unsigned char vect = 0;
    // Программная эмуляция процессора
    exec: switch (opcode[vect]){
    case '+': printf("\n %02X = %c", '+', '+'); goto exec;
    case ',': printf("\n %02X = %c", ',', ','); goto exec;
    case '-': printf("\n %02X = %c", '-', '-'); goto exec;
    case '.': printf("\n %02X = %c", '.', '.'); goto exec;
    // extented {
    case ':': printf("\n %02X = %c", ':', ':'); goto exec;
    case ';': printf("\n %02X = %c", ';', ';'); goto exec;
    // }
    case '<': printf("\n %02X = %c", '<', '<'); goto exec;
    case '>': printf("\n %02X = %c", '>', '>'); goto exec;

    case '[': printf("\n %02X = %c", '[', '['); goto exec;
    case ']': printf("\n %02X = %c", ']', ']'); goto exec;
    // service {
    // }
    default: printf("\n ?");
    }
    putchar('\n');
    return 0;
}
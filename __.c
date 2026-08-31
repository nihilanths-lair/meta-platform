#include <stdio.h>
#include <locale.h>

// Макрос принимает имя переменной (i) и количество повторений (N)
#define loop_(n) for (int _itr = 0; _itr < n; _itr++)

char ascii[256];

int main()
{
    setlocale(0, "");
    loop_(256) ascii[_itr] = _itr;
    ascii['\0'] = ' '; // 0
    ascii[0x01] = ' '; // 1
    ascii[0x02] = ' '; // 2
    ascii[0x03] = ' '; // 3
    ascii[0x04] = ' '; // 4
    ascii[0x05] = ' '; // 5
    ascii[0x06] = ' '; // 6
    ascii['\a'] = ' '; // 7
    ascii['\b'] = ' '; // 8
    ascii['\t'] = ' '; // 9
    ascii['\n'] = ' '; // 10
    ascii['\v'] = ' '; // 11
    ascii['\f'] = ' '; // 12
    ascii['\r'] = ' '; // 13
    ascii[0x0E] = ' '; // 14
    ascii[0x0F] = ' '; // 15
    ascii[0x10] = ' '; // 16
    ascii[0x11] = ' '; // 17
    ascii[0x12] = ' '; // 18
    ascii[0x13] = ' '; // 19
    ascii[0x14] = ' '; // 20
    ascii[0x15] = ' '; // 21
    ascii[0x16] = ' '; // 22
    ascii[0x17] = ' '; // 23
    ascii[0x18] = ' '; // 24
    ascii[0x19] = ' '; // 25
    ascii[0x1A] = ' '; // 26
    ascii['\e'] = ' '; // 27
    ascii[0x1C] = ' '; // 28
    ascii[0x1D] = ' '; // 29
    ascii[0x1E] = ' '; // 30
    ascii[0x1F] = ' '; // 31
    //for (int i = 0; i <= 31; i++) ascii[i] = ' '; // Глушим нижний диапазон 0-31 и 127
    ascii[0x7F] = ' '; // 127
    for (int i = 128; i <= 159; i++) ascii[i] = ' '; // Глушим верхний управляющий диапазон C1 (128 - 159)
    loop_(256)
    {
        printf("\n №%-3d | %02X | %03d | %c", _itr+1, _itr, _itr, ascii[_itr]);
    }
    putchar('\n');
    return 0;
}
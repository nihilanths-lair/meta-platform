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
    unsigned char cache[0x100] =
    {
        [0] = 0x06, // Код (операция)
        [1] = 0xA0, // Код (адрес ячейки памяти)
        [2] = 255,  // Данные

        [3] = 0x02, // Код (операция)
        [4] = 0x40  // Код (адрес ячейки памяти)
    };
    unsigned char ip = 0;
    // Программная эмуляция абстрактного процессора
    printf("\n Эмуляция начата.");
    printf("\n Отладчик памяти.\n");
    int itr = 0;
    printf("\n Итерация: %d.", itr);
    printf("\n Код операции: 0x%02X.", cache[ip]);
    int prev_ops = cache[ip];
    printf("\n ·----------·------------------------------------------·");
    printf("\n | Registry |                                          |");
    printf("\n ·----------·                                          |");
    printf("\n |                                                     |");
    printf("\n | IP (указатель команд): 0x%02X.                        |", ip);
    printf("\n ·-----------------------------------------------------·");
    int prev_ip = ip;
    printf("\n ·--------·------------------------------------------------·------------------·");
    printf("\n | Memory |                                                |                  |");
    printf("\n ·--------·                                                |                  |");
    printf("\n |                                                         |                  |");
    printf("\n |        ");
    goto exec_2;
    exec:
    printf("\n Итерация: %d.", ++itr);
    printf("\n Код операции: 0x%02X -> 0x%02X.", prev_ops, cache[ip]);
    prev_ops = cache[ip];
    printf("\n ·----------·------------------------------------------·");
    printf("\n | Registry |                                          |");
    printf("\n ·----------·                                          |");
    printf("\n |                                                     |");
    printf("\n | IP (указатель команд): 0x%02X -> 0x%02X.                |", prev_ip, ip);
    printf("\n ·-----------------------------------------------------·");
    prev_ip = ip;
    //printf("\n [%02X] = %02X", );
    printf("\n ·--------·------------------------------------------------·------------------·");
    printf("\n | Memory |                                                |                  |");
    printf("\n ·--------·                                                |                  |");
    printf("\n |                                                         |                  |");
    printf("\n |        ");
    exec_2:
    // Шапка (заголовок)
    for (int i = 0; i < 16; i++) printf(" %02X", i);
    printf(" | ");
    for (int i = 0; i < 16; i++) printf("%01X", i);
    printf(" |");
    printf("\n |                                                         |                  |");
    // Тело
    for (int i = 0, l; i < 16; i++)
    {
        l = i*16;
        printf("\n | %02X=%03d:", l, l); // Смещение
        for (int j = 0; j < 16; j++) printf(" %02X", cache[l+j]);
        printf(" | ");
        for (int j = 0; j < 16; j++) printf("%c", ascii[cache[l+j]]);
        printf(" |");
    }
    printf("\n ·---------------------------------------------------------·------------------·\n");
    switch (cache[ip]){
    case ',': printf("\n %02X = %c", ',', ','); goto exec;
    case '.': printf("\n %02X = %c", '.', '.'); goto exec;
    // extented {
    case ':': printf("\n %02X = %c", ':', ':'); goto exec;
    case ';': printf("\n %02X = %c", ';', ';'); goto exec;
    // }

    // Арифметико-логические операции (ALU)
    case '-': printf("\n []--"); cache[ip]--; ip++; goto exec; // декремент текущей ячейки памяти (однобайтовая операция)
    case '+': printf("\n []++"); cache[ip]++; ip++; goto exec; // инкремент текущей ячейки памяти (однобайтовая операция)
    case 0x01: cache[cache[ip+1]]--; ip+=2; goto exec; // декремент произвольной ячейки памяти (двухбайтовая операция)
    case 0x02: cache[cache[ip+1]]++; ip+=2; goto exec; // инкремент произвольной ячейки памяти (двухбайтовая операция)
    case '=': printf("\n [] = ?"); cache[ip]=cache[ip+1]; ip+=2; goto exec; // записать в текущую ячейку памяти (двухбайтовая операция)
    case 0x04: printf("\n [] += ?"); cache[ip]+=cache[ip+1]; ip+=2; goto exec; // добавить к текущей ячейки памяти (двухбайтовая операция)
    case 0x05: printf("\n [] -= ?"); cache[ip]-=cache[ip+1]; ip+=2; goto exec; // убавить из текущей ячейки памяти (двухбайтовая операция)
    case 0x06: cache[cache[ip+1]]=cache[ip+2]; ip+=3; goto exec; // записать в произвольную ячейку памяти (трёхбайтовая операция)
    case 0x07: cache[cache[ip+1]]+=cache[ip+2]; ip+=3; goto exec; // добавить к произвольной ячейки памяти (трёхбайтовая операция)
    case 0x08: cache[cache[ip+1]]-=cache[ip+2]; ip+=3; goto exec; // убавить из произвольной ячейки памяти (трёхбайтовая операция)
    
    // Управление потоком (безусловные переходы)
    case '<': printf("\n %02X = %c", '<', '<'); ip--; goto exec; // перейти к предыдущей ячейки памяти (однобайтовая операция)
    case '>': printf("\n %02X = %c", '>', '>'); ip++; goto exec; // перейти к следующей ячейки памяти (однобайтовая операция)
    case '_': printf("\n %02X = %c", '_', '_'); ip=cache[ip+1]; goto exec; // перейти к произвольной ячейки памяти (двухбайтовая операция)
    case '\\': printf("\n %02X = %c", '\\', '\\'); ip-=cache[ip+1]; goto exec; // перейти к произвольной ячейки памяти с вектором направления назад (двухбайтовая операция)
    case '/': printf("\n %02X = %c", '/', '/'); ip+=cache[ip+1]; goto exec; // перейти к произвольной ячейки памяти с вектором направления вперёд (двухбайтовая операция)

    // service {
    // }
    default: printf("\n Неизвестный опкод.");
    }
    printf("\n Эмуляция окончена.\n");
    return 0;
}
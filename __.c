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
        //[3] = 0     // Код (операция)
    };
    unsigned char frame = 0;
    // Программная эмуляция абстрактного процессора
    printf("\n Эмуляция начата.");
    printf("\n Отладчик памяти.\n");
    int itr = 0;
    printf("\n Итерация: %d.", itr);
    printf("\n Код операции: 0x%02X.", cache[frame]);
    char prev_ops = cache[frame];
    goto exec_2;
    exec:
    //static char checkpoint[256];
    //checkpoint[5] = 3;
    //Ыprintf("\n checkpoint[%d]: %d", 5, checkpoint[5]);
    printf("\n Итерация: %d.", ++itr);
    printf("\n Код операции: 0x%02X -> 0x%02X.", prev_ops, cache[frame]);
    prev_ops = cache[frame];
    exec_2:
    printf("\n ·-----------------------------------------------------·");
    printf("\n | frame: %02X                                           |", frame);
    printf("\n ·-----------------------------------------------------·\n |    ");
    for (int i = 0; i < 16; i++) printf(" %02X", i);
    printf(" |\n |                                                     |");
    for (int i = 0; i < 16; i++)
    {
        printf("\n | %02X:", i*16);
        for (int j = 0; j < 16; j++) printf(" %02X", cache[i*16+j]);
        printf(" |");
    }
    printf("\n ·-----------------------------------------------------·\n");
    switch (cache[frame]){
    case ',': printf("\n %02X = %c", ',', ','); goto exec;
    case '.': printf("\n %02X = %c", '.', '.'); goto exec;
    // extented {
    case ':': printf("\n %02X = %c", ':', ':'); goto exec;
    case ';': printf("\n %02X = %c", ';', ';'); goto exec;
    // }

    // Арифметико-логические операции (ALU)
    case '-': printf("\n []--"); cache[frame]--; frame++; goto exec; // декремент текущей ячейки памяти (однобайтовая операция)
    case '+': printf("\n []++"); cache[frame]++; frame++; goto exec; // инкремент текущей ячейки памяти (однобайтовая операция)
    case '=': printf("\n [] = ?"); cache[frame]=cache[frame+1]; frame+=2; goto exec; // записать в текущую ячейку памяти (двухбайтовая операция)
    case 0x04: printf("\n [] += ?"); cache[frame]+=cache[frame+1]; frame+=2; goto exec; // добавить к текущей ячейки памяти (двухбайтовая операция)
    case 0x05: printf("\n [] -= ?"); cache[frame]-=cache[frame+1]; frame+=2; goto exec; // убавить из текущей ячейки памяти (двухбайтовая операция)
    case 0x06: cache[cache[frame+1]]=cache[frame+2]; frame+=3; goto exec; // записать в произвольную ячейку памяти (трёхбайтовая операция)
    case 0x07: cache[cache[frame+1]]+=cache[frame+2]; frame+=3; goto exec; // добавить к произвольной ячейки памяти (трёхбайтовая операция)
    case 0x08: cache[cache[frame+1]]-=cache[frame+2]; frame+=3; goto exec; // убавить из произвольной ячейки памяти (трёхбайтовая операция)
    
    // Управление потоком (безусловные переходы)
    case '<': printf("\n %02X = %c", '<', '<'); frame--; goto exec; // перейти к предыдущей ячейки памяти (однобайтовая операция)
    case '>': printf("\n %02X = %c", '>', '>'); frame++; goto exec; // перейти к следующей ячейки памяти (однобайтовая операция)
    case '_': printf("\n %02X = %c", '_', '_'); frame=cache[frame+1]; goto exec; // перейти к произвольной ячейки памяти (двухбайтовая операция)
    case '\\': printf("\n %02X = %c", '\\', '\\'); frame-=cache[frame+1]; goto exec; // перейти к произвольной ячейки памяти с вектором направления назад (двухбайтовая операция)
    case '/': printf("\n %02X = %c", '/', '/'); frame+=cache[frame+1]; goto exec; // перейти к произвольной ячейки памяти с вектором направления вперёд (двухбайтовая операция)

    // service {
    // }
    default: printf("\n Неизвестный опкод.");
    }
    printf("\n Эмуляция окончена.\n");
    return 0;
}
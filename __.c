#include <stdio.h>
#include <locale.h>

// Макрос принимает имя переменной (i) и количество повторений (N)
#define loop_(n) for (int _itr = 0; _itr < n; _itr++)

char ascii[256];

int main(int argc, char * argv[])
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
    //FILE * file = fopen("stream.dump", "wb");
    //loop_(256) fprintf(stdout, "\n №%-3d | %02X | %03d | %c", _itr+1, _itr, _itr, ascii[_itr]);
    unsigned char cache[0x300] = {0};
    register unsigned short ip = 512; // зона (секция) кода R/W/E (чтение/запись/исполнение)
    register unsigned short dp = 256; // зона (секция) данных R/W (чтение/запись)
    printf(" Принято кол-во аргументов: %d", argc);
    for (int i = 0; i < argc; i++) printf("\n Аргумент №%d: %s", i+1, argv[i]);
    FILE * file = fopen(argv[1], "rb");
    if (file == NULL) { printf("\n Ошибка открытия файла программы на чтение"); return 0; }
    char ch;
    for (int i = ip; ((ch = fgetc(file)) != EOF); i++) { cache[i] = ch; }
    fclose(file);
    // Программная эмуляция абстрактного процессора
    printf("\n Эмуляция начата.");
    printf("\n Отладчик памяти.\n");
    int itr = 0;
    printf("\n Итерация: %d.", itr);
    printf("\n Код операции: 0x%02X.", cache[ip]);
    int prev_ops = cache[ip];
    printf("\n ·----------·");
    printf("\n | Registry |");
    printf("\n |          ·--------------------·");
    printf("\n | IP (указатель команд): 0x%04X |", ip);
    printf("\n | DP (указатель данных): 0x%04X |", dp);
    printf("\n ·-------------------------------·");
    int prev_ip = ip;
    int prev_dp = dp;
    printf("\n ·-------·");
    printf("\n | Memory \\");
    printf("\n |         ·-------------------------------------------------·------------------·");
    printf("\n |         |");
    goto exec_2;
    exec:
    printf("\n Итерация: %d.", ++itr);
    printf("\n Код операции: 0x%02X -> 0x%02X.", prev_ops, cache[ip]);
    prev_ops = cache[ip];
    printf("\n ·----------·");
    printf("\n | Registry |");
    printf("\n |          ·------------------------------·");
    printf("\n | IP (указатель команд): 0x%04X -> 0x%04X |", prev_ip, ip);
    printf("\n | DP (указатель данных): 0x%04X -> 0x%04X |", prev_dp, dp);
    printf("\n ·-----------------------------------------·");
    prev_ip = ip;
    prev_dp = dp;
    //printf("\n [%02X] = %02X", );
    printf("\n ·-------·");
    printf("\n | Memory \\");
    printf("\n |         ·-------------------------------------------------·------------------·");
    printf("\n |         |");
    exec_2:
    // Шапка (заголовок)
    for (int i = 0; i < 16; i++) printf(" %02X", i);
    printf(" | ");
    for (int i = 0; i < 16; i++) printf("%01X", i);
    printf(" |");
    printf("\n |                                                           |                  |");
    for (int i = 0, l; i < 16; i++) // Секция 1
    {
        l = i*16;
        printf("\n | %03d(%02Xh):", l, l); // Смещение
        for (int j = 0; j < 16; j++) printf(" %02X", cache[l+j]);
        printf(" | ");
        for (int j = 0; j < 16; j++) printf("%c", ascii[cache[l+j]]);
        printf(" |");
    }
    //printf("\n ·---------------------------------------------------------·------------------·\n");
    printf("\n |                                                           ·-·                ·-·");
    for (int i = 16, l; i < 32; i++) // Секция 2
    {
        l = i*16;
        printf("\n | %03ld(%04Xh):", l, l); // Смещение
        for (int j = 0; j < 16; j++) printf(" %02X", cache[l+j]);
        printf(" | ");
        for (int j = 0; j < 16; j++) printf("%c", ascii[cache[l+j]]);
        printf(" |");
    }
    //printf("\n ·-------------------------------------------------------------·------------------·\n");
    printf("\n |                                                             |                  |");
    for (int i = 32, l; i < 48; i++) // Секция 3
    {
        l = i*16;
        printf("\n | %03ld(%04Xh):", l, l); // Смещение
        for (int j = 0; j < 16; j++) printf(" %02X", cache[l+j]);
        printf(" | ");
        for (int j = 0; j < 16; j++) printf("%c", ascii[cache[l+j]]);
        printf(" |");
    }
    printf("\n ·-------------------------------------------------------------·------------------·\n");
    ///
    // Instruction Execution Flow Control (IEFC) / Управление Потоком Выполнения Инструкций (УПВИ)
    ///
    auto_vector_direction_ip__forward: switch (cache[ip]){ // auto-ip: right
    
//Ex={ 1 | Перенаправление потока выполнения кода в другую сторону
    case 'x': goto auto_vector_direction_ip__back; // авто-вектор направления IP: назад
    //case '(': ip++; goto auto_vector_direction_ip__forward; // авто-вектор направления IP: вперед
    //case ')':       goto auto_vector_direction_ip__back;    // авто-вектор направления IP: назад

    // 1 | Вектор направления над потоком выполнения кода (перешагиваем сам опкод, перед остановкой линии движения конвейера)
    //case '!': ip++; goto stop_conveyor; case '@': ip++; goto start_conveyor; // $^вторым аргументом можно указать вектор направления^$

    // 1 | Смещение каретки данных (назад/вперёд)
    case '<': dp--; ip++; goto exec;
    case '>': dp++; ip++; goto exec;

//Ex={ 2 | Смещение каретки данных (относительное)
    case '}': dp += cache[ip+1]; ip+=2; goto exec; // В сторону конца
    case '{': dp -= cache[ip+1]; ip+=2; goto exec; // В сторону начала
    // 2 | Смещение каретки данных (абсолютное)
    case '~': dp  = cache[ip+1]; ip+=2; goto exec; // В любую сторону

    // 2 | Изменение потока выполнения кода (относительное)
    case '/':  ip += cache[ip+1]; goto exec; // В сторону конца
    case '\\': ip -= cache[ip+1]; goto exec; // В сторону начала
    // 2 | Изменение потока выполнения кода (абсолютное)
    case 'j':  ip  = cache[ip+1]; goto exec; // В любую сторону
//};

    // 1 | Арифметика над данными (инкремент/декремент)
    case '+': cache[dp]++; ip++; goto exec;
    case '-': cache[dp]--; ip++; goto exec;
    
//Ex={ 2 | Арифметика над данными (сложение/вычитание)
    case 'a': cache[dp] += cache[ip+1]; ip+=2; goto exec;
    case 's': cache[dp] -= cache[ip+1]; ip+=2; goto exec;
    case 'm': cache[dp] *= cache[ip+1]; ip+=2; goto exec;
    case 'd': cache[dp] /= cache[ip+1]; ip+=2; goto exec;
    // 2 | Пересылка данных
    case '=': cache[dp]  = cache[ip+1]; ip+=2; goto exec;
//};

    default: printf("\n Неизвестный опкод."); goto proc_exit;
    }

    auto_vector_direction_ip__back: switch (cache[ip]){ // auto-ip: left

//Ex={ 1 | Перенаправление потока выполнения кода в другую сторону
    case 'x': goto auto_vector_direction_ip__forward; // авто-вектор направления IP: вперёд
    //case '(':       goto auto_vector_direction_ip__forward; // авто-вектор направления IP: вперед
    //case ')': ip--; goto auto_vector_direction_ip__back;    // авто-вектор направления IP: назад

    // 1 | Вектор направления над потоком выполнения кода (перешагиваем сам опкод, перед остановкой линии движения конвейера)
    //case '!': ip--; goto stop_conveyor; //case '@': ip--; goto start_conveyor; // $^вторым аргументом можно указать вектор направления^$
//};

    // 1 | Смещение каретки данных (назад/вперёд)
    case '<': dp--; ip--; goto exec;
    case '>': dp++; ip--; goto exec;

    // 1 | Арифметика над данными (инкремент/декремент)
    case '+': cache[dp]++; ip--; goto exec;
    case '-': cache[dp]--; ip--; goto exec;

    default: printf("\n Неизвестный опкод."); goto proc_exit;
    }

    // Заглушки
    stop_conveyor: printf("\n Заглушка №1."); goto proc_exit;
    start_conveyor: printf("\n Заглушка №2."); goto proc_exit;

    forward_direction_vector_in_manual_mode: printf("\n Заглушка №3."); goto proc_exit;
    backward_direction_vector_in_manual_mode: printf("\n Заглушка №4.");

    proc_exit:
    printf("\n Эмуляция окончена.\n");
    return 0;
}

/*
    // Ручное (в этом режиме программист самостоятельно управляет потоком выполнения инструкций)
    // Автоматическое (в этом режиме процессор управляет потоком выполнения инструкций: сверху-вниз) - по умолчанию
    // Автоматическое (в этом режиме процессор управляет потоком выполнения инструкций: снизу-вверх)
    // Опкоды линии конвеера: 0x?? - отключить/остановить линию конвеера (ручное управление), 0x?? - включить/запустить линию конвеера (автоматическое управление)
    //case 0x80: goto // Управление указателем команд: ручное / автоматическое (назад / вперёд) ?
    // [Extented:
    // 1 | Вектор направления над потоком выполнения кода (реализация временно заморожена)
    case 4: ip--;                        goto exec; // Перенаправить поток кода на шаг назад (использовать в режиме ручного управления, в целях избежания багов)
    case 5: ip++;                        goto exec; // Перенаправить поток кода на шаг вперёд (использовать в режиме ручного управления, в целях избежания багов)

    case '+': cache[ip]++;                       ip++;  goto exec; // инкремент текущей ячейки памяти
    case '-': cache[ip]--;                       ip++;  goto exec; // декремент текущей ячейки памяти

    case '=': cache[ip] = cache[ip+1];           ip+=2; goto exec; // записать в текущую ячейку памяти
    case 128: cache[ip] += cache[ip+1];          ip+=2; goto exec; // добавить к текущей ячейки памяти
    case 129: cache[ip] -= cache[ip+1];          ip+=2; goto exec; // убавить из текущей ячейки памяти

    case 130: cache[cache[ip+1]]  = cache[ip+2]; ip+=3; goto exec; // записать в произвольную ячейку памяти
    case 131: cache[cache[ip+1]] += cache[ip+2]; ip+=3; goto exec; // добавить к произвольной ячейки памяти
    case 132: cache[cache[ip+1]] -= cache[ip+2]; ip+=3; goto exec; // убавить из произвольной ячейки памяти

    case '<': dp--;                                      goto exec; // перейти к предыдущей ячейки памяти
    case '>': dp++;                                      goto exec; // перейти к следующей ячейки памяти

    case 133: ip += cache[ip+1];                        goto exec; // перейти к произвольной ячейки памяти с вектором направления вперёд
    case 134: ip -= cache[ip+1];                        goto exec; // перейти к произвольной ячейки памяти с вектором направления назад
    case 135: ip = cache[ip+1];                         goto exec; // перейти к произвольной ячейки памяти
*/
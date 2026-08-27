### 🗺️ Карта навигации: Общая структура (Иерархия)
<pre>
Обозначения:
🔒 ─ Закрытый исходный код
🔴 ─ Красная зона, зона системной разработки ПО (System [Development Tools / Software Development] Environment)
🟡 ─ Жёлтая зона, зона прикладной разработки ПО (Application [Development Tools / Software Development] Environment)
🟢 ─ Зелёная зона, зона конечного пользователя (User-end)

meta-platform/
├── meta/
│   ├── re/ 🟢
│   │   ├── re.c 🔒
│   │   └── re.exe (cli)    <-- [🇺🇸] Meta Runtime Environment / [🇷🇺] Мета Среда Выполнения
│   ├── adte/ 🟡
│   │   ├── adte.c 🔒
│   │   └── adte.exe (cli)  <-- [🇺🇸] Meta Application Development Tools Environment / [🇷🇺] Мета Среда Инструментов Прикладной Разработки
│   └── sdte/ 🔴
│       ├── sdte.c 🔒
│       └── sdte.exe (cli)
├── mde.c 🔒                <-- Закрытый исходный код оркестратора
└── mde.exe (cli)           <-- Сердце системы (Managed Development Environment)
</pre>
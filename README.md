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
│   │   ├── re.c 🔒         <-- Закрытый исходный код плеера
│   │   └── re.exe (cli)    <-- [🇺🇸] Meta Runtime Environment / [🇷🇺] Мета Среда Выполнения
│   ├── adte/ 🟡
│   │   ├── adte.c 🔒       <-- Закрытый исходный код прикладного SDK
│   │   └── adte.exe (cli)  <-- 
│   └── sdte/ 🔴
│       ├── sdte.c 🔒       <-- Закрытый исходный код системного SDK
│       └── sdte.exe (cli)
├── mde.c 🔒                <-- Закрытый исходный код оркестратора
└── mde.exe (cli)           <-- Сердце системы (Managed Development Environment)
</pre>
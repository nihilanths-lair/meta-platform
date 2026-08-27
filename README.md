### 🗺️ Карта навигации: Общая структура (Иерархия)
<pre>
Обозначения:
🔒 ─ Закрытый исходный код
🟩 ─ Зелёная зона, зона конечного пользователя (User-end)
🟨 ─ Жёлтая зона, зона прикладной разработки ПО (Application Development Tools Environment)
🟥 ─ Красная зона, зона системной разработки ПО (System Development Tools Environment)

meta-platform/
├── meta/
│   ├── re/ 🟩
│   │   ├── re.c 🔒         <-- Закрытый исходный код плеера
│   │   └── re.exe (cli)    <-- Плеер-коммутатор
│   ├── adte/ 🟨
│   │   ├── adte.c 🔒       <-- Закрытый исходный код прикладного SDK
│   │   └── adte.exe (cli)
│   └── sdte/ 🟥
│       ├── sdte.c 🔒       <-- Закрытый исходный код системного SDK
│       └── sdte.exe (cli)
├── mde.c 🔒                <-- Закрытый исходный код оркестратора
└── mde.exe (cli)           <-- Сердце системы (Managed Development Environment)
</pre>
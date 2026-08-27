### 🗺️ Карта навигации: Общая структура (Иерархия)
<pre>
Обозначения:
🔒 ─ Закрытый исходный код
⚫ ─ Чёрная зона
🔴 ─ Красная зона, зона системной разработки ПО (System [Development Tools / Software Development] Environment)
🟡 ─ Жёлтая зона, зона прикладной разработки ПО (Application [Development Tools / Software Development] Environment)
🟢 ─ Зелёная зона, зона конечного пользователя (User-end)
📟 ─ Интерфейс командной строки (ИКС) / Command Line Interface (CLI)

meta-platform/
├── meta/
│   ├── re/ 🟢
│   │   ├── re.c 🔒
│   │   └── re.exe 📟    <-- [🇺🇸] Meta Runtime Environment / [🇷🇺] Мета Среда Выполнения
│   ├── adte/ 🟡
│   │   ├── adte.c 🔒
│   │   └── adte.exe 📟  <-- [🇺🇸] Meta Application Development Tools Environment / [🇷🇺] Мета Среда Инструментов Прикладной Разработки
│   └── sdte/ 🔴
│       ├── sdte.c 🔒
│       └── sdte.exe 📟  <-- [🇺🇸] Meta System Development Tools Environment / [🇷🇺] Мета Среда Инструментов Системной Разработки
├── mde.c 🔒
└── mde.exe 📟           <-- Оркестратор ─ сердце системы (Managed Development Environment)
</pre>
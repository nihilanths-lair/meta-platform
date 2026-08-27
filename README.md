### 🗺️ Карта навигации: Общая структура (Иерархия)
<pre>
Обозначения:
🔐 ─ Закрытый исходный код
⚫ ─ Чёрная зона, зона системной разработки ядра (Meta Bare-Metal Environment)
🔴 ─ Красная зона, зона системной разработки ПО (System DT/SD Environment)
🟡 ─ Жёлтая зона, зона прикладной разработки ПО (Application DT/SD Environment)
🟢 ─ Зелёная зона, зона конечного пользователя (User-end)
<!--📟/-->⌨️ ─ Command Line Interface (CLI) / Интерфейс командной строки (ИКС)
<!--🖼️/🎨/-->🖱️ ─ Graphical User Interface (GUI) / Графический интерфейс пользователя (ГИП)

meta-platform/
├── meta/
│   ├── re/ 🟢
│   │   ├── re.c 🔐
│   │   └── re.exe ⌨️    <-- [🇺🇸] Meta Runtime Environment / [🇷🇺] Мета Среда Выполнения
│   ├── adte/ 🟡
│   │   ├── adte.c 🔐
│   │   └── adte.exe ⌨️  <-- [🇺🇸] Meta Application Development Tools Environment / [🇷🇺] Мета Среда Инструментов Прикладной Разработки
│   └── sdte/ 🔴
│       ├── sdte.c 🔐
│       └── sdte.exe ⌨️  <-- [🇺🇸] Meta System Development Tools Environment / [🇷🇺] Мета Среда Инструментов Системной Разработки
├── mde.c 🔐
└── mde.exe ⌨️           <-- Оркестратор ─ сердце системы (Managed Development Environment)
</pre>
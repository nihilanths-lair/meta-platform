### 🗺️ Карта навигации: Общая структура (Иерархия)

<pre>
meta-platform/
├── meta/
│   ├── dte/ <-- Модули управления компонентами M^DTE (^A/S)
│   │   ├── app/ 🟡
│   │   │   ├── ui/
│   │   │   ├── adte.c 🔐
│   │   │   ├── adte.exe ⌨️
│   │   │   <s>└── adte-gui.exe 🖱️</s>
│   │   ├── sys/ 🔴
│   │   │   ├── ui/
│   │   │   │   ├── cli/
│   │   │   │   └── gui/
│   │   │   ├── sdte.c 🔐
│   │   │   ├── sdte.exe ⌨️
│   │   │   <s>└── sdte-gui.exe 🖱️</s>
│   │   ├── ui/
│   │   │   ├── cli/
│   │   │   │   ├── <s>dte.c 🔐</s>
│   │   │   │   └── <s>dte.exe ⌨️</s>
│   │   │   └── gui/
│   │   │       ├── <s>dte.c 🔐</s>
│   │   │       └── <s>dte.exe 🖱️</s>
│   │   ├── <s>dte-cli.c 🔐</s>
│   │   ├── <s>dte-cli.exe ⌨️</s>
│   │   ├── <s>dte-gui.c 🔐</s>
│   │   ├── <s>dte-gui.exe 🖱️</s>
│   └── re/ 🟢
│       ├── re.c 🔐
│       └── re.exe ⌨️
├── mde.c 🔐
└── mde.exe ⌨️ <-- Оркестратор ─ диспетчер задач мета-платформы (Managed Development Environment)
</pre>

#### Обозначения:

<pre>
🔐: Закрытый исходный код
<s>⚫: [🇺🇸] ─ / [🇷🇺] ─</s>
🔴: [🇺🇸] Meta System Development Tools Environment / [🇷🇺] Мета Среда Инструментов Системной Разработки
🟡: [🇺🇸] Meta Application Development Tools Environment / [🇷🇺] Мета Среда Инструментов Прикладной Разработки
🟢: [🇺🇸] Meta Runtime Environment (MRE) / [🇷🇺] Мета Среда Выполнения (МСВ)
<!--📟/-->⌨️: [🇺🇸] Command Line Interface (CLI) / [🇷🇺] Интерфейс командной строки (ИКС)
<!--🖼️/🎨/-->🖱️: [🇺🇸] Graphical User Interface (GUI) / [🇷🇺] Графический интерфейс пользователя (ГИП)
<!--
meta-platform/
├── meta/
│   ├── re/ 🟢
│   │   ├── re.c 🔐
│   │   └── re.exe ⌨️    <-- [🇺🇸] Meta Runtime Environment / [🇷🇺] Мета Среда Выполнения
│   ├── adte/ 🟡
│   │   ├── adte.c 🔐
│   │   ├── adte.exe ⌨️  <-- [🇺🇸] Meta Application Development Tools Environment / [🇷🇺] Мета Среда Инструментов Прикладной Разработки
│   │   <s>└── adte-gui.exe 🖱️</s>
│   └── sdte/ 🔴
│       ├── sdte.c 🔐
│       ├── sdte.exe ⌨️  <-- [🇺🇸] Meta System Development Tools Environment / [🇷🇺] Мета Среда Инструментов Системной Разработки
│       <s>└── sdte-gui.exe 🖱️</s>
├── mde.c 🔐
└── mde.exe ⌨️           <-- Оркестратор ─ сердце системы (Managed Development Environment)
-->
</pre>
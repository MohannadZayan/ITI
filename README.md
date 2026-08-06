# My ITI Journey

This repo is where I've been keeping everything from my time at ITI (Information Technology Institute) — every quiz, task, and project from the **C++**, **Admin Linux**, and **Qt/QML** tracks. It's less a polished portfolio and more a running log of how I got from "what's a pointer" to building a translated, multi-page desktop app with a live UI. I put this README together to actually look back at what I've learned instead of letting it all sit scattered across folders.

---

## Table of Contents

- [C++](#c)
  - [The basics: pointers, vectors, strings](#the-basics-pointers-vectors-strings)
  - [Object-Oriented Programming](#object-oriented-programming)
  - [Bigger tasks](#bigger-tasks)
  - [Graduation Project: Bank Management System](#graduation-project-bank-management-system)
- [Admin Linux](#admin-linux)
- [Qt / QML](#qt--qml)
  - [Calculator](#calculator)
  - [Task 2: Car Catalog](#task-2-car-catalog)
  - [Smart Home](#smart-home)
- [How this repo is organized](#how-this-repo-is-organized)

---

## C++

The C++ track is where most of the repetition (in a good way) happened — a lot of the same core ideas practiced over and over from slightly different angles: quizzes to check I understood something right after learning it, then tasks to actually build with it.

### The basics: pointers, vectors, strings

Early on this was about getting comfortable with the language itself:

- **Pointers** (`C++/Tasks/Tasks_Pointers/`) — passing values by pointer into functions like `increment`, `decrement`, and `reset`, and building a small menu-driven program around them.
- **Vectors & STL** (`C++/Quizzes/quiz_stl.cpp`, `Quiz_Vectors.cpp`, `Task_Vectors/`) — merging two sorted vectors manually, removing negative numbers with `erase_if`, finding max/min with `min_element`/`max_element`, counting frequencies, and general in-place vector manipulation (reversing, finding the second-largest element).
- **Strings** (`quiz_string.cpp`, `quiz_day10.cpp`, `quiz_day13.cpp`) — reversing strings and sentences in place, counting vowels, finding non-repeating characters with a counting array, and counting words in a sentence.
- **Daily quizzes** (`quiz_day10.cpp` → `quiz_day13.cpp`) form a nice little timeline — each one a fresh problem (missing number in a sequence, palindrome check on a vector, word counting) solved from scratch under quiz conditions.

### Object-Oriented Programming

This is where the C++ track really opens up, and it's clearly the part I spent the most time on (`C++/OOP/`, `C++/Tasks/Task1_OOP/`, `Task2_OOP/`):

- **Constructors & the rule of three** — `Complex` (`Tasks/Complex/main.cpp`) walks through default, one-parameter, and two-parameter constructors plus a destructor, all with print statements to trace exactly when each one fires.
- **Deep copying** — `Stack` (`OOP/stack.cpp`) manages its own heap array and implements a proper deep-copy constructor so copies don't share memory, plus a static counter (`stk_count`) to track how many stacks exist.
- **Inheritance & polymorphism** — `Employee`/`Developer` (`OOP/inheritence.cpp`) and `Geometry`/`Rectangle` and `Vehicle`/`Car` (`Tasks/Task2_OOP/`) both use virtual functions and `override` so that calling `.work()` or `.move()` on a base pointer runs the correct derived behavior. Both also use `static` counters to track how many objects of each hierarchy have been created.
- **The Singleton pattern** — `NetworkManager` (`OOP/singleton.cpp`) is a clean, from-scratch singleton with a private constructor and a static `getInstance()`, proven with a pointer-equality check.
- **Exception handling** — the Grade System (`Tasks/Grade System/GradeSystem.cpp`) validates grade input (0–100) using `try`/`catch` and `invalid_argument`, re-prompting on bad input instead of crashing.
- **Abstract classes & interfaces** — the Library Management System (`Tasks/Library.cc`, [README](C++/Tasks/) — see below) defines a `borrowable` interface and an abstract `User` base class, with `Book`, `Student`, and `Teacher` implementing them. It manages `vector<Book>` and `vector<User*>` and runs an add/borrow/return menu loop.
- **Student Management System** (`Tasks/Task1_OOP/`) — a `Student` class holding ID, name, age, major, and GPA, wired into a menu that adds students, lists them, and searches by ID.

### Bigger tasks

- **Bank Menu (procedural)** (`Tasks/Task1/`) — an earlier, function-based bank simulator (`CheckBalance`, `Deposit`, `Withdraw` in `bank.cpp`/`bank.h`, driven by a `menu.cpp`) — a nice "before" snapshot compared to the OOP bank system that came later.
- **Library Management System** (`Tasks/Library.cc` + `Library.puml`) — includes a UML diagram (`Library.puml`) alongside the code, showing the class relationships were actually planned out rather than written ad hoc.

### Graduation Project: Bank Management System

`C++/Graduation_Project_C++/` is the capstone of the C++ track, and it pulls together everything above into one real system:

- **`Account`** — an abstract base class holding ID, owner, and balance.
- **`SavingsAccount`** — inherits `Account`, blocks the balance from going negative.
- **`CheckingAccount`** — inherits `Account`, allows a limited overdraft.
- **`Bank`** — the orchestrator. Manages accounts through smart pointers (safe memory management, no raw `new`/`delete` bugs), finds accounts by ID, and routes deposits/withdrawals through the base class so the correct derived behavior runs via polymorphism.
- **Persistence** — accounts and a full transaction history are saved to and loaded from text files (`data/accounts.txt`, `data/transactions.txt`), so the bank doesn't forget everything on exit.
- **Structure** — properly split into `include/` (headers) and `src/` (implementation), which is the first project in the repo organized like a "real" multi-file C++ project rather than a single `.cpp`.

This project is really the sum of the whole track: inheritance and polymorphism from the OOP unit, smart pointers and file I/O layered on top, and a menu-driven interface tying it all together.

---

## Admin Linux

The Linux track (`LINUX/`) is shorter but hands-on — actual shell scripting and system administration rather than just command references.

- **Task 1 — Users & Groups** (`task1.sh`) — a script that idempotently creates a `student` user and an `ITI` group (deleting them first if they already exist so re-runs don't fail), adds the user to the group with `usermod -aG`, and verifies every step by grepping `/etc/passwd` and `/etc/group` before printing the final group membership with `getent`.
- **Task 2 — File Organization** (`task2.sh`) — generates a batch of dummy files (images, docs, archives) and then sorts them into `organizedDirectory/{images,documents,others}` using a `case` statement pattern-matched on file extension, logging each move as it happens.
- **Command reference notes** (`LINUX/Task 1_Linux/README.md`) — a set of personal notes covering the fundamentals: command structure, getting help (`man`, `--help`, `info`, `whatis`, `apropos`), navigation (`pwd`, `ls`, `cd`), absolute vs. relative paths, file operations (`touch`, `mkdir`, `cp`, `mv`, `rm`, `rmdir`), and viewing files (`cat`, `less`, `head`, `tail -f`).

---

## Qt / QML

The Qt track (`QT/`) is where things shift from "console programs" to real applications with a UI, and it shows the clearest jump in scope across the three projects.

### Calculator

`QT/Calculator/` — a working calculator app with the logic cleanly separated from the interface:

- **`Calculator` class** (`calculator.h`/`.cpp`) — a `QObject` exposed to QML via `QML_ELEMENT`, with a `display` property wired up through `Q_PROPERTY` (`READ` + `NOTIFY`) so the UI updates automatically whenever the internal state changes.
- **`Q_INVOKABLE` methods** callable straight from QML: `inputDigit`, `inputDecimal`, `inputOperator`, `equals`, `clear`, and even `calculateTrig` for sin/cos/tan.
- Internally it tracks the running expression, the number currently being typed, the pending operator, and a `m_waitingForOperand` flag so a fresh digit after an operator correctly starts a new number instead of appending to the old one — the classic calculator state-machine problem, solved cleanly.
- This is the first project where C++ and QML are talking to each other properly — C++ owns the logic, QML just binds to it.

### Task 2: Car Catalog

`QT/Task2/` — a car showcase built around a `GridView` of flip-cards:

- **`CarModel.qml`** — a `ListModel` of eight cars (BMW, Audi, Porsche, Mercedes-AMG, etc.) each with name, image, engine, horsepower, top speed, and a description.
- **`CarDelegate.qml`** — each card is a `Flipable` component: hovering scales and tilts the card (`NumberAnimation` with `Easing.OutBack`), and tapping flips it over to reveal the spec sheet on the back, with animated border color/width changes to highlight the flipped state.
- Shows a solid grip on QML's declarative animation system (`Behavior on`, easing curves) and data-driven UI via `ListModel`/delegate patterns, rather than hardcoding each card by hand.

### Smart Home

`QT/Smart_Home/` — the most feature-complete Qt project in the repo, a multi-page dashboard app:

- **Multi-page navigation** — a `StackView` in `Main.qml` moves between `LoginPage`, `DashboardPage`, and `settingsPage`, with `DeviceCard.qml` as a reusable component for individual smart-home devices (fan, light, garage).
- **Internationalization (i18n)** — full translation support for **English, Arabic, and French** (`translations/smart_home_{en,ar,fr}.ts/.qm`), driven by a custom `TranslationController` C++ class that loads the right `.qm` file, persists the chosen language with `QSettings`, and triggers `engine.retranslate()` so the whole UI updates live without restarting the app.
- **Robustness** — `resolveTranslationPath()` checks several candidate paths (app dir, relative dir, Qt resource system) so translations still load correctly whether running from source, from a resource-embedded build, or from an install directory.
- This project brings together QML UI composition, C++/QML interop, settings persistence, and localization — the most "production-shaped" thing in the repo.

---

## How this repo is organized

```
ITI/
├── C++/
│   ├── OOP/                     — core OOP concepts (inheritance, singleton, deep copy)
│   ├── Quizzes/                 — daily timed quizzes (day10–day13, STL, strings, vectors)
│   ├── Tasks/                   — standalone exercises (pointers, vectors, complex numbers, grades, library, student system)
│   └── Graduation_Project_C++/  — capstone: full OOP bank system with file persistence
├── LINUX/                       — Admin Linux scripts + command reference notes
└── QT/
    ├── Calculator/              — C++/QML calculator with trig support
    ├── Task2/                   — animated car catalog (GridView + Flipable)
    └── Smart_Home/              — multi-page, multi-language smart home dashboard
```

Looking at it end to end, the progression is pretty visible: plain functions and pointers → classes and inheritance → a full OOP system with persistence → shell scripting for system administration → and finally real applications where C++ logic drives a live, translated QML interface. A decent stretch for one course.

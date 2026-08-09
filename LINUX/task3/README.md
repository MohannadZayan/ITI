# Bash Assignments 1-3

This folder contains the solutions for Assignments 1, 2, and 3.

## Assignment 1 - Arithmetic Operations (`arithmetic.sh`)

Asks the user for two integers and prints their sum, difference,
multiplication, division, and modulus using `$((...))` arithmetic expansion.

```bash
./arithmetic.sh
```

```
Enter first number: 20
Enter second number: 5

Sum = 25
Difference = 15
Multiplication = 100
Division = 4
Modulus = 0
```

## Assignment 2 - Mini Linux System Monitor (`toolkit.sh`)

A menu-driven script. Each menu option is implemented as its own function
(`show_date`, `show_uptime`, `show_users`, `show_pwd`, `show_disk`,
`show_memory`, `list_files`), and a `while` loop with a `case` statement
reads the user's choice until they select Exit.

```bash
./toolkit.sh
```

```
=====================
Linux Toolkit
=====================
1) Show Date
2) Show Uptime
3) Show Logged Users
4) Show Current Directory
5) Show Disk Usage
6) Show Memory Usage
7) List Files
8) Exit
Choose an option:
```

## Assignment 3 - Password Strength Checker (`password_check.sh`)

Asks the user to enter a password, then checks it against 5 rules:

- Length is at least 8 characters
- Contains an uppercase letter
- Contains a lowercase letter
- Contains a digit
- Contains a special character

Each rule prints `OK` or `Missing`, and the script gives an overall rating
based on how many rules passed:

- 5/5 → Strong
- 3-4/5 → Medium
- 0-2/5 → Weak

`${#password}` gets the string length, and `[[ "$password" =~ [A-Z] ]]`
(and similar regex checks) test for uppercase, lowercase, digit, and
special characters. A `score` counter is incremented for every rule that
passes and used to decide the overall rating.

```bash
./password_check.sh
```

```
Enter your password: Abc123!

Password Strength Report

Length          : Missing
Uppercase       : OK
Lowercase       : OK
Digit           : OK
Special Char    : OK

Overall: Medium
```

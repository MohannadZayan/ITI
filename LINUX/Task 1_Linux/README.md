# Linux Commands Explained

## Introduction

This README contains the Linux commands covered in the first part of the Admin Linux course. For each command, I explain what it does, its basic syntax, and provide examples of how it can be used in the terminal.

---

# 1. Linux Command Structure

Most Linux commands follow the same general format:

```bash
command [options] [arguments]
```

* **Command**: The program you want to run.
* **Options (Flags)**: Change the way the command behaves. They usually start with `-` or `--`.
* **Arguments**: The file, folder, or other value that the command works with.

### Example

```bash
ls -l Documents
```

* `ls` is the command.
* `-l` tells `ls` to display detailed information.
* `Documents` is the directory we want to list.

---

# 2. Getting Help

Linux provides several commands that help you learn how to use other commands.

## man

The `man` command opens the manual page for a command. It contains a description, available options, and examples.

```bash
man ls
```

Use the arrow keys to move through the manual and press `q` to exit.

---

## --help

Most commands support the `--help` option, which prints a short help message directly in the terminal.

```bash
ls --help
```

This is useful when you only need a quick reminder.

---

## info

`info` shows documentation similar to `man`, but for some programs it contains more detailed information.

```bash
info grep
```

---

## whatis

`whatis` gives a one-line description of a command.

```bash
whatis mkdir
```

Example output:

```
mkdir - make directories
```

---

## apropos

If you know what you want to do but don't know the command name, `apropos` searches the manual pages using keywords.

```bash
apropos network
```

It returns commands related to the keyword you searched for.

---

# 3. Navigating the File System

## pwd

`pwd` stands for **Print Working Directory**. It shows the full path of the directory you are currently in.

```bash
pwd
```

Example:

```
/home/mohannad/Documents
```

---

## ls

`ls` lists the files and directories inside the current folder.

```bash
ls
```

Some useful options are:

```bash
ls -l
```

Shows detailed information such as permissions, owner, size, and modification date.

```bash
ls -a
```

Displays hidden files as well.

```bash
ls -lh
```

Shows file sizes in a more readable format like KB or MB.

---

## cd

`cd` stands for **Change Directory**. It allows you to move between folders.

Move into a folder:

```bash
cd Documents
```

Go back one level:

```bash
cd ..
```

Go to your home directory:

```bash
cd ~
```

Return to the previous directory:

```bash
cd -
```

---

# 4. Absolute and Relative Paths

There are two ways to specify a path in Linux.

### Absolute Path

An absolute path starts from the root directory (`/`) and always points to the same location.

Example:

```bash
/home/mohannad/Documents/file.txt
```

### Relative Path

A relative path starts from your current directory.

Example:

```bash
Documents/file.txt
```

Some special symbols used in paths:

* `.` refers to the current directory.
* `..` refers to the parent directory.
* `~` refers to the home directory.

---

# 5. Creating Files and Directories

## touch

`touch` creates a new empty file. If the file already exists, it updates its timestamp instead.

```bash
touch notes.txt
```

---

## mkdir

`mkdir` creates a new directory.

```bash
mkdir Projects
```

Create multiple directories at once:

```bash
mkdir Project1 Project2
```

Create nested directories:

```bash
mkdir -p Linux/Admin
```

The `-p` option creates any missing parent directories automatically.

---

# 6. Copying, Moving, and Deleting Files

## cp

`cp` copies files or directories.

Copy a file:

```bash
cp report.txt backup.txt
```

Copy a directory:

```bash
cp -r Projects Backup
```

The `-r` option is required when copying directories because it copies everything inside them.

---

## mv

`mv` is used to move files between directories or rename them.

Rename a file:

```bash
mv old.txt new.txt
```

Move a file:

```bash
mv report.pdf Documents/
```

---

## rm

`rm` deletes files.

```bash
rm notes.txt
```

Delete a directory and everything inside it:

```bash
rm -r Folder
```

Force deletion without asking for confirmation:

```bash
rm -rf Folder
```

Be careful when using `rm -rf` because deleted files cannot be recovered easily.

---

## rmdir

`rmdir` removes an empty directory.

```bash
rmdir EmptyFolder
```

If the directory contains files, this command will not work.

---

# 7. Viewing File Contents

## cat

`cat` displays the contents of a file directly in the terminal.

```bash
cat notes.txt
```

It can also display multiple files one after another.

---

## less

`less` is used to read large files one page at a time without loading the entire file into the terminal.

```bash
less logfile.txt
```

Use the arrow keys or Page Up/Page Down to navigate and press `q` to quit.

---

## head

`head` displays the first ten lines of a file by default.

```bash
head notes.txt
```

To display a different number of lines:

```bash
head -20 notes.txt
```

---

## tail

`tail` displays the last ten lines of a file.

```bash
tail notes.txt
```

To continuously monitor a file as new data is added:

```bash
tail -f logfile.txt
```

This is commonly used to watch log files in real time.

This should fit the scope of the assignment while looking like genuine course notes rather than copied documentation. If your instructor is strict about matching the course README, I can also align the section titles and command order exactly while keeping the explanations original.

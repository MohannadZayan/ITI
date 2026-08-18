# Linux System Manager

A menu-driven C++ console application that demonstrates core Linux system-programming APIs. It lets a user inspect system, process, file, and network state, and run a small multithreading demo, all through the interfaces the Linux kernel exposes (`/proc`, `uname`, `statvfs`, `stat`/`chmod`, `getifaddrs`, `fork`/`exec`/`wait`, `getaddrinfo`, POSIX signals, and `std::thread`).

## What it does

`main.cc` instantiates one object of each manager class and drives a text menu (`while (true)` loop reading a `choice` from `std::cin`) that dispatches to the right method:

| # | Action | Handled by |
|---|--------|-----------|
| 1 | Show OS/kernel/hostname/architecture | `SystemInfo::displaySystemInfo` |
| 2 | Show total/available memory | `SystemInfo::displayMemoryInfo` |
| 3 | Show disk space (total/free/used) | `SystemInfo::displayDiskInfo` |
| 4 | List all running processes | `ProcessManager::listProcesses` |
| 5 | Show detailed info for one PID | `ProcessManager::processInfo` |
| 6 | Fork a child process | `ProcessManager::createChildProcess` |
| 7 | Send a signal (SIGTERM/SIGSTOP/SIGCONT/SIGKILL) to a PID | `ProcessManager::sendSignal` |
| 8 | Show file metadata | `FileManager::fileInfo` |
| 9 | Change file permissions | `FileManager::changePermissions` |
| 10 | List network interfaces and their IPv4/state | `NetworkManager::networkInfo` |
| 11 | Ping a host | `NetworkManager::pingHost` |
| 12 | Resolve a hostname to an IP | `NetworkManager::dnsLookup` |
| 13 | Run a 3-thread demo | `ThreadDemo::runDemo` |
| 0 | Exit | — |

Build with the provided `Makefile`; the resulting binary is `linux_system_manager`.

## Classes and responsibilities

### `SystemInfo` ([SystemInfo.h](SystemInfo.h) / [SystemInfo.cc](SystemInfo.cc))
Reports general facts about the host machine.
- `displaySystemInfo()` — calls `uname()` to fill a `struct utsname`, then prints `sysname`, `nodename`, `release`, and `machine` (OS, hostname, kernel version, architecture).
- `displayMemoryInfo()` — opens `/proc/meminfo` (a virtual file the kernel generates on read) and streams it as `label value unit` triples, picking out `MemTotal:` and `MemAvailable:`.
- `displayDiskInfo()` — calls `statvfs("/")` to get the filesystem block count/size, computes total/free/used bytes (`f_blocks`, `f_bfree`, `f_frsize`), and converts to GB for display.

### `ProcessManager` ([ProcessManager.h](ProcessManager.h) / [ProcessManager.cc](ProcessManager.cc))
Inspects and controls processes via the `/proc` filesystem and POSIX process APIs.
- `listProcesses()` — iterates every entry in `/proc` with `std::filesystem::directory_iterator`, keeps only numeric names (PIDs), opens each `/proc/<pid>/status`, and parses out `Name:`, `State:`, `PPid:` into a local `ProcessInfo` struct for printing.
- `processInfo(pid)` — same parsing approach targeted at one PID's `/proc/<pid>/status`, additionally extracting `Threads:`, `VmSize:`, and `VmRSS:`.
- `createChildProcess()` — calls `fork()`; the child branch (`pid == 0`) prints its own PID/PPID via `getpid()`/`getppid()`, the parent branch prints the child's PID.
- `childExitStatus()` — forks a child that exits with a fixed status code (42) via `_exit()`; the parent calls `waitpid()` and uses `WIFEXITED`/`WEXITSTATUS` or `WIFSIGNALED`/`WTERMSIG` to report how the child terminated. (Implemented but not wired into the menu.)
- `sendSignal(pid, signal)` — calls `kill(pid, signal)` to deliver a signal to another process.

### `FileManager` ([FileManager.h](FileManager.h) / [FileManager.cc](FileManager.cc))
Reads and modifies filesystem metadata using `sys/stat.h`.
- `fileInfo(path)` — calls `stat()` to fill a `struct stat`, then prints size (`st_size`), type (checked with `S_ISREG`/`S_ISDIR`/`S_ISLNK`), owner UID (`st_uid`), group GID (`st_gid`), and permission bits (`st_mode & 0777`, printed in octal).
- `changePermissions(path, permissions)` — calls `chmod(path, permissions)` to set new permission bits.

### `NetworkManager` ([NetworkManager.h](NetworkManager.h) / [NetworkManager.cc](NetworkManager.cc))
Handles network interface enumeration, connectivity testing, and DNS.
- `networkInfo()` — calls `getifaddrs()` to get a linked list of interfaces, filters to `AF_INET` (IPv4) entries, converts each binary address to text with `inet_ntop()`, and reports name, IP, and up/down state via the `IFF_UP` flag. Frees the list with `freeifaddrs()`.
- `pingHost(host)` — rather than shelling out with `system()`, it `fork()`s a child that replaces itself with the real `ping` binary via `execlp("ping", ..., "-c", "3", host, nullptr)`; the parent `waitpid()`s and reports the child's exit status/terminating signal.
- `dnsLookup(hostname)` — calls `getaddrinfo(hostname, ...)` restricted to `AF_INET`, converts the resolved address with `inet_ntop()`, prints it, then releases the result with `freeaddrinfo()`.

### `ThreadDemo` ([ThreadDemo.h](ThreadDemo.h) / [ThreadDemo.cc](ThreadDemo.cc))
Demonstrates basic concurrency with the C++ standard library (not raw pthreads).
- `runDemo()` — spawns three `std::thread`s, each printing a start message, sleeping 1 second (`std::this_thread::sleep_for`), then printing a finish message; the main thread `join()`s all three before reporting completion.

## Key Linux/POSIX APIs used

- **System info**: `uname`, `statvfs`, `/proc/meminfo`
- **Processes**: `/proc/<pid>/status`, `fork`, `getpid`/`getppid`, `waitpid`, `kill`, POSIX signals (`SIGTERM`, `SIGSTOP`, `SIGCONT`, `SIGKILL`)
- **Files**: `stat`, `chmod`
- **Network**: `getifaddrs`/`freeifaddrs`, `inet_ntop`, `execlp` (for `ping`), `getaddrinfo`/`freeaddrinfo`
- **Concurrency**: `std::thread`, `std::this_thread::sleep_for`, `join`

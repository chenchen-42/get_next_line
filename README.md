*This project has been created as part of the 42 curriculum by andmigue.*

# get_next_line

## Description

`get_next_line` is a C function that reads a file descriptor line by line, returning one line per call including the newline character `\n`. It is a fundamental utility function used in many 42 projects.

The goal is to implement a function that can be called in a loop to read a text file or standard input one line at a time, without reading the entire file into memory at once. The function must handle any buffer size defined at compile time via `BUFFER_SIZE`.

The key challenge is managing leftover data between calls using a `static` variable — when a `read()` call retrieves more data than one line, the remainder must be preserved for the next call.

---

## Instructions

### Compilation

```bash
# compile with default buffer size
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl

# compile with custom buffer size
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

### Execution

```bash
# read from a file
./gnl

# test with different buffer sizes
cc -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl && ./gnl
cc -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c main.c -o gnl && ./gnl
```

### Usage in code

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Memory check

```bash
gcc -g -D BUFFER_SIZE=5 get_next_line.c get_next_line_utils.c main.c -o gnl
valgrind --leak-check=full ./gnl
```

---

## File Structure

```
get_next_line.h           → header file, prototypes, BUFFER_SIZE define
get_next_line.c           → main function
get_next_line_utils.c     → helper functions
```

### Helper functions

| Function | Description |
|---|---|
| `if_new_line_exists` | checks if `\n` exists in string |
| `get_size` | counts characters up to and including `\n` |
| `copy_to_line` | joins current line with buffer content up to `\n` |
| `get_the_rest` | shifts buffer content after `\n` for next call |

---

## Algorithm

### Approach: Static Buffer with Line Extraction

`get_next_line` uses a `static` character buffer of size `BUFFER_SIZE + 1` that persists between function calls. This is the core mechanism that allows the function to remember leftover data from the previous `read()`.

### How it works step by step

```
call 1:
  buffer is empty → read() → buffer = "hello\nworld"
  no \n in line yet → copy "hello\n" to line
  get_the_rest() → buffer = "world"
  \n found in line → return "hello\n"

call 2:
  buffer = "world" (leftover from call 1)
  copy "world" to line
  read() → buffer = "\nfoo"
  copy "\n" to line → line = "world\n"
  get_the_rest() → buffer = "foo"
  \n found → return "world\n"

call 3:
  buffer = "foo"
  copy "foo" to line
  read() → returns 0 = EOF
  return "foo" (no \n at end, still valid)

call 4:
  read() returns 0 immediately
  line is NULL → return NULL
```

### Why this approach

- **Memory efficient** — only `BUFFER_SIZE` bytes are read at a time, not the whole file
- **Simple state** — one static buffer is enough to track position between calls
- **Handles any BUFFER_SIZE** — works correctly whether buffer is 1 byte or 1 million bytes
- **No seek** — works on non-seekable file descriptors like pipes and stdin

### Edge cases handled

| Case | Handling |
|---|---|
| Empty file | `read()` returns 0 immediately, return `NULL` |
| No `\n` at end of file | returns last line without `\n` when `read()` returns 0 |
| Read error | `read()` returns -1, free line and return `NULL` |
| Invalid fd | guard clause at start returns `NULL` |
| `BUFFER_SIZE = 1` | reads one byte at a time, still correct |

### Justification

The static buffer approach was chosen over alternatives such as reading the entire file into memory because:

1. It works on **non-seekable** file descriptors (pipes, stdin) where you cannot seek back
2. It uses **constant memory** proportional to `BUFFER_SIZE`, not file size
3. It is **simple to reason about** — one static variable, one read loop
4. It matches the **expected behavior** of line-by-line reading in Unix utilities

---

## Resources

- [Linux man page — read(2)](https://man7.org/linux/man-pages/man2/read.2.html)
- [Linux man page — open(2)](https://man7.org/linux/man-pages/man2/open.2.html)
- [Static variables in C — GeeksForGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File descriptors explained](https://bottomupcs.com/chapter01.xhtml)
- [42 Docs — get_next_line](https://harm-smits.github.io/42docs/projects/get_next_line)

### AI Usage

AI (Claude by Anthropic) was used during this project for the following tasks:

- **Debugging** — identifying the cause of segfaults and infinite loops in edge cases such as giant lines and files without a trailing newline
- **Code review** — reviewing helper functions for correctness and identifying issues with malloc size calculation in `copy_to_line`
- **Explaining concepts** — clarifying how static variables persist between function calls and how the buffer shift mechanism works
- **README writing** — structuring and writing this README document

AI was not used to write the core implementation directly. All code was written and understood by the student, with AI used as a debugging and learning tool.
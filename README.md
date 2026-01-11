*This project has been created as part of the 42 curriculum by gastesan.*

# Get Next Line — 42 Paris Project

[![42](https://img.shields.io/badge/-black?logo=42&style=flat)](https://42.fr/)
[![C](https://img.shields.io/badge/Language-C-A8B9CC?style=flat&logo=c&logoColor=white)](#)
[![Bonus](https://img.shields.io/badge/Bonus%20included-YES-darkgreen)](#)
[![Grade: 125/100](https://img.shields.io/badge/Grade-125%2F100-darkgreen)]()

<img src="https://github.com/user-attachments/assets/1b5fc9ec-79df-401e-9320-7b51150797bf" style="width:100%;height:100%;object-fit:cover;" />
<img src="https://github.com/user-attachments/assets/3ccc3c58-81db-4617-ba99-7f7229af1d1e" style="width:100%;height:100%;object-fit:cover;" />
<img src="https://github.com/user-attachments/assets/d1fb3a2a-dfcd-4b6c-86ff-d093db34e21f" style="width:100%;height:100%;object-fit:cover;" />

> After evaluation, I refactored this project and integrated it into my [libft](https://github.com/guillaumeast/42_libft) as a separator-agnostic `get_next_chunk()` function.  
You can find the detailed _Doxygen_ documentation [here](https://guillaumeast.github.io/42_libft/html/group__gnl.html)

## 📋 Table of Contents
- [📇 Description](#-description)
- [📖 Instructions](#-instructions)
- [🧠 Technical Choices](#-technical-choices)
- [🧩 Algorithm explanation](#-algorithm-explanation)
- [📚 Resources](#-resources)
- [🤖 AI usage notice](#-ai-usage-notice)

## 📇 Description

### TL;DR

`get_next_line` is an implementation of a line-by-line reader for file descriptors (`fd`).  

### Precisions

Its goal is to provide a reliable, stateful, and norm-compliant function capable of returning one line per call while handling arbitrary buffer sizes and multiple file descriptors (bonus).  
This project explores static storage, controlled memory management, and iterative parsing of streamed input.

### Repository structure

```bash
.
├── README.md
├── main.c			# Only for tests
├── file.txt		# Only for tests
├── get_next_line.h
├── get_next_line.c
├── get_next_line_bonus.h
├── get_next_line_bonus.c
├── get_next_line_utils.c
└── get_next_line_utils_bonus.c
```

## 📖 Instructions

### Compilation

This project doesn't include `main()` function, so you need to provide your own one to compile:
```bash
cc get_next_line.c get_next_line_utils.c <your_main.c>
```

> You can compile get_next_line with a custom `BUFFER_SIZE` by adding the `-D BUFFER_SIZE=<N>` flags

### Usage

Call `get_next_line(fd)` to get the next line of a given `fd` (You can use as many `fd` you want, in any order).  
When end of file (`EOF`) is reached or if an error occurs, `get_next_line(fd)` will return `NULL`.  

### Example
```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
    close(fd);
	return (0);
}
```
> 💡 Returned strings include the trailing newline (`\n`) when present.

> ⚠️ Don't forget to `free()` the line returned by `get_next_line(fd)`

## 🧠 Technical choices

### Dynamic exponential growth

The output line buffer grows exponentially to minimize reallocations.  
This ensures **O(1) amortized concatenation** when appending data read from the internal buffer.

### Final shrink-to-fit

Once the line is complete, the allocated memory is reduced to the minimum required capacity before returning it.  
This **reduces memory footprint** and avoids over-provisioning resulting from exponential growth.

### Linked-list based `fd` management

To support multiple file descriptors simultaneously (required for the bonus),
each `fd` is associated with its own `stash` node stored inside a linked list.

This prevents static global arrays, avoids overflow of the `.bss` segment, and
keeps memory usage proportional to the number of active FDs.

Every node stores:
- its `fd`
- its read buffer and length
- a pointer to the next node

Nodes are created on demand and removed as soon as the `fd` reaches `EOF` or an error occurs.

### Norm constraints

No _libc_ helpers such as `memset`/`bzero` were allowed, which would otherwise optimize buffer resets.  
All operations are done manually.

### Memory handling

Buffers are `free`'d as soon as possible (errors, `EOF` per `fd`, etc.).  
However, since only the caller knows when an `fd` is no longer needed, some memory remains `malloc`'d until the program ends.  
These are **not** _true_ leaks; they remain “reachable” and intentionally persist due to project constraints.

## 🧩 Algorithm explanation
The algorithm centers around a per-`fd` stash storing:
- a fixed-size read buffer
- its current length
- its continuation pointer for the **linked list** of stashes

### Process summary
1. Retrieve or create a stash for the requested `fd`.  
2. If leftover data exists in the buffer, process it first.  
3. Otherwise, read from the `fd` into the buffer.  
4. Search for `\n`.  
    - If found → append the slice, adjust buffer, shrink the allocated (line) buffer and return it.  
    - If not → append the full buffer, reset it, read again.  
5. If `EOF` is reached, return whatever has been accumulated (or `NULL`).  
6. When an `fd` finishes, remove its stash.

This ensures:
- Minimal reads  
- Perfect multi-`fd` support  
- Norm‑compliant modularity
- **O(n)** total complexity per returned line (where *n* is the length of the returned line)  
  _(Each character is copied at most once thanks to exponential buffer growth.)_
## 📚 Resources
- `man 2 read` (RTFM 🙈)
- Project subject
- Norm.v4

## 🤖 AI usage notice

**No code was generated by AI.**

AI was used only to:
- reason about architectural approaches,
- clarify tester/compiler logs,
- refine explanations during debugging,

**All technical decisions and implementations are original.**

<div align="center">

# rplib.h

### Write C. Skip the repetition.

A single-header C library that gives you short, Python-style keywords for input, output, math, arrays, strings, matrices, sorting and more.

![Language](https://img.shields.io/badge/language-C-blue.svg)
![Type](https://img.shields.io/badge/type-header--only-orange.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-green.svg)
![License](https://img.shields.io/badge/license-MIT-purple.svg)
![Keywords](https://img.shields.io/badge/keywords-99-ff69b4.svg)

</div>

---
## Project Overview

<p align="center">
  <img src="image/file_00000000e3cc81fa98e3076f25d2d53c.png"
       alt="Project Image"
       width="800">
</p>

## Table of Contents

- [Why rplib.h?](#why-rplibh)
- [Features](#features)
- [Quick Start](#quick-start)
- [Installation](#installation)
  - [Way 1: Keep it next to your program](#way-1-keep-it-next-to-your-program)
  - [Way 2: Install as a default library](#way-2-install-as-a-default-library)
    - [Windows](#windows-msys2--mingw)
    - [Linux](#linux)
    - [macOS](#macos)
  - [Uninstall](#uninstall)
- [Compiling](#compiling)
- [API Reference](#api-reference)
- [Examples](#examples)
- [Good to Know](#good-to-know)
- [Documentation Book](#documentation-book)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

---

## Why rplib.h?

Standard C is powerful but wordy. `rplib.h` wraps the common, repetitive parts into short, readable keywords so beginners (and anyone who wants cleaner code) can focus on the logic.

**Before**

```c
int n;
scanf("%d", &n);
for (int i = 0; i < n; i++)
    printf("%d\n", i);
```

**After**

```c
#include "rplib.h"

int main(void)
{
    int i, n = ReadInt();
    F(i, n) Out("%d\n", i);
    return 0;
}
```

---

## Features

- **Header-only**: one file, nothing to build or link (except `-lm` for math on Linux/macOS).
- **99 keywords** across 8 categories.
- **Zero overhead**: functions are `static inline`, so the compiler can paste them directly into your code.
- **Cross-platform**: Windows, Linux and macOS (`Clear()` and `Delay()` pick the right system call automatically).
- **Safe defaults**: NULL checks, bounds clamping and divide-by-zero protection where it matters.
- **Beginner friendly**: short names, readable source, fully documented.

| Category | Keywords |
|---|---|
| Input / Output | `In` `Out` `NL` `ReadInt` `ReadFloat` `ReadLine` `ReadStr` `PrintInt` `PrintFloat` `PrintStr` `Pause` |
| Math | `Sqrt` `Pow` `Abs` `Max` `Min` `Round` `Floor` `Ceil` `Mod` `Sign` `GCD` `LCM` `Fact` `IsPrime` `IsEven` `IsOdd` `IsPerfect` `IsArmstrong` `IsPalindrome` `Digits` |
| Arrays | `Read` `Print` `Sum` `Avg` `MaxA` `MinA` `Sort` `Rev` `Swap` `Find` `First` `Last` `Count` `Copy` `Equal` `Unique` `Freq` `Insert` `Delete` `Rotate` |
| Strings | `Len` `CopyStr` `Cat` `Cmp` `RevStr` `Upper` `Lower` `Trim` `CountChar` `FindChar` `FindStr` `Replace` `IsDigit` `IsAlpha` `IsSpace` |
| Loop Helpers | `F` `R` `Repeat` `Choose` |
| Matrix | `ReadMat` `PrintMat` `MatAdd` `MatSub` `MatMul` `Transpose` `Trace` `Diag` `MatEqual` `Identity` |
| Search & Sort | `Linear` `Binary` `Bubble` `Select` `InsertSort` `MergeSort` `QuickSort` `SecondMax` `SecondMin` `Missing` |
| Utilities | `Clear` `Delay` `Random` `Seed` `Malloc` `Free` `TimerStart` `TimerStop` `Time` |

---

## Quick Start

```c
#include "rplib.h"

int main(void)
{
    int a[5] = {5, 2, 8, 1, 3};

    Sort(a, 5);
    Print(a, 5);  NL();

    Out("Sum = %lld\n", Sum(a, 5));
    return 0;
}
```

Compile and run:

```bash
gcc main.c -o main -lm
./main
```

Output:

```
1 2 3 5 8
Sum = 19
```

---

## Installation

There are **two ways** to use `rplib.h`.

### Way 1: Keep it next to your program

The simplest option. Put `rplib.h` in the same folder as your `main.c`:

```
my-project/
├── rplib.h
└── main.c
```

Then include it with quotes:

```c
#include "rplib.h"
```

No setup and no admin rights are needed. This is the recommended way for school projects and for sharing code with others.

### Way 2: Install as a default library

Install `rplib.h` into your compiler's default include folder. After that you can use it from **any** project, in **any** folder, with angle brackets:

```c
#include <rplib.h>
```

#### Windows (MSYS2 / MinGW)

1. Open **Command Prompt** and run:

   ```cmd
   where gcc
   ```

2. Look at the path printed on your screen, for example:

   ```
   C:\msys64\mingw64\bin\gcc.exe
   ```

3. Go to that directory, then **move back one folder** so you are no longer inside `bin`.
4. Look for the folder named **`include`**.

   | Toolchain | Typical include folder |
   |---|---|
   | MSYS2 (MinGW-w64) | `C:\msys64\mingw64\include\` |
   | MinGW | `C:\MinGW\include\` |

5. Move (or copy) your `rplib.h` file **directly into that `include` folder**.

   Or do it from Command Prompt (run as Administrator if needed):

   ```cmd
   copy rplib.h C:\msys64\mingw64\include\
   ```

6. Test it from any folder:

   ```c
   #include <rplib.h>
   ```

#### Linux

The standard place for user-installed headers is `/usr/local/include`:

```bash
sudo cp rplib.h /usr/local/include/
```

Optional check of where your compiler searches:

```bash
echo | gcc -E -Wp,-v -xc - 2>&1 | grep -A10 "search starts"
```

> `/usr/include` also works, but `/usr/local/include` is preferred because system package updates will not touch it.

#### macOS

Apple's `clang` (used when you type `gcc` on a Mac) searches `/usr/local/include` by default:

```bash
sudo mkdir -p /usr/local/include
sudo cp rplib.h /usr/local/include/
```

Using GCC from Homebrew? Find its include folder with:

```bash
brew --prefix
```

Then copy the file into `$(brew --prefix)/include/` (for Apple Silicon this is usually `/opt/homebrew/include/`). If the compiler does not pick it up, add the folder once with `-I`:

```bash
gcc main.c -o main -I/opt/homebrew/include
```

#### Don't want to touch system folders?

You can keep `rplib.h` anywhere and tell the compiler where it is. No installation is needed:

```bash
gcc main.c -o main -I/path/to/folder/containing/rplib -lm
```

### Uninstall

Delete `rplib.h` from the include folder you used:

| OS | Command |
|---|---|
| Windows | `del C:\msys64\mingw64\include\rplib.h` |
| Linux / macOS | `sudo rm /usr/local/include/rplib.h` |

---

## Compiling

| Situation | Command |
|---|---|
| Header next to `main.c` | `gcc main.c -o main -lm` |
| Installed as default library | `gcc main.c -o main -lm` |
| Header in a custom folder | `gcc main.c -o main -I<folder> -lm` |
| Windows (MinGW / MSYS2) | `gcc main.c -o main.exe` |

The `-lm` flag links the math library (needed for `Sqrt`, `Pow`, `Round`, ...). It is not required on Windows.

> `Swap` uses `__typeof__`, so use **GCC** or **Clang**.

---

## API Reference

### Input / Output

| Keyword | Description |
|---|---|
| `In(...)` | Macro for `scanf` |
| `Out(...)` | Macro for `printf` |
| `NL()` | Print a newline |
| `int ReadInt(void)` | Read and return an integer |
| `float ReadFloat(void)` | Read and return a float |
| `void ReadLine(char *s, int n)` | Read a full line (with spaces) safely |
| `void ReadStr(char *s, int n)` | Alias of `ReadLine` |
| `void PrintInt(int x)` | Print an integer |
| `void PrintFloat(double x)` | Print a number using `%g` |
| `void PrintStr(const char *s)` | Print a string (NULL-safe) |
| `void Pause(void)` | Wait for Enter |

### Math

| Keyword | Description |
|---|---|
| `Sqrt(x)` `Pow(x,y)` | Square root, power |
| `Abs(x)` `Max(x,y)` `Min(x,y)` | Absolute value, larger, smaller (return `double`) |
| `Round(x)` `Floor(x)` `Ceil(x)` | Rounding functions |
| `Mod(x,y)` | Remainder (returns 0 if `y` is 0) |
| `Sign(x)` | Returns -1, 0 or 1 |
| `GCD(a,b)` `LCM(a,b)` | Greatest common divisor, least common multiple |
| `Fact(n)` | Factorial (up to 20!) |
| `IsPrime(n)` `IsEven(n)` `IsOdd(n)` | Number checks |
| `IsPerfect(n)` `IsArmstrong(n)` `IsPalindrome(n)` | Special number checks |
| `Digits(n)` | Count decimal digits |

### Arrays

| Keyword | Description |
|---|---|
| `Read(a,n)` `Print(a,n)` | Read / print `n` elements |
| `Sum(a,n)` `Avg(a,n)` | Total and average |
| `MaxA(a,n)` `MinA(a,n)` | Largest and smallest element |
| `Sort(a,n)` `Rev(a,n)` | Sort ascending, reverse |
| `Swap(x,y)` | Swap any two variables (macro) |
| `Find(a,n,x)` `First(a,n,x)` `Last(a,n,x)` | Index of a value, or -1 |
| `Count(a,n,x)` `Freq(a,n,x)` | How many times `x` appears |
| `Copy(dest,src,n)` `Equal(a,b,n)` | Copy / compare arrays |
| `Unique(a,n)` | Remove duplicates, returns new length |
| `Insert(a,n,pos,x)` `Delete(a,n,pos)` | Return new length |
| `Rotate(a,n,k)` | Rotate right by `k` |

### Strings

| Keyword | Description |
|---|---|
| `Len(s)` | String length |
| `CopyStr(dest,src)` `Cat(a,b)` `Cmp(a,b)` | Copy, append, compare |
| `RevStr(s)` `Upper(s)` `Lower(s)` `Trim(s)` | In-place transformations |
| `CountChar(s,c)` `FindChar(s,c)` `FindStr(s,t)` | Search (index or -1) |
| `Replace(s,cap,old,new)` | Replace the first match (buffer size required) |
| `IsDigit(c)` `IsAlpha(c)` `IsSpace(c)` | Character checks |

### Loop Helpers

| Keyword | Description |
|---|---|
| `F(i,n)` | `for i = 0 .. n-1` |
| `R(i,n)` | `for i = n-1 .. 0` |
| `Repeat(n) { ... }` | Run a block `n` times |
| `Choose(cond,a,b)` | `cond ? a : b` |

### Matrix

Matrices are stored as flat arrays: element `(i, j)` is at `a[i*cols + j]`.

| Keyword | Description |
|---|---|
| `ReadMat(a,r,c)` `PrintMat(a,r,c)` | Read / print |
| `MatAdd(a,b,out,r,c)` `MatSub(a,b,out,r,c)` | Add / subtract |
| `MatMul(a,b,out,r1,c1,c2)` | Multiply |
| `Transpose(a,out,r,c)` | Transpose into `out` |
| `Trace(a,n)` `Diag(a,n)` | Diagonal sum / print diagonal |
| `MatEqual(a,b,r,c)` `Identity(a,n)` | Compare / create identity matrix |

### Search & Sort

| Keyword | Description |
|---|---|
| `Linear(a,n,x)` | Linear search |
| `Binary(a,n,x)` | Binary search (array must be sorted) |
| `Bubble` `Select` `InsertSort` | O(n²) sorts |
| `MergeSort` `QuickSort` | O(n log n) sorts |
| `SecondMax(a,n)` `SecondMin(a,n)` | Second largest / smallest distinct value |
| `Missing(a,n)` | Find the missing number (XOR trick) |

### Utilities

| Keyword | Description |
|---|---|
| `Clear()` | Clear the screen (`cls` / `clear`) |
| `Delay(seconds)` | Pause for a number of seconds |
| `Seed()` `Random(n)` | Seed the generator, random 0 to n-1 |
| `Malloc(n)` `Free(p)` | Memory helpers |
| `TimerStart()` `TimerStop(start)` | Measure elapsed seconds |
| `Time()` | Current time (`time_t`) |

---

## Examples

### Reading and summing numbers

```c
#include "rplib.h"

int main(void)
{
    int a[100];
    int n = ReadInt();

    Read(a, n);
    Out("Max = %d, Min = %d, Avg = %g\n", MaxA(a, n), MinA(a, n), Avg(a, n));
    return 0;
}
```

### Number checks

```c
#include "rplib.h"

int main(void)
{
    Out("GCD(24,18) = %lld\n", GCD(24, 18));
    Out("29 prime?   %s\n", Choose(IsPrime(29), "yes", "no"));
    Out("153 Armstrong? %s\n", Choose(IsArmstrong(153), "yes", "no"));
    return 0;
}
```

### Matrix multiplication

```c
#include "rplib.h"

int main(void)
{
    int a[2*3] = {1,2,3, 4,5,6};
    int b[3*2] = {7,8, 9,10, 11,12};
    int c[2*2];

    MatMul(a, b, c, 2, 3, 2);
    PrintMat(c, 2, 2);
    return 0;
}
```

### Timing an algorithm

```c
#include "rplib.h"

int main(void)
{
    int a[5] = {5, 2, 8, 1, 3};

    clock_t t0 = TimerStart();
    QuickSort(a, 5);
    Out("Sorted in %g seconds\n", TimerStop(t0));
    return 0;
}
```

---

## Good to Know

- **`Swap(x, y)`** takes the variables themselves, not their addresses. It needs GCC or Clang.
- **`Replace`** changes only the first match and needs the buffer capacity: `Replace(s, cap, old, new)`.
- **`Transpose`** writes into a separate array: `Transpose(a, out, r, c)`.
- **`Insert`, `Delete` and `Unique`** return the new length. Store it: `n = Delete(a, n, 2);`.
- **`Binary`** only works on a sorted array.
- **`Missing(a,n)`** expects `n` distinct values from `0..n` with exactly one missing.
- **`Fact`** overflows after `20!`.
- **`CopyStr` and `Cat`** do not check buffer sizes. Make sure the destination is large enough.
- **`ReadLine` after `ReadInt`:** a leftover newline stays in the input. Call `Pause()` once in between.
- **`Delay`** takes seconds, not milliseconds.

---

## Documentation Book

A full colorful, book-style reference with an explanation, an example, and the exact source code for every keyword is available in [`rplib_book.pdf`](rplib_book.pdf).

## Project Structure

```
rplib/
├── rplib.h              # The library (single header)
├── main.c               # Your program
├── examples/            # Small example programs
├── docs/
│   └── rplib_book.pdf   # Illustrated documentation book
├── README.md
└── LICENSE
```

---

## Contributing

Contributions are welcome.

1. Fork the repository.
2. Create a branch: `git checkout -b feature/my-feature`
3. Commit your changes: `git commit -m "Add my feature"`
4. Push the branch: `git push origin feature/my-feature`
5. Open a Pull Request.

Please keep new helpers small, `static inline`, NULL-safe where possible, and add an example for each new keyword.

---

## License

Distributed under the **MIT License**. See `LICENSE` for details.

---

<div align="center">

If this project helped you, consider giving it a star.

**rplib.h: Write C. Skip the repetition.**

</div>

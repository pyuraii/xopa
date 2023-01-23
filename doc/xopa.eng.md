# xopa &sect; a C style guide for humans [v1.0.0]

xopa is a C style guide that produces readable, organized code that looks good
in any terminal.	

Table of contents:

- [Organization](#organization)
- [Structure](#structure)
- [Features](#features)
- [Blocks](#blocks)
- [Whitespace](#whitespace)
- [Functions](#functions)
- [Variables](#variables)
- [Keywords](#keywords)
- [Headers](#headers)
- [Miscellaneous](#miscellaneous)

## Organization

* Divide your code into multiple files whenever possible, having one file for
  each logical section of the program.

* When large amounts of compiler directives are needed, use header files. When a
  certain header file is only used in one file (let's call it `foobar.c`), name
  the header file accordingly (like `foobar.h`).

* Put your `main` function in either `main.c` or `<program name>.c`.

### Example

```sh
$ ls -1
ast.h
lexer.c
main.c
main.h
parser.c
token.h
```

## Structure

* All of your files should have the following layout:

	* Comment with a short explanation of the tool
	* `#include` statements for external libraries
	* `#include` statements for internal files
	* `#define` macros
	* `#define` constants
	* ~~Global variables~~ (don't use these though)
	* Function definitions
	* `main` / `wmain` function (if the file has one)

* Group statements into groups of two to four lines. For example, a `struct` and
  its members should be declared together.

* Lines should be limited to 80 characters.

* Explain confusing design choices and code that doesn't "explain itself"
  **above** the line(s) in question (not below).

### Example

```c
#include <stdio.h>
#include <string.h>

#define FOO 1

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		#ifdef FOO
			// `bar` is bad. `foo` is better.
			if (strcmp(argv[i], "bar") == 0) return -1;
		#endif
	}

	return 0;
}
```

## Features

* Use C11 (ISO/IEC 9899:2011) without extensions. In scenarios that require an
  older standard, use C99 (ISO/IEC 9899:1999). When working with POSIX APIs, use
  POSIX.1-2008.

* In scenarios where code must be usable on systems that do not support modern C
  features, use `/* ... */` for comments instead of `// ...` and do not
  initialize variables in for loops.

### Example (C89)

```c
#include <stdio.h>
#include <string.h>

#define FOO 1

int main(int argc, char *argv[]) {
	int i;

	for (i = 0; i < argc; i++) {
		#ifdef FOO
			/* `bar` is bad. `foo` is better. */
			if (strcmp(argv[i] "bar") == 0) return -1;
		#endif
	}

	return 0;
}
```

## Blocks

* Put `{` on the same line preceded by a single space, and put `}` on its own
  line (with the exception of continuing statements like `if { ... } else`).

* Use a block for inner statements if the inner statement needs a block or the
  outer statement is part of a continuing statement in which one of its branches
  requires an inner block.

### Example

```c
for (i = 1; i <= 100; i++) printf("%d", i);

for (;;) {
	if (foo) {
		bar();
		baz();
	}
}

if (foo) {
	bar();
} else {
	baz();
	foo = !foo;
}
```

## Whitespace

Use tabs for indentation and spaces for alignment. This means (a) no tabs except
at the beginning of the line and (b) spaces for multiline macros.

## Functions

* Return type, modifiers, and the opening curly bracket should all be on the same
  line (unless it exceeds 80 characters). In that case, wrap after parameters
  reach the 80 character limit, and align (with spaces!) to the first parameter.
  If the function name is too long, then you should consider giving the function
  a shorter name.

* Functions not used outside of the translation unit should be declared with the
  `static` modifier.

* Never use K&R notation. (It's being removed in C2x.)

### Example

```c
int foo(char *bar) {
	/* ... */
}

int baz(char *qux, char* foo2, char *bar2, char *baz2, char *qux2, char *foo3,
        char *bar2) {
	/* ... */
}
```

## Variables

* Global variables not used outside of the translation unit should be declared
  with the static modifier.

* When declaring a pointer, put the `*` to the left of the variable identifier,
  not to the right of the variable type.

### Example

```c
char *var = malloc(5);
```

## Keywords

* Use a space after `if`, `for`, `while`, `switch`, `do`, etc., as they are not
  function calls.

* Do not use a space directly after the opening `(` or directly before the
  closing `)`.

* Do not use a space with `sizeof` and use parentheses.

### Example

```c
if (i == 2) return -1;
int *var = malloc(4 * sizeof(int));
```

## Headers

Place system and standard library headers first in alphabetical order. If they
must be included in a specific order, write a comment explaining that.

### Example

```c
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
```

## Miscellaneous

When a function returns `-1` on error, check for `-1`, but check against `0`.

### Good Example

```c
if (foo() < 0)
	bar();
```

### Bad Examples

```c
if (foo() == -1) bar();

if (foo() == 0) return;
bar();
```

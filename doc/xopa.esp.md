# xopa &sect; una guía de estilo de C para humanos [v1.0.0]

xopa es una guia de estilo de C que produce código legible y organizado que luce
bien en cualquier terminal.

Tabla de contenidos:

* [Organización](#organizacion)
* [Estructura](#estructura)
* [Caracteristicas](#caracteristicas)
* [Bloques](#bloques)
* [Espacios en blanco](#espacios-en-blanco)
* [Funciones](#funciones)
* [Variables](#variables)
* [Palabras clave](#palabras-clave)
* [Headers](#headers)
* [Miscelaneo](#miscelaneo)

## Organizacion

* Divide tu codigo en multiples archivos siempre que puedas, teniendo un archivo
  por cada semento lógico del programa.

* Cuando necesites muchas directivas de compilador, usa archivos header. Cuando
  un archivo header solo se use en un archivo (vamos a llamarlo `foobar.c`,),
  llama el archivo header acorde (en este caso `foobar.h`).

* Pon tu función 'main' en 'main.c' o `<nombre de programa>.c`.

### Ejemplo

```sh $ ls -1
ast.h
lexer.c
main.c
main.h
parser.c
token.h
```

## Estructura

* Todos tus archivos deberían seguir este esquema:
	* Un comentario con una pequeña explicacion de la herramienta
	* Declaraciones `#include` para librerias externas
	* Declaraciones `#include` para archivos internos
	* Macros `#define`
	* Constantes `#define`
	* ~~Variables globales~~ (no las uses)
	* Definiciones de funciones
	* funcion `main` / `wmain` (si el archivo tiene una)

* Declaraciones de grupo en grupos de dos o cuatro lines. Por ejemplo, un
  `struct` y sus miembros deberian ser declarados juntos.

* Las lineas deberían estar limitadas a 80 caracteres.

* Explica decisiones de diseño confusas y el codigo que no "se explica a si
  mismo" **por encima** de la(s) linea(s) en cuestion (no por debajo)

### Ejemplo

```c
#include <stdio.h>
#include <string.h>

#define FOO 1

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		#ifdef FOO
			// `bar` es malo, `foo` es mejor
			if (strcmp(argv[i], "bar") == 0) return -1;
		#endif
	}

	return 0;
}
```

## Caracteristicas

* Usa [C11 (ISO/IEC 9899:2011)](https://www.iso.org/standard/57853.html) sin
  extensiones. En escenarios en los que necesites usar una estandarizacion mas
  vieja, usa [C99(ISO/IEC 9899:1999)](https://www.iso.org/standard/29237.html).
  Cuando estes trabajando con APIs POSIX, usa POSIX.1-2008.

* En escenarios en los que el codigo tiene que ser util en sistemas que no
  soportan funciones de C moderno usa `/* ... */` para comentarios en vez de `//
  ...` y no inicialices variables en bucles `for`

### Ejemplo (C89)

```c
#include <stdio.h>
#include <string.h>

#define FOO 1

int main(int argc, char *argv[]) {
	int i;

	for (i = 0; i < argc; i++) {
		#ifdef FOO
			/* `bar` es malo, `foo` es mejor */
			if (strcmp(argv[i] "bar") == 0) return -1;
		#endif
	}

	return 0;
}
```

## Bloques

* Pon `{` on la misma linea precedido por un único espacio, y pon `}` en su
  propia linea (con la excepcion de continuar declaraciones como `if { ... }
  else`)

* Usa un bloque para declarciones internas si la declaracion interna necesita un
  bloque o si la declaración externa es parte de la continuación de una
  declaración en el que cada una de sus ramas necesita un bloque interno

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

## Espacios en blanco

Usa tabulaciones para indentación y espacios para alineamiento. Esto significa
que (a) nada de tabulaciones excepto a principio de la linea y (b) espacios para
macros multilinea.

## Funciones

* Tipo return, modificadores y las llaves deberian estar todos en la misma linea
  (a no ser que exceda 80 caracteres). En ese caso, salta a la siguiente linea
  los parametros si llega a 80 caracteres, y alinea (con espacios!) al primer
  parametro. si el nombre de la función es demasiado largo, deberías considerar
  ponerle un nombre distinto.

* Funciones no usadas fuera de la unidad de traducción deberian ser declaradas
  con el modificador `static`.

* Nunca uses la notacion K&R. (Va a ser removida en C2x.)

### Ejemplo

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

* Variables globales no deberían ser usadas fuera de la unidad de traducción con
  el modificador static.

* Cuando declares un pointer, pon el `*` a la izquierda del identificador de la
  variable no a la derecha de el tipo de variable.

### Ejemplo

```c
char *var = malloc(5);
```

## Palabras clave

* Usa un espacio despues de `if`, `for`, `while`, `switch`, `do`, etc. teniendo
  en cuenta que no son llamadas a una función.

* No uses un espacio despues de la apertura de `(` o directamente antes de el
  `)` de cierre.

* No uses un espacio con `sizeof` y usa parentesis.

### Ejemplo

```c
if (i == 2) return -1;
int *var = malloc(4 * sizeof(int));
```

## Headers

Pon las librerias de sistema y estandar primero en orden alfabetico. Si
necesitan ser incluidas en otro orden, escribe un comentario explicando por qué.

### Ejemplo

```c
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
```

## Miscelaneo

Cuando una función devuelve `-1` en caso de error, compruebe `-1`, pero
compruebe contra `0`.

### Buen Ejemplo

```c
if (foo() < 0) bar();
```

### Mal Ejemplo

```c
if (foo() == -1) bar();

if (foo() == 0) return;
bar();
```

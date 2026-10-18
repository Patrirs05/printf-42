*Este proyecto ha sido creado como parte del currículo de 42 por patrirod.*

# ft_printf

## Descripción

**ft_printf** es una reimplementación de la función `printf()` de la librería estándar de C. El objetivo es construir una librería estática, `libftprintf.a`, que exponga una función con el siguiente prototipo:

```c
int	ft_printf(char const *, ...);
```

El proyecto sirve sobre todo para aprender cómo funcionan las **funciones variádicas** en C (`<stdarg.h>`): cómo recibir un número desconocido de argumentos y cómo leerlos con el tipo correcto.

### Conversiones soportadas

| Conversión | Salida |
|------------|--------|
| `%c` | Un solo carácter |
| `%s` | Una cadena de caracteres (imprime `(null)` si el puntero es `NULL`) |
| `%p` | Un puntero `void *` en hexadecimal, con el prefijo `0x` (imprime `(nil)` si el puntero es `NULL`) |
| `%d` / `%i` | Un entero decimal con signo |
| `%u` | Un entero decimal sin signo |
| `%x` | Un entero sin signo en hexadecimal, en minúsculas |
| `%X` | Un entero sin signo en hexadecimal, en mayúsculas |
| `%%` | El símbolo del porcentaje |

Igual que el `printf` original, `ft_printf` devuelve el **número de caracteres impresos**. Además, las funciones auxiliares comprueban el resultado de `write` y propagan `-1` si una escritura falla.

La gestión del buffer del `printf` original **no** se reimplementa, como pide el subject: cada carácter se envía directamente a la salida estándar con `write`.

### Estructura del proyecto

```
.
├── Makefile
├── README.md
├── ft_printf.h
├── ft_printf.c           # lectura del formato y selección de la conversión
├── ft_print_char.c       # %c
├── ft_print_str.c        # %s
├── ft_print_ptr.c        # %p
├── ft_print_nbr.c        # %d y %i
├── ft_print_unsigned.c   # %u
└── ft_print_hex.c        # %x y %X
```

## Instrucciones

### Compilación

La librería se compila con `cc -Wall -Wextra -Werror` y se empaqueta con `ar`:

```sh
make        # genera libftprintf.a en la raíz del repositorio
make clean  # elimina los ficheros objeto
make fclean # elimina los ficheros objeto y libftprintf.a
make re     # fclean + all
```

### Uso

Incluye el header en tu código y enlaza con la librería:

```c
#include "ft_printf.h"

int	main(void)
{
	int	count;

	count = ft_printf("Hola %s, tienes %d años (0x%x)\n", "Ana", 20, 255);
	ft_printf("Se han impreso %d caracteres\n", count);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o test
./test
```

### Pruebas

La salida y el valor de retorno se pueden comparar con los del `printf` real:

```c
int	a = printf("[%s] [%p] [%x]\n", NULL, NULL, 255);
int	b = ft_printf("[%s] [%p] [%x]\n", NULL, NULL, 255);
```

Las dos líneas deben imprimir el mismo texto y `a` debe ser igual a `b`. Casos límite que conviene probar: `INT_MIN`, `INT_MAX`, `UINT_MAX`, `0` con `%x`, `%u` y `%d`, `NULL` con `%s` y `%p`, una cadena vacía y `%%`.

## Algoritmo y estructura de datos

### Lectura del formato

`ft_printf` recorre el string de formato una sola vez, desde el primer carácter hasta el `'\0'` final:

1. Si el carácter actual no es `%`, se imprime tal cual.
2. Si es `%`, se lee el carácter siguiente y `ft_convert` decide qué hacer con él.
3. Cada conversión consume **exactamente un argumento** de la lista de argumentos variables (salvo `%%`, que no consume ninguno).

Los argumentos variables se leen con las macros de `va_list`: `va_start` inicializa la lista con el último parámetro fijo (`format`), `va_arg` extrae el siguiente argumento con el tipo que exige la conversión y `va_end` cierra la lista.

El tipo que se pasa a `va_arg` depende de la conversión:

| Conversión | Tipo en `va_arg` | Motivo |
|------------|------------------|--------|
| `%c` | `int` | un `char` se promociona a `int` en las llamadas variádicas |
| `%s` | `char *` | |
| `%p` | `void *` | |
| `%d`, `%i` | `int` | |
| `%u`, `%x`, `%X` | `unsigned int` | |

### Por qué no hace falta ninguna estructura de datos adicional

El formato se analiza en una única pasada lineal, así que el único estado necesario es la posición dentro del string, el contador de caracteres impresos y la propia `va_list`. Un selector basado en `if / else if` es simple, fácil de leer y fácil de ampliar con nuevas conversiones (y con flags para la parte bonus), sin el coste de tablas ni de memoria reservada. El proyecto no usa `malloc`, así que no puede haber fugas de memoria.

### Impresión de números

Los números se imprimen de forma **recursiva**, sin reservar memoria ni usar un buffer intermedio:

- Para imprimir `n` en base `b`, la función se llama primero a sí misma con `n / b` (los dígitos más significativos) y después imprime el dígito `n % b`. Así los dígitos salen en el orden correcto, porque el menos significativo se calcula primero pero se imprime el último.
- El dígito se elige indexando un string con la base (`"0123456789"`, `"0123456789abcdef"` o `"0123456789ABCDEF"`).
- **`INT_MIN`**: `-INT_MIN` no cabe en un `int`, así que el entero se copia a un `long` antes de quitarle el signo. Con eso `%d` e `%i` funcionan con cualquier valor.
- **`%p`**: un puntero ocupa 64 bits en las máquinas de destino, por lo que la dirección se convierte a `unsigned long` antes de imprimirla en hexadecimal. Un `unsigned int` truncaría la dirección.
- La recursión tiene como máximo 20 niveles (los dígitos de un valor de 64 bits), así que es segura.

### Conteo de caracteres y errores

Cada función `ft_print_*` devuelve el número de caracteres que escribió, o `-1` si una llamada a `write` falla. Las funciones recursivas suman el valor devuelto por la llamada interior a su propio contador, y se detienen en cuanto reciben `-1`. De este modo el valor final que devuelve `ft_printf` coincide con el del `printf` original.

## Recursos

### Referencias

- `man 3 printf`, `man 3 stdarg`
- [cppreference: `printf` y `<stdarg.h>`](https://en.cppreference.com/w/c/io/fprintf)
- La Norma de 42 (`norminette`) y el subject de `ft_printf`

### Uso de IA

Se usó IA (Claude) como **ayuda para aprender**, no para generar el proyecto. En concreto, para:

- Explicar cómo funcionan las funciones variádicas (`va_list`, `va_start`, `va_arg`, `va_end`) y qué significa el prototipo `int ft_printf(char const *, ...)`.
- Explicar el comportamiento esperado de cada funcion, del valor de retorno y de los casos límite (punteros `NULL`, gestión de errores de `write`).
- Revisar fragmentos de código escritos por mí y señalar problemas de Norma, variables sin inicializar y errores.
- Ayudar a redactar este README.
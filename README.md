# Warm Up Homework 1

Shirui Liu

Four C functions: a command-line parser, an integer-to-string converter, a
generic printer, and a segment descriptor packer.

## Build and run

```
gcc -Wall -Wextra -o ASG1 ASG1.c
./ASG1
```

Compiles clean with no warnings. `main` exercises all four functions.

## Functions

### `int parse_command(char *inp, int *argc, char *argv[])`

Splits a space-separated string into words, in place.

Walks the string once, tracking whether it is currently inside a word. On the
first character of a word it records that address in `argv`; on the first space
after a word it overwrites the space with `'\0'`, terminating that word. No
copying and no allocation — `argv` points into the original buffer.

The word count is written to `*argc` and also returned. Repeated spaces produce
no empty entries.

Note: `inp` is modified. Only `' '` is treated as a separator, not tabs.

### `char *itoa(int value, char *str, int base)`

Converts `value` to a string in base 2, 8, 10 or 16, writing into the
caller-supplied `str` and returning it.

In base 10 a negative value is prefixed with `-` and the digits come from its
magnitude. In every other base the value is reinterpreted as unsigned, so
`-512` in base 16 is `fffffe00`. An invalid base yields an empty string.

Two passes over the number. The first divides by the base repeatedly to count
how many digits are needed; the second writes those digits right to left into
their final positions, so no reversal step is required. Zero is handled up
front, since the digit loop would otherwise write nothing.

`str` must have room for at least 34 characters (32 binary digits, a sign, and
the terminator).

| input | base | output |
|---|---|---|
| 512 | 2 | `1000000000` |
| 512 | 8 | `1000` |
| 512 | 10 | `512` |
| 512 | 16 | `200` |
| -512 | 10 | `-512` |
| -512 | 16 | `fffffe00` |

### `void printany(char type, void *data)`

Prints a value of any primitive type, within the two-argument limit and using
no global variables.

One parameter cannot be five different types, so `data` is the *address* of the
value and `type` is a letter saying how to read it: `'c'` char, `'i'` int,
`'u'` unsigned, `'l'` long, `'f'` float. Each branch casts the pointer to the
matching type before dereferencing it, which is what tells the compiler how
many bytes to read and how to interpret them. An unrecognized letter prints a
message rather than guessing.

The type letter is a promise from the caller that the compiler cannot verify —
passing a mismatched letter reads the bytes as the wrong type.

### `void populate_desc(int base, int limit, int flag, DESC *g)`

Packs a 32-bit base, a 20-bit limit and a 4-bit flag into an x86 segment
descriptor.

None of the three values is stored contiguously. `base` is split across three
fields, `limit` across two, and the leftover nibble of `limit` shares a byte
with `flag`. Each field is extracted with a right shift to bring the wanted
bits down to position 0, then a mask to discard everything above them.

The shared byte follows the x86 layout: `limit` bits 16-19 occupy the low
nibble, the four flag bits the high nibble.

```
limit_and_flag
┌──────────┬──────────┐
│ flag     │ limit    │
│ bits 4-7 │ bits 0-3 │
└──────────┴──────────┘
```

Values wider than their field are masked off rather than rejected, so an
oversized `flag` cannot overflow into limit's half of the byte.

With `base = 0x12345678`, `limit = 0xABCDE`, `flag = 0x7`:

| field | value |
|---|---|
| `base_0_15` | `5678` |
| `base_16_23` | `34` |
| `base_24_31` | `12` |
| `limit_0_15` | `bcde` |
| `limit_and_flag` | `7a` |

## Notes

`itoa` uses no library functions. `printany` uses `printf`, which is the point
of the function.
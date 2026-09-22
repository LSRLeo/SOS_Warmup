# Warm Up Homework 1

Shirui Liu

## Build

```
gcc -Wall -Wextra -o ASG1 ASG1.c
./ASG1
```

## Functions

**`parse_command(inp, argc, argv)`** — splits a string into words in place.
Replaces each separating space with `'\0'` and stores a pointer to each word in
`argv`. Word count goes to `*argc` and is also returned. Modifies `inp`.

**`itoa(value, str, base)`** — converts an int to a string in base 2, 8, 10 or
16. Base 10 keeps the sign; other bases treat the value as unsigned. Counts the digits first, then writes them right to
left into their final spots. 

**`printany(type, data)`** — prints any primitive. `data` is the address of the
value, `type` says how to read it and it's designed to be: `'c'` char, `'i'` int, `'u'` unsigned,
`'l'` long, `'f'` float.

**`populate_desc(base, limit, flag, g)`** — packs a 32-bit base, 20-bit limit
and 4-bit flag into an x86 segment descriptor, using shifts to position each
chunk and masks to trim it. In the shared byte, limit's top nibble goes in the
low half and flag in the high half.
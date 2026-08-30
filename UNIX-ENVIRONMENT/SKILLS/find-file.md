#### `find-file`: search bypattern

**Examples:**

```sh
find ./tree -type f -name '*.c' -print
find ./tree -type f '(' -name '*.c' -o -name '*.h' ')' -print
find ./tree -name skip -prune -o -type f -print
find ./tree -type f -size +10c -print
find ./tree -type f -mtime -1 -print
find ./tree -type f -newer ./reference-file -print
find ./tree -type f -perm 640 -print
find ./tree -type f -user me -print
```

Quote patterns so the shell does not expand them first. `-size +10c` means more than ten bytes; `-perm 640` is an exact mode match. The prune example skips every directory named `skip`. Hidden entries are included by `find`.

**Limitations and alternatives:**

`-path`, `-maxdepth`, `-print0`, `-delete`, and `-exec ... +` were rejected. A verified path-filter alternative delegates the pathname as a single argument:

```sh
find ./tree -type f -exec /bin/sh -c \
    'case "$1" in */sub/*) echo "$1";; esac' probe '{}' \;
```

For operations on discovered files, prefer `-exec ... '{}' \;` to whitespace-separated output piped into `xargs`. The former correctly handled the tested filename containing spaces. Do not assume `find` will propagate errors from its child commands.


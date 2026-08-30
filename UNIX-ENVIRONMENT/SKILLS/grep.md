### `grep`: text search, recursive search, and binary-mode search...

Divide into two contexts: for short text files, and larger (or binary-mode)
files.

#### Context 1: short, LF-terminated text

**Examples:**

```sh
grep -n 'pattern' ./file
grep -n -i 'pattern' ./file
grep -c 'pattern' ./file
grep -l 'pattern' ./file1 ./file2
grep -w 'word' ./file
fgrep -n 'literal a.b' ./file
egrep -n 'alpha|beta' ./file
```

Use `fgrep` for a fixed string and `egrep` for alternation/extended expressions. Basic `grep 'alpha\|beta'` did not provide GNU-style alternation. `grep -r`, `-A`, `-E`, `-F`, `-a`, and `-x` were rejected. For a whole-line basic-regex match, use explicit `^` and `$` anchors on contract-compliant text.

Verified recursive search:

```sh
find ./tree -type f -name '*.c' -exec grep -n 'pattern' '{}' /dev/null \;
```

The second input `/dev/null` forces filenames into the output. Expect `path:line:text`, but do not treat that as an unambiguous serialization for arbitrary pathnames. For context or a targeted edit, read a numbered range from the exact file after checking its text contract.

#### Context 2: long text, or binary-mode files

**Be careful!** We use *Perl*, not standard Unix `grep`. All three grep variants damaged at least one tested long-line or NUL-containing fixture. Do not use their output to reconstruct arbitrary files.

**Examples:**

For a literal match in long lines, Perl can report physical line numbers without the basic grep buffer limit:

```sh
perl -ne 'if (index($_,"needle") >= 0) { print "$.:$_"; }' < ./file
```
For a byte sequence anywhere in a binary file, including across LF/NUL boundaries:

```sh
perl -e 'binmode(STDIN); $d=join("",<STDIN>); $n=pack("H*","414243"); $p=-1; while (($p=index($d,$n,$p+1))>=0) { print "$p\n"; }' < ./file.bin
```
This reports zero-based decimal byte offsets, including overlapping matches. The tested `ABC` sequence was found at offset 5. The whole-file recipe uses memory proportional to file size; use a streaming scanner with overlap for large files rather than assuming this recipe is unbounded.


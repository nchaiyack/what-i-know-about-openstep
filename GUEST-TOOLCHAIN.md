
# The OPENSTEP 4.2 Unix environment: guest-side file and shell tasks

**About and scope:** See `GETTING-STARTED.md` for instructions about working with OPENSTEP remotely.

This documents various tasks in the OPENSTEP 4.2 Unix environment in both:

- The  `sh` shell -- **run it manually**; the default
is often `csh`. Be careful: this is BSD `sh` as distributed with 4.2 BSD!

- Perl 5.001, which is a useful fallback.

The writing here is a little robotic;  it's because I've used ChatGPT as a "robot Unix expert" to talk to other Unix experts.

In particular, we define various "skills", representing specific tasks:  `ls`, `find-file`, `chmod`, `read`, `create`, `delete`, `grep`, `edit-text` and `patch-text`, `edit-bin` and `patch-bin`, and ``script-sh``

**NB:** the header names for the tools (e.g. `find-file`) aren't actual Unix tools, but concise "skill names" I've been using as personal notation.

And, as we state in `GETTING-STARTED.md`: in general, this is Unix, but very far removed from modern Unices:

- **Standards:** OPENSTEP 4.2 provides a historical NeXT/Mach Unix environment with 4.3BSD-style commands and interfaces, plus documented POSIX.1 support for C applications through cc -posix and cc -posixstrict. 

- **Versions:** The working account uses csh, and the installed compiler is based on GCC 2.7.2.1. Target ANSI C89/C90 and consult the guest’s manuals before assuming command options, library APIs, or shell syntax.

## Basic shell work guidelines

Use `/bin/sh` for the scripting examples. The normal login shell is `/bin/csh`; its syntax differs. Quote path arguments. Prefix relative filenames with `./` when they might begin with `-`. Do not infer filenames by splitting `ls` output.

**Line numbers and offsets:** Line numbers in these recipes are one-based. Byte offsets in the recommended Perl and `dd skip=` recipes are zero-based. `tail +Nc` is an exception: its starting byte is one-based. `cmp -l` reports one-based byte positions and octal byte values.

**A best practice -- back up and edit:** Distinguish four operations: inspect, construct a candidate, validate the candidate, and replace the original. Keep backups for mutations. Check the original/preimage before applying a patch; discovering a match earlier does not guarantee that the file is unchanged now.

## Scripting in general

Both `sh` and Perl 5.001 are available. Prefer Perl for your own internal/throwaway tools; it's not worth worrying about compatibility issues with a plain `sh` workflow.

### The supplied `sh`: programming, abilities, limits

**A cheatsheet:**

| Task | Verified `sh` syntax |
|---|---|
| Variable | `name=value` |
| Export | `name=value; export name` |
| Child-only environment | `name=value program args` |
| Read one environment key | `printenv name` |
| Arguments | `$#`, `$1`, `"$@"`, `shift` |
| Loop | `for arg in "$@"; do ...; done` |
| Conditional loop | `while test "$n" -lt 3; do ...; done` |
| Branch | `if test ...; then ...; fi`; `case "$x" in pattern) ...;; esac` |
| Function | `name() { commands; }` |
| Arithmetic | ``n=`expr "$n" + 1` `` |
| Command substitution | Backticks, rather than `$(...)` |
| Redirections | `>`, `>>`, `<`, `2>file`, `2>&1` |
| Literal multiline input | `<<'DELIMITER'` |
| Exit hook | `trap 'command' 0` |

**Scripting complexities we found when testing:**

`false | cat` returned 0: a pipeline's final command controls its status. `set -e` on its own script line and `sh -ec '...'` stopped on a failed command, but `sh -c 'set -e; false; echo ...'` ran the final echo. Prefer explicit checks at critical boundaries.

The shell's `echo -n` suppressed LF and `echo` interpreted backslash escapes. It is unsuitable for arbitrary literal or binary payloads. There was no standalone `printf`; Perl's `printf` is available..

#### Advanced: use of `xargs`

**Examples:**

```sh
echo 'one two three' | xargs -n2 echo
```
**Limitations and alternatives:**

This emitted two arguments per invocation. The argument must be attached: `-n 2` was rejected. `-0` was unsupported, whitespace split the input, and empty input still invoked the command. Replacement mode `-i` reproducibly printed output and then crashed. Prefer `find -exec ... '{}' \;` for pathname operations.

### Advanced warning: exit status subtleties

For advanced shell scripters, some warnings about interpreting output values:

| Tool or operation | Observed behavior | Consequence for an agent |
|---|---|---|
| `ls -ld missing` | Printed `not found`, returned 0 | Do not use `ls` status as an existence predicate |
| `od -b file` | Correct dump, repeatedly returned 228 | Prefer Perl when output and success status must both be reliable |
| `sed -i ... file` | Returned 0, printed transformed text, left file unchanged | There is no verified in-place `-i` operation |
| `sort -k2,2n` | Returned 0 without the intended key sort | Use the verified historical key syntax |
| Invalid address supplied to `ed -` | Printed `?`, returned 0 | Stage edits and validate the result; status alone is insufficient |
| `find ... -exec command ... \;` | Returned 0 even when children returned 2 | Its status is not an aggregate child-command status |
| `grep` | 0 for matches, 1 for no match, 2 for an error | A no-match result is not an execution failure |
| `diff` / `cmp -s` | 0 for equal, 1 for different, 2 for tested errors | Differences are expected results, not necessarily failures |

### Perl 5.001 as a multipurpose polyfill

In a pinch, Perl is a good scripting environment that replaces a standard
shell workflow, especially for throwaway tools! (Treat this as the equivalent of modern Python.)

**Age-related caveats for advanced users:** The installed interpreter is Perl 5.001, unofficial patchlevel 1m. The examples intentionally avoid modern syntax. `sysopen` was unavailable in the tested interpreter; do not substitute modern Perl examples without verification. STDIN/STDOUT filters also avoid interpreting arbitrary input filenames through Perl's historical two-argument `open`/diamond conventions.


## Standard Unix tasks (and skills)

Reminder of the skills listed here: `ls`, `find-file`, `chmod`, `read`, `create`, `delete`, `grep`, `edit-text` and `patch-text`, `edit-bin` and `patch-bin`, and `script-sh`.

### Advanced warning: plain text processing on OPENSTEP

For a standard Unix text-processing pipeline (e.g. `grep`, `sed`, `awk`, and `ed`), following these age-related restrictions:

| Property | Requirements |
|---|---|
| Encoding | Printable ASCII bytes `0x20`–`0x7e`, plus TAB and LF |
| Record separator | LF, byte `0x0a` |
| Final record | Ends with LF; an empty file is valid |
| Line length | At most 1,023 data bytes plus the terminating LF |
| NUL and other control bytes | Not accepted |

**But, dont worry:** A file can be plain text in an encoding such as UTF-8 and still be unsafe for this image's legacy line-processing tools. File storage itself does not impose ASCII or short-line restrictions: `cat` and the verified Perl byte workflows preserve arbitrary bytes.

Long JSON lines, UTF-8 source, CRLF files, and files without a final newline can be legitimate text; route them through the byte-preserving Perl recipes instead of silently normalizing or rejecting them as meaningless data.

### `ls`: inspect files and directories

**Examples:**

```sh
ls -la ./directory
ls -ld ./directory
ls -lR ./directory
ls -l ./file
```

`-a` includes hidden entries; `-d` describes the directory itself; `-R` traverses subdirectories. These are presentation commands, not a stable machine metadata format. In particular, a missing path can still produce exit status 0.

**Limitations and alternatives:** 

For an explicit existence check or numeric metadata, use the verified Perl alternatives:

```sh
perl -e 'exit(-e $ARGV[0] ? 0 : 1)' ./file

perl -e '@s=lstat($ARGV[0]); die "$!\n" unless @s; printf "mode=%o size=%d mtime=%d\n",$s[2]&07777,$s[7],$s[9];' ./file
```

`lstat` inspects the directory entry; `-e` tests existence through a symlink. Select that policy deliberately. For ordinary files/directories, the shell's `test -f`, `test -d`, `test -r`, `test -w`, and `test -x` are available. Shell `test -e` is not supported here.

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

### `chmod`: change permissions

**Examples:**

```sh
chmod 640 ./file
chmod u+x,g-w ./file
chmod -R u+rwX ./owned-tree
ls -l ./file
```

Numeric modes, symbolic changes, and recursive `X` were verified. `X` added directory traversal permission without making an ordinary nonexecutable fixture executable. Restrict recursive changes to an explicitly chosen owned tree.

Use `umask 077` before creating private fixtures. `cp -p` preserved the tested file's mode; a staged edit retained mode `0640`. Redirecting into a newly created candidate otherwise uses the current umask, not the original file's permissions.

### `read`: complete or partial files (text and binary)

We provide instructions for 3 contexts: plain-text, byte-oriented access, and for
work with bytes in displayed or encoded forms(e.g. `od` or `uuencode`.)

#### Context 1: plain text

**Examples:**

```sh
cat ./file
cat -n ./file
sed -n '10,20p' ./file
awk 'NR >= 10 && NR <= 20 { print NR ":" $0 }' ./file
head -20 ./file
tail -20 ./file
tail +10 ./file
```

**Limitations and alternatives:**

The `sed` and `awk` examples require the text contract above. `head -n 20`, `tail -n 20`, and `head -c ...` are not the verified syntax.

For long lines, NULs, or an unterminated final line, use Perl to preserve the selected records' bytes:

```sh
perl -ne 'print if $. >= 10 && $. <= 20; exit if $. == 20;' < ./file
```

#### Context 2: byte-oriented access

**Examples:**

`cat` was verified to copy the binary fixture byte-for-byte. To read four bytes at zero-based offset two:

```sh
dd if=./file.bin of=./slice.bin bs=1 skip=2 count=4 2>./read.log
wc -c ./slice.bin
```

`skip` and `count` are block counts; `bs=1` makes them byte counts. A successful `dd` can still reach EOF before the requested count, so verify the length. For exact-length enforcement:

```sh
perl -e 'binmode(STDIN); binmode(STDOUT); seek(STDIN,2,0) or die "$!\n"; $n=read(STDIN,$b,4); die "short read\n" unless defined($n) && $n==4; print $b or die;' \
    < ./file.bin > ./slice.bin
```

`tail -4c file` returns the final four bytes. `tail +3c file` starts at the third byte. The separated spelling `tail -c 4` did not work.

#### Context 3: bytes, in display and encoded format

**Examples:**

```sh
od -bv ./file.bin
strings - -o -3 ./file.bin
```

`od -b` displays octal bytes and octal addresses. Modern `od -An -tx1 -j... -N...` syntax is unsupported, and successful `od` calls returned 228 on this image.

The standalone `-` in `strings - -o -3` requests raw-file scanning; `-o` prints decimal offsets and `-3` sets the minimum string length. `strings -a file` still expects an object file here and is not a generic raw-file alternative. Printable strings are clues, not an exact binary representation.

For a reliable hex dump with explicit hexadecimal offsets:

```sh
perl -e 'binmode(STDIN); $off=0; while (1) { $n=read(STDIN,$b,16); die "$!\n" unless defined($n); last unless $n; printf "%08x %s\n",$off,unpack("H*",$b); $off += $n; }' < ./file.bin
```

For reversible text-only representation, the following UUencode round trip was verified:

```sh
uuencode ./file.bin decoded.bin > ./file.uue
uudecode ./file.uue
cmp -s ./file.bin ./decoded.bin
```

UUencoded input carries an output filename and mode. Inspect its header and decode only trusted data in a controlled directory. `base64`, `xxd`, and `hexdump` were not available on the inspected path.

### `create`: text, empty files, directories, binary data

We provide instructions for 2 contexts: plain text and binary data.

#### Context 1: plain text

**Examples:**

```sh
umask 077
mkdir ./workdir
cat > ./workdir/file.txt <<'END_TEXT'
Literal text: $HOME and backticks are not expanded here.
END_TEXT

cat >> ./workdir/file.txt <<'END_TEXT'
One appended line.
END_TEXT

: > ./workdir/empty.txt
touch ./workdir/another-empty.txt
```

`>` creates or truncates; `>>` appends. `touch` also changes the timestamp of an existing file. The quoted here-document delimiter prevents shell expansion, but here-documents are not an arbitrary-byte input mechanism.

**Limitations and alternatives:**

`mkdir -p` did not create missing parents and actually created a directory named `-p`. Create each parent explicitly and check each result. A checked `mkdir` for a new private working directory is also preferable to guessing a temporary filename; `mktemp` was absent.

### Context 2: binary data

To create specified binary bytes:

```sh
perl -e 'binmode(STDOUT); print pack("H*","000a7f80ff414243005a0a") or die;' > ./file.bin
```

For a hex file supplied as data, validate characters and even length before decoding:

```sh
perl -e '$h=join("",<STDIN>); $h =~ s/\s//g; die "invalid hex\n" if $h =~ /[^0-9a-fA-F]/ || length($h)%2; binmode(STDOUT); print pack("H*",$h) or die;' \
    < ./file.hex > ./file.bin
```

The hex round trip and UUencode round trip both matched the original binary fixture exactly. Neither shell variables nor `echo` should carry arbitrary binary data.

### `delete`: files and directories

**Examples:**

```sh
rm ./file
rm -f ./optional-file
rmdir ./empty-directory
find ./disposable-tree -print
rm -r ./disposable-tree
rm ./-leading-hyphen-name
```

**Limitations and alternatives:**

`rmdir` refuses nonempty directories. The recursive removal above was verified only against a newly created disposable tree. Resolve the exact target, inspect it, and avoid broad roots or unverified wildcard expansion. Deletion is not recoverable through these commands; retain a separate backup when recovery matters.

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

### `edit-text`: targeted text rewrites

**Examples**

For plain text, `sed` writes a new stream:

```sh
sed 's/old/new/g' < ./file.txt > ./candidate.txt
```

Never redirect output back onto the input filename: the shell truncates it before `sed` reads it. `sed -i` did not edit the file in place, even though its status was 0. Quote regexes; escape pattern/replacement metacharacters when they are meant literally.

For exact literal replacement with a precondition and byte preservation, the verified recipe is:

```sh
cp -p ./file.txt ./file.new || exit 1
perl -e '$d=join("",<STDIN>); $n=($d =~ s/\Qbeta two\E/BETA changed/g); die "expected exactly one match\n" unless $n==1; print $d or die;' \
    < ./file.txt > ./file.new || exit 1
# Inspect or compare the candidate before committing it.
cp -p ./file.txt ./file.bak || exit 1
mv ./file.new ./file.txt || exit 1
```
Choose unused candidate/backup paths. The pre-copy preserves the ordinary owned file's permissions when its candidate is subsequently truncated and rewritten. The probe retained mode `0640` and an unchanged backup. A failed precondition leaves the original untouched; discard its incomplete candidate.

This filter accepts long lines, high bytes, and missing final LF without changing them incidentally. It is byte-oriented, not Unicode-aware. Enumerate directory targets first, then apply checked single-file operations; do not launch an unchecked recursive rewrite.

Replacing a directory entry with `mv` is not equivalent to modifying an inode in place. Decide how symlinks, hard links, ownership, and concurrent edits should be handled before generalizing this into an agent tool.

### `patch-text`: a quirky historical `diff` and `ed` workflow

**Examples:**

`diff -c old new` produces a context diff. `diff -u` was rejected. A `patch` executable was not found on the default path or in the inspected executable/source locations; ordinary unified-patch application is therefore not a verified primitive.

The verified native alternative is an `ed` script:

```sh
diff -e ./base.txt ./desired.txt > ./change.ed
rc=$?
case "$rc" in 0|1) ;; *) exit "$rc";; esac
```

Given a trusted, already-delivered `change.ed`, generated on the guest or elsewhere:

```sh
cmp -s ./target.txt ./expected-base.txt || exit 1
cp -p ./target.txt ./candidate.txt || exit 1
(cat ./change.ed; echo w; echo q) | ed - ./candidate.txt > ./ed.log 2>&1
cat ./ed.log
cmp -s ./candidate.txt ./expected-result.txt || exit 1
cp -p ./target.txt ./target.bak || exit 1
mv ./candidate.txt ./target.txt || exit 1
```

Both guest-generated `diff -e` output and a host-created `ed` patch were applied and byte-compared successfully. `diff -e` does not append a write command; the extra `w` and `q` are intentional.

**Limitations:**

An `ed` patch is positional and executable editor input, not a context-checked unified diff. Require the expected base, apply only trusted scripts, and verify the candidate. `ed` printed `?` but returned 0 on an invalid address. It also lost the unterminated final line in a read/write test. Use this workflow only for contract-compliant text.

For direct line edits, a script can contain `2c`, replacement lines, a line containing only `.`, then `w` and `q`. Apply it to a candidate, not immediately to the authoritative file. To consume ordinary unified patches, first add and verify a compatible patch implementation or regenerate the change as an `ed` script; this investigation installed neither.

### `edit-bin`: quick online edits to byte-mode files

**Examples:**
The following tested patch replaces bytes `7f80` at zero-based offset 2 with `5859`, preserving every other byte:

```sh
cp -p ./file.bin ./file.new || exit 1
perl -e 'binmode(STDIN); binmode(STDOUT); $d=join("",<STDIN>); $old=pack("H*","7f80"); die "preimage mismatch\n" unless substr($d,2,length($old)) eq $old; substr($d,2,length($old))=pack("H*","5859"); print $d or die;' \
    < ./file.bin > ./file.new || exit 1
wc -c ./file.bin ./file.new
cmp -l ./file.bin ./file.new
```
**Notes:**
For an equal-length patch, check equal total lengths and the intended differing offsets before replacing the original. The test reported differences only at one-based byte positions 3 and 4. `cmp -l` reports old/new byte values in octal and returns 1 when differences exist.

The same `substr` mechanism supports length changes. Replacing `ABC` with `HELLO` was verified as an insertion/expansion, and replacing it with `""` was verified as deletion. Validate the expected old bytes and expected resulting length. Use an anchored preimage check for insertion rather than an unguarded empty-string match.

This is also a practical binary-patch representation: record the zero-based offset, expected old bytes, and replacement bytes in hex, then apply a checked operation. It is not a standard binary-diff format or a format-aware executable patcher.

### `patch-bin`: incremental changes to large files

**Example:**

For a large, controlled file where a full rewrite is unsuitable, this literal-path example was verified:

```sh
cp -p ./file.bin ./file.bak || exit 1
perl -e 'open(F,"+<./file.bin") or die "$!\n"; binmode(F); seek(F,2,0) or die; $n=read(F,$b,2); die "preimage mismatch\n" unless defined($n) && $n==2 && $b eq pack("H*","7f80"); seek(F,2,0) or die; print F pack("H*","5859") or die; close(F) or die;'
```

**Limitations:**
Use only an explicitly selected pathname and equal-length replacement. This operation is not transactional; interruption can leave a partial edit. Keep the backup and verify afterward.

**Don't get lost: do not use modern `dd` overwrite recipes here.** `conv=notrunc` was rejected. Omitting it in a `seek=2` test truncated an 11-byte file to four bytes and replaced the prefix with zeroes. `dd` is useful for reads and new-file construction, not for the proposed safe in-place primitive.

### `script-sh`: save and run compound operations in `sh`

Again, this is for the supplied `sh`, not Perl.
Scripts may be prepared elsewhere or created directly on the guest.

**Examples:**

```sh
cat > ./task.sh <<'SCRIPT'
#!/bin/sh
umask 077
PROBE_MODE=guest
export PROBE_MODE
echo "argc=$#"
for arg in "$@"; do
    echo "<$arg>"
done
SCRIPT
sh -n ./task.sh || exit 1
chmod 700 ./task.sh || exit 1
./task.sh 'with space' plain
```

**Limitations and alternatives:**

`sh -n` accepted valid syntax and rejected an invalid `if` statement. The executable script preserved the argument containing a space. Edit scripts with the same staged text workflows as other files. Use explicit `command || exit 1` checks for mutations and inspect results rather than relying on a long unchecked command chain.

### Other standard Unix tools...

We make special notes (likely most readable to Unix gurus) about age-related gotchas.

| Tool | Example | Advanced notes/caveats |
|---|---|---|
| `awk` | `awk -F: '{print $1,$2}' file` | Attach the field separator to `-F`; short-line text only |
| `head` | `head -20 file` | Historical numeric option; not `-n 20` or `-c` |
| `tail` | `tail -20 file`; `tail +10 file` | Last N lines / from line N; `-Nc` and `+Nc` for bytes |
| `sort` | `sort -u file`; `sort +1 -2n file` | Zero-based old key positions; do not use `-k` |
| `sort` with delimiter | `sort -t: +1n file` | Verified numeric sort from the second colon-separated field |
| `uniq` | `sort file | uniq -c` | Only adjacent duplicates are grouped |
| `wc` | `wc -lc file`; `wc -c file` | Combine flags; `wc -l -c` selected only the final flag in the test. `-l` counts LF bytes |
| `diff` | `diff -c old new`; `diff -e old new` | Context display / `ed` script; no verified `-u` support |
| `cmp` | `cmp -s a b`; `cmp -l a b` | Byte equality / differing positions and octal byte values |
| `split` | `split -2 file part.` | Produced two-line chunks `part.aa`, `part.ab`, etc.; `-l` and `-b` failed |
| `tr` | `tr a-z A-Z`; `tr -d '\015'` | Byte transformations; deleting CR removes all CR bytes, not just CRLF endings |
| `tr` squeeze | `tr -s ' ' ' '` | Both sets were needed; the one-set modern-looking form did not squeeze |
| `tee` | `tee file`; `tee -a file` | Copy standard input to standard output and a file |
| `comm` | `comm -3 sorted1 sorted2` | Requires correspondingly sorted inputs |
| `join` | `join sorted1 sorted2` | Default first-field join verified on sorted inputs |
| `expand` / `unexpand` | `expand`; `unexpand -a` | Verified TAB/space conversion |
| `touch` | `touch file` | Creates an empty file if missing, otherwise updates timestamps |
| `cp` / `mv` | `cp -p original candidate`; `mv candidate target` | Basis of staged edits; choose unused candidate/backup paths |
| `uuencode` / `uudecode` | See binary-read section | Verified reversible binary-to-text representation |

**Not available:** `cut`, `paste`, `env`, `dirname`, `cksum`, `iconv`, `locale`, and `mktemp` were absent from the inspected path. `sum` was found, but no checksum-strength or cross-platform-format guarantee was established; use `cmp` when exact bytes are available on both sides.

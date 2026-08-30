
# The OPENSTEP 4.2 Unix environment: guest-side file and shell tasks

**About and scope:** See `GETTING-STARTED.md` for instructions about working with OPENSTEP remotely.

This documents various points about OPENSTEP 4.2 Unix environment in both:

- The  `sh` shell -- **run it manually**; the default
is often `csh`. Be careful: this is BSD `sh` as distributed with 4.2 BSD!

- Perl 5.001, which is a useful fallback.

**Subfolder: SKILL.** For a guide to specific tasks, see the subfolder `SKILLS`, representing specific tasks:  `ls`, `find-file`, `chmod`, `read`, `create`, `delete`, `grep`, `edit-text` and `patch-text`, `edit-bin` and `patch-bin`, and ``script-sh``.

***NB:**** the header names for the tools (e.g. `find-file`) aren't actual Unix tools, but concise "skill names" I've been using as personal notation.

**Note about age:** and, as we state in `GETTING-STARTED.md`: in general, this is Unix, but very far removed from modern Unices:

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

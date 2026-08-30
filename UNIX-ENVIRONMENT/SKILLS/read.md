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


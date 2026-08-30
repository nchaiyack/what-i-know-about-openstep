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


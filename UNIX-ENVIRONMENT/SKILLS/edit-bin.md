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


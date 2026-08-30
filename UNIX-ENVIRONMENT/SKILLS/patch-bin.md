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


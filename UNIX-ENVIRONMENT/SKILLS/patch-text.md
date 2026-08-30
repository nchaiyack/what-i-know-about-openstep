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


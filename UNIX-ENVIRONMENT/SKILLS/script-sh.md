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


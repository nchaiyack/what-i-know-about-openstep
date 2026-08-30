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


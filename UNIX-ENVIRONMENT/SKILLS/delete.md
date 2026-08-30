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


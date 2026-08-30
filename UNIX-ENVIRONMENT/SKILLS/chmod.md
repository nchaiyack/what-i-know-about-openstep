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


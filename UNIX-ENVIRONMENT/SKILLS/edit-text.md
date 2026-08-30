### `edit-text`: targeted text rewrites

**Examples**

For plain text, `sed` writes a new stream:

```sh
sed 's/old/new/g' < ./file.txt > ./candidate.txt
```

Never redirect output back onto the input filename: the shell truncates it before `sed` reads it. `sed -i` did not edit the file in place, even though its status was 0. Quote regexes; escape pattern/replacement metacharacters when they are meant literally.

For exact literal replacement with a precondition and byte preservation, the verified recipe is:

```sh
cp -p ./file.txt ./file.new || exit 1
perl -e '$d=join("",<STDIN>); $n=($d =~ s/\Qbeta two\E/BETA changed/g); die "expected exactly one match\n" unless $n==1; print $d or die;' \
    < ./file.txt > ./file.new || exit 1
# Inspect or compare the candidate before committing it.
cp -p ./file.txt ./file.bak || exit 1
mv ./file.new ./file.txt || exit 1
```
Choose unused candidate/backup paths. The pre-copy preserves the ordinary owned file's permissions when its candidate is subsequently truncated and rewritten. The probe retained mode `0640` and an unchanged backup. A failed precondition leaves the original untouched; discard its incomplete candidate.

This filter accepts long lines, high bytes, and missing final LF without changing them incidentally. It is byte-oriented, not Unicode-aware. Enumerate directory targets first, then apply checked single-file operations; do not launch an unchecked recursive rewrite.

Replacing a directory entry with `mv` is not equivalent to modifying an inode in place. Decide how symlinks, hard links, ownership, and concurrent edits should be handled before generalizing this into an agent tool.


# OPENSTEP 4.2 headless development guide

Section include a setup guide for humans ("**Humans: setting up...**");
then  **Credentials**, **Services exposed via port forwarding**
(Telnet and FTP), and a **Quick Unix shell workflow guide**.

## Humans: setting up...

1. On the guest:

	1. Configure `/etc/resolv.conf` with the desired DNS domain and name server.

	2. Configure OPENSTEP without NetInfo by following Chapter 11, “NEXTSTEP Computers in a Mixed Network,” in the System Administration manual. (See `/NextLibrary/Bookshelves`.)

	3. A default standalone server configuration should kick in, that serves via `inetd`. Reboot and verify that `inetd` exposes guest `telnetd` on `23/tcp` and guest `ftpd` on `21/tcp`; review `/etc/inetd.conf` if needed.
	
1. On the host:

	1. Forward guest port 23 to host `127.0.0.1:50023` and guest port 21 to host `127.0.0.1:50021`.

## Credentials

| Role | Username | Password | Notes |
|---|---|---|---|
| Working user | `me` | `roooot` | Home directory: `/me` |
| Superuser | `root` | `roooot` | From a `me` shell, use `su` |

## Services exposed via port forwarding

### Telnet

**Connection and initiation:** Connect to `telnetd` through `127.0.0.1:50023/tcp` with a PTY:

```console
TERM=xterm telnet -c -K 127.0.0.1 50023
```

Log in as `me`. Sudo only when required:

```console
openstep> su
Password:
openstep:1# whoami
root
```

**Exiting:** Exit the root shell and login shell separately. To escape a stuck client, type `Ctrl-]`, followed by `quit`.

**Shell environment:** The shell is `csh`. The login process emits terminal-control sequences and may clear the screen after authentication. Send one command at a time, wait for `openstep>` or the root prompt, and use `whoami` before deciding that a silent login failed. Large batches of newline-separated commands occasionally needed an extra newline before processing continued.

Useful commands include `whoami`, `hostinfo`, `pwd`, and `ps -ax`. Do not assume modern commands or options exist: `id`, `uname`, and `dmesg` were unavailable through the default path.

Telnet is suitable for builds, tests, and diagnostics. It is not a binary-safe transfer mechanism.

### FTP

Connection instructions first; requirements, tricks, and gotchas follow.

**Connection:** The `ftpd` control service is available at `127.0.0.1:50021/tcp`. Its verified banner is:

```text
220 openstep FTP server (Version 5.1 (NeXT 1.0) Tue Jan 26, 1999) ready.
```

Open a raw control connection with:

```console
nc 127.0.0.1 50021
```

Then authenticate and select binary mode:

```text
USER me
PASS roooot
TYPE I
```

The initial FTP directory is `/me`.

#### FTP gotcha: active-mode requirement

Only the FTP control port is forwarded. Passive mode advertises a guest-private address and an unforwarded data port, so clients can authenticate and then fail on `LIST`, `STOR`, or `RETR`.

Use active mode. The guest reaches the host as `10.0.2.2`. For host data port `P`, calculate:

```text
p1 = floor(P / 256)
p2 = P modulo 256
PORT 10,0,2,2,p1,p2
```

For example, port `42000` becomes `PORT 10,0,2,2,164,16`.

#### FTP task example: uploading a file

**Upload:** In host terminal 1, supply the local file:

```console
nc -l 42000 < local-file
```

In host terminal 2, open the FTP control connection and enter:

```text
USER me
PASS roooot
TYPE I
CWD destination-directory
PORT 10,0,2,2,164,16
STOR remote-file
QUIT
```

**Verification:** A successful transfer reports FTP statuses `200`, `150`, and `226`. Use a fresh unused high port and a new `PORT` command for each data operation.

**Capabilities:** `PWD`, `MKD`, `CWD`, and `STOR` were verified. Standard `DELE`, `RNFR`/`RNTO`, `RMD`, `LIST`, and `RETR` behavior is expected but has not yet been independently tested. `LIST` and `RETR` also require an active host listener.

**NB:** The raw `nc` session echoes `PASS`; do not publish its transcript. Verify important transfers with `wc -c`, `sum`, or another comparison on both sides.
	
## Quick Unix shell workflow guide

Refer to `GUEST-TOOLCHAIN.md` for detailed information on the Unix environment.

In general, this is Unix, but very far removed from modern Unices:

- **Standards:** OPENSTEP 4.2 provides a historical NeXT/Mach Unix environment with 4.3BSD-style commands and interfaces, plus documented POSIX.1 support for C applications through cc -posix and cc -posixstrict

- The working account uses csh, and the installed compiler is based on GCC 2.7.2.1. Target ANSI C89/C90 and consult the guest’s manuals before assuming command options, library APIs, or shell syntax.

### Workflow: editing and build loop

Keep the authoritative source tree on the host. For each iteration:

1. Edit the host source.
2. Upload changed files with FTP `STOR` in binary mode.
3. Build and run through Telnet.
4. Match compiler line numbers to the host source.
5. Fix the host source, upload again, and rebuild cleanly.

**NB about FTP:**  FTP updates are not atomic and provide neither synchronization nor conflict detection. Do not start a build until every required upload has completed, and keep the host copy authoritative.

**Toolchain:** The verified toolchain is `/bin/cc`, `/bin/make`, `/bin/as`, `/bin/ld`, `/bin/file`, and `/bin/nm`. The standalone `gcc` command is absent; `/bin/cc` is NeXT `cc-744.13`, based on GCC 2.7.2.1.

A suitable ANSI C command is:

```console
cc -ansi -pedantic -Wall -o hello hello.c
```

A normal feedback loop is:

```console
make clean
make
./hello
```
Successful executables are i386 Mach-O binaries. This version of `make` does not support `make -v` (print version).

# busybox-chroots

This script builds a small busybox-based chroot, useful
for compiling software that has a hard time with cross-compilation.

The arm/aarch64 chroots have `qemu-[arm|aarch64]-static` installed
under `/bin`, and these have been patched to allow intercepting execve calls
(so you don't need to change your `binfmt_misc` entries).

You should be able to run them with a command like:

```
chroot chroots/arm-linux-musleabihf /bin/qemu-arm-static -execve /bin/sh
```

See the releases tab for downloadable tarballs.

## Usage

```bash
./download
./build arm-linux-musleabihf
./build arm-linux-musleabi
./build aarch64-linux-musl
./build x86_64-linux-musl
./build i486-linux-musl
```

Tarballs will be in the `dist` directory.


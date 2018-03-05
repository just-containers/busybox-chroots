# busybox-chroots

This script builds a small busybox-based chroot, useful
for compiling software that has a hard time with cross-compilation.

See the releases tab for downloadable tarballs.

Some tips for running these chroots:

## Patched QEMU

See https://github.com/just-containers/qemu/releases - this is
a version of qemu with an additional "-execve" flag. You'll
be able to run this chroots like:

```
cp qemu-arm-static /path/to/chroot/bin/qemu-arm-static
chroot /path/to/chroot /bin/qemu-arm-static -execve /bin/sh
```

You'll likely still need root access for this to work, or
the right combination of fakeroot + fakechroot.

## PRoot + any QEMU

This has a few benefits:

* No root access
* No need to copy qemu into the chroot

Example:

```
proot -r /path/to/chroot -q qemu-arm-static -w / /bin/sh
```

Or better yet:

```
env - PATH=/usr/bin:/bin:/usr/sbin:/sbin \
  proot -S /path/to/chroot \
  -q qemu-arm-static \
  -w /
  /bin/sh
```

`proot -S` is similar to `-r`, but with binds to `/dev`, `/sys`, etc.

See https://github.com/just-containers/PRoot/releases for statically-compiled
binaries of proot.


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


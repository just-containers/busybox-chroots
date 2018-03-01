# busybox-chroots

This script builds a small busybox-based chroot, useful
for compiling software that has a hard time with cross-compilation.

The arm/aarch64 chroots have `/bin/sh` replaced with a static program
to load and run qemu (included in the chroot). This way you can just run
something like:

```
chroot /path/to/chroot /bin/sh
```

And everything should just work. No special kernel requirements needed!

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


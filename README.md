# busybox-chroots

This script builds a small busybox-based chroot, useful
for compiling software that has a hard time with cross-compilation.

See the releases tab for downloadable tarballs.

## Usage

```bash
docker build -t chroots .
docker create --name tmp chroots
docker cp tmp:/tmp/dist/chroot-x86_64.tar.gz ./
docker cp tmp:/tmp/dist/chroot-x86.tar.gz ./
docker cp tmp:/tmp/dist/chroot-arm.tar.gz ./
docker cp tmp:/tmp/dist/chroot-armhf.tar.gz ./
docker cp tmp:/tmp/dist/chroot-aarch64.tar.gz ./
docker rm tmp
docker rmi chroots
```

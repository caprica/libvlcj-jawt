# libvlcj-jawt

This component provides a shared library containing native functions used by
vlcj to access AWT native functions.

Only 64-bit Linux and 64-bit Windows are supported.

## Building

This project uses `Docker` to build native libraries for Linux and Windows.

```shell
./build.sh
```

This will compile the shared libraries and put them into the `build` directory.

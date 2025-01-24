# libvlcj-jawt

This component provides a bridge to native AWT functions used by vlcj.

Only 64-bit Linux and 64-bit Windows are supported.

## Building

This project uses `Docker` to build native libraries for Linux and Windows.

```shell
./build.sh
```

This will compile the shared libraries and put them into the `build` directory.

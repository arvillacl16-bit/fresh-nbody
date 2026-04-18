# FreshNBody

A WIP gravitational N-body simulator written in C++, which will support various different integrators. The code should be cross-platform.

## Dependencies

- C++17
- Meson
- OpenMP

## Building

Just run:

```sh
git clone https://github.com/arvillacl16-bit/fresh-nbody.git
cd fresh-nbody
meson setup builddir --buildtype=release -Dbuild-tests=false
meson compile -C builddir
```

Or if you want a static library:

```sh
git clone https://github.com/arvillacl16-bit/fresh-nbody.git
cd fresh-nbody
meson setup builddir --buildtype=release -Dbuild-tests=false -Ddefault_library=static
meson compile -C builddir
```

The shared library should be located at ./builddir/freshnbody.[so/dll/dylib] or static library at ./builddir/freshnbody.a. If you want to install the library system-wide, use:

```sh
meson install -C builddir
```

## Contributing

Because this project is linked to a YouTube video series, pull requests will be reviewed on video. You are free to make issues or suggestions, though.

## License

This uses an LGPL 3.0 license.


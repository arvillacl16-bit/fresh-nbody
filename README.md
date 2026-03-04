# FreshNBody

A WIP N-body simulator written in C++.

## Dependencies

- C++17
- Meson

## Building

Just run:

```sh
git clone https://github.com/arvillacl16-bit/fresh-nbody.git
cd fresh-nbody
meson setup builddir --buildtype=release
meson compile -C builddir
```

The static library should be located at ./builddir/freshnbody.a. If you want to install the library system-wide, use:

```sh
meson install -C builddir
```

## Contributing

Because this project is linked to a youtube video series, I will not accept pull requests.

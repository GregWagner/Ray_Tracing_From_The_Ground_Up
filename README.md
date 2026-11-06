# Ray Tracing from the Ground Up

C++17 ray tracer based on "Ray Tracing from the Ground Up" (Kevin Suffern).
wxWidgets 3.2 (GTK3) GUI.

## Build

Requires CMake 3.16+, a C++17 compiler (GCC 9+ or Clang 9+), and wxWidgets 3.2+.

```sh
cmake -S . -B build
cmake --build build
```

The executable lands at `build/wxraytracer`.

CMake presets are provided for common workflows:

```sh
cmake --preset default && cmake --build --preset default
cmake --preset clang    && cmake --build --preset clang
cmake --preset tidy     && cmake --build --preset tidy      # enables clang-tidy
cmake --preset sanitize && cmake --build --preset sanitize  # ASan/UBSan
```

## Run

```sh
./build/wxraytracer
```

Then start rendering from the Render menu.

## Development

- Format code: `cmake --build build --target format`
- Check formatting: `cmake --build build --target check-format`
- Enable clang-tidy during build: `-DENABLE_CLANG_TIDY=ON` (or the `tidy` preset)
- Enable sanitizers: `-DENABLE_SANITIZERS=ON` (or the `sanitize` preset)

## Conventions

- Headers live in `include/`, sources in `src/`.
- Headers use `#ifndef __NAME__` guards and are included by bare module name.
- `World` owns objects/lights through raw pointers and frees them in its destructor.

## Notes

- Do not compile `src/main.cpp` (unused stub) or anything under `src/build/`.
- `BuildShadedObjects.cpp` is meant to be `#include`d into `World.cpp`, not compiled standalone.
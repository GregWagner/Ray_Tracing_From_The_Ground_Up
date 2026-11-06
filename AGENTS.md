# AGENTS.md

## Project

C++17 ray tracer based on "Ray Tracing from the Ground Up" (Kevin Suffern). Qt6 Widgets GUI. No tests or CI in this checkout.

## Build

Use CMake (Qt6 is found via its CMake config package):

```sh
cmake -S . -B build
cmake --build build
```

Executable lands at `build/qtraytracer`. Do not compile `src/main.cpp` (unused stub) or anything under `src/build/`.

The legacy Makefile and prebuilt `bin/qtraytracer` have been removed; CMake is the only supported build.

## Run

`./build/qtraytracer`, then start rendering from the Render menu.

## Architecture

- Entry point is `src/UserInterface/qtraytracer.cpp` (`main` / Qt application); `src/main.cpp` has been removed.
- `RenderCanvas::renderStart()` creates the `World`, but `w->build()` is commented out (TODO), and `World.cpp`'s `#include "BuildShadedObjects.cpp"` is also commented out. As a result `tracer_ptr`/`camera_ptr` stay null and rendering crashes until the builder is wired back in. The scene builder is `src/build/BuildShadedObjects.cpp` (`World::build()`).
- Rendering runs in `RenderThread::Entry()` via `world->camera_ptr->render_scene(*world)`; pixels go back to the canvas through `setPixel`.
- `World::render_scene()` is a legacy orthographic path; the active path is `Pinhole::render_scene()`.
- `World::paintArea` (a `RenderThread*`) bridges `World::display_pixel` to the GUI.
- use doubles for all ray- object intersection calculations, where numerical accuracy is critical, and floats for shading calculations. This involves storing geometric object data members, and the components of all the utility classes as doubles.

## Conventions

- Headers use `#ifndef __NAME__` guards and are included by bare module name (e.g. `"World.hpp"`); include dirs are per-module.
- `World` owns objects/lights through raw pointers and frees them in its destructor; materials are owned by objects.
- Floats for view-plane geometry, doubles for math constants (`Constants.hpp`).

## Gotchas

- `BuildShadedObjects.cpp` is meant to be `#include`d into `World.cpp` when enabled, not compiled on its own.
- `src/build/` is not part of `CMakeLists.txt` sources.
- Qt6 widgets flags come from the Qt6 CMake config package; do not hand-write them.

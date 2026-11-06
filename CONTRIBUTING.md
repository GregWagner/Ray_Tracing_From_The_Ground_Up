# Contributing

Thank you for contributing to this ray tracer. This project uses C++17, CMake, and Qt6 Widgets.

## Development Setup

```sh
cmake -S . -B build
cmake --build build
```

For sanitizers:

```sh
cmake --preset sanitize
cmake --build --preset sanitize
```

## Before Submitting a Change

- Build successfully with the default preset.
- Run tests:

  ```sh
  ctest --test-dir build --output-on-failure
  ```

- Keep formatting compliant:

  ```sh
  cmake --build build --target check-format
  ```

- Ensure new or changed code compiles cleanly with strict warnings.
- Update `AGENTS.md`, `README.md`, or `TODO.txt` when architecture or tooling changes.

## Coding Guidelines

- Use C++17 and follow the existing include guards, naming, and ownership conventions.
- `World` owns objects, lights, tracers, cameras, and ambient lights through raw
  pointers unless explicitly changed to smart pointers. Document ownership transfers.
- Materials are owned by geometric objects; `ShadeRec::material_ptr` is non-owning.
- Use `double` for ray/object intersection calculations and `float` for shading and
  view-plane geometry.
- Avoid changing public APIs without updating tests and callers.
- Do not commit build directories or generated CMake artifacts.

## Pull Requests

- Keep changes focused and minimal.
- Add tests for behavior changes where possible.
- Describe the rendering, memory-ownership, or GUI impact of the change.
- Note any sanitizer or Qt platform oddities relevant to reviewers.
EOF
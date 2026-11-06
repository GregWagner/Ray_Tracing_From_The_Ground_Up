## Summary

Describe the change and its motivation.

## Changes

- 

## Testing

- [ ] `cmake -S . -B build && cmake --build build`
- [ ] `ctest --test-dir build --output-on-failure`
- [ ] Sanitizer build tested (`cmake --preset sanitize`)
- [ ] Formatting checked (`cmake --build build --target check-format`)

## Memory / Ownership Impact

Describe any changed raw-pointer ownership, leaks, renderer lifetime, or GUI thread behavior.

## Notes

Add screenshots, rendered images, sanitizer output, or follow-up work.
EOF
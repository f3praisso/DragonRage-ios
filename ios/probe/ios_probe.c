#include <stdint.h>

// Compile-only smoke test. This does not link an app or validate BT3 runtime behavior.
uint64_t dragonrage_ios_arm64_probe(uint64_t value) {
    return (value ^ UINT64_C(0x445241474f4e)) + UINT64_C(1);
}

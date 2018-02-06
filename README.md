# libOpencastIngest

A library to ease communication with the Opencast ingest REST-endpoint


### Requirements:

- cmake
- C++ Compiler (C++11)
- libcurl (7.47.1 compatible) (with cmake modules)
- tinyxml2 (5.0.1 compatible) (with cmake modules)


### How to build:
On Linux you can install the dependencies with your package manager, on Windows you can install them from source with the cmake install target `install`.

Go into the source dir and execute the following commands:
```bash
mkdir build
cd build/
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

Warning (Windows): You can only have one version of the dependencies (32/64-bit) installed, so if you want to build 32 and 64-bit versions you have to remove the other version of the dependency first.

### How to use:
1. Include `src/libOpencastIngest.{h,hpp}` into your project
2. Link your project against the shared or static library
3. Dynamic linking only: define `LIBOPENCASTINGEST_AS_DYNAMIC_LIB`
4. Static linking only: Link your project against tinyxml2
5. Static linking only: Link your project against libcurl

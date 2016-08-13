Some C++ datastructures that would be handy for building map generators.

The map grid is modelled as a `Graph` (with a fixed number of nodes), and everything else is done by means of `TotalField<T>`s which assign a value to every node (e.g. elevation, water flux, etc).
The node's (x, y) position can also be laid out as a field with coordinate pairs as its values.
There's also a `PartialField<T>` which only assign values to some nodes (might be handy for e.g. settlement locations).

Currently completely undocumented, but the [integration test](tests/test_integration.cpp) should demonstrate the principle.

# Building

```
cmake .
make
make test
```

The project is set up to emit a static library, you can probably hack a shared library out of it if you really need one.

# Requirements

* C++11 compiler
* [CMake](https://cmake.org/)
* [Doxygen](http://doxygen.org/) (for building documentation)

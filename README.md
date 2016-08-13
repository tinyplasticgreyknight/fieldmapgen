Some C++ datastructures that would be handy for building map generators.

The map grid is modelled as a [`Graph`](include/graph.hpp) (with a fixed number of nodes), and everything else is done by means of [`IField<T>`](include/field.hpp) instances which assign values to the graph's nodes.

The simplest form is the [`TotalField<T>`](include/total_field.hpp), which assign a value to every single node (e.g. elevation, water flux, etc).  The node's (x, y) position can also be laid out as a field with coordinate pairs as its values.

There's also a [`PartialField<T>`](include/partial_field.hpp) which only assign values to some nodes (might be handy for e.g. settlement locations).  This uses efficient storage so that nodes with no values don't take up space in memory.

See the [integration test](tests/test_integration.cpp) for a demonstration of the principle.

# Building

To build and run tests:

    cmake .
    make
    make test

To build documentation:

    doxygen

The project is set up to emit a static library, you can probably hack a shared library out of it if you really need one.

# Requirements

* C++11 compiler
* [CMake](https://cmake.org/)
* [Doxygen](http://doxygen.org/) (for building documentation)

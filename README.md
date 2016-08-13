Some C++ datastructures that would be handy for building map generators.

# Overview

## Grid
The map grid is modelled as a [`Grid`](include/grid.hpp), which consists of a fundamental [`Graph`](include/graph.hpp) (with a fixed number of nodes), and a [`IField`](include/field.hpp)`<`[`Point2D`](include/point2d.hpp)`>` which assigns a two-dimensional coordinate to each node.  The `Grid` class contains named constructors which you can use to build a grid with a particular geometry, and with neighbouring nodes already linked in the `Graph`.  You can also modify the coordinates and node links after construction.

## Fields
In addition to the `IField<Point2D>`, you can also build other `IField<T>` instances on your `Graph`.  The [`FieldFactory`](include/field_factory.hpp) class has a number of methods to make this easy.

The simplest form is the [`TotalField<T>`](include/total_field.hpp), which assign a value to every single node (e.g. elevation, water flux, etc).

There's also a [`PartialField<T>`](include/partial_field.hpp) which only assign values to some nodes (might be handy for e.g. settlement locations).  This uses efficient storage so that nodes with no values don't take up space in memory.

## Samples
See the [integration test](tests/test_integration.cpp) for a demonstration of the principle.

# Building

To build and run tests:

    cmake .
    make
    make test

To build documentation:

    doxygen

The project is set up to emit a static library, you can probably hack a shared library out of it if you really need one.

## Requirements

* C++11 compiler
* [CMake](https://cmake.org/)
* [Doxygen](http://doxygen.org/) (for building documentation)

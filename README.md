# Overview

A C++ implementation of an interpreter for the A++ Programming Language (variant of [Delta](https://projects.ics.forth.gr/hci/files/plang/Delta/Delta.html)). 
Developed as the main project of the graduate course ["Advanced Topics in Programming Language Development"](https://www.csd.uoc.gr/~hy540/description.html) (Department of Computer Science, University of Crete), by [Emmanouil Giortamis](https://github.com/manosgior), [Anastasios Livanidis](https://github.com/AlivasGR) and [Georgios Lydakis](https://github.com/geomlyd).

The project showcases metaprogramming capabilities including runtime code modifications and dynamic execution of code strings, along with a functional visual debugger that supports breakpoints and dynamic code/variable inspection.

# Notable language features

The A++ language is a variant of the [Delta programming language](https://projects.ics.forth.gr/hci/files/plang/Delta/Delta.html), developed in ICS-FORTH.
The syntax is in general similar to Javascript, with the addition of **metaprogramming** features that allow dynamic changes to the code being executed.
The following metaprogramming features are available:

- `eval("string")`: parses and executes strings as code.
- `<<expr>>` (quasi-quotes): returns the enclosed expression as a syntax tree.
    - `~expr` (escape): evaluates the expression normally and inserts its value in the syntax tree.
    Only usable inside within quasi-quotes.
    - `!(syntax_tree)` (inline): executes a syntax tree (usually created with quasi-quotes).
- `@("string")` (compile string): parses a string into a syntax tree.
Similar to eval, except for the fact that the code is not immediately executed.
- `#(syntax_tree)` (unparse): converts a syntax tree to source code.
Useful for debugging meta-programs by showing the generated code.

The `metaprogrammingTests` directory contains several examples for these features: each `.asc` file contains A++ code, and the corresponding `.res` file contains the expected output of the program.

# Installation

You'll need the gtkmm3 library in order to use the visual debugger.
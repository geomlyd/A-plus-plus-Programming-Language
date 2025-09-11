# Overview

A C++ implementation of an interpreter for the A++ Programming Language (variant of [Delta](https://projects.ics.forth.gr/hci/files/plang/Delta/Delta.html)). 
Developed as the main project of the graduate course ["Advanced Topics in Programming Language Development"](https://www.csd.uoc.gr/~hy540/description.html) (Department of Computer Science, University of Crete), by [Emmanouil Giortamis](https://github.com/manosgior), [Anastasios Livanidis](https://github.com/AlivasGR) and [Georgios Lydakis](https://github.com/geomlyd).

The project showcases metaprogramming capabilities including runtime code modifications and dynamic execution of code strings, along with a functional visual debugger that supports breakpoints and dynamic code/variable inspection.

# Notable language features

The A++ language is a variant of the [Delta programming language](https://projects.ics.forth.gr/hci/files/plang/Delta/Delta.html), developed in ICS-FORTH.
The syntax is in general similar to Javascript, with the addition of **metaprogramming** features that allow dynamic changes to the code being executed.
The following metaprogramming features are available:

- `eval("string")`: parses and executes strings as code.

    Example:

    ```
    eval("print(2 + 3);");
    ```

    Prints 5.
- `<<expr>>` (quasi-quotes): returns the enclosed expression as a syntax tree.

    Example: 

    ```
    tree = <<x = 1; y = 2; print(x + y);>>;
    ``` 
    
    Produces a syntax tree whose execution would assign the variables `x`, `y` and print "3".
- `~(expr)` (escape): evaluates the expression normally and inserts its value in the syntax tree.

    Example: if `z = 9` then:
    
    ```
    tree = <<x = ~(sqrt(z)); y = 2; print(x + y);>>;
    ``` 
    
    returns a syntax tree whose execution would assign the variables `x`, `y` and print "5".
    Only usable inside inside quasi-quotes.
- `!(syntax_tree)` (inline): executes a syntax tree (usually created with quasi-quotes).
    Any of the two example trees from above can be executed by `!(tree)`.
- `@("string")` (compile string): parses a string into a syntax tree.
    Similar to eval, except for the fact that the code is not immediately executed..

    Example:

    ```
    tree = @("print(2 + 3);");
    !(tree);
    ```

    Prints 5, i.e., has the same effect as `eval("print(2 + 3);")`.
- `#(syntax_tree)` (unparse): converts a syntax tree to source code.

    Example:
    ```
    z = <<x = 1; y = 2; print(x + y);>>;
    w = #(z);
    ``` 

    `w` is assigned the string `"x = 1;\n y = 2\n; print(x + y);"`.
Useful for debugging meta-programs by showing the generated code.

The `metaprogrammingTests` directory contains several examples for these features: each `.asc` file contains A++ code, and the corresponding `.res` file contains the expected output of the program.

# Installation & usage

You'll need the gtkmm3 library in order to use the visual debugger.
Installation instructions can be found [here](https://gtkmm.gnome.org/en/download.html).

After installing gktmm3, from the project root, run 
```bash
make -C src release
```
This will create a directory named `build` next to `src`, containing three executables:
- `app.out <sourceFile>`: the A++ interpreter.
- `appGUIDebug.out <sourceFile>`: the visual debugger for A++.
- `appCLIDebug.out <sourceFile>`: a simple CLI debugger; functional but less refined than the visual debugger.

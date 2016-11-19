# Json
A C++ JSON Library

##What is JSON?##
JSON (JavaScript Object Notation) is a lightweight open-standard that uses human readable cleartext to transmit data. It is one of the few format that is both human and machine readable. It is based on a subset of the JavaScript Programming Language, Standard ECMA-262 3rd Edition - December 1999. JSON gained its popularity where other competiting standards lost (less verbose, less overhead in parsing and generation, easy to read).
Today JSON is the primary choice for

1. AJAX, largely replacing XML for asyncronous communiction
2. NOSQL, where the Key-Value attributes pair can easily make the data scalable across both dimension
3. For Data Serialization

## Why another JSON Library?
The current implementation uses templates and recursive pattern and polymorphism to create an hierarchial structure that has the minimal footprint with high performance. Moreover, the entire structure is iterable enabling easy integration with the existing C++ Design patterns. The JSON generator can be created statically or dynamically. JSON Objects and Arrays can be subscripted, the syntax of which is not alien to a C++ Developer. Moreover, the implementation is C++11 compliant making it more secure (no explicite memory management, no buffer overrun, no type mismatch). The Code has been remediated for any code issues by distilling through Static Analyzer guranteeing that the code would not add any warnings in your existing project.

## Design Pattern


Intuitive syntax. JSON and JSON elements gives a feeling of first class data.  

Trivial integration. Our whole code consists of a single header file json.hpp. That's it. No library, no subproject, no dependencies, no complex build system. The class is written in vanilla C++11. All in all, everything should require no adjustment of your compiler flags or project settings.

Serious testing. Our class is heavily unit-tested and covers 100% of the code, including all exceptional behavior. Furthermore, we checked with Valgrind that there are no memory leaks. To maintain high quality, the project is following the Core Infrastructure Initiative (CII) best practices.

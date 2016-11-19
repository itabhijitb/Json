# Json
A C++ JSON Library

What is JSON?##
JSON (JavaScript Object Notation) is a lightweight open-standard that uses human readable cleartext to transmit data. It is one of the few format that is both human and machine readable. It is based on a subset of the JavaScript Programming Language, Standard ECMA-262 3rd Edition - December 1999. JSON gained its popularity where other competiting standards lost (less verbose, less overhead in parsing and generation, easy to read).
Today JSON is the primary choice for

1. AJAX, largely replacing XML for asyncronous communiction
2. NOSQL, where the Key-Value attributes pair can easily make the data scalable across both dimension
3. For Data Serialization

Why another JSON Library?
The current implementation uses templates and recursive pattern and polymorphism to create an hierarchial structure that has the minimal footprint with high performance. Moreover, the entire structure is iterable enabling easy integration with the existing C++ Design patterns. The JSON generator 

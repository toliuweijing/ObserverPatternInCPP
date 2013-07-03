ObserverPatternInCPP
====================
Goals:
  1. no inheritance needed for observers and subjects.
  2. provide a uniform interface with sufficient flexibility on parameter types.
  3. no RTTI needed for casting parameters.
  
Details:
  C++ is known as the only "native" language that also provides great levels of abstractions. Observer pattern
  in C++ used to be implemented in multiple inheritances, which introduced lots of problems(name collisions and 
  diamond relations of inheritance). Moveover, according to Wiki, some languages use RTTI to down-cast parameters,
  which should be avoided in C++.
  
Usage: see file tester.cpp

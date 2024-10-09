# C++ Botan-3 library

Botan-3 is a C++ cryptography library.

This directory contains the Botan-3 shared objects and header files. The purpose is to easily put them in a Docker container.

# Usual placements

1. Header files: /usr/local/include/botan-3/
- botan/\*.h
2. Libraries: /usr/local/lib/
- libbotan-3.a
- libbotan-3.so -> libbotan-3.so.5.5.0
- libbotan-3.so.5 -> libbotan-3.so.5.5.0
- libbotan-3.so.5.5.0

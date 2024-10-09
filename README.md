# C++ Botan SHA-3 hashing application

This directory contains a C++-based program that uses the Botan-3 cryptography library for hashing a given input.
The hashing algorithm of choice is SHA-3.



## Usage

The application looks in the same directory as the executable for an input file called `input.in`.

It will then output the hash of the data from the input file into another filled called `output.out`, in the same directory.



## File contents

- `README.md` - Markdown documentation file about the application.
- `main.cpp` - Main C++ application code.
- `Dockerfile` - Steps for making a minimized Docker image for the application. *'Minimized' in this context means that only the files necessary for running the application (mostly the library files), are present on an empty Linux filesystem.*
- `Kraftfile` - Unikraft configuration file for building an unikernel of the application.
- `urunc.json` - JSON file with some urunc labels necessary for making an Unikernel image runnable with urunc.
- `Dockerfile_urunc` - Docker instructions for making a Docker image for the application. The image is runnable as an unikernel by Kubernetes (K3s) or nerdctl, with urunc.
- `app/` - Directory with Botan-3 headers and compiled libraries. Can only be used on Linux. *Since Botan-3 can be configured and compiled differently, these are the files used when compiling the application, or when making the Docker images.*



## Run and Use

1. Create a file called `input.in`, in the same folder as the executable.
2. Add the data you would like to be hashed, in the `input.in` file.
3. Run the application.
4. The hash will be put in a new file called `output.out`, in the same folder as the executable. It is in binary format.

Throughout the execution, there are messages printed to stdout, to log the application state as it runs.





## Local profile

The subsections below detail the building and running of the application, directly on the local machine.
If you want the details for running as an unikernel, scroll down to the Docker profile section.


### Building requirements

The local running and building environment is a virtual machine, running Ubuntu server 22.04.

In order to build the application and run it on the local machine, you will need:
- g++ (with support for c++20 standard)
- Botan-3 library (In case you do not want to use the `app/` version of it)


### Building commands

If you want to build the application on the local machine and run it locally, you can compile it with this command:
```
# Do not forget to configure ld to find the botan-3 libraries!
# If you compiled your own Botan-3 library, modify the -I argument with the new headers path.
g++ -std=c++20 -o hashing main.cpp -Iapp/ -lbotan-3
```





## Docker profile

The subsections below detail the building and running of the application as a unikernel, running in a docker (kubernetes or nerdctl) environment.


### Building requirements

In order to obtain a Docker image, capable to run as an unikernel with urunc, you will need the following applications:
- Botan-3 library (In case you do not want to use the `app/` version of it)
- Docker engine
- urunc (version 0.3.0-851848e was used in this case, urunc built from main branch, 2 October 2024, after commits)
- Unikraft (version 0.17.0) with a buildkit container running. Unikraft must be configured to use the buildkit container.
- Kraft kit (kraft 0.9.2 (b7229cd89331f610819b7741490fad0358330947))
- Golang (go1.22.3 2024-08-21T10:24:44Z)
- For running the Docker image, use k3s or nerdctl, either of them configured with urunc (scroll down to 'Running environment' section).


### Building commands

If you want to build the application as a Docker image, you must follow those steps:
```
# 1. Build with kraft
kraft build --arch x86_64 --plat qemu

# 2. Build the docker image with the steps from Dockerfile_urunc
docker build -f Dockerfile_urunc -t hashing-test:latest .
```


### Running environment

You must set up k3s or nerdctl, configured with urunc.

Follow the comments here, for instructions:
- https://github.com/nubificus/urunc/issues/52#issuecomment-2373953356
- https://github.com/nubificus/urunc/issues/52#issuecomment-2377173643

Afterwards, start a kubernetes job with the Docker image, or use nerdctl to start it.

**WARNING: You need to mount the `input.in` and `output.out` files to the unikernel image, when using k3s or nerdctl.**


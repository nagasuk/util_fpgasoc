util\_fpgasoc (Utilities to control FPGA fabric)
================================================

Overview
--------
This is utility set to control FPGA fabric of FPGA SoC (e.g. Cyclone V SoC).

How to build
------------
```sh
$ cmake -S . -B build
$ cmake --build build
```

How to install
--------------
```sh
$ cmake --install build --prefix <Path to install>
```

Requirement
-----------
* cmake
* boost program\_options
* drvfpgasoc
* libfpgasoc

License
-------
Please see `LICENSE.md` file for details.


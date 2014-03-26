# Master thesis

This repository contains all the code and the results of my Master Thesis "Iterative Sparse Matrix partitioning", written under the supervision of prof. Rob H. Bisseling at Utrecht University, The Netherlands. The actual implementation is found in the `iter_partitioning` folder.

### General information
The material consists of MATLAB and C implementations of the various algorithm designed.

### Building the project

Giving `make` in the root directory builds both Mondriaan (the svn version) and the actual project. Specific Makefiles are provided also in sub-directories.

To clean up, `make clean` is sufficient.

### Dependencies
The software contains everything needed to reproduce the final results of the thesis. 

It is written to run on top of the [Mondriaan](http://www.staff.science.uu.nl/~bisse101/Mondriaan/) software partitioner. In the root folder there are two different versions of Mondriaan used during development: 3.11 and the SVN version from June 2013, which can be considered a sort of 4beta.

Moreover, there is the `patoh` folder which contains version 3.2 of the [PaToH](http://bmi.osu.edu/~umit/software.html) (Partitioning Tool for Hypergraphs) and it is used by Mondriaan instead of the internal engine if the user decides so.

### Structure

* The folders `Mondriaan3.11`, `Mondriaan4RC` and `patoh` contain the needed software to run the code.

* The folder `iter_partitioning` contains the actual files written for the thesis. It is subdivided in
    * `hot_restart`, the material of Section 2.4
    * `localview`, the material of Section 2.1
    * `other_approaches`, the material of the remainder of Chapter 2
    * `utils`, miscellaneous utilities for C or Matlab (function to manage matrices, or to produce some kind of visualization in Matlab, etc.)
    * various files which act more like wrappers and are used to combine all the pieces of the thesis
 
* The folder `logs` which contains all the numerical results. The subfolder `old_logs` contains various logfiles used during development and not accurate anymore, but still kept around for documenting the process.

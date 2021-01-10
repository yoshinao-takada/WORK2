# Overview
## Components
* base : basic data structures, macros, and their related functions
* math : mathematical functions, e.g. linear algebra, non-linear optimization
* 1D : 1-dimensional signal processing for electronics and finance
* 2-3D : 2D, 3D signal processing, e.g. imaging and computational geometry
* text : json, xml, CSV, unformated text
* binutl : binary utilities for ELF, ASM, C, MUC debugging, etc.
* comm_usci : communication library for USCI functions targeting UART, I2C, and SPI

## base
### base
* BLbase.h : macro and type definitions which are commonly used across the library
* BLsv.h : type declarations and related macros for short number vectors
* BLmat.h : type declarations and related macros for small matrices
* BLmat.c : linear math for small matrices and short vectors
* BLts.h/.cpp : funtions and macros for timespec manipulation
* BLthread.h/.c : threading and synchronization
* BLprocess.h/.c : unix process I/F
* BLfile.h/.c : file utils
* BLfsm.h/.c : finite state machine base class implemented with C struct
* BLerr.h : Error codes extending errno.h
### baseUT
* mat.c
* thread.c
* process.c
* futils.c
* fsm.c
## math
### math
### mathUT
## 1D
### 1D
### 1DUT
## 2-3D
### 2-3D
### 2-3DUT
## text
### text
### textUT
## binutl
### binutl
### binutlUT
## comm
### comm
* BLuart.h
* BLi2c.h
* BLsock.h
### comm
* BLuart.h
* BLi2c.h
* BLsock.h

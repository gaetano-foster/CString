@echo off

set "RM=del"
set "CC=gcc"
set "CFLAGS=-Wall -O3 -std=c11"
set "SOURCE=src/cstring.c src/allocator.c"
set "INCLUDE=-I./src/ -I./include/"
set "OBJECT=cstring.o allocator.o"
set "BINPATH=bin/"
set "PROGNAME=libcstr.a"

%CC% -c %SOURCE% %CFLAGS% %INCLUDE%
ar -rc %BINPATH%%PROGNAME% %OBJECT%
ranlib %BINPATH%%PROGNAME%
%RM% %OBJECT%

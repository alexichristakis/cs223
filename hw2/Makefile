# Any line that starts with a sharp is a comment and is ignored
# by Make.

# These lines set variables that control make's default rules.
# We STRONGLY recommend putting "-Wall -pedantic -g3" in your CFLAGS.
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

# The next line is a dependency line.
# It says that if somebody types "make all"
# make must first make "hello-world".
# By default the left-hand-side of the first dependency is what you
# get if you just type "make" with no arguments.
all: transpose
	 modulo

# Command lines can do more than just build things.  For example,
# "make test" will rebuild hello-world (if necessary) and then run it.
test: transpose
	  modulo
	./transpose
	./modulo

# This lets you type "make clean" and get rid of anything you can
# rebuild.  The $(RM) variable is predefined to "rm -f"
clean:
	$(RM) transpose *.o
# Define the C compiler to use
CC=gcc

# Define any compile-time flags
CFLAGS=-Wall -g  # -Wall: Enable all warning messages, -g: Add debugging information

# 'all' is the default target. It's customary to have it as the first target.
# This target will be executed when you just type 'make' in the terminal.
all: CS470_RR CS470_SJF

# Rule to compile CS470_RR.c into CS470_RR.o
CS470_RR: CS470_RR.c
	$(CC) $(CFLAGS) -o CS470_RR CS470_RR.c

# Rule to compile CS470_SJF.c into CS470_SJF.o
CS470_SJF: CS470_SJF.c
	$(CC) $(CFLAGS) -o CS470_SJF CS470_SJF.c

# Clean rule to remove generated files
clean:
	rm -f CS470_RR CS470_SJF

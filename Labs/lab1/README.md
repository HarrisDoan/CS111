## UID: 605317270
## Harris Doan

## Pipe Up

One sentence description:
Create a C file that replicates the functionality of the built in terminal '|'. Where terminal commands such as ls | cat | wc can be rewritten as ./pipe ls cat wc and they would produce the same results.

## Building

Explain briefly how to build your program:

To build the program, assuming you already have the pipe.c file and Makefile, you run the command 'make' which creates the executable file from pipe.c. Now with the executable made you can use ./pipe as if it was any other normal terminal pipe command. Now instead of writing your commands followed by pipes, you just write ./pipe <all-your-commands-here>.

## Running

Show an example run of your program, using at least two additional arguments, and what to expect:

Example from spec:
./pipe ls cat wc
    7   7   63

ls | cat | wc
    7   7   63

My example with two additional arguments:

./pipe ls cat wc sort wc
    1   3   24

1.) ls: Lists the contents of the current directory.
2.) cat: Takes the output of ls (the list of files) and outputs it unchanged (since cat simply concatenates and displays file content).
3.) wc: Takes the output of cat and provides a count of lines, words, and bytes.
4.) sort: Tries to sort the output of wc, which is a bit unusual because wc output is typically a single line of three numbers (line count, word count, byte count). As sort is expecting text to sort line by line, its input from wc won't be meaningful for sorting purposes.
5.) wc (again): Takes the sorted output and gives a count of lines, words, and bytes.



## Cleaning up

Explain briefly how to clean up all binary files:

Run 'make clean' and that will clean all the binary files created by our original 'make'.

# Hey! I'm Filing Here

In this lab, I successfully implemented the following TODO:

I successfully developed a functional example of a "file system" structured with a root directory. This directory includes a file titled "hello-world" that contains the text "hello world", and a symbolic link named "hello" that references the "hello-world" file. Additionally, I configured the inode bitmap, allocated the block bitmap, populated the inode table, and completed the details of the superblock within this directory setup.

## Building

TODO

To build the lab, simply run the command "make" after unzipping the tar.

## Running

TODO

To run this, run the command "./ex2-create"

To interact with the file system you can do:

"mkdir mnt"
"sudo mount -o loop cs111-base.img mnt"

Then finally, to test the file system:

"python -m unittest"

Result:

..
---------------------------------------------
Ran 2 tests in 1.008s

OK

## Cleaning up

TODO

To clean it all up. First you need to unmount from the directory its mounted to. Here its called "mnt."

"sudo unmoubnt mnt"
"rmdir mnt"

Then you're good. To remove all files created during the make process, you can run "make clean"

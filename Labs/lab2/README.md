# You Spin Me Round Robin

Name: Harris Doan
UID: 605317270

This laboratory exercise aimed to replicate the behavior of a round-robin scheduler, akin to those utilized by operating systems for standard application management. Through the implementation of a simulated 'clock' mechanism, we mimicked the process of task preemption, with the clock advancing incrementally with each cycle. Task switching was enacted upon reaching a predetermined quantum time, which was input as an argument. Furthermore, we employed a queue to manage the tasks, organizing them according to their time of arrival and, in cases where multiple tasks arrived simultaneously, by their process identification numbers also known as their PIDs

TODO

## Building

```shell
TODO
```

When it comes to building the lab, you just run the command 'make'. This forms the executable ./rr file and lets you run it via the terminal.

## Running

cmd for running TODO
```shell
TODO
```

when you want to run it after creating the executable. you do:

./rr file_name.txt quantum_size

file_name.txt -> being some file with .txt extension
quantum_size -> some value int

our example:
./rr processes.txt 3

results TODO
```shell
TODO

```

When checking for validity, you can run:

python -m unittest and it will run the test python file. The results I got were:

..

----------------------------------------------------------------------

Ran 2 tests in 0.184s
OK



## Cleaning up

```shell
TODO
```

To clean up simply run 'make clean' :)

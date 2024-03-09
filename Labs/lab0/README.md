# A Kernel Seedling
TODO: intro
I began by unzipping the lab0.zip. I then 
-> scp -r /Users/harrisdoan/CS111/lab0 harris@lnxsrv07.seas.ucla.edu:/u/cs/ugrad/harris/CS111

I also couldn't access the server from my apartment so I used the Cisco Remote VPN to access the server.

I copied the local lab0 zip into my CS111 directory on the remote Linux server. I then installed the VM and did the emulation process. I installed the lightweight version containing only the command line version and then I began by doing another scp from the remote Linux server onto the local virtual machine. To do that I did another scp:

-> scp -r harris@lnxsrv07.seas.ucla.edu:/u/cs/ugrad/harris/CS111 /home/cs111/Downloads

I used the remote ssh for VSCode to code locally. I changed the code locally in VSCode and it updated in the server.

## Building
```shell
TODO: cmd for build
```

First, I use the 'make' command to build out the neccessary files including proc_count.ko which we will add to the kernel.

After I used the make command to create all the subsequent files, the most important one being proc_count.ko. I then used:
-> sudo insmod proc_count.ko

This added the proc_count.ko to our kernel so that it can count the number of processes.

## Running
```shell
TODO: cmd for running binary
```
TODO: results?

Now I have to check if the program works successfully. Now I would run:
-> cat /proc/count

This will return an integer the number of processes. This returned a count of 88. So the result was 88. At first when I compiled, in my code I had extra lines: seq_printf(m,"The number of processes: %d\n", total_processes); This threw an error. So when I omitted it, it ran fine and I didn't get the unit test failure. 

## Cleaning Up
```shell
TODO: cmd for cleaning the built binary
```

The command for cleaning the built binary in order to make changes to proc_count.c would be:
-> make clean

This deletes all the files made from the 'make' command and allows you to make changes to the proc_count.c to make subsequent changes to proc_count.ko. When you do the make clean, you can also check that the previous proc_count.ko is also removed. The command rmmod does the opposite of insmod and removes the file from kernel level.

## Testing
```python
python -m unittest
```
TODO: results?

Also running 'modinfo proc_count.ko', I got:
filename: /home/cs111/Downloads/lab0/proc_count.ko
license: GPL
description: CS111 lab0 count proc number
author: Harris Doan
srcversion: badf833a034700ea3d8e112
depends:
retpoline: Y
name: proc_count
vermagic: 5.14.8-arch1-1 SMP preempt mod_unload

After running 'python -m unittest':

Ran 3 tests in 6.753s

OK

This means I passed all the cases. Then I considered myself done with lab0.

Report which kernel release version you tested your module on
(hint: use `uname`, check for options with `man uname`).
It should match release numbers as seen on https://www.kernel.org/.

```shell
uname -r -s -v
```
TODO: kernel ver?
Linux 5.14.8-arch1-1 #1 SMP PREEMPT Sun, 26 Sep 2021 19:36:15 +0000
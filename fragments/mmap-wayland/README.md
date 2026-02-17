# mmap() revisit, and Wayland

It's been 13 years since I have to handle mmap().
When I study Wayland client, I ran into this, and it became so new to me.
Besides, Wayland uses cool linux feature, memfd_create() (created in 2014, Linux Kernel 3.17)

This feature is not available in BSD or MacOS, (Or Windows, lol)
BSD recently supported this to par-with Linux, (FreeBSD 13.0, 2021).

So, restudying the mmap().



## Basic usage.

mmap() is mapping a virtual memory with SOMETHING.
This SOMETHING can be different stuff, and easiest to understand is "file".

In read/write world, open() returns fd, and fd handles the
cursor control.  offset, read(or write), rewind, flush, close, etc...

In mmap world, Data is mapped to a memory, and we play with pointer.
read/write brings block by offset and hitting system call,
mmap uses page-fault, and kernel helps to fill the gap (missing pages).

This is very efficient, and later in Wayland, we pass FD which accomplishes
ZERO-COPY.  The compositor (server) just reads the buffer to draw.  So Cool!!

[file example](mmap-file.c)


## Wayland way

memfd_create() is a brilliant way to share data in zero-copy.

The benefit of memfd_create() is,  1) anonymous, hence, no worry about
naming collision,  2) auto clean-up.  It's a memory block, belong to the
process.  No reference left.  3) AND, Linux provides SEAL to protect the
compositor.


Example:  
  - TODO: finish writing!   
    - It's in ~/tmp/memfd_create/
	

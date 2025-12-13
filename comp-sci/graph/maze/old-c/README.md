# Okay, I made this, but How did I do that?

From my blog:  
  - https://litdream.blogspot.com/2014/12/maze-generating-in-c-like-lumosity.html

But, How did I figure this out?
So, I run recursive of genMaze.
( Init by all blocked grid.  Then, step to unvisited random neighbor,
  starting from beginning to end. )


Initialize with all 0:  Locate cell by X, Y method ( %, / )


I just realized.  It's a some-sort-of spanning tree.
I always move from unvisited->visited, which naturally:
  1. Makes Tree structure,  
  2. Will not make Cycle
  3. Eventually a path will reach the exit (5,5) first, and that path will be chosen to be the solution.
  4. Late expansions will be eventually all blocked out, because right paths are visited, no way to punch hole there.




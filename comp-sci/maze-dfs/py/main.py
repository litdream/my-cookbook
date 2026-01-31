from maze import Maze
import os, sys

def main():
    width, height = 6,6
    if len(sys.argv) > 1:
        sz = int(sys.argv[1])
        width, height = sz, sz
    
    maze = Maze(width, height)
    maze.generate()
    print(maze)

if __name__ == "__main__":
    main()

import pygame
import sys
from maze import Maze

CELL_SZ = 30
WALL_THICK = 8
WALL_SHADOW = 2

# Colors
COLOR_BG = (34, 139, 34)      # Forest green
COLOR_PATH = (74, 114, 232)   # Blue
COLOR_WALL = (247, 211, 8)    # Gold
COLOR_WALL_SHADOW = (156, 132, 0)  # Darker Gold
COLOR_SOL  = (255, 255, 255)  # White  (Solution path)


def draw_maze(screen, maze:Maze, solution_path):
    screen.fill(COLOR_BG)

    #
    # Draw maze
    #   - Tile
    for cell in maze.cells:
        x,y = cell.x * CELL_SZ, cell.y * CELL_SZ
        rect = pygame.Rect( x + WALL_THICK,  y + WALL_THICK,
                            CELL_SZ - WALL_THICK,  CELL_SZ - WALL_THICK )
        pygame.draw.rect(screen, COLOR_PATH, rect)

        # fill walls, if punched.
        if not cell.north_wall:
            conn_rect = pygame.Rect( x + WALL_THICK, y,
                                    CELL_SZ - WALL_THICK, WALL_THICK )
            pygame.draw.rect(screen, COLOR_PATH, conn_rect)
        if not cell.west_wall:
            conn_rect = pygame.Rect(x, y + WALL_THICK, 
                                    WALL_THICK, CELL_SZ - WALL_THICK)
            pygame.draw.rect(screen, COLOR_PATH, conn_rect)
            
    #
    # Draw maze
    #   - Wall
    for y in range(maze.height + 1):
        for x in range(maze.width + 1):
            cell = maze.get_cell(x, y)
            
            # Draw Horizontal wall (North of cell)
            if y < maze.height:
                cell = maze.get_cell(x, y)
                if cell and cell.north_wall:
                    rect = pygame.Rect(x * CELL_SZ, y * CELL_SZ, CELL_SZ + WALL_THICK, WALL_THICK)
                    pygame.draw.rect(screen, COLOR_WALL, rect)
                    pygame.draw.rect(screen, COLOR_WALL_SHADOW, rect, WALL_SHADOW)

            # Draw Vertical wall (West of cell)
            if x < maze.width:
                cell = maze.get_cell(x, y)
                if cell and cell.west_wall:
                    rect = pygame.Rect(x * CELL_SZ, y * CELL_SZ, WALL_THICK, CELL_SZ + WALL_THICK)
                    pygame.draw.rect(screen, COLOR_WALL, rect)
                    pygame.draw.rect(screen, COLOR_WALL_SHADOW, rect, WALL_SHADOW)

    # Draw Solution
    if solution_path:
        for i in range(len(solution_path) - 1):
            c1 = solution_path[i]
            c2 = solution_path[i+1]
            x1 = c1.x * CELL_SZ + CELL_SZ // 2 + WALL_THICK // 2
            y1 = c1.y * CELL_SZ + CELL_SZ // 2 + WALL_THICK // 2
            x2 = c2.x * CELL_SZ + CELL_SZ // 2 + WALL_THICK // 2
            y2 = c2.y * CELL_SZ + CELL_SZ // 2 + WALL_THICK // 2
            pygame.draw.line(screen, COLOR_SOL, (x1, y1), (x2, y2), 4)

    # Final borders
    pygame.draw.rect(screen, COLOR_WALL, (0, 0, maze.width * CELL_SZ + WALL_THICK, WALL_THICK))
    pygame.draw.rect(screen, COLOR_WALL, (0, 0, WALL_THICK, maze.height * CELL_SZ + WALL_THICK))
    
    pygame.draw.rect(screen, COLOR_WALL, (0, maze.height * CELL_SZ, maze.width * CELL_SZ + WALL_THICK, WALL_THICK))
    pygame.draw.rect(screen, COLOR_WALL, (maze.width * CELL_SZ, 0, WALL_THICK, maze.height * CELL_SZ + WALL_THICK))

    # Entry/Exit
    pygame.draw.rect(screen, COLOR_BG, (WALL_THICK, 0, CELL_SZ, WALL_THICK))
    pygame.draw.rect(screen, COLOR_BG, ( (maze.width-1) *CELL_SZ,
                                         maze.height *CELL_SZ,
                                         CELL_SZ, WALL_THICK))
        
def main():
    pygame.init()

    width, height = 20, 20       # default
    if len(sys.argv) > 1:
        sz = int(sys.argv[1])    # Eh~~ no err check
        width, height = sz, sz

    screen_width = width * CELL_SZ + WALL_THICK
    screen_height = height * CELL_SZ + WALL_THICK
    screen = pygame.display.set_mode( (screen_width, screen_height))
    pygame.display.set_caption("Maze with DFS")
    
    maze = Maze(width, height)
    maze.generate()
    solution = maze.solve()

    clock = pygame.time.Clock()
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_r:     # Regenerate
                    maze = Maze(width, height)
                    maze.generate()
                    solution = maze.solve()
        draw_maze(screen, maze, solution)
        pygame.display.flip()
        clock.tick(30)
        
    
if __name__ == '__main__':
    main()

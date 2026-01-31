import random

class MazeCell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.north_wall = True
        self.west_wall = True
        self.visited = False

class Maze:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [ MazeCell(x, y) for y in range(height) for x in range(width) ]

    def get_cell(self, x, y):
        if 0 <= x < self.width and 0 <= y < self.height:
            return self.cells[x + y * self.width]
        return None

    def get_neighbors(self, cell):
        # Order:
        #  - 0: North,
        #  - 1: West,
        #  - 2: East,
        #  - 3: South
        neighbors = []
        
        coords = [(0, -1), (-1, 0), (1, 0), (0, 1)]
        for dx, dy in coords:
            neighbor = self.get_cell(cell.x + dx, cell.y + dy)
            neighbors.append(neighbor)
        return neighbors

    def punch_wall(self, node1, node2):
        x1, y1 = node1.x, node1.y
        x2, y2 = node2.x, node2.y

        if x1 < x2 and y1 == y2:
            node2.west_wall = False
        elif x2 < x1 and y1 == y2:
            node1.west_wall = False
        elif y1 > y2 and x1 == x2:
            node1.north_wall = False
        elif y2 > y1 and x1 == x2:
            node2.north_wall = False

    def generate(self, current_cell=None):
        if current_cell is None:
            current_cell = self.cells[0]
        
        current_cell.visited = True
        neighbors = self.get_neighbors(current_cell)
        
        # Filter out None and already visited neighbors
        valid_neighbors = [ n for n in neighbors if n is not None and \
                           not n.visited ]
        random.shuffle(valid_neighbors)
        for next_cell in valid_neighbors:
            if not next_cell.visited:
                self.punch_wall(current_cell, next_cell)
                self.generate(next_cell)

#    def print_maze(self):
    def __str__(self):
        rtn = []
        for y in range(self.height):
            north_row = ""
            for x in range(self.width):
                cell = self.get_cell(x, y)
                north_row += "+"
                if cell.north_wall:
                    if cell.x == 0 and cell.y == 0:
                        north_row += "  "
                    else:
                        north_row += "--"
                else:
                    north_row += "  "
            rtn.append(north_row + "+")
            
            west_row = ""
            for x in range(self.width):
                cell = self.get_cell(x, y)
                if cell.west_wall:
                    west_row += "|  "
                else:
                    west_row += "   "
            rtn.append(west_row + "|")

        bottom = ""
        for x in range(self.width - 1):
            bottom += "+--"
        rtn.append(bottom + "+  +")

        return "\n".join(rtn)

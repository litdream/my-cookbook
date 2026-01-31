#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define WIDTH   6
#define HEIGHT  6

struct node {
    int north_wall;
    int west_wall;
    int visited;
    int x;
    int y;
};

void printMaze(int cnt, struct node *cells)
{
    int y,x;
    for (y=0; y<HEIGHT; ++y) {
        for (x=0; x<WIDTH; ++x) {
            struct node *c = cells + ( x + y*WIDTH );
            printf("+");
            if (c->north_wall) {
                if (c->x == 0 && c->y == 0) 
                    printf("  ");
                else
                    printf("--");
            }
            else 
                printf("  ");
        }
        printf("+\n");

        for (x=0; x<WIDTH; ++x) {
            struct node *c = cells + (x + y*WIDTH) ;
            if (c->west_wall) 
                printf("|  ");
            else
                printf("   ");
        }
        printf("|\n");
    }
    
    for (x=0; x<WIDTH-1; ++x) {
        printf("+--");
    }
    printf("+  +\n\n");
}

// rtn is a pointer array.  NWES.
int neighbor(struct node *cells, struct node *cur, struct node **rtn)
{
    int x = cur->x;
    int y = cur->y;
    rtn[0] = rtn[1] = rtn[2] = rtn[3] = NULL;

    if (y-1 >= 0) rtn[0] = cells + (x + (y-1)*WIDTH);
    if (x-1 >= 0) rtn[1] = cells + ((x-1) + y*WIDTH);
    if (x+1 < WIDTH)  rtn[2] = cells + ((x+1) + y*WIDTH);
    if (y+1 < HEIGHT) rtn[3] = cells + (x + (y+1)*WIDTH);

    return rtn[0] != NULL || rtn[1] != NULL ||
           rtn[2] != NULL || rtn[3] != NULL;
}

void shuffle(struct node **array, size_t n) {    
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int usec = tv.tv_usec;
    srand48(usec);

    if (n > 1) {
        size_t i;
        for (i = n - 1; i > 0; i--) {
            size_t j = (unsigned int) (drand48()*(i+1));
            struct node  *t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void punchWall(struct node *node1, struct node *node2)
{
    int x1 = node1->x;
    int y1 = node1->y;
    int x2 = node2->x;
    int y2 = node2->y;

    if (x1 < x2 && y1 == y2)
        node2->west_wall =0;
    if (x2 < x1 && y1 == y2)
        node1->west_wall =0;

    if (y1 > y2 && x1 == x2)
        node1->north_wall =0;
    if (y2 > y1 && x1 == x2)
        node2->north_wall =0;
        
}

void genMaze(struct node *cells, struct node *cur)
{
    int i;
    if (cur->visited == 0) {
        struct node *nei[4];

        cur->visited = 1;
        if (neighbor( cells, cur, nei)) {
            shuffle(nei, 4);
            for (i=0; i<4; ++i) {
                if (nei[i] && nei[i]->visited==0) {
                    punchWall(cur, nei[i]);
                    genMaze(cells, nei[i]);
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    int i;
    struct node cells[ WIDTH * HEIGHT ];

    // Initialize Cells
    for (i=0; i < WIDTH*HEIGHT; ++i) {
        cells[i].north_wall = cells[i].west_wall = 1;
        cells[i].visited = 0;
        cells[i].x = i % WIDTH;
        cells[i].y = i / WIDTH;
    }
    genMaze(cells, &cells[0]);
    printMaze(WIDTH * HEIGHT, cells);
    return 0;
}


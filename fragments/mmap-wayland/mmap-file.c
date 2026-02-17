#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("alice.txt", O_RDONLY);
    struct stat st;
    fstat(fd, &st);   // for size

    // man: https://linux.die.net/man/2/mmap
    //
    //   void *mmap(void addr[.length], size_t length, int prot, int flags,
    //              int fd, off_t offset);
    //
    char *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    
    if (map == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    printf("Alice in Wonderland:\n%s\n", map);

    // Clean up
    munmap(map, st.st_size);
    close(fd);
    return 0;
}

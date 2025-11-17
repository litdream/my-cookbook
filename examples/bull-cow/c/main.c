#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>   // gcc -std=c99 or better, but no need to worry for modern Linux.


struct result {
	int bulls;
	int cows;
};

void gen_number(int com[], const int len) {
	srand(time(NULL));
	do {
		com[0] = (rand() % 9) + 1; 
		com[1] = (rand() % 9) + 1;
		com[2] = (rand() % 9) + 1;
		
	} while ( com[0] == com[1] ||	\
		  com[0] == com[2] ||	\
		  com[1] == com[2] );
}


// TODO: finish validate_input() function.
//   Modern C provides "bool" as type. <stdbool.h>
//
//   - c17 or earlier:  true/false is macro
//   - c23:  true/false are keyword.  no <stdbool.h> necessary(?)
//
bool validate_input(const char *userinput) {
	if (strlen(userinput) != 3) {
		return false;
	}
	for (int i = 0; i < 3; i++) {
		// Check if the character is a digit '1' through '9'
		if (userinput[i] < '1' || userinput[i] > '9') {
			return false;
		}
	}
	return true;
}

struct result match(const char *userinput, const int *com) {
	int guess[3];  // userinput (string) to int arr.
	struct result res = {0,0};
	
	for (int i=0; i <3; ++i) {
		guess[i] = userinput[i] - '0'; 
	}

	for (int i=0; i <3; ++i) {
		if (guess[i] == com[i]) {
			res.bulls++;
		}
	}

	for (int i=0; i <3; ++i) {
		if (guess[i] == com[ i+1 %3] ||
		    guess[i] == com[ i+2 %3] ) {
			res.cows++;
		}
	}
	
	return res;
}


int main()
{     
	int com[3];
	char userinput[10];

	gen_number(com, 3);
	for (int i=1; i <=10; ++i) {
		printf("Round %d: Enter your 3-digit guess (e.g., 123): ", i);
		if (fgets(userinput, sizeof(userinput), stdin) == NULL) {
			fprintf(stderr, "Error reading input.\n");
			return 1;
		}
		// Remove the newline character if present
		userinput[strcspn(userinput, "\n")] = 0;

		// TODO: Validate userinput

		struct result res = match(userinput, com);
		if (res.bulls == 3) {
			printf("Great! You got this in %d rounds. The number was: %d%d%d\n", i, com[0], com[1], com[2]);
			return 0;
		}
		printf("%d bulls, %d cows\n", res.bulls, res.cows);
	}
    
	printf("Sorry: The number was %d%d%d.\n", com[0], com[1], com[2]);
	return 0;
}


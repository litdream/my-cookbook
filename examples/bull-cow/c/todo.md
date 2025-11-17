# TODO

1. finish validate() function

2. (DONE) BUG
check-in #2:  Perenthesis!!

```
[rchung@arch-dell14 c]$ ./a.out
Round 1: Enter your 3-digit guess (e.g., 123): 123
0 bulls, 1 cows
Round 2: Enter your 3-digit guess (e.g., 123): 234
0 bulls, 0 cows
Round 3: Enter your 3-digit guess (e.g., 123): 516
0 bulls, 1 cows
Round 4: Enter your 3-digit guess (e.g., 123): 781   <- SHOULD BE: 1,2
1 bulls, 1 cows
Round 5: Enter your 3-digit guess (e.g., 123): 971
2 bulls, 0 cows
Round 6: Enter your 3-digit guess (e.g., 123): 371
2 bulls, 0 cows
Round 7: Enter your 3-digit guess (e.g., 123): 271
2 bulls, 0 cows
Round 8: Enter your 3-digit guess (e.g., 123): 571
2 bulls, 0 cows
Round 9: Enter your 3-digit guess (e.g., 123): 671
2 bulls, 0 cows
Round 10: Enter your 3-digit guess (e.g., 123): 871
Great! You got this in 10 rounds. The number was: 871


[rchung@arch-dell14 c]$ ./a.out
Round 1: Enter your 3-digit guess (e.g., 123): 123 <- SHOULD BE: 1,1
1 bulls, 0 cows
Round 2: Enter your 3-digit guess (e.g., 123): 145
0 bulls, 1 cows
Round 3: Enter your 3-digit guess (e.g., 123): 526
1 bulls, 0 cows
Round 4: Enter your 3-digit guess (e.g., 123): 427
1 bulls, 1 cows
Round 5: Enter your 3-digit guess (e.g., 123): 824
2 bulls, 0 cows
Round 6: Enter your 3-digit guess (e.g., 123): 924
2 bulls, 0 cows
Round 7: Enter your 3-digit guess (e.g., 123): 724
2 bulls, 0 cows
Round 8: Enter your 3-digit guess (e.g., 123): 824
2 bulls, 0 cows
Round 9: Enter your 3-digit guess (e.g., 123): 924
2 bulls, 0 cows
Round 10: Enter your 3-digit guess (e.g., 123): 1234
1 bulls, 0 cows
Sorry: The number was 324.
```

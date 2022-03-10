# Problem 5 - Alice’s Bookshelf (100 pts)
Time Limit : 7 s <br>
Memory Limit : 1024 MB
## Problem Description
Alice loves reading books and has a bookshelf. For each book in her bookshelf, there’s a number,
indicating the corresponding priority. You have to maintain the sequence of the books’ priority
with operations specified in the Input section.

## Input
The first line contains two numbers N, Q (1 ≤ N, Q ≤ 8 × 105), indicating the number of books in the initial bookshelf and the number of operations. <br>
The second line contains N integers, representing the priority of books in the bookshelf. <br>

Each of the following Q lines contains one of the following operations, which can be identified with the first number in each line:
1. p k: Insert a book with priority p after the k-th position. Note that the position index
starts from 1. If k = 0, then insert it as the first book in the bookshelf.
2. k: Delete the k-th book.
3. l r p: Increase the priorities of the books between the positions l and r by p (including
books at position l and r, and l ≤ r.) Note that p may be negative.
4. l r: Query the largest priority of books between the positions l and r (including books
at position l and r, and l ≤ r.)
5. l r: Reverse the order of books between the positions l and r (including books at
position l and r, and l ≤ r.)
6. Remove the book with the largest priority.
You can assume that the given priorities can be stored in a 32-bit int variable and all operations
are valid. Note that the bookshelf may become empty. When performing operation 6, if there
are multiple books with the largest priority, you should remove the book with smallest position
index.

## Output
For each operation 4 in the sequence of given operations, the largest priority of books between the position l and r (inclusive) has to be printed out. You don’t have to print anything for any other operation.

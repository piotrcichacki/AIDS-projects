# Variable Length Integers

### Instructions

Write a program which stores N integers (N <= 100000) with any number of digits, and is able to perform the following operations:
<ul>
  <li>i = j + k - save under the index i the result of the addition of the numbers stored under j and k indices (i, j, k are from range [0, N-1]),</li>
  <li>i = j - k - save under the index i the result of the substraction of the numbers stored under j and k indices (i, j, k are from range [0, N-1]),</li>
  <li>min - print the minimum of the stored numbers</li>
  <li>max - print the maximum of the stored numbers</li>
  <li>? - print all of the stored numbers.</li>
</ul>
You should implement your own data structures (you should not use STL library, vector, string etc.).

### Input

First line: N - the number of numbers to be stored, Next N lines: numbers to be stored, with any number of digits (one number per line), Next lines: one of the following commands:
<ul>
  <li>i = j + k,</li>
  <li>i = j - k,</li>
  <li>min</li>
  <li>max</li>
  <li>?</li>
  <li>q (exit the program)</li>
</ul>

### Output

For each 'min/max' command: one line with the number which is the minimum/maximum of the stored numbers. </br>
For each '?' command: N lines with all the stored numbers.



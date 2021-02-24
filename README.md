# MAST

Algorithms and Data Structures project

### Instructions 

The exercise is to implement an algorithm that reads a set of n rooted trees in the NEWICK format, and then for each of n(n-1)/2 pairs of trees will calculate the minimum number of leaves whose removal from both trees will make them isomorphic. The problem is known in IT as Maximum agreement subtree problem .

### Input
The value of n denotes the size of the set of n rooted trees.<br/>
n rooted trees in NEWICK format.

### Output
n(n-1)/2 comparisons of input trees (each with each). The order of comparison: 1-2, 1-3, ..., 1-n, 2-3, 2-4, ..., 2-n, ..., (n-1) -n

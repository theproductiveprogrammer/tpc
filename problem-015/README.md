You are given a tree (an acyclic undirected connected graph) with N nodes, and edges numbered 1, 2, 3...N-1.

We will ask you to perfrom some instructions of the following form:

**CHANGE** i ti : change the cost of the i-th edge to ti
or
**QUERY** a b : ask for the maximum edge cost on the path from node a to node b


== Input

The first line of input contains an integer t, the number of test cases (t <= 20). t test cases follow.

For each test case:

* In the first line there is an integer N (N <= 10000),
* In the next N-1 lines, the i-th line describes the i-th edge: a line with three integers a b c denotes an edge between a, b of cost c (c <= 1000000),
* The next lines contain instructions "CHANGE i ti" or "QUERY a b",
* The end of each test case is signified by the string "DONE".
* There is one blank line between successive tests.

== Output

For each "QUERY" operation, write one integer representing its result.

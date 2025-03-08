# Xoracle

## Problem

The judge has a tree with $N$ nodes, and you should reconstruct the degrees of the nodes using at most $Q$ queries asking the XOR of the degrees of 2 nodes.

## Subtask 1, limited degrees

We are guaranteed that each node has degree at most 3, and that there exist at least one node with degree 1, 2, and 3 respectively.
Note that for any number $d$, there exist no positive integer $x$ such that $d \oplus x = d$. 
As such, we can deduce the degree of node 1, by querying `? 1 i` for each $i \in [2, 3, .., N]$ and noting what result isn't returned at any point.
Once we know the degree of node 1, we can easily find the degree of any other node, since we already know $deg(1) \oplus deg(i)$, by using the following property of XOR:
$a \oplus a \oplus b = b$.

## Subtask 2, limited degrees 2

We are guaranteed that each node has degree at most 4, and that at least 3 of the possible degrees are present in the tree.
By realizing that if node 1 has degree 1, all query answers will be in the set $0, 3, 2, 5$.

Similar patterns can be seen for the other possible degrees, giving us the following combinations

* $1 : {0, 3, 2, 5}$
* $2 : {3, 0, 1, 6}$
* $3 : {2, 1, 0, 7}$
* $4 : {5, 6, 7, 0}$

By checking the cases with the giving answers, we can find the degree of node 1,
and construct the solution as in subtask 1.

## Subtask 3, $N \leq 1000$, $Q = N * N$

With $Q = N * N$, we have enough queries to recieve as much information as we want.

So, how can we construct the tree using the queries in time $O(N^2)$?

We realize that at least one node must be a leaf.
If we iterate over each node, and guess that this node is a leaf, we can calculate the total degree over all nodes of the tree. We now that this number needs to equal $2 * N - 2$ if the graph needs to be a valid tree.
There is a second condition, however, which several contestants forgot.
You need to check whether any node has degree 0, in the proposed solution.
If so, the graph isn't connected, and furthermore it contains at least 1 cycle, and as such isn't a valid tree.

These 2 conditions are sufficient to construct the tree, and as such we have our solution to this subtask.

## Subtask 4, $N \leq 1000$, $Q \leq N \sqrt{N}$

In this subtask we have fewer available queries than subtask 3.
As such we have to observe, that if we at some point query $i$ and $j$, and recieve the answer 0, node $i$ and $j$ must have the same degree.
As such we say they are in the same "group".
When we want to query two nodes, we can instead query any two nodes from the corresponding groups.
By observing, that the number of groups is O(\sqrt{N}) we have reduced the problem to subtask 3.

## Subtask 5, $N \leq 1000$, $Q = N - 1$

By using the property of XOR used in subtask 1, we have reduced this subtask to subtask 3

## Subtask 6, $N \leq 10^5$

By observing that the group of nodes representing the leaves (degree 1) is either the largest or second largest group,
we can use our solution to subtask 5, but running in linear time.


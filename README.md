# SkyLine-of-a-City-C++-

A city’s skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return the skyline formed by these buildings collectively.
You are given a list of the building x-coordinates and their heights:
(l1, h1, r1),(l2, h2, r2), ...,(ln, hn, rn)
Here, we will assume all values are between 1 and 100. The list will be sorted in increasing order of left-most x-coordinate. Format of the output would be :
(x1, y1),(x2, y2),(x3, y3), ...


This means that at x1 we draw a building at height y1 until x2 at which point we draw a line up or down to high y2 and then continue horizontally until x3 and so on.
a) Describe an O(n log n)-time algorithm for solving this problem. Give your description in words and pseudocode.
b) Implement your algorithm using a compiled programming language.
c) Simulate 5 increasingly datasets by creating the following number of points selected at random: 10 points, 100 points, 1000 points, 10000 points and 100000 points. Run your algorithm on each dataset, and graph the run-time to illustrate the order notation of your algorithm. The graph should demonstrate an O(n log n) running time.

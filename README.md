# Point Location
<h1>Point Location</h1>
<p>
This project is an implementation of two point location algorithms, as described in chapter 6 of "Computational Geometry – Algorithms and Applications" by Mark de Berg, Otfried Cheong, Marc van Kreveld, Mark Overmars. The algorithms were learned as part of a Computional Geometry seminar, but implemented independently. 
<br>
<br>
Both algorithms solve the following problem:
For a given planar subdivision, consisting of faces made of non-crossing edges, we need to be able to recieve coordinates of a point in the subdivision and return to the user in what face the point is. 
Note that each edge is associated with the face that is directly above it by a pointer.
<br>
<br>
<h1>User Interface</h1>
When you run the program a window with the planar subdivision drawn appears. The input of the subdivision is in the code and can be changed. Clicking on a point in the window will highlight the edges of the face that contain the point. If the point is in the infinity face, no edges will be highlighted. The console also prints the vertices that the face consists of, or "infinity face" in the case the point is in the infinity face. To exit click the X in the console.
<br>

<h1>Algorithms</h1>
First algorithm - Division into slabs:
<br>
Divides the planar subdivision into slabs, each slab is between two successive vertices in the subdivision, and contains the edges that cross it. The slabs are sorted from left to right and in each slabs the edges are sorted from bottom to top. To find the point's face, we search the slab that contains the point with binary search, and then the edge that is directly below the point by binary search, and get the face that is associated with the edge, i.e. above it. If no such edge exists the point is in the outside infinite face.
<br>
This algorithm is very fast for each query, with time complexity of O(log n) (two binary searches). However, it falls short in storage complexity which is O(n^2) (because we have O(n) slabs, and in the worst case each contains O(n) edges). The average storage complexity is O(n^1.5)
<br>
<br>
Second algorithm - Division into trapezoids:
Divides the planar subdivision into a complex structure of trapezoids and triangles. Maintains a directional acyclic graph (DAG) to search for the point's trapezoid. When we search for a point's face, we'll search the DAG until we reach one of its leaves, which is associated with the trapezoid of the point. The trapezoid bottom edge is the edge that is directly below the point, from which we can get the face the point is in.
<br>
This algorithm is better then the first on the average case. While the query time complexity is O(n) in the worst case, it is O(log n) in the average case. It improves on the first algorithm by having a storage complexity of O(n) in the average case (although it is still O(n^2) in the worst case).
</p>

<h1>Author</h1>
<p>Shaked Stossel <br>
Email: skd988@gmail.com</p>

<h1>Initialization and execution</h1>
<p>
Build and run the project with Debug for x86
</p>

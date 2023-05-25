# GPS-Distance-to-and-Point-inside-a-Polygon
C/C++ Algorithm for Point inside a Polygon and distance of a point to a Polygon
Most common and efficient algorithm for this is Ray-casting Algorithm.

<h2> Point inside a polygon </h2>

Algorithm to figure out if a point lies inside a polygon or outside. Efficient algorithm implementation in just 7 lines of code orignally posted byby W. Randolph Franklin: [https://wrfranklin.org/Research/Short_Notes/pnpoly.html](url) 

For visualisation you can easily create polygones using the following tool and directly copy and use it in your code: [https://www.keene.edu/campus/maps/tool/](url)

<h2> Distance of a Point to a Polygon <h2>

The Point in Polygon (PIP) algorithm, also known as the ray casting algorithm, is used to determine whether a given point lies inside or outside a closed polygon. The algorithm works by drawing a semi-infinite ray from the test point in any direction, and counting the number of times the ray intersects the polygon's edges. If the number of intersections is odd, then the point is inside the polygon, otherwise it is outside.
The algorithm iterates over each edge of the polygon and checks if the endpoints of the edge are on opposite sides of the ray. If they are, then the algorithm checks if the x-coordinate of the intersection point between the edge and the ray is to the left of the test point. If both conditions are true, then the parity of a counter variable is inverted, indicating that the ray intersects the polygon at that edge.
At the end of the algorithm, if the counter is even, then the point lies outside the polygon, and if the counter is odd, then the point lies inside the polygon. This algorithm can be used for any closed polygon, including concave and convex polygons. It is commonly used in computer graphics and geographic information systems to determine if a point lies inside a polygonal region.




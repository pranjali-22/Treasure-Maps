# Treasure-Maps

### Part 1 - Implementation of Stack, Dequeue and Queue Data Structures
The Dequeue, Stack and Queue Class contains the implementation of data structures with there respestive operations.

### Part 2 - Creating a Map
This part contains the implementation of an algorithm for creating a treasure map. A treasure map consists of a base image, a maze image, and a starting position.The location of the starting position is always provided, and the treasure is found at the point (pixel location) whose shortest distance to the start in the maze is longest.

A maze is simply an image containing a collection of points whose pixel colours are equivalent to the pixel colour of the start location, and reachable from the start location via a path of same-coloured pixels. 

The algorithm for embedding the maze into a treasure map is as follows:

The treasure map begins as a copy of the base map. The pixels in the treasure map corresponding to the maze image will be adjusted in a way that is not obvious to the naked eye.
The start position should be embedded with maze-value 
If a point has been embedded with maze-value, then its compass neighbors who are also in the maze, and whose maze-values are not yet set, should be embedded with maze-value 

### Part 3 - Finding the Treasure
This part contains the implementation of decoder for treasure maps created using the embedding algorithm, and then solving the maze to find the treasure!The algorithm for finding the maze embedded in the treasure map, given a starting point.

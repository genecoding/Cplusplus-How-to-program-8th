9.11 (Rectangle Class) Create a class Rectangle with attributes length and width, each of which
defaults to 1. Provide member functions that calculate the perimeter and the area of the rectangle.
Also, provide set and get functions for the length and width attributes. The set functions should 
verify that length and width are each floating-point numbers larger than 0.0 and less than 20.0.

9.12 (Enhancing Class Rectangle) Create a more sophisticated Rectangle class than the one you
created in Exercise 9.11. This class stores only the Cartesian coordinates of the four corners of the
rectangle. The constructor calls a set function that accepts four sets of coordinates and verifies that
each of these is in the first quadrant with no single x- or y-coordinate larger than 20.0. The set 
function also verifies that the supplied coordinates do, in fact, specify a rectangle. Provide member 
functions that calculate the length, width, perimeter and area. The length is the larger of the two
dimensions. Include a predicate function square that determines whether the rectangle is a square.

9.13 (Enhancing Class Rectangle) Modify class Rectangle from Exercise 9.12 to include a draw
function that displays the rectangle inside a 25-by-25 box enclosing the portion of the first quadrant
in which the rectangle resides. Include a setFillCharacter function to specify the character out of
which the body of the rectangle will be drawn. Include a setPerimeterCharacter function to specify
the character that will be used to draw the border of the rectangle. If you feel ambitious, you might
include functions to scale the size of the rectangle, rotate it, and move it around within the designated 
portion of the first quadrant.

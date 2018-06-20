7.23 (Turtle Graphics) The Logo language, which is popular among elementary school children,
made the concept of turtle graphics famous. Imagine a mechanical turtle that walks around the room
under the control of a C++ program. The turtle holds a pen in one of two positions, up or down.
While the pen is down, the turtle traces out shapes as it moves; while the pen is up, the turtle moves
about freely without writing anything. In this problem, you’ll simulate the operation of the turtle
and create a computerized sketchpad as well.  
Use a 20-by-20 array floor that is initialized to false. Read commands from an array that
contains them. Keep track of the current position of the turtle at all times and whether the pen is
currently up or down. Assume that the turtle always starts at position (0, 0) of the floor with its
pen up. The set of turtle commands your program must process are shown in Fig. 7.27.  

Command | Meaning
------- | -------
1 | Pen up
2 | Pen down
3 | Turn right
4 | Turn left
5,10 | Move forward 10 spaces<br>(or a number other than 10)
6 | Print the 20-by-20 array
9 | End of data (sentinel)

Suppose that the turtle is somewhere near the center of the floor. The following “program”
would draw and print a 12-by-12 square and end with the pen in the up position:  
2  
5,12  
3  
5,12  
3  
5,12  
3  
5,12  
1  
6  
9  
As the turtle moves with the pen down, set the appropriate elements of array floor to true. When
the 6 command (print) is given, wherever there is a true in the array, display an asterisk or some
other character you choose. Wherever there is a zero, display a blank. Write a program to implement 
the turtle graphics capabilities discussed here. Write several turtle graphics programs to draw
interesting shapes. Add other commands to increase the power of your turtle graphics language.

## Matrix Operations Program

The program targets various matrix operations, with matrices being dynamically allocated.

In the main function, there are 10 possible commands.
Upon entering the letter L, the program will allocate memory to read a matrix from the keyboard. If there is already a matrix read, the new one will be added after the previous one. At the same time, there will be two vectors that will store the dimensions of each read matrix.

Upon entering the letter D, a character is read, and the dimensions of the respective matrix will be displayed.

Upon entering the letter P, another character is read, representing the index of the matrix for which the display on the screen is made.

Upon entering the letter C, a number representing the index of the matrix for which resizing is desired is read. Subsequently, a number representing the number of rows is read, and then the row indices are read for which resizing is done. The same procedure is followed for the next read, this time for columns. In an auxiliary matrix, the new matrix will be built (the corresponding position will be taken from the initial matrix).
Upon entering the letter M, two indices will be read for which the multiplication of the respective matrices will be done. The resulting matrix will be added at the end of the collection of matrices, and the new dimensions will also be saved in the row and column vectors.

Upon entering the letter T, an index of the matrix for which transposition is desired will be read.
Upon entering the letter O, the matrices will be sorted based on the sum of their elements. They will be exchanged, along with their position in each corresponding size vector.
Upon entering the letter F, an index will be read, representing the matrix that is to be removed from the collection. All matrices that follow will be moved one position back to avoid any unoccupied space.
Upon entering the letter R, an attempt will be made to raise a matrix to a logarithmic power. For an even exponent, the matrix will be squared, and the exponent will be halved. When the exponent is odd, the retained matrix will be multiplied by the first matrix, and the exponent will be reduced.

Upon entering the letter Q, all allocated memory will be released.
Each time a matrix is added or removed from the collection, the vector that retains all addresses will be resized accordingly, as well as those that retain the dimensions of the matrices.
When a different command is entered, an error message will be displayed, as well as in the case of entering indices of matrices that do not correspond to an already allocated matrix.

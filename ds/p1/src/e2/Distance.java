package e2;

import java.util.Arrays;

public class Distance {

    /**
     * Given a layout and a position in the array, counts the students
     * surrounding the given seat in its eight adjacent positions.
     */
    public static int surroundedBy (char[][] layout, int x, int y) {

        int counter = 0;

        if (x > 0 && y > 0 && layout[y-1][x-1] == '#') counter++; // Top-left
        if (y > 0 && layout[y-1][x] == '#') counter++; // Top
        if (x < layout[y].length - 1 && y > 0 && layout[y-1][x+1] == '#') counter++; // Top-right
        if (x < layout[y].length - 1 && layout[y][x+1] == '#') counter++; // Right
        if (x < layout[y].length - 1 && y < layout.length - 1 && layout[y+1][x+1] == '#') counter++; // Bottom-right
        if (y < layout.length - 1 && layout[y+1][x] == '#') counter++; // Bottom
        if (x > 0 && y < layout.length - 1 && layout[y+1][x-1] == '#') counter++; // Bottom-left
        if (x > 0 && layout[y][x-1] == '#') counter++; // Left

        return counter;
    }

    /**
    * Given the layout of a class with available sites marked with an 'A' and
    * invalid sites marked with a '.', returns the resulting layout with the
    * sites occupied by the students marked with a '#' following two rules:
    * - Students occupy an empty seat if there are no other adjacent students.
    * - A student leaves a seat empty if they have 4 or more adjacent students.
    * @param layout The initial layout.
    * @return The resulting layout.
    * @throws IllegalArgumentException if the initial layout is invalid (is null,
    * is ragged, or includes characters other than '.' or 'A').
    */
    public static char [][] seatingPeople ( char [][] layout ) {

        // Check whether the given layout is null
        if (layout == null) throw new IllegalArgumentException("layout is null");

        int colsNum = layout[0].length;
        for (int y = 0; y < layout.length; y++) {

            // Check whether the layout is "ragged", i.e. whether all
            // rows have the same number of columns
            if (layout[y].length != colsNum)
                throw new IllegalArgumentException("layout is ragged");

            // Check for invalid characters
            for (int x = 0; x < layout[y].length; x++) {
                if (layout[y][x] != 'A' && layout[y][x] != '.')
                    throw new IllegalArgumentException("invalid char: " + layout[y][x]);
            }
        }

        while (true) {

            // Copy of the layout to seat and stand up students simultaneously,
            // comparing the copy against the original layout
            char[][] copy = new char[layout.length][];
            for (int y = 0; y < layout.length; y++) {
                copy[y] = layout[y].clone();
            }

            // Seat or stand up a student depending on how many students
            // surround that specific position
            for (int y = 0; y < layout.length; y++) {
                for (int x = 0; x < layout[y].length; x++) {

                    int count = surroundedBy(copy, x, y);

                    // If surrounded by 4 or more, the student stands up
                    if (count >= 4 && copy[y][x] == '#') layout[y][x] = 'A';

                    // If nobody is nearby, the student sits down
                    else if (count == 0 && copy[y][x] == 'A') layout[y][x] = '#';
                }
            }

            // If nobody sat down or stood up, everyone is in their final position
            if (Arrays.deepEquals(layout, copy)) return layout;
        }
    }
}

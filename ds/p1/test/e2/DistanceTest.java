package e2;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import org.junit.jupiter.api.Test;

class DistanceTest {

    @Test
    void canBeInstantiated() {
        assertNotNull(new Distance());
    }

    @Test
    void surroundedBy() {
        char[][] empty = {
            {'.', '.', '.'},
            {'.', 'A', '.'},
            {'.', '.', '.'}
        };
        assertEquals(0, Distance.surroundedBy(empty, 1, 1));

        char[][] filled = {
            {'#', '#', '#'},
            {'#', 'A', '#'},
            {'#', '#', '#'}
        };
        assertEquals(8, Distance.surroundedBy(filled, 1, 1));

        char[][] topLeft = {
            {'A', '#', '.'},
            {'#', '#', '.'},
            {'.', '.', '.'}
        };
        assertEquals(3, Distance.surroundedBy(topLeft, 0, 0));

        char[][] bottomRight = {
            {'.', '.', '.'},
            {'.', '#', '#'},
            {'.', '#', 'A'}
        };
        assertEquals(3, Distance.surroundedBy(bottomRight, 2, 2));

        char[][] top = {
            {'.', 'A', '.'},
            {'#', '#', '#'},
            {'.', '.', '.'}
        };
        assertEquals(3, Distance.surroundedBy(top, 1, 0));

        char[][] alone = {
            {'A', 'A', 'A'},
            {'A', '#', 'A'},
            {'A', 'A', 'A'}
        };
        assertEquals(0, Distance.surroundedBy(alone, 1, 1));
    }

    @Test
    void seatingPeople() {
        char[][] one = {{'A'}};
        assertEquals('#', Distance.seatingPeople(one)[0][0]);

        char[][] two = {{'A', 'A'}};
        assertArrayEquals(new char[][]{{'#', '#'}}, Distance.seatingPeople(two));

        char[][] none = {{'.', '.'}, {'.', '.'}};
        assertArrayEquals(new char[][]{{'.', '.'}, {'.', '.'}}, Distance.seatingPeople(none));

        char[][] cross = {
            {'.', 'A', '.'},
            {'A', 'A', 'A'},
            {'.', 'A', '.'}
        };
        char[][] expectedCross = {
            {'.', '#', '.'},
            {'#', 'A', '#'},
            {'.', '#', '.'}
        };
        assertArrayEquals(expectedCross, Distance.seatingPeople(cross));
    }

    @Test
    void seatingPeopleThrows() {
        assertEquals("layout is null",
            assertThrows(IllegalArgumentException.class, () -> Distance.seatingPeople(null)).getMessage());

        char[][] ragged = new char[][]{{'A', 'A'}, {'A'}};
        assertEquals("layout is ragged",
            assertThrows(IllegalArgumentException.class, () -> Distance.seatingPeople(ragged)).getMessage());

        char[][] invalidChar = {{'A', 'B'}, {'A', 'A'}};
        assertEquals("invalid char: B",
            assertThrows(IllegalArgumentException.class, () -> Distance.seatingPeople(invalidChar)).getMessage());
    }
}

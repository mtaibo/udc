package e3;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertNotSame;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Test;

class TriangleTest {

    @Test
    void constructorThrows() {
        assertEquals("Angles do not sum 180 degrees",
            assertThrows(IllegalArgumentException.class, () -> new Triangle(90, 90, 90)).getMessage());

        assertEquals("Angles do not sum 180 degrees",
            assertThrows(IllegalArgumentException.class, () -> new Triangle(10, 20, 30)).getMessage());
    }

    @Test
    void copyConstructor() {
        Triangle original = new Triangle(60, 60, 60);
        Triangle copy = new Triangle(original);

        assertEquals(original, copy);
        assertNotSame(original, copy);
    }

    @Test
    void isRight() {
        assertTrue(new Triangle(90, 60, 30).isRight());
        assertTrue(new Triangle(30, 90, 60).isRight());
        assertTrue(new Triangle(30, 60, 90).isRight());
        assertFalse(new Triangle(60, 60, 60).isRight());
    }

    @Test
    void isAcute() {
        assertTrue(new Triangle(60, 60, 60).isAcute());
        assertFalse(new Triangle(90, 60, 30).isAcute());
        assertFalse(new Triangle(100, 40, 40).isAcute());
        assertFalse(new Triangle(40, 100, 40).isAcute());
        assertFalse(new Triangle(40, 40, 100).isAcute());
    }

    @Test
    void isObtuse() {
        assertTrue(new Triangle(100, 40, 40).isObtuse());
        assertTrue(new Triangle(40, 100, 40).isObtuse());
        assertTrue(new Triangle(40, 40, 100).isObtuse());
        assertFalse(new Triangle(90, 60, 30).isObtuse());
        assertFalse(new Triangle(60, 60, 60).isObtuse());
    }

    @Test
    void isEquilateral() {
        assertTrue(new Triangle(60, 60, 60).isEquilateral());
        assertFalse(new Triangle(90, 60, 30).isEquilateral());
        assertFalse(new Triangle(70, 70, 40).isEquilateral());
    }

    @Test
    void isIsosceles() {
        assertTrue(new Triangle(60, 60, 60).isIsosceles());
        assertTrue(new Triangle(70, 70, 40).isIsosceles());
        assertTrue(new Triangle(40, 70, 70).isIsosceles());
        assertTrue(new Triangle(70, 40, 70).isIsosceles());
        assertFalse(new Triangle(90, 60, 30).isIsosceles());
    }

    @Test
    void isScalene() {
        assertTrue(new Triangle(90, 60, 30).isScalene());
        assertFalse(new Triangle(70, 70, 40).isScalene());
        assertFalse(new Triangle(60, 60, 60).isScalene());
        assertFalse(new Triangle(100, 40, 40).isScalene());
        assertFalse(new Triangle(70, 40, 70).isScalene());
    }

    @Test
    void equalsSameOrder() {
        Triangle t1 = new Triangle(90, 60, 30);
        Triangle t2 = new Triangle(90, 60, 30);

        assertEquals(t1, t2);
    }

    @Test
    void equalsDifferentOrder() {
        Triangle t1 = new Triangle(90, 60, 30);
        Triangle t2 = new Triangle(30, 90, 60);
        Triangle t3 = new Triangle(60, 30, 90);

        assertEquals(t1, t2);
        assertEquals(t1, t3);
        assertEquals(t2, t3);
    }

    @Test
    void equalsDifferentAngles() {
        Triangle t1 = new Triangle(90, 60, 30);
        Triangle t2 = new Triangle(80, 60, 40);

        assertNotEquals(t1, t2);
    }

    @Test
    void equalsNullAndOtherType() {
        Triangle t = new Triangle(90, 60, 30);

        assertNotEquals(t, null);
        assertNotEquals(t, "not a triangle");
    }

    @Test
    void hashCodeConsistentWithEquals() {
        Triangle t1 = new Triangle(90, 60, 30);
        Triangle t2 = new Triangle(30, 90, 60);

        assertEquals(t1, t2);
        assertEquals(t1.hashCode(), t2.hashCode());
    }
}

package e1;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Test;

class StringCountTest {

    @Test
    void canBeInstantiated() {
        assertNotNull(new StringCount());
    }

    @Test
    void countWords() {
        assertEquals(4, StringCount.countWords("hola mundo que tal"));
        assertEquals(2, StringCount.countWords("  hola   mundo  "));
        assertEquals(1, StringCount.countWords("hola"));
        assertEquals(0, StringCount.countWords(null));
        assertEquals(0, StringCount.countWords("   "));
        assertEquals(0, StringCount.countWords(""));
    }

    @Test
    void countChar() {
        assertEquals(3, StringCount.countChar("banana", 'a'));
        assertEquals(0, StringCount.countChar("Hola", 'h'));
        assertEquals(0, StringCount.countChar("hola", 'z'));
        assertEquals(0, StringCount.countChar(null, 'a'));
        assertEquals(1, StringCount.countChar("a", 'a'));
    }

    @Test
    void countCharIgnoringCase() {
        assertEquals(1, StringCount.countCharIgnoringCase("Hola", 'h'));
        assertEquals(2, StringCount.countCharIgnoringCase("HaHa", 'h'));
        assertEquals(3, StringCount.countCharIgnoringCase("banana", 'a'));
        assertEquals(0, StringCount.countCharIgnoringCase(null, 'a'));
    }

    @Test
    void isPasswordSafe() {
        assertTrue(StringCount.isPasswordSafe("Hello1@b"));
        assertFalse(StringCount.isPasswordSafe("He1@b"));
        assertFalse(StringCount.isPasswordSafe("HELLO1@B"));
        assertFalse(StringCount.isPasswordSafe("hello1@b"));
        assertFalse(StringCount.isPasswordSafe("Hello@@b"));
        assertFalse(StringCount.isPasswordSafe("Hello123"));
        assertFalse(StringCount.isPasswordSafe("Hello1!b"));
        assertTrue(StringCount.isPasswordSafe("Hello1?."));
    }
}

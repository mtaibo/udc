package e4;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import org.junit.jupiter.api.Test;

class CalculatorTest {

    @Test
    void addOperation() {
        Calculator calculator = new Calculator();

        assertEquals("Operation does not exist",
            assertThrows(IllegalArgumentException.class, () -> calculator.addOperation("x", 1.0f, 2.0f)).getMessage());

        calculator.addOperation("+", 4.0f, 6.0f);
        calculator.addOperation("-", 1.0f, 999.0f);
        assertEquals(9.0f, calculator.executeOperations());
    }

    @Test
    void executeOperations() {
        Calculator calculator = new Calculator();

        calculator.addOperation("+", 4.5f, 6.8f);
        assertEquals(11.3f, calculator.executeOperations(), 0.0001f);

        calculator.addOperation("-", 10.0f, 4.0f);
        assertEquals(6.0f, calculator.executeOperations());

        calculator.addOperation("*", 3.0f, 4.0f);
        assertEquals(12.0f, calculator.executeOperations());

        calculator.addOperation("/", 12.0f, 4.0f);
        assertEquals(3.0f, calculator.executeOperations());

        calculator.addOperation("/", 12.0f, 0.0f);
        assertEquals("Invalid operation (division by zero)",
            assertThrows(ArithmeticException.class, calculator::executeOperations).getMessage());

        calculator.addOperation("+", 1.0f, 2.0f);
        assertEquals(3.0f, calculator.executeOperations());

        calculator.addOperation("+", 4.5f, 6.8f);
        calculator.addOperation("-", 3.1f);
        calculator.addOperation("/", 6.0f);
        assertEquals((4.5f + 6.8f - 3.1f) / 6.0f, calculator.executeOperations(), 0.0001f);
    }

    @Test
    void cleanOperations() {
        Calculator calculator = new Calculator();
        calculator.addOperation("+", 4.5f, 6.8f);

        calculator.cleanOperations();

        calculator.addOperation("-", 10.0f, 4.0f);
        assertEquals(6.0f, calculator.executeOperations());
    }

    @Test
    void toStringFormat() {
        Calculator calculator = new Calculator();
        calculator.addOperation("+", 4.5f, 6.8f);
        assertEquals("[+]4.5_6.8", calculator.toString());

        calculator.cleanOperations();
        calculator.addOperation("+", 4.5f, 6.8f);
        calculator.addOperation("-", 3.1f);
        calculator.addOperation("/", 6.0f);
        assertEquals("[+]4.5_6.8[-]3.1[/]6.0", calculator.toString());

        calculator.cleanOperations();
        calculator.addOperation("-", 3.7f, 5.8f);
        calculator.addOperation("*", 4.8f);
        calculator.addOperation("/", 2.0f);
        calculator.addOperation("+", 2.04f);
        assertEquals("[-]3.7_5.8[*]4.8[/]2.0[+]2.04", calculator.toString());
    }
}

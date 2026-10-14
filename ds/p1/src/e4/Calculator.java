package e4;

import java.util.ArrayList;
import java.util.List;

public class Calculator {

    private final List<String> operators = new ArrayList<>();
    private final List<Float> operands = new ArrayList<>();

    /**
     * Public constructor of the calculator.
     */
    public Calculator () {

    }

    /**
     * Clean the internal state of the calculator
     */
    public void cleanOperations () {
        this.operators.clear();
        this.operands.clear();
    }

    /**
     * Add a new operation to the internal state of the calculator.
     * It is worth mentioning that the calculator behaves in an accumulative way,
     * thus only first operation has two operands.
     * The rest of computations work with the accumulated value and only an extra
     * new operand. Second input value must be ignored if the operation does not
     * correspond to the first one.
     *
     * @param operation operation to add, as string, "+", "-", "*", "/".
     * @param values Operands of the new operation (one or two operands).
     * Uses the varargs feature.
     * https://docs.oracle.com/javase/8/docs/technotes/guides/language/varargs.html
     * @throws IllegalArgumentException If the operation does not exist.
     */
    public void addOperation ( String operation , float ... values ) {

        String validOperations = "+-*/";

        if (validOperations.contains(operation)) this.operators.add(operation);
        else throw new IllegalArgumentException("Operation does not exist");

        if (this.operands.isEmpty())
            for (float value: values) this.operands.add(value);

        else this.operands.add(values[0]);
    }

    /**
     * Execute the set of operations of the internal state of the calculator.
     * Once execution is finished, internal state (operands and operations)
     * is restored (EVEN if exception occurs).
     * This calculator works with "Batches" of operations.
     * @return result of the execution
     * @throws ArithmeticException If the operation returns an invalid value
     * (division by zero)
     */
    public float executeOperations () {

        try {
            float result = this.operands.getFirst();

            for (int i = 0; i < this.operators.size(); i++ ) {

                String operator = this.operators.get(i);
                float operand = this.operands.get(i+1);

                switch (operator) {
                    case "+" -> result += operand;
                    case "-" -> result -= operand;
                    case "*" -> result *= operand;
                    default -> {
                        if (operand == 0) throw new ArithmeticException("Invalid operation (division by zero)");
                        else result /= operand;
                    }
                }
            }

            return result;
        } finally {
            cleanOperations();
        }
    }

    /**
     * Current internal state of calculator is printed
     * FORMAT:
     * "[{+/ -/"/"/*}]value1_value2[{+/ -/"/"/*}]value1[{+/ -/"/"/*}]value1 {...}"
     * EXAMPLES:
     * "[+]4.5_6.8[-]3.1[/]6.0"
     * "[-]3.7_5.8[*]4.8[/]2.0[+]2.04"
     * @return String of the internal state of the calculator
     */
    @Override
    public String toString () {

        String format = "";
        format += String.format("[%s]", this.operators.getFirst());
        format += this.operands.getFirst().toString().concat("_");
        format += this.operands.get(1).toString();

        for (int i = 1; i < this.operators.size(); i++ ) {
            format += String.format("[%s]", this.operators.get(i));
            format += this.operands.get(i+1).toString();
        }

        return format;
    }
}
package e1;

public class StringCount {

    /**
     * Counts the number of words in a given String.
     * Words are groups of characters separated by one or more spaces.
     *
     * @param text String with the words
     * @return Number of words in the String or zero if it is null
     */

    public static int countWords ( String text ) {

        // Check if the string is null or has no chars in it
        if (text == null || text.isBlank()) return 0;

        // Divide the string by spaces and create an array with every word in it
        String[] words = text.trim().split("\\s+");

        return words.length;
    }

    /**
     * Counts the number of times the given character appears in the String.
     * Accented characters are considered different characters.
     * @param text String with the characters
     * @param c the character to be found
     * @return Number of times the character appears in the String or zero if null
     */

    public static int countChar ( String text , char c) {

        if (text == null) return 0;

        int count = 0;

        for (int i = 0; i < text.length(); i++) {
            if (text.charAt(i) == c) count++;
        }

        return count;
    }

    /**
     * Counts the number of times the given character appears in the String.
     * The case is ignored so an 'a' is equal to an 'A'.
     * Accented characters are considered different characters.
     * @param text String with the characters
     * @param c the character to be found
     * @return Number of times the character appears in the String or zero if null
     */

    public static int countCharIgnoringCase ( String text , char c ) {

        if (text == null) return 0;

        int count = 0;

        for (int i = 0; i < text.length(); i++) {
            if (Character.toLowerCase(text.charAt(i)) == Character.toLowerCase(c)) count++;
        }

        return count;
    }

    /**
     * Checks if a password is safe according to the following rules:
     * - Has at least 8 characters
     * - Has an uppercase character
     * - Has a lowercase character
     * - Has a digit
     * - Has a special character among these: '?', '@', '#', '$', '.' and ','
     * @param password The password, we assume it is not null.
     * @return true if the password is safe, false otherwise
     */

    public static boolean isPasswordSafe ( String password ) {

        if (password.length() < 8) return false;

        boolean hasUpper = false;
        boolean hasLower = false;
        boolean hasDigit = false;
        boolean hasSpecial = false;

        String specialChars = "?@#$.,";

        for (int i = 0; i < password.length(); i++) {

            char c = password.charAt(i);

            if (Character.isUpperCase(c)) hasUpper = true;
            else if (Character.isLowerCase(c)) hasLower = true;
            else if (Character.isDigit(c)) hasDigit = true;
            else if (specialChars.indexOf(c) != -1) hasSpecial = true;
        }

        return hasUpper && hasLower && hasDigit && hasSpecial;
    }
}
import java.lang.Math;
import java.util.ArrayList;
import java.math.BigInteger;
import java.util.Scanner;
/** *************************************************************************
 * CS454 - Project 1: DFA Counting                                          *
 * Sean Sponsler, Evan Walters                                              *
 * Spring 2023                                                              *
 * Description: This program takes the given DFA and counts the number      *
 * of strings of length N that are accepted by the DFA                      *
 *                                                                          *
 * DFA: Given string w of length 0<=N<=300, using the alphabet = {a,b,c,d}, *
 * any substring of length 6 in string w, must have one of each symbol      *
 * Strings less than length 6 are accepted                                  *
 *                                                                          *
 ***************************************************************************/

public class P1 {

    /** *************************************************************************
     * main                                                                     *
     * Description: Main runner, will ask user for input of n between 0 and 300,*
     * or -1 to quit.                                                           *
     * Will return value of count(n) to console                                 *
     ***************************************************************************/
    public static void main(String[] args) {
        int n = 0;
        Scanner scan = new Scanner(System.in);
        System.out.print("Input a length N (0-300) to find the amount of possible strings for the DFA (-1 to quit): ");
        n = scan.nextInt();
        while (n != -1) {
            while (n < 0 || n > 300) {
                System.out.print("N is outside of accepted range (0<= N <= 300). Please enter a value for N within this range: ");
                n = scan.nextInt();
            }
            System.out.println("\nThe number of valid strings of length: " + n + " for the DFA is: " + count(n) + "\n");
            System.out.print("Input a length N (0-300) to find the amount of possible strings for the DFA (-1 to quit): ");
            n = scan.nextInt();
        }
        scan.close();
    }
    /** ************************************************************************
     * delta                                                                   *
     * Input: int stateNum: current state index,                               *
     *        Char input: next input number                                    *
     * Output: integer of resulting state number in DFA                        *
     *                                                                         *
     * Description: The state number and symbol numbers will be decoded into   *
     *              a string and char respectively to break down.              *
     *              The function will iterate through the decoded state string,*
     *              evaluate the presence of each required symbol, and check   *
     *              if the new symbol will satisfy the DFA. If the result is a *
     *              reject state (there is one or more missing symbols with    *
     *              length < 6), "reject" is encoded as the resulting output.  *
     *              Otherwise, the resulting state of stateNum + symbolNum is  *
     *              encoded as the output.                                     *
     *                                                                         *
     **************************************************************************/
    public static int delta(int stateNum, int symbolNum) {
        String state = decode(stateNum);
        char input = 0;

        //reject if already in rejecting state
        if (state == "reject") {return encode(state); }

        //decode invidual symbol number into character
        switch(symbolNum) {
            case 0: input = 'a';
                break;
            case 1: input = 'b';
                break;
            case 2: input = 'c';
                break;
            case 3: input = 'd';
                break;
        }

        String newState = state + input;
        boolean a = false, b = false, c = false, d = false;

        //setting boolean flags for existing characters in completed state
        for (int i = 0; i < newState.length(); i++) {
            if (newState.charAt(i) == 'a') { a = true;}
            else if (newState.charAt(i) == 'b') { b = true;}
            else if (newState.charAt(i) == 'c') { c = true;}
            else if (newState.charAt(i) == 'd') { d = true;}
            else {
                System.err.println("ERROR: State houses incorrect symbol.");
                System.exit(1);
            }
        }
        if (newState.length() < 6) {
            return encode(newState);
        }
        else if (a && b && c && d) {
            //cut off first character
            //java substring: inclusive beginIndex, exclusive endIndex
            return encode(newState.substring(1,6));
        }

        else { return encode("reject"); }
    }

    /** ************************************************************************
     * encode                                                                  *
     * Input: String state: state within DFA                                   *
     *                                                                         *
     * Output: integer representing state number of DFA                        *
     *                                                                         *
     * Description: Using {0,1,2,3} as our conversion base, convert the given  *
     *              String state of symbols {a,b,c,d} to an integer            *
     *              representation. An offset is given at each iterative length*
     *              of the string of 4^i, which is needed to determine         *
     *              successive values of a = 0 in the string. For example:     *
     *              "abcd" => (0 * 4^3)+(1 * 4^2)+(2 * 4^1)+(3 * 4^0) = 27,    *
     *              with a needed offset of =>(4^0 + 4^1 + 4^2) = 21).         *
     *              Therefore the encoded integer would be (27+21) = 48        *
     *                                                                         *
     **************************************************************************/
    public static int encode(String state) {
        int encodedInt = 0;
        //reject relates to final state in DFA
        if (state=="reject") return 1365;
        for (int i = 0; i < state.length(); i++) {
            int exp = state.length() - (i+1);
            switch(state.charAt(i)) {
                case 'a':
                    //0
                    encodedInt += (0 * Math.pow(4, exp));
                    break;
                case 'b':
                    //1
                    encodedInt += (1 * Math.pow(4, exp));
                    break;
                case 'c':
                    //2
                    encodedInt += (2 * Math.pow(4, exp));
                    break;
                case 'd':
                    //3
                    encodedInt += (3 * Math.pow(4, exp));
                    break;
            }
            //need to add positional offset
            encodedInt += (Math.pow(4, i));
        }
        return encodedInt;
    }

    /** ************************************************************************
     * decode                                                                  *
     * Input: int stateNum: state number of DFA between 0 and 1365             *
     *                                                                         *
     * Output: Valid string state of DFA                                       *
     *                                                                         *
     * Description: Using {a,b,c,d} as our conversion base, convert the given  *
     *              state number to the corresponding string within the DFA.   *
     *              Working backwards in relation to encode, we determine the  *
     *              proper offset within powers of 4 to find the length of the *
     *              string. From this length, we iterate through 0-L and       *
     *              subtract powers of 4^i to retrieve the raw state number    *
     *              with no offset. We then push remainders of division by 4   *
     *              into a list where we determine the character at each index *
     *                                                                         *
     **************************************************************************/
    public static String decode(int stateNum) {
        int temp = stateNum;
        int L = 0; //length
        //store numerical remainders
        ArrayList<Integer> remainders = new ArrayList<Integer>(); 
        String resState = "";
        if (stateNum == 1365) {	// reject state
		    return "reject";
        }
        else if (stateNum > 1364) {
            System.err.println("ERROR: stateNum is too large. Terminating...");
            System.exit(1);
        }
        else if (stateNum < 0) {
            System.err.println("ERROR: stateNum cannot be below zero. Terminating...");
            System.exit(1);
        }
        else if (stateNum == 0)	// empty state
            return "";
        //find length by checking range of offsets
        else if (stateNum >= 1 && stateNum <= 4)
            L = 1;
        else if (stateNum >= 5 && stateNum <= 20)
            L = 2;
        else if (stateNum >= 21 && stateNum <= 84)
            L = 3;
        else if (stateNum >= 85 && stateNum <= 340)
            L = 4;
        else if (stateNum >= 341 && stateNum <= 1364)
            L = 5;
        else {
            System.err.println("ERROR: Invalid stateNum. Terminating...");
            System.exit(1);
        }

        //substract to account for leading a's (0)
        for (int i = 0; i < L; i++) {
            temp -= Math.pow(4, i);
        }
        //push remainders onto list
        for (int i = 0; i < L; i++) {
            remainders.add(temp % 4);
            temp /= 4;
        }
        //convert list of remainders to symbols in reverse order
        for (int i = remainders.size() - 1; i >= 0; i--) {
            if (remainders.get(i) == 0) { resState += 'a';}
            else if (remainders.get(i) == 1) { resState += 'b';}
            else if (remainders.get(i) == 2) { resState += 'c';}
            else if (remainders.get(i) == 3) { resState += 'd';}
        }        
        return resState;
    }

    /** ************************************************************************
     * count                                                                   *
     * Input: int n: Requested length of string (0 - 300)                      *
     *                                                                         *
     * Output: BigInteger representing the sum of all strings accepted by the  *
     *         DFA                                                             *
     *                                                                         *
     * Description: Counts the number of strings which are accepted by the DFA *
     *              starting from 0 to n. Two lists current and next are       *
     *              initialized with 1s and 0s respectively (the final index   *
     *              of current is initialized to 0 as the reject state). The   *
     *              function will loop through 0 to the given size n and check *
     *              every state and every possible state symbol to add.        *
     *                                                                         *
     **************************************************************************/
    public static BigInteger count(int n) {
        //max size of array (1365 is reject state)
        int SIZE = 1366;
        BigInteger[] current = new BigInteger[SIZE];
        BigInteger[] next = new BigInteger[SIZE];

        //assign 1 to every position in current except the last position
        for (int i = 0; i < SIZE; i++) {
            current[i] = BigInteger.valueOf(1);
        }
        //initializing next to prevent adding to null value
        for (int i = 0; i < SIZE; i++) {
            next[i] = BigInteger.valueOf(0);
        }

        //for reject state
        current[SIZE - 1] = BigInteger.valueOf(0);

        //loop for given size
        for (int s = 0; s < n; s++) {
            //inner double loop to look at every input(j) for each state(i)
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < 4; j++) {
                    next[i] = next[i].add(current[delta(i,j)]);
                }
            }

            //copy next into current and reset next
            for (int k = 0; k < SIZE; k++) {
                current[k] = next[k];
                next[k] = BigInteger.valueOf(0);
            }
        }
        return current[0];
    }
}

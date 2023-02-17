import java.lang.Math;
import java.util.ArrayList;
import java.math.BigInteger;
import java.util.Scanner;
/** *******************
 * CS454 - Project 1
 * Sean Sponsler, Evan Walters
 * Spring 2023
 * 
 * 
 **********************/
public class P1 {
    public static void main(String[] args) {
        int n = 0;
        Scanner scan = new Scanner(System.in);
        System.out.print("Input a length N (1-300) to find the amount of possible strings for the DFA: ");
        n = scan.nextInt();
        System.out.println("The number of valid strings of length: " + n + " for the DFA is: " + count(n));
    }
    /*
     * delta
     * Input: String state, Char input
     * Output: 
     * 
     */
    public static int delta(int stateNum, int symbolNum) {
        String state = decode(stateNum);
        //System.out.println("state: " + state);
        //System.out.println("stateNum: " + stateNum);
        char input = 0;

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
        //can't get states with > 5 symbols, unless it's the rejecting state
        //if (state.length() <= 5) throw new RuntimeException("Invalid state length!");

        //reject if already in rejecting state
        if (state == "reject") {return encode(state); }

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
            //java substring: inclusive beginIndex, exclusive endIndex
            return encode(newState.substring(1,6));
        }

        else { return encode("reject"); }
    }
    /*
     * Using {0,1,2,3} as our conversion base,
     * Convert the String s to Base4
     * i.e.: 
     * abcd => (0 * 4^3)+(1 * 4^2)+(2 * 4^1)+(3*4^0)
     * + the offset needed, in case length = 4
     * => offset = (4^0 + 4^1 + 4^2) = 21
     * 
     */
    public static int encode(String s) {
        int encodedInt = 0;

        if (s=="reject") return 1365;
        for (int i = 0; i < s.length(); i++) {
            int exp = s.length() - (i+1);
            switch(s.charAt(i)) {
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
    /*
     * 
     */
    public static String decode(int stateNum) {
        int temp = stateNum;
        int L = 0; //length
        ArrayList<Integer> remainders = new ArrayList<Integer>(); //store numerical remainders
        String resState = "";
        if (stateNum == 1365) {	// reject state
		    return "reject";
        }
        else if (stateNum < 0) {
            System.err.println("ERROR: stateNum cannot be below zero. Terminating...");
            System.exit(1);
        }
        else if (stateNum == 0)	// empty state
            return "";
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
        else if (stateNum > 1364) {
            System.err.println("ERROR: stateNum is too large. Terminating...");
            System.exit(1);
        }
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

    
    public static BigInteger count(int n) {
        int SIZE = 1366;
        BigInteger[] current = new BigInteger[SIZE];
        BigInteger[] next = new BigInteger[SIZE];

        //assign 1 to every position in current except the last position
        for (int i = 0; i < SIZE; i++) {
            current[i] = BigInteger.valueOf(1);
        }
        System.out.println("current[0] val: " + current[0]);
        //initializing next to prevent adding to null value
        for (int i = 0; i < SIZE; i++) {
            next[i] = BigInteger.valueOf(0);
        }

        //for reject state
        //current[SIZE - 1] = BigInteger.valueOf(0);

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
                
                //System.out.println("next[0] val: " + next[0]);
                current[k] = next[k];
                next[k] = BigInteger.valueOf(0);
            }
        }
        return current[0];
    }
}

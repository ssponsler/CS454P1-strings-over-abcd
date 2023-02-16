import java.lang.Math;
import java.util.ArrayList;

public class P1 {
    public static void main(String[] args) {
        System.out.println(encode("ddddd"));
        //List<List<Integer>> delta = new ArrayList<List<Integer>>();
        System.out.println("Testing string 'abacb': " + delta("abacb", 'c'));
        System.out.println("Testing string 'abacb': " + delta("abacb", 'd'));
        System.out.println("Testing DECODE for 89: " + decode(89));
    }

    public static String delta(String state, char input) {
        if (state == "reject") { return "reject"; }

        String newState = state + input;
        boolean a = false, b = false, c = false, d = false;

        for (int i = 0; i < newState.length(); i++) {
            if (newState.charAt(i) == 'a') { a = true;}
            else if (newState.charAt(i) == 'b') { b = true;}
            else if (newState.charAt(i) == 'c') { c = true;}
            else if (newState.charAt(i) == 'd') { d = true;}
            else {
                System.err.println("ERROR: State houses incorrect symbol.");
                return null;
            }
        }
        if (newState.length() < 6) {
            return newState;
        }
        else if (a && b && c && d) {
            return newState.substring(1,6);
        }

        else { return "reject"; }
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
        else {
            System.err.println("\nERROR: stateNum is too large. Terminating...\n");
            System.exit(1);
        }
        for (int i = 0; i < L; i++) {
            temp -= Math.pow(4, i);
        }

        for (int i = 0; i < L; i++) {
            remainders.add(temp % 4);
            temp /= 4;
        }

        for (int i = remainders.size() - 1; i >= 0; i--) {
            if (remainders.get(i) == 0) { resState += 'a';}
            else if (remainders.get(i) == 1) { resState += 'b';}
            else if (remainders.get(i) == 2) { resState += 'c';}
            else if (remainders.get(i) == 3) { resState += 'd';}
        }    
        return resState;
    }
}

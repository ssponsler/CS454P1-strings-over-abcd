import java.lang.Math;

public class P1 {
    public static void main(String[] args) {
        System.out.println(encode("bac"));
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
    public static String decode(int n) {
        String decodedString = "";
        
        return decodedString;
    }
}

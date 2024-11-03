import java.util.Scanner;

public class hrllo {
    public static void main(String[] args) {
    
        Scanner in = new Scanner(System.in);
        String str = in.nextLine();
        
     
        int[] counts = new int[26];
        
        
        for (char c : str.toCharArray()) {
            if (Character.isLetter(c)) {
              
                int index = Character.toUpperCase(c) - 'A';
                counts[index]++;
            }
        }
        
     
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < 26; i++) {
            if (counts[i] > 0) {
              
                char letter = (char)('A' + i);
                result.append("(").append(letter).append(")Num=").append(counts[i]).append("\n");
            }
        }
        
        
        System.out.print(result.toString());
        
        in.close();
    }
}
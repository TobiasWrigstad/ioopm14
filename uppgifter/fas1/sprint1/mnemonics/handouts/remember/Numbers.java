package remember;

import java.io.*;
import java.util.*;

public class Numbers {
    // E | J N Q | R W X | D S Y | F T | A M | C I V | B K U | L O P | G H Z
    // e | j n q | r w x | d s y | f t | a m | c i v | b k u | l o p | g h z
    // 0 |   1   |   2   |   3   |  4  |  5  |   6   |   7   |   8   |   9
    private static final String digit0 = "Ee";
    private static final String digit1 = "JNQjnq";
    private static final String digit2 = "RWXrwx";
    private static final String digit3 = "DSYdsy";
    private static final String digit4 = "FTft";
    private static final String digit5 = "AMam";
    private static final String digit6 = "CIVciv";
    private static final String digit7 = "BKUbku";
    private static final String digit8 = "LOPlop";
    private static final String digit9 = "GHZghz";

    public static String lettersForDigit(String digit) {
	switch (Integer.parseInt(digit)) {
	case 0: return digit0;
	case 1: return digit1;
	case 2: return digit2;
	case 3: return digit3;
	case 4: return digit4;
	case 5: return digit5;
	case 6: return digit6;
	case 7: return digit7;
	case 8: return digit8;
	case 9: return digit9;
	default:
	    assert false; 
	    return null;
	}
    }

    public static void processWithDictionary(final String fileName, final Dictionary dict) {
	processWithDictionary(new File(fileName), dict);
    }
    
    public static void processWithDictionary(final File f, final Dictionary dict) {
	final Numbers converter = new Numbers(dict);
	FileUtils.processEachLine(f, new FileUtils.Apply() {
		public void apply(String word) {
		    converter.findCombinationsForNumber(word.trim());
		}
	    });
    }

    private final Dictionary dict;

    public Numbers(Dictionary dict) {
	this.dict = dict;
    }

    public static String lastWord(String words) {
	int idx = words.lastIndexOf(" ");
	return (idx < 0) ? words : words.substring(idx+1);
    }

    private final void solve(String number, int index, String words) {
	if (index >= number.length()) {
	    String lastWord = lastWord(words);
	    if (dict.contains(lastWord)) 
		System.err.println(number + ": " + words);
	    return;
	}

	String letters = Numbers.lettersForDigit(number.substring(index, index + 1));

	for (int i=0; i<letters.length(); ++i) {
	    String word = lastWord(words) + letters.charAt(i);
	    if (dict.contains(word)) {
		solve(number, index+1, words + letters.charAt(i) + " ");
	    }
	    if (dict.couldMatch(word)) {
		solve(number, index+1, words + letters.charAt(i));
	    }
	}
    }

    public void findCombinationsForNumber(String number) {
	solve(number, 0, "");
    }
}

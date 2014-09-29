package remember;

public class Mnemonics {
    public static void main(String[] args) {
	if (args.length == 2) {
	    Dictionary dict = Dictionary.createFromFile(args[0]);
	    Numbers.processWithDictionary(args[1], dict);
	} else {
	    System.err.println("Usage: java Mnemonics <dictionary> <numbers>");
	}
    }
}


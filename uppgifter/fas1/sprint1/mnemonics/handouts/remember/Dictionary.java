package remember;

import java.io.*;
import java.util.*;

public class Dictionary {
    public static Dictionary createFromFile(final String fileName) {
	return createFromFile(new File(fileName));
    }

    public static Dictionary createFromFile(final File f) {
	final Dictionary dict = new Dictionary();
	FileUtils.processEachLine(f, new FileUtils.Apply() {
		public void apply(String word) {
		    dict.insert(word.trim());
		}
	    });
	return dict;
    }

    private final Set<String> words = new HashSet<String>();

    public void insert(String word) {
	words.add(word);
    }

    public boolean contains(String word) {
	return words.contains(word);
    }

    public boolean couldMatch(String match) {
	for (String word : words) {
	    if (word.startsWith(match)) return true;
	}
	return false;
    }

    public String toString() {
	return "Dictionary(" + words + ")";
    }
}

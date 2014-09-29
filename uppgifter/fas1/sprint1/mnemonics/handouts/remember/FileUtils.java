package remember;

import java.io.*;
import java.util.*;

public class FileUtils {
    public static interface Apply { public void apply(String line); }
    
    public static void processEachLine(final File f, final Apply lambda) {
	try {
	    BufferedReader file = new BufferedReader(new FileReader(f));
	    for (String word = file.readLine(); word != null; word = file.readLine()) {
		lambda.apply(word);
	    }
	    file.close();
	} catch (IOException ioe) {
	    ioe.printStackTrace(System.err);
	    System.err.println("Error reading " + f + ", bailing out.\n\n");
	    System.exit(-1);
	}
    }
}

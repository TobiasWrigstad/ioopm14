public class Light {
    private int period;
    private int time;  // Intern klocka: 0, 1, ... period-1, 0, 1 ...
    private int green; // Signalen grön när time<green 

    public Light(int period, int green) {
    	//...
    	}

    public void    step() { 
       // Stegar fram klocka ett steg
    }

    public boolean isGreen()   {
    	return false;
    	// Returnerar true om time<green, annars false
    }

    public String  toString()  {
    	return null;
    	//...
    	}
	
}
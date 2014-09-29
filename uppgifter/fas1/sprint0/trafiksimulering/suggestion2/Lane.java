public class Lane {

    public static class OverflowException extends RuntimeException {
        // Undantag som kastas när det inte gick att lägga 
        // in en ny bil på vägen
    }

    protected CarPosition[] theLane;

    public Lane(int n) {
	// Konstruerar ett Lane-objekt med plats för n fordon
    // Samt länker ihop varje CarPosition med forward för den framför
    }
    
    public boolean matchEnd(CarPosition target)
    {
    	if(theLane[0] == target)
    		return true;
    	else
    		return false;
    }
    
    public int getLength(){
    	return theLane.length;
    }
    
    public void setParallel(Lane sideLane)
    {
    	int i = 0;
    	
    	while(i < sideLane.getLength() && i < theLane.length)
    	{
    		theLane[i].setTurn(sideLane.theLane[i]);
    		i++;
    	}
    }

    public void step() {
	// Stega fram alla fordon (utom det på plats 0) ett steg 
        // (om det går). (Fordonet på plats 0 tas bort utifrån 
	// mm h a metoden nedan.)
    }

    public Car getFirst() {
    	return null;
	// Returnera och tag bort bilen som står först
    }

    public Car firstCar() {
    	return null;
	// Returnera bilen som står först utan att ta bort den
    }


    public boolean lastFree() {
    	return false;
	// Returnera true om sista platsen ledig, annars false
    }

    public void putLast(Car c) throws OverflowException {
	// Ställ en bil på sista platsen på vägen
	// (om det går).
    }

    public String toString() {
    	return "";
    	//...
    	}

}
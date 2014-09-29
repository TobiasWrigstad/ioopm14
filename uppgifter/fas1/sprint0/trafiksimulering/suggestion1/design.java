/*
  Modell för trafiksimulering
  ===========================

  Följande klasser skall användas: 

     Car representerar fordon
         ankomsttid och destination som sätts när objektet skapas

     Light representerar ljussignaler
         Se nedan
  
     Lane representerar ett vägavsnitt
         En väg representeras av en array där varje element
	 antingen är tomt eller innehåller en referens till 
         ett bil-objekt.
         OBS: Klassen Lane påminner om kömekanismen i föregående
         uppgift men den skiljer sig också i flera avseende.
         I denna klass ställs nya bilar i ena änden av ARRAYEN
         och inte närmast efter den som finns där. I kömekanismen        
         var alltid elementen (kunderna) samlade medan bilarna
         i denna klass kan vara utspridda över hela arrayen.
         
 
     TrafficSystem
         Definierar de komponeneter dvs de vägar och signaler
	 som ingår i systemet. Se vidare nedan

     Simulation
         main-metod som driver simuleringen


  Den situation som skall simuleras ser schematiskt ut enligt



         C           B                               A
       s1<----r1-----<---------r0---------------------
       s2<----r2-----< 


  En fil (vägsträcka) r0 delar sig vid B i två filer r1 och r2.
  Signal s1 kontrollerar fil r1 och och signal s2 fil r2.
 
  Bilar uppstår vid A. Sannolikheten att en bil skall komma till A
  vid ett visst tidsteg kallas ankomstintensiteten.

  Vid ett tidssteg rör sig bilarna ett steg framåt (om platsen framför
  är ledig). Vid C tas bilarna ut från filerna om repektive
  signal är grön. Vid B tas bilar ut från r0 och läggs in på r1 eller r2
  beroende på destination (och om platsen är ledig).

  Anm: Man skulle kunna representera systemet med två Lane-objekt
  men då måste man ha något sätt att representera en "avtappning"
  (där svängfilen börjar). Med den här valda representationen
  blir Lane-klassen enklare.  
    
*/



// Skiss av klasser. Angivna klasser och metoder skall finnas.
// Det är tillåtet att tillfoga fler attribut och metoder

public class Car {

    private int bornTime;
    private int dest; // 1 för rakt fram, 2 för vänstersväng

    // konstruktor och get-metoder
    ...

    public String toString() {...}
	
}



public class Light {
    private int period;
    private int time;  // Intern klocka: 0, 1, ... period-1, 0, 1 ...
    private int green; // Signalen grön när time<green 

    public Light(int period, int green) {...}

    public void    step() { 
       // Stegar fram klocka ett steg
    }

    public boolean isGreen()   {
	// Returnerar true om time<green, annars false
    }

    public String  toString()  {... }
	
}



public class Lane {

    public static class OverflowException extends RuntimeException {
        // Undantag som kastas när det inte gick att lägga 
        // in en ny bil på vägen
    }

    private Car[] theLane;

    public Lane(int n) {
	// Konstruerar ett Lane-objekt med plats för n fordon
    }

    public void step() {
	// Stega fram alla fordon (utom det på plats 0) ett steg 
        // (om det går). (Fordonet på plats 0 tas bort utifrån 
	// mm h a metoden nedan.)
    }

    public Car getFirst() {
	// Returnera och tag bort bilen som står först
    }

    public Car firstCar() {
	// Returnera bilen som står först utan att ta bort den
    }


    public boolean lastFree() {
	// Returnera true om sista platsen ledig, annars false
    }

    public void putLast(Car c) throws OverflowException {
	// Ställ en bil på sista platsen på vägen
	// (om det går).
    }

    public String toString() {...}

}



public class TrafficSystem {
    // Definierar de vägar och signaler som ingår i det 
    // system som skall studeras.
    // Samlar statistik
    
    // Attribut som beskriver beståndsdelarna i systemet
    private Lane  r0;
    private Lane  r1;
    private Lane  r2;
    private Light s1;
    private Light s2;

    // Diverse attribut för simuleringsparametrar (ankomstintensiteter,
    // destinationer...)

    // Diverse attribut för statistiksamling
    ....    
    
    private int time = 0;

    public TrafficSystem() {...}

    public readParameters() {
	// Läser in parametrar för simuleringen
	// Metoden kan läsa från terminalfönster, dialogrutor
	// eller från en parameterfil. Det sista alternativet
	// är att föredra vid uttestning av programmet eftersom
	// man inte då behöver mata in värdena vid varje körning.
        // Standardklassen Properties är användbar för detta. 
    }

    public void step() {
	// Stega systemet ett tidssteg m h a komponenternas step-metoder
	// Skapa bilar, lägg in och ta ur på de olika Lane-kompenenterna
    }

    public void printStatistics() {
	// Skriv statistiken samlad så här långt
    }

    public void print() {
	// Skriv ut en grafisk representation av kösituationen
	// med hjälp av klassernas toString-metoder
    }

}



public class Simulation {

    public static void main(String [] args) {
	// Skapar ett TrafficSystem
	// Utför stegningen, anropar utskriftsmetoder

	...

    }
}

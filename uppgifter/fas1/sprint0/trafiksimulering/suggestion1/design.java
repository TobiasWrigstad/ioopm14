/*
  Modell f�r trafiksimulering
  ===========================

  F�ljande klasser skall anv�ndas: 

     Car representerar fordon
         ankomsttid och destination som s�tts n�r objektet skapas

     Light representerar ljussignaler
         Se nedan
  
     Lane representerar ett v�gavsnitt
         En v�g representeras av en array d�r varje element
	 antingen �r tomt eller inneh�ller en referens till 
         ett bil-objekt.
         OBS: Klassen Lane p�minner om k�mekanismen i f�reg�ende
         uppgift men den skiljer sig ocks� i flera avseende.
         I denna klass st�lls nya bilar i ena �nden av ARRAYEN
         och inte n�rmast efter den som finns d�r. I k�mekanismen        
         var alltid elementen (kunderna) samlade medan bilarna
         i denna klass kan vara utspridda �ver hela arrayen.
         
 
     TrafficSystem
         Definierar de komponeneter dvs de v�gar och signaler
	 som ing�r i systemet. Se vidare nedan

     Simulation
         main-metod som driver simuleringen


  Den situation som skall simuleras ser schematiskt ut enligt



         C           B                               A
       s1<----r1-----<---------r0---------------------
       s2<----r2-----< 


  En fil (v�gstr�cka) r0 delar sig vid B i tv� filer r1 och r2.
  Signal s1 kontrollerar fil r1 och och signal s2 fil r2.
 
  Bilar uppst�r vid A. Sannolikheten att en bil skall komma till A
  vid ett visst tidsteg kallas ankomstintensiteten.

  Vid ett tidssteg r�r sig bilarna ett steg fram�t (om platsen framf�r
  �r ledig). Vid C tas bilarna ut fr�n filerna om repektive
  signal �r gr�n. Vid B tas bilar ut fr�n r0 och l�ggs in p� r1 eller r2
  beroende p� destination (och om platsen �r ledig).

  Anm: Man skulle kunna representera systemet med tv� Lane-objekt
  men d� m�ste man ha n�got s�tt att representera en "avtappning"
  (d�r sv�ngfilen b�rjar). Med den h�r valda representationen
  blir Lane-klassen enklare.  
    
*/



// Skiss av klasser. Angivna klasser och metoder skall finnas.
// Det �r till�tet att tillfoga fler attribut och metoder

public class Car {

    private int bornTime;
    private int dest; // 1 f�r rakt fram, 2 f�r v�nstersv�ng

    // konstruktor och get-metoder
    ...

    public String toString() {...}
	
}



public class Light {
    private int period;
    private int time;  // Intern klocka: 0, 1, ... period-1, 0, 1 ...
    private int green; // Signalen gr�n n�r time<green 

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
        // Undantag som kastas n�r det inte gick att l�gga 
        // in en ny bil p� v�gen
    }

    private Car[] theLane;

    public Lane(int n) {
	// Konstruerar ett Lane-objekt med plats f�r n fordon
    }

    public void step() {
	// Stega fram alla fordon (utom det p� plats 0) ett steg 
        // (om det g�r). (Fordonet p� plats 0 tas bort utifr�n 
	// mm h a metoden nedan.)
    }

    public Car getFirst() {
	// Returnera och tag bort bilen som st�r f�rst
    }

    public Car firstCar() {
	// Returnera bilen som st�r f�rst utan att ta bort den
    }


    public boolean lastFree() {
	// Returnera true om sista platsen ledig, annars false
    }

    public void putLast(Car c) throws OverflowException {
	// St�ll en bil p� sista platsen p� v�gen
	// (om det g�r).
    }

    public String toString() {...}

}



public class TrafficSystem {
    // Definierar de v�gar och signaler som ing�r i det 
    // system som skall studeras.
    // Samlar statistik
    
    // Attribut som beskriver best�ndsdelarna i systemet
    private Lane  r0;
    private Lane  r1;
    private Lane  r2;
    private Light s1;
    private Light s2;

    // Diverse attribut f�r simuleringsparametrar (ankomstintensiteter,
    // destinationer...)

    // Diverse attribut f�r statistiksamling
    ....    
    
    private int time = 0;

    public TrafficSystem() {...}

    public readParameters() {
	// L�ser in parametrar f�r simuleringen
	// Metoden kan l�sa fr�n terminalf�nster, dialogrutor
	// eller fr�n en parameterfil. Det sista alternativet
	// �r att f�redra vid uttestning av programmet eftersom
	// man inte d� beh�ver mata in v�rdena vid varje k�rning.
        // Standardklassen Properties �r anv�ndbar f�r detta. 
    }

    public void step() {
	// Stega systemet ett tidssteg m h a komponenternas step-metoder
	// Skapa bilar, l�gg in och ta ur p� de olika Lane-kompenenterna
    }

    public void printStatistics() {
	// Skriv statistiken samlad s� h�r l�ngt
    }

    public void print() {
	// Skriv ut en grafisk representation av k�situationen
	// med hj�lp av klassernas toString-metoder
    }

}



public class Simulation {

    public static void main(String [] args) {
	// Skapar ett TrafficSystem
	// Utf�r stegningen, anropar utskriftsmetoder

	...

    }
}

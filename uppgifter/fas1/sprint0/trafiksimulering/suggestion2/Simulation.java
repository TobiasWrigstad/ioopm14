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





public class Simulation {

    public static void main(String [] args) {
	// Skapar ett TrafficSystem
	// Utför stegningen, anropar utskriftsmetoder

	//...

    }
}

// extends ==> "is a(n)"
// "en hund är ett djur" och ärver därför alla egenskaper som ett
// djur har
class Dog extends Animal{
    private String race;

    public Dog(String name, String race, int age){
        // super ==> "min superklass"
        // I det här fallet Animals konstruktor
        super(name, age);
        this.race = race;
    }

    // Den här metoden är privat och kan alltså inte anropas från
    // någon annan klass
    private boolean isPuppy(){
        // Om det inte står något framför en variabel eller metod
        // läggs "this." in automatiskt.
        return getAge() < 3;
    }

    public void speak(){
        if(isPuppy())
            System.out.println("Viff viff viff!");
        else
            System.out.println("Voff voff voff!");
    }

    // Alla objekt har en toString-metod som är den som anropas
    // när man försöker använda objektet som en sträng. Till
    // exempel anropas den här metoden om man skriver så här:
    // Dog d = new Dog("Fido", "Pudel", 9);
    // System.out.println(d);
    public String toString(){
        if(isPuppy())
            return "en liten " + race;
        else
            return "en " + race;
    }
}
class Animal{
    // Attribut (fields)
    // "Vilka egenskaper har ett djur?"
    // private ==> inte synlig utanför klassen
    private String name;
    private int age;

    // Konstruktor(er)
    // "Hur skapar man ett djur?"
    // public ==> synlig för alla klasser
    public Animal(String name, int age){
        // "this" refererar till objektet som anropades (i det här
        // fallet objektet som håller på att skapas)
        this.name = name;
        this.age = age;
    }

    // Metoder
    // "Vad kan djur göra?"
    public String getName(){
        return this.name;
    }

    public int getAge(){
        return this.age;
    }

    public void speak(){
        System.out.println("???");
    }

    public String toString(){
        return "ett djur";
    }
}
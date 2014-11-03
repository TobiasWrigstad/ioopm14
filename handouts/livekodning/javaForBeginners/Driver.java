class Driver{
    public static void main(String args[]){
        Storyteller s = new Storyteller();

        Dog d1 = new Dog("Fido", "Labrador", 8);
        Dog d2 = new Dog("Lufsen", "Dalmatiner", 2);
        Duck a = new Duck("Kalle", 89);

        s.tellStory(d1, a);
        System.out.println("===========");
        s.tellStory(a, d2);
    }
}
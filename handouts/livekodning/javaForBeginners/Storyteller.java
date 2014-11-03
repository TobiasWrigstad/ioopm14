class Storyteller{
    public void tellStory(Animal a1, Animal a2){
        System.out.println("Det var en gång " + a1 +
                           " som hette " + a1.getName());
        System.out.println(a1.getName() + " sa: ");
        a1.speak();

        System.out.println("En dag mötte " + a1.getName() +
                           " " + a2 + " som hette " + a2.getName());
        System.out.println(a2.getName() + " sa:");
        a2.speak();

        System.out.println("Sen levde de lyckliga i alla sina dagar");
    }
}
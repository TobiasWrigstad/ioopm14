class Duck extends Animal{
    private boolean isAlive;

    public Duck(String name, int age){
        super(name, age);
        this.isAlive = true;
    }

    public void speak(){
        if(this.isAlive){
            System.out.println("Quack quack!");
        }
        else{
            System.out.println("...");
        }
    }

    public void kill(){
        this.isAlive = false;
    }

    public String toString(){
        return "en anka";
    }
}
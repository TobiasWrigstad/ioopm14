package model;

public class Input {
    public enum Dir { UP, DOWN };
    final public BarKey key;
    final public Dir dir;

    public Input(BarKey key, Dir dir) {
        this.key = key;
        this.dir = dir;
    }
}

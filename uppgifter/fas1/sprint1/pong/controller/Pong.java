package controller;

import java.awt.event.*;
import view.*;
import model.*;

import java.util.Map;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Set;
import java.util.Collections;

import javax.swing.*;

class Pong {
    public static void main(String[] args) {
        ControllerOptions opt = new ControllerOptions();

        for (String arg : args) {
            opt.parse(arg);
        }
        
        final PongController controller = new PongController(opt);

        controller.loop();
    }
}

class ControllerOptions {
    private int framerate = 30;
    private String leftPlayer = "Left Player";
    private char leftPlayerUp = 'w';
    private char leftPlayerDown = 's';

    private String rightPlayer = "Right Player";
    private char rightPlayerUp = 'i';
    private char rightPlayerDown = 'k';
    public ControllerOptions parse(String opt) {
        try {
            String[] parts = opt.split("=");
            switch (parts[0]) {
            case "--help":
                this.printUsage();
                System.exit(0);
            case "--framerate":
                this.framerate = new Integer(parts[1]);
                break;
            case "--leftPlayer":
                this.leftPlayer = parts[1];
                break;
            case "--rightPlayer":
                this.rightPlayer = parts[1];
                break;
            case "--leftPlayerUp":
                if (parts[1].length()>1) throw new RuntimeException("only one character as option!");
                this.leftPlayerUp = parts[1].charAt(0);
                break;
            case "--leftPlayerDown":
                if (parts[1].length()>1) throw new RuntimeException("only one character as option!");
                this.leftPlayerDown = parts[1].charAt(0);
                break;
            case "--rightPlayerUp":
                if (parts[1].length()>1) throw new RuntimeException("only one character as option!");
                this.rightPlayerUp = parts[1].charAt(0);
                break;
            case "--rightPlayerDown":
                if (parts[1].length()>1) throw new RuntimeException("only one character as option!");
                this.rightPlayerDown = parts[1].charAt(0);
                break;
            default:
                System.err.println("Unrecognized option: \""+opt+"\"");
                System.exit(1);
            }
        } catch (Exception e) {
            System.err.println("Couldn't parse option \""+opt+"\": " + e);
            System.exit(1);
        }
        return this;
    }

    private void printUsage() {
        System.out.println("SWING-PONG -- a pong implementation for the IOOPM course.");
        System.out.println("--help                   : show this help");
        System.out.println("--framerate=<int>        : set the target framerate (and game speed)");
        System.out.println("--leftPlayer=<name>      : set the left player name");
        System.out.println("--rightPlayer=<name>     : set the right player name");
        System.out.println("--leftPlayerUp=<char>    : set the left player up button (default: 'w')");
        System.out.println("--leftPlayerDown=<char>  : set the left player down button (default: 's')");
        System.out.println("--rightPlayerUp=<char>   : set the right player up button (default: 'w')");
        System.out.println("--rightPlayerDown=<char> : set the right player down button (default: 's')");
        System.out.println();
    }

    public int getFramerate() {
        return framerate;
    }

    public char getLeftPlayerUp() {
        return this.leftPlayerUp;
    }
    public char getLeftPlayerDown() {
        return this.leftPlayerDown;
    }
    public char getRightPlayerUp() {
        return this.rightPlayerUp;
    }
    public char getRightPlayerDown() {
        return this.rightPlayerDown;
    }

    public String getLeftPlayer() {
        return leftPlayer;
    }
    public String getRightPlayer() {
        return rightPlayer;
    }
}

class PongController implements KeyListener {
    private final ControllerOptions options;
    private final Map<Character, Input> inputMap;
    private final Set<Input> input = new HashSet<Input>();
    private final PongView view;
    private final PongModel model;

    public PongController(final ControllerOptions opt) {
        this.options = opt;
        this.model = new MyPongModel(options.getLeftPlayer(), options.getRightPlayer());
        this.view = new PongView(model);

        this.inputMap = Collections.unmodifiableMap(new HashMap<Character,Input>() {{
            put(options.getLeftPlayerUp(), new Input(BarKey.LEFT, Input.Dir.UP));
            put(options.getLeftPlayerDown(), new Input(BarKey.LEFT, Input.Dir.DOWN));
            put(options.getRightPlayerUp(), new Input(BarKey.RIGHT, Input.Dir.UP));
            put(options.getRightPlayerDown(), new Input(BarKey.RIGHT, Input.Dir.DOWN));
        }});
    }

    public void keyPressed(KeyEvent e) { }

    public void keyTyped(KeyEvent e) {
        if (inputMap.containsKey(e.getKeyChar())) {
            input.add(inputMap.get(e.getKeyChar()));
        }
    }

    public void keyReleased(KeyEvent e) {
        if (inputMap.containsKey(e.getKeyChar())) {
            input.remove(inputMap.get(e.getKeyChar()));
        }
    }

    public void loop() {
        final KeyListener This = this;
        SwingUtilities.invokeLater(new Runnable() {
                public void run() {
                    view.getFrame().addKeyListener(This);
                    view.show();
                }
            });

        long target_delta = 1000/options.getFramerate();
        long delta = 1000/options.getFramerate();
        for (;;) {
            try {
                long last_compute = System.currentTimeMillis();
                model.compute(input, delta);
                view.update();

                delta = System.currentTimeMillis() - last_compute;

                if (delta < target_delta) {
                    Thread.currentThread().sleep(target_delta-delta);
                }
                delta = System.currentTimeMillis() - last_compute;


            } catch (Exception ignore) {}
        }
    }
}

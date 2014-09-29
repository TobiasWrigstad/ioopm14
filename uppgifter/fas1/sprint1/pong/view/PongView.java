package view;

import javax.swing.*;
import java.awt.Point;
import java.awt.Color;
import java.awt.Font;
import java.awt.Dimension;
import java.awt.BorderLayout;

import java.util.Collections;
import java.util.Map;
import java.util.HashMap;

import model.PongModel;
import model.BarKey;

public class PongView {
    private final int WIDTH_PXL;
    private final int HEIGHT_PXL;

    private final PongModel model;

    final Map<BarKey,Bar> bars;
    final Map<BarKey,JLabel> scorelabels;
    final JLabel msglabel;
    final Ball ball;

    final JFrame frame;

    private JLabel makeScoreLabel(BarKey k) {
        JLabel ret = new JLabel("0");
        switch (k) {
        case LEFT:
            ret.setBounds(20,20, 50,50);
            ret.setHorizontalAlignment(SwingConstants.LEFT);
            break;
        case RIGHT:
            ret.setBounds(WIDTH_PXL-20-50,20, 50,50);
            ret.setHorizontalAlignment(SwingConstants.RIGHT);
            break;
        }
        ret.setForeground(Color.WHITE);
        ret.setBackground(Color.BLACK);
        ret.setFont(new Font("Mono", Font.PLAIN, 40));
        ret.setOpaque(true);
        return ret;
    }

    public PongView(PongModel model) {
        //initialize the View members:
        this.model = model;

        WIDTH_PXL = 600;
        HEIGHT_PXL = WIDTH_PXL*((int)model.getFieldSize().getHeight())/((int)model.getFieldSize().getWidth());

        this.ball = new Ball();

        this.bars = Collections.unmodifiableMap(new HashMap<BarKey,Bar>() {{
                    put(BarKey.LEFT, new Bar(0));
                    put(BarKey.RIGHT, new Bar(WIDTH_PXL));
                }});
        final Map<BarKey,JLabel> scorelabels = new HashMap<BarKey,JLabel>();

        // initialize the graphics stuff:
        final JFrame frame = new JFrame("SwingPong");
        final JLabel msglabel = new JLabel("Messages");
        try {
        SwingUtilities.invokeAndWait(new Runnable() {
                public void run() {
                    final int MSG_HEIGHT = 30;
                    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                    
                    frame.setLayout(null);
                    JLabel background = new JLabel("");
                    background.setBackground(Color.BLACK);
                    background.setOpaque(true);
                    background.setBorder(BorderFactory.createLineBorder(Color.WHITE));
                    background.setBounds(0,0,WIDTH_PXL,HEIGHT_PXL);

                    JLabel centerline = new JLabel("");
                    final int CENTERLINE_WIDTH = 5;
                    centerline.setBackground(Color.WHITE);
                    centerline.setOpaque(true);
                    centerline.setBounds(WIDTH_PXL/2-CENTERLINE_WIDTH/2,0,
                                         CENTERLINE_WIDTH, HEIGHT_PXL);

                    msglabel.setPreferredSize(new Dimension(WIDTH_PXL, MSG_HEIGHT));
                    msglabel.setBounds(1,10, WIDTH_PXL-20, MSG_HEIGHT);
                    msglabel.setForeground(Color.WHITE);
                    msglabel.setBackground(Color.BLACK);
                    msglabel.setOpaque(true);
                    msglabel.setHorizontalAlignment(SwingConstants.CENTER);

                    for (BarKey k : BarKey.values()) {
                        scorelabels.put(k, makeScoreLabel(k));
                    }

                    frame.getContentPane().setPreferredSize(new Dimension(WIDTH_PXL, HEIGHT_PXL));
                    
                    for (Bar bar : bars.values()) {
                        frame.getContentPane().add(bar.getJComponent());
                    }
                    frame.getContentPane().add(ball.getJComponent());
                    for (JLabel scorelabel : scorelabels.values()) {
                        frame.getContentPane().add(scorelabel);
                    }
                    frame.getContentPane().add(msglabel);
                    frame.getContentPane().add(centerline);
                    frame.getContentPane().add(background);
                    
                    frame.pack();
                }
            });
        } catch (Exception e) {
            System.err.println("Couldn't initialize PongView: " + e);
            System.exit(1);
        }
        this.frame = frame;
        this.msglabel = msglabel;
        this.scorelabels = scorelabels;
    }

    public void show() {
        this.frame.setVisible(true);
    }

    public JFrame getFrame() {
        return frame;
    }

    private Point scalePoint(Point modelPoint) {
        return new Point(scaleXPos((int)modelPoint.getX()), scaleYPos((int)modelPoint.getY()));
    }

    private int scaleXPos(int modelXPos) {
        return (int)(((modelXPos)*1.0/((int)model.getFieldSize().getWidth()))
                     * WIDTH_PXL);
    }

    private int scaleYPos(int modelYPos) {
        return (int)((modelYPos*1.0/((int)model.getFieldSize().getHeight())) * HEIGHT_PXL);
    }

    public void update() {
        SwingUtilities.invokeLater(new Runnable() {
                public void run() {
                    bars.get(BarKey.LEFT).update(scaleYPos(model.getBarPos(BarKey.LEFT)), scaleYPos(model.getBarHeight(BarKey.LEFT)));
                    bars.get(BarKey.RIGHT).update(scaleYPos(model.getBarPos(BarKey.RIGHT)), scaleYPos(model.getBarHeight(BarKey.RIGHT)));
                    ball.update(scalePoint(model.getBallPos()));
                    if (model.getMessage() == null) {
                        msglabel.setVisible(false);
                    } else {
                        msglabel.setVisible(true);
                        msglabel.setText(model.getMessage());
                    }
                    for (BarKey k : BarKey.values()) {
                        scorelabels.get(k).setText(model.getScore(k));
                    }
                }
            });
    }
}

/**
 * visualizing the bar of a player
 */
class Bar {
    public static final int WIDTH_PXL = 10;

    private final int XPOS;

    private JComponent comp = new JLabel("");

    // p in [0..10]
    public void update(int pxl, int bar_height_pxl) {
        this.comp.setBounds(this.XPOS - WIDTH_PXL/2, pxl-bar_height_pxl/2, WIDTH_PXL, bar_height_pxl);
    }

    public Bar(int xpos) {
        this.XPOS = xpos;
        this.comp.setBackground(Color.WHITE);
        this.comp.setOpaque(true);
        //final Dimension size = new Dimension(width, height);
        //        this.comp.setPreferredSize(size);
        //        this.comp.setMinimumSize(size);
        //        this.comp.setMaximumSize(size);
    }

    public JComponent getJComponent() {
        return this.comp;
    }
}

/**
 * visualizing the ball
 */
class Ball {
    public static final int SIZE = 20;

    private final JComponent comp = new JLabel("");

    public Ball() {
        this.comp.setBackground(Color.WHITE);
        this.comp.setOpaque(true);
    }

    public void update(Point loc) {
        this.comp.setBounds((int)loc.getX() - SIZE/2, (int)loc.getY() - SIZE/2, SIZE, SIZE);
    }

    public JComponent getJComponent() {
        return this.comp;
    }
}

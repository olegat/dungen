package mazemaker;

import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Theseus is the greek dude that killed the minotaur. He has experience with mazes,
 * hence he will go through it:
 * 
 * @author SanitySlayer
 *
 */
public class Theseus implements Runnable, ActionListener
{
	public static final long DEFAULT_WAIT_TIME = 250;
	
	private MazeMaker maker;
	private MazeGUI gui;
	private boolean exit;
	private boolean started;
	private long waitTime;
	
	public Theseus(MazeMaker maker, MazeGUI gui) 
	{
		if(maker.getWidth() != gui.getWidth())
			throw new IllegalArgumentException("widths don't match");
		if(maker.getHeight() != gui.getHeight())
			throw new IllegalArgumentException("heights don't match");
		
		this.maker = maker;
		this.gui = gui;
		gui.addActionListener(this);
		exit = false;
		started = false;
		waitTime = DEFAULT_WAIT_TIME;
	}
	
	public void setWaitTime(long l) {this.waitTime = l;}
	public long setWaitTime() {return this.waitTime;}
	
	private void refreshGUI() {
		refreshGUI(true);
	}
	private void refreshGUI(boolean drawLastVisited) {
		int w = maker.getWidth();
		int h = maker.getHeight();
		
		for(int x=0; x<w; x++)
			for(int y=0; y<h; y++) {
				int node = maker.getNode(x, y);
				
				switch(node) {
				case MazeMaker.UNVISITED: gui.setFree(x, y); break;
				case MazeMaker.FLOOR : gui.setFloor(x, y); break;
				case MazeMaker.WALL : gui.setWall(x, y); break;
				default:
					throw new IllegalArgumentException("node");
				}
			}
		
		if(drawLastVisited){
			Point p = maker.getLastVisited();
			gui.setNew(p.x, p.y);
		}
	}
	
	public void prepare() {
		maker.init();
		refreshGUI();
	}

	@Override
	public void run() 
	{
		while(!exit) 
		{
			try {
				
				exit = maker.step();
				refreshGUI();
				Thread.sleep(waitTime);
				
			} catch (InterruptedException e) {}
		}
		
		maker.clot();
		refreshGUI(false);
	}
	
	public void exit() {
		exit = true;
	}

	@Override
	public synchronized void actionPerformed(ActionEvent ae) 
	{
		if(started) return;
		else started = true;
		new Thread(this).start();
	}
}

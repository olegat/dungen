package mazemaker;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class MazeGUI 
{
	public static final int CELL_SIZE = 10;
	public static final Dimension CELL_DIM = new Dimension(CELL_SIZE, CELL_SIZE);
	public static final Color COLOR_FLOOR = Color.WHITE;
	public static final Color COLOR_WALL = Color.BLACK;
	public static final Color COLOR_FREE = Color.GRAY;
	public static final Color COLOR_NEW = Color.RED;
	
	private JFrame frame;
	private JPanel cellPanel;
	private JPanel framePanel;
	private JLabel[][] cells;
	private JButton start;
	
	public MazeGUI(int width, int height) 
	{
		if(width <= 0) throw new IllegalArgumentException("width out of range");
		if(height <= 0) throw new IllegalArgumentException("height out of range");
		
		frame = new JFrame("Maze Maker");
		cells = new JLabel[width][height];
		
		cellPanel = new JPanel(new GridLayout(height, width));
		frame.add(framePanel = new JPanel(new BorderLayout()));
		framePanel.add(cellPanel, "Center");

		// Init the cells
		for(int y=0; y<height; y++)
			for(int x=0; x<width; x++)
			{
				cells[x][y] = new JLabel();
				cells[x][y].setOpaque(true);
				cells[x][y].setBackground(COLOR_FREE);
				cells[x][y].setPreferredSize(CELL_DIM);
				cellPanel.add(cells[x][y]);
			}	

		framePanel.add(start = new JButton("Start"), "South");
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public int getWidth() {
		return cells.length;
	}
	public int getHeight() {
		return cells[0].length;
	}
	
	public void showGUI() {
		frame.pack();
		frame.setVisible(true);
	}
	
	public void setWall(int x, int y) {
		setColor(x, y, COLOR_WALL);
	}
	public void setFree(int x, int y) {
		setColor(x, y, COLOR_FREE);
	}
	public void setFloor(int x, int y) {
		setColor(x, y, COLOR_FLOOR);
	}
	public void setNew(int x, int y) {
		setColor(x, y, COLOR_NEW);
	}
	public void setColor(int x, int y, Color c) {
		cells[x][y].setBackground(c);
	}
	
	public void addActionListener(ActionListener al) {
		start.addActionListener(al);
	}
}

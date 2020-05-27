package mazemaker;

import java.awt.Point;
import java.util.LinkedList;
import java.util.Random;

public abstract class MazeMaker {

	public static final int UNVISITED = 0;
	public static final int FLOOR = 1;
	public static final int WALL = 2;
	
	protected int lastVisitedX = 1, lastVisitedY = 1;
	protected int[][] nodes;
	protected Random rand;
	
	public MazeMaker(int width, int height) 
	{
		if(width <= 0) throw new IllegalArgumentException("width out of range");
		if(height <= 0) throw new IllegalArgumentException("height out of range");
		
		nodes = new int[width+2][height+2];
		
		// Init border walls:
		for(int x = 0; x < width; x ++) {
			nodes[x][0] = WALL;
			nodes[x][height-1] = WALL;
		}
		for(int y = 0; y < height; y++) {
			nodes[0][y] = WALL;
			nodes[width-1][y] = WALL;
		}
		
		rand = new Random();
	}
	
	public int getWidth() {
		return nodes.length - 2;
	}
	public int getHeight() {
		return nodes[0].length - 2;
	}
	public int getNode(int x, int y) {
		return nodes[x][y];
	}
	public boolean isLeaf(int x, int y) {
		return getUnvisitedChildren(x, y).length == 0;
	}
	public boolean isUnvisited(int x, int y) {
		return nodes[x][y] == UNVISITED;
	}
	public boolean isVisited(int x, int y) {
		return !isUnvisited(x, y);
	}
	
	private Point[] pointArrayCaster = new Point[0];
	/**
	 * Get the unvisited children of node x,y.
	 * @param x
	 * @param y
	 * @return The unvisited children.
	 */
	public Point[] getUnvisitedChildren(int x, int y) 
	{
		LinkedList<Point> unvisited = new LinkedList<Point>();

		// Look to the left and right
		if(isUnvisited(x-1, y)) 
			unvisited.add(new Point(x-1, y));

		if(isUnvisited(x+1, y))
			unvisited.add(new Point(x+1, y));

		// Look down and above.
		if(isUnvisited(x, y-1))
			unvisited.add(new Point(x, y-1));

		if(isUnvisited(x, y+1))
			unvisited.add(new Point(x, y+1));

		// return the (unvisited children).
		return unvisited.toArray(pointArrayCaster);
	}
	
	/**
	 * Get the visited children of node x,y.
	 * @param x
	 * @param y
	 * @return The visited children.
	 */
	public Point[] getChildrenOfType(int x, int y, int type) 
	{
		LinkedList<Point> unvisited = new LinkedList<Point>();

		// Look to the left and right
		if(nodes[x-1][y] == type) 
			unvisited.add(new Point(x-1, y));

		if(nodes[x+1][y] == type)
			unvisited.add(new Point(x+1, y));

		// Look down and above.
		if(nodes[x][y-1] == type)
			unvisited.add(new Point(x, y-1));

		if(nodes[x][y+1] == type)
			unvisited.add(new Point(x, y+1));

		// return the (unvisited children).
		return unvisited.toArray(pointArrayCaster);
	}
	
	/**
	 * Determines whether this newly visited node should be walled
	 * off or not.
	 * @return true if node x,y should == WALL.
	 */
	public boolean shouldBeWalled(int x, int y, Point from) {
		int dx = from.x - x;
		int dy = from.y - y;
		
		if(dx < 0) {
			if(nodes[x][y-1] == FLOOR) return true;
			if(nodes[x][y+1] == FLOOR) return true;
			if(nodes[x+1][y] == FLOOR) return true;
			if(nodes[x+1][y-1] == FLOOR) return true;
			if(nodes[x+1][y+1] == FLOOR) return true;
		}
		else if(dx > 0) {
			if(nodes[x][y-1] == FLOOR) return true;
			if(nodes[x][y+1] == FLOOR) return true;
			if(nodes[x-1][y] == FLOOR) return true;
			if(nodes[x-1][y-1] == FLOOR) return true;
			if(nodes[x-1][y+1] == FLOOR) return true;
		}
		else if(dy > 0) {
			if(nodes[x-1][y] == FLOOR) return true;
			if(nodes[x+1][y] == FLOOR) return true;
			if(nodes[x][y-1] == FLOOR) return true;
			if(nodes[x-1][y-1] == FLOOR) return true;
			if(nodes[x+1][y-1] == FLOOR) return true;
		}
		else if(dy < 0) {
			if(nodes[x-1][y] == FLOOR) return true;
			if(nodes[x+1][y] == FLOOR) return true;
			if(nodes[x][y+1] == FLOOR) return true;
			if(nodes[x-1][y+1] == FLOOR) return true;
			if(nodes[x+1][y+1] == FLOOR) return true;
		}
		
		return false;
	}
	
	/**
	 * Initialize the algorithm.
	 */
	public void init() {
		nodes[lastVisitedX][lastVisitedY] = FLOOR;
	}
	/**
	 * One single iteration.
	 * @return True when done. False if still looping
	 */
	public abstract boolean step();
	/**
	 * Additional commands after the looping is complete.
	 */
	public abstract void clot();
	
	public Point getLastVisited() {
		return new Point(lastVisitedX, lastVisitedY);
	}
}

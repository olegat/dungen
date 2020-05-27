package mazemaker;

import java.awt.Point;
import java.util.LinkedList;

public class PrimMaker extends MazeMaker 
{
	private LinkedList<Point> leaves;
	
	public PrimMaker(int width, int height) 
	{
		super(width, height);
		leaves = new LinkedList<Point>();
	}

	@Override
	public void init() 
	{
		super.init();
		leaves.add(new Point(lastVisitedX, lastVisitedY));
	}
	
	private Point getRandomLeaf() 
	{
		Point leaf = null;

		while(leaves.size() > 0 && leaf == null) 
		{
			int index = rand.nextInt(leaves.size());
			leaf = leaves.get(index);
			
			// Check if this leaf has children:
			if ( getUnvisitedChildren(leaf.x, leaf.y).length == 0 ) {
				// No. Remove this leaf and try get another one.
				leaf = null;
				leaves.remove(index);
			}
		}

		return leaf;
	}
	
	@Override
	public boolean step() 
	{
		// Get a random leaf:
		Point leaf = getRandomLeaf();
		if(leaf == null) return true; // done!
		
		// Get a random child:
		Point[] children = getUnvisitedChildren(leaf.x, leaf.y);
		Point child = children[rand.nextInt(children.length)];
		
		// Get x and y
		int x = child.x;
		int y = child.y;
		
		// Should this child be a wall?
		if ( shouldBeWalled(x, y, leaf) ) {
			nodes[x][y] = WALL;
		}
		else {
			nodes[x][y] = FLOOR;
			
			if ( getUnvisitedChildren(x, y).length > 0 ) {
				leaves.add(child);
			}
		}
		
		lastVisitedX = x;
		lastVisitedY = y;
		
		return false;
	}

	@Override
	public void clot() {
		// TODO Auto-generated method stub

	}

}

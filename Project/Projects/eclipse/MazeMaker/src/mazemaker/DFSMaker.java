package mazemaker;

import java.awt.Point;
import java.util.LinkedList;

public class DFSMaker extends MazeMaker 
{
	private LinkedList<Point> backtrackNodes;
	
	public DFSMaker(int width, int height) {
		super(width, height);
		
		backtrackNodes = new LinkedList<Point>();
	}

	public Point pick(int x, int y) 
	{
		Point[] points = getUnvisitedChildren(x, y);
		return points[rand.nextInt(points.length)];
	}

	protected Point backtrack() {
		Point p = null;
		
		while (! backtrackNodes.isEmpty() && p == null) {

			p = backtrackNodes.getLast();
			Point[] children = getUnvisitedChildren(p.x, p.y);

			if(children.length <= 1)
				// Don't backtrack to p ever again (no more paths)
				backtrackNodes.removeLast();
			
			if(children.length == 0)
				// Nodes have already been visited by another path.
				// Keep backtracking:
				p = null;
		}
		return p;
	}
	
	@Override
	public void init() {
		super.init();
		backtrackNodes.add(getLastVisited());
	}
	
	@Override
	public boolean step() 
	{
		if(isLeaf(lastVisitedX, lastVisitedY) || nodes[lastVisitedX][lastVisitedY] == WALL) 
		{
			// Back-track to the last branch:
			Point branch = backtrack();
			if(branch==null) return true; // done!
			
			lastVisitedX = branch.x;
			lastVisitedY = branch.y;
		}
		
		// Get the new nodes which we are visiting
		Point newVisited = pick(lastVisitedX, lastVisitedY);
		int x = newVisited.x, y = newVisited.y;
		
		// This node should be a wall, because it already touches another floor
		//if( getChildrenOfType(x, y, FLOOR).length > 1 )
		if( shouldBeWalled(x, y, new Point(lastVisitedX, lastVisitedY)) )
			nodes[x][y] = WALL;
		
		// This node should be a floor, because no it has no adjacent visited nodes.
		else
		{
			nodes[x][y] = FLOOR;
			if( getUnvisitedChildren(x, y).length > 1)
				backtrackNodes.addLast(new Point(x,y));
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

package mazemaker;

public class MazeMain 
{
	public static String DFS = "DFS";
	public static String PRIM = "Prim";
	
	private static MazeGUI gui;
	private static MazeMaker maker;
	private static Theseus theseus;
	
	public static void main(String[] args) 
	{
		// Set default args:
		int w = 40; int h = 20; String a = DFS;
		long t = Theseus.DEFAULT_WAIT_TIME;
		
		// Parse args and overwrite defaults:
		for(int i=0; i<args.length; i++) 
		{
			try {
			if(args[i].startsWith("-w"))
				w = Integer.parseInt(args[++i]);
			
			else if(args[i].startsWith("-h"))
				h = Integer.parseInt(args[++i]);
			
			else if(args[i].startsWith("-a"))
				a = args[++i];
			
			else if(args[i].startsWith("-t"))
				t = Long.parseLong(args[++i]);
			
			else 
				printUsageAndExit();
			}
			catch(Exception $) {printUsageAndExit();}
		}
		
		// Create maker:
		if(a.equals(DFS))
			maker = new DFSMaker(w, h);
		else if (a.equals(PRIM))
			maker = new PrimMaker(w, h);
		
		// Create gui:
		gui = new MazeGUI(w, h);
		gui.showGUI();
		
		// Create thread:
		theseus = new Theseus(maker, gui);
		theseus.prepare();
		theseus.setWaitTime(t);
	}
	
	private static void outln() {
		System.out.println();
	}
	private static void outln(String s) {
		System.out.println(s);
	}
	
	private static void printUsageAndExit() {
		String white = "            ";
		
		outln("usage: java -jar MazeMain.jar [-w WIDTH] [-h HEIGHT] [-t TIME] [-a ALG]");
		outln("  WIDTH<int>     - width of the maze.");
		outln("  HEIGHT<int>    - height of the maze.");
		outln("  TIME<long>     - time delay between iterations (milliseconds).");
		outln();
		outln("  ALG is one of these strings:");
		outln("     "+DFS+white.substring(DFS.length())+"- Depth first search.");
		outln("     "+PRIM+white.substring(PRIM.length())+"- Prim's search algorithm.");
		System.exit(0);
	}
	
}

package launcher;



@SuppressWarnings("serial")
public class UniformDialog extends DungenDialog
{
	private static int id = 0 ;
	private int myid = 0;
	
	public UniformDialog(LaunchFrame owner, RandomComboBoxUpdater updater)
	{
		super(owner, "no title", "no dialog", updater);
		myid = id ++;
	}
	
	@Override
	public String getClassRepresentation(int tabcount)
	{
		String tabs = getTabs(tabcount);
		StringBuffer sb = new StringBuffer(tabs);
		
		sb.append("UniformRandom\n");
		sb.append(tabs).append("{\n");
		{
			LaunchFrame f = (LaunchFrame) getOwner();
			String seed = f.seed.getText().trim();
			if ( ! seed.isEmpty()) 
				sb.append(tabs).append('\t').append("Seed:").append(seed).append('\n');
		}
		sb.append(tabs).append("}\n");
		
		return sb.toString();
	}
	
	@Override
	public String toString()
	{
		return "UniformRandom "+myid;
	}
	
	@Override
	public boolean isRandomI() {return true;}
	@Override
	public boolean isRandomF() {return true;}
	@Override
	public boolean isEditable() {return false;}
}

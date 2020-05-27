package launcher;



import java.util.ArrayList;
import java.util.List;

import javax.swing.AbstractListModel;

@SuppressWarnings("serial")
public class DiggerList extends AbstractListModel
{
	List<DungenDialog> diggers;
	
	public DiggerList()	{ this (new ArrayList<DungenDialog>()) ; }
	public DiggerList(DungenDialog[] diggers)
	{
		this ( new ArrayList<DungenDialog>(diggers.length + 100) );
		
		for (DungenDialog d : diggers) this.diggers.add(d);
	}
	public DiggerList(List<DungenDialog> diggers)
	{
		this.diggers = diggers;
	}
	
	@Override
	public Object getElementAt(int index) { return diggers.get(index); }
	@Override
	public int getSize() { return diggers.size(); }

}

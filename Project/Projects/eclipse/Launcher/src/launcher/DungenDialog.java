package launcher;



import java.awt.BorderLayout;
import java.awt.Frame;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.border.TitledBorder;

@SuppressWarnings("serial")
public abstract class DungenDialog extends JDialog implements ActionListener
{
	protected JPanel center;
	protected JPanel footer;
	protected JButton close;
	protected RandomComboBoxUpdater updater;
	
	public DungenDialog(Frame owner, String frameTitle, String borderTitle, RandomComboBoxUpdater updater)
	{
		super(owner, frameTitle, true);
		
		this.updater = updater;
		
		{
			this.center = new JPanel();
			this.center.setBorder(new TitledBorder(null, borderTitle, TitledBorder.LEADING, TitledBorder.TOP, null, null));
			getContentPane().add(this.center, BorderLayout.CENTER);
			GridBagLayout gbl_center = new GridBagLayout();
			gbl_center.columnWidths = new int[]{0, 0, 0};
			gbl_center.rowHeights = new int[]{0, 0};
			gbl_center.columnWeights = new double[]{0.0, 1.0, Double.MIN_VALUE};
			gbl_center.rowWeights = new double[]{0.0, Double.MIN_VALUE};
			this.center.setLayout(gbl_center);
		}
		{
			this.footer = new JPanel();
			getContentPane().add(this.footer, BorderLayout.SOUTH);
			{
				this.close = new JButton("Close");
				this.footer.add(this.close);
				this.close.addActionListener(this);
			}
		}
	}
	
	@Override
	public void actionPerformed(ActionEvent ae)
	{
		// just hide the dialog. There's only 1 button we're listening to anyway :)
		this.setVisible(false);
	}
	
	@Override
	public void setVisible(boolean b)
	{
		if ( isEditable() )
		{
			this.pack();
			this.setLocationRelativeTo(this.getOwner());
			super.setVisible(b);
		}
		else super.setVisible(false);
	}
	
	@Override
	public String toString()
	{
		return this.getClass().getSimpleName();
	}
	
	public final String getClassRepresentation()
	{
		return getClassRepresentation(0);
	}
	
	public String getClassRepresentation(int tabcount)
	{
		String s = getTabs(tabcount);
		return s+"AbstractDigger\n";
	}
	
	protected String getTabs(int tabcount)
	{
		char[] tabchars = new char[tabcount];
		for (int t=0; t<tabcount; t++) tabchars[t] = '\t';
		String tabs = new String(tabchars);
		return tabs;
	}
	
	public boolean isEditable() { return true; }
	public boolean isRandomI() { return false;}
	public boolean isRandomF() { return false;}

	public void doComboItemRemoved(JComboBox box, Object removed)
	{
		Object selected = box.getSelectedItem();
		if ( selected == removed )
		{
			box.removeItem(selected);
			
			if (box.getItemCount() > 0)
				box.setSelectedIndex(0);
		}
	}
}

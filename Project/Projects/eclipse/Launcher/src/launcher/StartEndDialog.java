package launcher;



import java.awt.Frame;
import java.awt.GridBagConstraints;
import java.awt.Insets;

import javax.swing.JComboBox;
import javax.swing.JLabel;

@SuppressWarnings("serial")
public class StartEndDialog extends DungenDialog implements ComboItemRemovedListener
{
	protected JLabel direction_picker;
	protected JComboBox random;
	
	public StartEndDialog(Frame owner, RandomComboBoxUpdater updater)
	{
		super (owner, "Start-End Digger", "Start-end Digger", updater);
		this.direction_picker = new JLabel("Direction Picker:");
		GridBagConstraints gbc_direction_picker = new GridBagConstraints();
		gbc_direction_picker.insets = new Insets(0, 0, 0, 5);
		gbc_direction_picker.anchor = GridBagConstraints.EAST;
		gbc_direction_picker.gridx = 0;
		gbc_direction_picker.gridy = 0;
		this.center.add(this.direction_picker, gbc_direction_picker);

		this.random = new JComboBox();
		GridBagConstraints gbc_comboBox = new GridBagConstraints();
		gbc_comboBox.fill = GridBagConstraints.HORIZONTAL;
		gbc_comboBox.gridx = 1;
		gbc_comboBox.gridy = 0;
		this.center.add(this.random, gbc_comboBox);
	}
	
	@Override
	public String toString()
	{
		return "Start-end digger";
	}
	
	@Override
	public String getClassRepresentation(int tabcount)
	{
		String tabs = getTabs(tabcount);
		
		StringBuffer sb = new StringBuffer(tabs);
		sb.append("StartEndDigger\n");
		sb.append(tabs).append("{\n");
		sb.append(tabs).append("}\n");
		
		return sb.toString();
	}
	
	@Override
	public void setVisible(boolean v)
	{
		super.setVisible(false);
	}

	@Override
	public void comboItemRemoved(Object removed)
	{
		doComboItemRemoved( this.random, removed );
	}
}

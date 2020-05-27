package launcher;



import java.awt.Frame;
import java.awt.GridBagConstraints;
import java.awt.Insets;

import javax.swing.JComboBox;
import javax.swing.JLabel;

@SuppressWarnings("serial")
public class KruskalDialog extends DungenDialog implements ComboItemRemovedListener
{
	protected JLabel picker;
	protected JComboBox random;
	
	public KruskalDialog(Frame owner, RandomComboBoxUpdater updater)
	{
		super (owner, "Kruskal Digger", "Kruskal's algorithm", updater);
		this.picker = new JLabel("Picker:");
		GridBagConstraints gbc_direction_picker = new GridBagConstraints();
		gbc_direction_picker.insets = new Insets(0, 0, 0, 5);
		gbc_direction_picker.anchor = GridBagConstraints.EAST;
		gbc_direction_picker.gridx = 0;
		gbc_direction_picker.gridy = 0;
		this.center.add(this.picker, gbc_direction_picker);

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
		return "Kruskal's maze generator";
	}
	
	@Override
	public String getClassRepresentation(int tabcount)
	{
		String tabs = getTabs(tabcount);
		
		StringBuffer sb = new StringBuffer(tabs);
		sb.append("KruskalDigger\n");
		sb.append(tabs).append("{\n");
		{
			sb.append(tabs).append('\t').append("RandomI:").append(random.getSelectedIndex()).append('\n');
		}
		sb.append(tabs).append("}\n");
		
		return sb.toString();
	}
	
	@Override
	public void setVisible(boolean v)
	{
		updater.UpdateRandomI( this.random, this );
		super.setVisible(v);
	}

	@Override
	public void comboItemRemoved(Object removed)
	{
		doComboItemRemoved( this.random, removed );
	}
}

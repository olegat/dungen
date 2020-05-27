package launcher;



import java.awt.Frame;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JTextField;

@SuppressWarnings("serial")
public class LoopDialog extends DungenDialog implements ComboItemRemovedListener
{
	protected JTextField remove;
	protected JComboBox randomF;
	protected JLabel randomI_label;
	protected JComboBox randomI;
	public LoopDialog(Frame owner, RandomComboBoxUpdater updater)
	{
		super(owner, "Loop adder", "Loop Digger", updater);
		GridBagLayout gridBagLayout = (GridBagLayout) center.getLayout();
		gridBagLayout.columnWeights = new double[]{0.0, 0.0, 0.0};
		{
			this.randomI_label = new JLabel("RandomI");
			GridBagConstraints gbc_randomI_label = new GridBagConstraints();
			gbc_randomI_label.anchor = GridBagConstraints.EAST;
			gbc_randomI_label.insets = new Insets(0, 0, 5, 5);
			gbc_randomI_label.gridx = 0;
			gbc_randomI_label.gridy = 0;
			center.add(this.randomI_label, gbc_randomI_label);
		}
		{
			this.randomI = new JComboBox();
			this.randomI.setToolTipText("Int generator used.");
			GridBagConstraints gbc_randomI = new GridBagConstraints();
			gbc_randomI.fill = GridBagConstraints.HORIZONTAL;
			gbc_randomI.insets = new Insets(0, 0, 5, 5);
			gbc_randomI.gridx = 1;
			gbc_randomI.gridy = 0;
			center.add(this.randomI, gbc_randomI);
		}
		{
			JLabel randomF_label = new JLabel("RandomF");
			GridBagConstraints gbc_randomF_label = new GridBagConstraints();
			gbc_randomF_label.anchor = GridBagConstraints.EAST;
			gbc_randomF_label.insets = new Insets(0, 0, 5, 5);
			gbc_randomF_label.gridx = 0;
			gbc_randomF_label.gridy = 2;
			center.add(randomF_label, gbc_randomF_label);
		}
		{
			this.randomF = new JComboBox();
			this.randomF.setToolTipText("Float generator used.");
			GridBagConstraints gbc_randomF = new GridBagConstraints();
			gbc_randomF.insets = new Insets(0, 0, 5, 5);
			gbc_randomF.fill = GridBagConstraints.HORIZONTAL;
			gbc_randomF.gridx = 1;
			gbc_randomF.gridy = 2;
			center.add(this.randomF, gbc_randomF);
		}
		{
			JLabel remove_label = new JLabel("Remove Probability");
			GridBagConstraints gbc_remove_label = new GridBagConstraints();
			gbc_remove_label.anchor = GridBagConstraints.WEST;
			gbc_remove_label.insets = new Insets(0, 0, 0, 5);
			gbc_remove_label.gridx = 0;
			gbc_remove_label.gridy = 3;
			center.add(remove_label, gbc_remove_label);
		}
		{
			this.remove = new JTextField();
			this.remove.setText("0.8");
			this.remove.setToolTipText("Probability of removing a dead-end [0 to 1].");
			GridBagConstraints gbc_remove = new GridBagConstraints();
			gbc_remove.anchor = GridBagConstraints.WEST;
			gbc_remove.insets = new Insets(0, 0, 0, 5);
			gbc_remove.gridx = 1;
			gbc_remove.gridy = 3;
			center.add(this.remove, gbc_remove);
			this.remove.setColumns(3);
		}
		
	}
	
	@Override
	public String toString()
	{
		return "Loop adder ["+remove.getText()+"]";
	}
	
	@Override
	public String getClassRepresentation(int tabcount)
	{
		String tabs = getTabs(tabcount);
		
		StringBuffer sb = new StringBuffer(tabs);
		sb.append("LoopDigger\n");
		sb.append(tabs).append("{\n");
		{
			sb.append(tabs).append('\t').append("RandomI:").append(updater.getAbsoluteSelectedIndex(randomI))
			.append('\n');
			sb.append(tabs).append('\t').append("RandomF:").append(updater.getAbsoluteSelectedIndex(randomF))
			.append('\n');
			sb.append(tabs).append('\t').append("RemoveProb:").append(remove.getText())
			.append('\n');
		}
		sb.append(tabs).append("}\n");
		
		return sb.toString();
	}
	
	@Override
	public void setVisible(boolean v)
	{
		updater.UpdateRandomI( this.randomI, this );
		updater.UpdateRandomF( this.randomF, this );
		super.setVisible(v);
	}
	
	@Override
	public boolean isRandomI() { return false; }

	@Override
	public void comboItemRemoved(Object removed) {
		doComboItemRemoved( randomI, removed );
		doComboItemRemoved( randomF, removed );
	}
}

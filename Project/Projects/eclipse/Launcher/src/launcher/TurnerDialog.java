package launcher;



import java.awt.Frame;
import javax.swing.JLabel;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import javax.swing.JTextField;
import java.awt.GridBagLayout;
import javax.swing.JComboBox;

@SuppressWarnings("serial")
public class TurnerDialog extends DungenDialog implements ComboItemRemovedListener
{
	protected JTextField left;
	protected JTextField right;
	protected JComboBox randomF;
	protected JLabel randomI_label;
	protected JComboBox randomI;
	public TurnerDialog(Frame owner, RandomComboBoxUpdater updater)
	{
		super(owner, "Random turner", "Turner", updater);
		GridBagLayout gridBagLayout = (GridBagLayout) center.getLayout();
		gridBagLayout.columnWeights = new double[]{0.0, 0.0, 0.0, 0.0};
		{
			this.randomI_label = new JLabel("RandomI");
			GridBagConstraints gbc_randomI_label = new GridBagConstraints();
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
			gbc_randomI.gridwidth = 3;
			gbc_randomI.insets = new Insets(0, 0, 5, 0);
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
			gbc_randomF.insets = new Insets(0, 0, 5, 0);
			gbc_randomF.gridwidth = 3;
			gbc_randomF.fill = GridBagConstraints.HORIZONTAL;
			gbc_randomF.gridx = 1;
			gbc_randomF.gridy = 2;
			center.add(this.randomF, gbc_randomF);
		}
		{
			JLabel left_label = new JLabel("Left");
			GridBagConstraints gbc_left_label = new GridBagConstraints();
			gbc_left_label.anchor = GridBagConstraints.WEST;
			gbc_left_label.insets = new Insets(0, 0, 5, 5);
			gbc_left_label.gridx = 0;
			gbc_left_label.gridy = 3;
			center.add(left_label, gbc_left_label);
		}
		{
			this.left = new JTextField();
			this.left.setText("0.15");
			this.left.setToolTipText("Probability of turning left [0 to 1].");
			GridBagConstraints gbc_left = new GridBagConstraints();
			gbc_left.anchor = GridBagConstraints.WEST;
			gbc_left.insets = new Insets(0, 0, 5, 5);
			gbc_left.gridx = 1;
			gbc_left.gridy = 3;
			center.add(this.left, gbc_left);
			this.left.setColumns(3);
		}
		{
			JLabel right_label = new JLabel("Right");
			GridBagConstraints gbc_right_label = new GridBagConstraints();
			gbc_right_label.anchor = GridBagConstraints.WEST;
			gbc_right_label.insets = new Insets(0, 0, 5, 5);
			gbc_right_label.gridx = 0;
			gbc_right_label.gridy = 4;
			center.add(right_label, gbc_right_label);
		}
		{
			this.right = new JTextField();
			this.right.setText("0.15");
			this.right.setToolTipText("Probability of turning right [0 to 1].");
			GridBagConstraints gbc_right = new GridBagConstraints();
			gbc_right.anchor = GridBagConstraints.WEST;
			gbc_right.insets = new Insets(0, 0, 5, 5);
			gbc_right.gridx = 1;
			gbc_right.gridy = 4;
			center.add(this.right, gbc_right);
			this.right.setColumns(3);
		}
		
	}
	
	@Override
	public String toString()
	{
		return "RandomTurner ["+left.getText()+", "+right.getText()+"]";
	}
	
	@Override
	public String getClassRepresentation(int tabcount)
	{
		String tabs = getTabs(tabcount);
		
		StringBuffer sb = new StringBuffer(tabs);
		sb.append("RandomTurner\n");
		sb.append(tabs).append("{\n");
		{
			sb.append(tabs).append('\t').append("RandomI:").append(updater.getAbsoluteSelectedIndex(randomI))
			.append('\n');
			sb.append(tabs).append('\t').append("RandomF:").append(updater.getAbsoluteSelectedIndex(randomF))
			.append('\n');
			sb.append(tabs).append('\t').append("LeftProb:").append(left.getText())
			.append('\n');
			sb.append(tabs).append('\t').append("RightProb:").append(right.getText())
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
	public boolean isRandomI() { return true; }

	@Override
	public void comboItemRemoved(Object removed) {
		doComboItemRemoved( randomI, removed );
		doComboItemRemoved( randomF, removed );
	}
}

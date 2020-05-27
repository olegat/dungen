package launcher;



import java.awt.Frame;
import javax.swing.JLabel;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import javax.swing.JTextField;
import java.awt.GridBagLayout;

@SuppressWarnings("serial")
public class DeadEndDialog extends DungenDialog
{
	protected JLabel sparseness_label;
	protected JTextField sparseness;
	public DeadEndDialog(Frame owner, RandomComboBoxUpdater updater)
	{
		super(owner, "Dead-end remover", "Dead-end remover", updater);
		GridBagLayout gridBagLayout = (GridBagLayout) center.getLayout();
		gridBagLayout.columnWeights = new double[]{0.0, 1.0};
		{
			this.sparseness_label = new JLabel("Spareness:");
			this.sparseness_label.setToolTipText("The amount of dead-end removal iterations.");
			GridBagConstraints gbc_spareness_label = new GridBagConstraints();
			gbc_spareness_label.anchor = GridBagConstraints.EAST;
			gbc_spareness_label.insets = new Insets(0, 0, 0, 5);
			gbc_spareness_label.gridx = 0;
			gbc_spareness_label.gridy = 0;
			center.add(this.sparseness_label, gbc_spareness_label);
		}
		{
			this.sparseness = new JTextField();
			GridBagConstraints gbc_textField = new GridBagConstraints();
			gbc_textField.fill = GridBagConstraints.HORIZONTAL;
			gbc_textField.gridx = 1;
			gbc_textField.gridy = 0;
			center.add(this.sparseness, gbc_textField);
			this.sparseness.setColumns(3);
		}
	}
	
	@Override
	public String toString()
	{
		return "DeadEndDigger [" + sparseness.getText() +"]"; 
	}
	
	@Override
	public String getClassRepresentation(int tabcount)
	{
		String tabs = getTabs(tabcount);
		
		StringBuffer sb = new StringBuffer(tabs);
		sb.append("DeadEndDigger\n");
		sb.append(tabs).append("{\n");
		{
			sb.append(tabs).append('\t').append("Sparseness:").append(sparseness.getText()).append('\n');
		}
		sb.append(tabs).append("}\n");
		
		return sb.toString();
	}
}

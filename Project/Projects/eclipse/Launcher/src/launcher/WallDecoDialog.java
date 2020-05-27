package launcher;



import java.awt.Frame;
import javax.swing.JLabel;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import javax.swing.JTextField;
import java.awt.GridBagLayout;
import javax.swing.border.TitledBorder;
import javax.swing.border.EtchedBorder;
import java.awt.Color;
import javax.swing.JComboBox;

@SuppressWarnings("serial")
public class WallDecoDialog extends DungenDialog implements ComboItemRemovedListener
{
	protected JLabel sparseness_label;
	protected JTextField filename;
	protected JLabel lblRandomi;
	protected JLabel lblRandomf;
	protected JLabel lblDensity;
	protected JTextField density;
	protected JComboBox randomI;
	protected JComboBox randomF;
	public WallDecoDialog(Frame owner, RandomComboBoxUpdater updater)
	{
		super(owner, "Wall Decorator", "Wall Decorator", updater);
		setTitle("Wall Decorator");
		center.setBorder(new TitledBorder(new EtchedBorder(EtchedBorder.LOWERED, null, null), "Wall Decorator", TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 0, 0)));
		GridBagLayout gridBagLayout = (GridBagLayout) center.getLayout();
		gridBagLayout.columnWeights = new double[]{0.0, 0.0};
		{
			this.lblRandomi = new JLabel("RandomI:");
			GridBagConstraints gbc_lblRandomi = new GridBagConstraints();
			gbc_lblRandomi.anchor = GridBagConstraints.EAST;
			gbc_lblRandomi.insets = new Insets(0, 0, 5, 5);
			gbc_lblRandomi.gridx = 0;
			gbc_lblRandomi.gridy = 0;
			center.add(this.lblRandomi, gbc_lblRandomi);
		}
		{
			this.randomI = new JComboBox();
			GridBagConstraints gbc_randomI = new GridBagConstraints();
			gbc_randomI.anchor = GridBagConstraints.WEST;
			gbc_randomI.gridwidth = 2;
			gbc_randomI.insets = new Insets(0, 0, 5, 0);
			gbc_randomI.gridx = 1;
			gbc_randomI.gridy = 0;
			center.add(this.randomI, gbc_randomI);
		}
		{
			this.lblRandomf = new JLabel("RandomF:");
			GridBagConstraints gbc_lblRandomf = new GridBagConstraints();
			gbc_lblRandomf.anchor = GridBagConstraints.EAST;
			gbc_lblRandomf.insets = new Insets(0, 0, 5, 5);
			gbc_lblRandomf.gridx = 0;
			gbc_lblRandomf.gridy = 1;
			center.add(this.lblRandomf, gbc_lblRandomf);
		}
		{
			this.randomF = new JComboBox();
			GridBagConstraints gbc_randomF = new GridBagConstraints();
			gbc_randomF.anchor = GridBagConstraints.WEST;
			gbc_randomF.gridwidth = 2;
			gbc_randomF.insets = new Insets(0, 0, 5, 5);
			gbc_randomF.gridx = 1;
			gbc_randomF.gridy = 1;
			center.add(this.randomF, gbc_randomF);
		}
		{
			this.lblDensity = new JLabel("Density:");
			this.lblDensity.setToolTipText("Probabilty [0,1] of placing a prop on a wall face.");
			GridBagConstraints gbc_lblDensity = new GridBagConstraints();
			gbc_lblDensity.anchor = GridBagConstraints.WEST;
			gbc_lblDensity.insets = new Insets(0, 0, 5, 5);
			gbc_lblDensity.gridx = 0;
			gbc_lblDensity.gridy = 2;
			center.add(this.lblDensity, gbc_lblDensity);
		}
		{
			this.density = new JTextField();
			this.density.setText("0.2");
			this.density.setToolTipText("Probabilty [0,1] of placing a prop on a wall face.");
			GridBagConstraints gbc_density = new GridBagConstraints();
			gbc_density.anchor = GridBagConstraints.WEST;
			gbc_density.insets = new Insets(0, 0, 5, 5);
			gbc_density.gridx = 1;
			gbc_density.gridy = 2;
			center.add(this.density, gbc_density);
			this.density.setColumns(3);
		}
		{
			this.sparseness_label = new JLabel("Mesh database:");
			this.sparseness_label.setToolTipText("The amount of dead-end removal iterations.");
			GridBagConstraints gbc_spareness_label = new GridBagConstraints();
			gbc_spareness_label.anchor = GridBagConstraints.WEST;
			gbc_spareness_label.insets = new Insets(0, 0, 0, 5);
			gbc_spareness_label.gridx = 0;
			gbc_spareness_label.gridy = 3;
			center.add(this.sparseness_label, gbc_spareness_label);
		}
		{
			this.filename = new JTextField();
			this.filename.setText("data/deco/deco.txt");
			GridBagConstraints gbc_filename = new GridBagConstraints();
			gbc_filename.gridwidth = 2;
			gbc_filename.fill = GridBagConstraints.HORIZONTAL;
			gbc_filename.gridx = 1;
			gbc_filename.gridy = 3;
			center.add(this.filename, gbc_filename);
			this.filename.setColumns(10);
		}
	}
	
	@Override
	public String toString()
	{
		return "Wall Decorator [" + filename.getText() +"]"; 
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
	
	@Override
	public String getClassRepresentation(int tabcount)
	{
		String tabs = getTabs(tabcount);
		
		StringBuffer sb = new StringBuffer(tabs);
		sb.append("WallDecoDigger\n");
		sb.append(tabs).append("{\n");
		{
			sb.append(tabs).append('\t').append("RandomI:").append(updater.getAbsoluteSelectedIndex(randomI))
			.append('\n');
			sb.append(tabs).append('\t').append("RandomF:").append(updater.getAbsoluteSelectedIndex(randomF))
			.append('\n');
			sb.append(tabs).append('\t').append("Density:").append(density.getText())
			.append('\n');
			sb.append(tabs).append('\t').append("Filename:").append(filename.getText())
			.append('\n');
		}
		sb.append(tabs).append("}\n");
		
		return sb.toString();
	}
}

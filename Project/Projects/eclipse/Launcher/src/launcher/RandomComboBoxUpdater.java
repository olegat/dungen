package launcher;



import javax.swing.JComboBox;

public interface RandomComboBoxUpdater
{
	public void UpdateRandomI(JComboBox box, Object invoker);
	
	public void UpdateRandomF(JComboBox box, Object invoker);
	
	public int  getAbsoluteSelectedIndex(JComboBox box);
}

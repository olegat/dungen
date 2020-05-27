package launcher;



import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JCheckBox;

public class OutputTabListener implements ActionListener 
{
	private LaunchFrame frame;
	
	public OutputTabListener(LaunchFrame frame)
	{
		this.frame = frame;
		listenToObjects();
	}
	
	private void listenToObjects()
	{
		//frame.output_obj_check.addActionListener(this);
		frame.saveProfile_check.addActionListener(this);
		frame.clearConsole_button.addActionListener(this);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) 
	{
		// TODO Auto-generated method stub
		
		Object src = e.getSource();
		
		/*if (src == frame.output_obj_check)
		{
			JCheckBox box = (JCheckBox) src;
			frame.output_obj.setEnabled( box.isSelected() );
		}*/
		
		if (src == frame.saveProfile_check)
		{
			JCheckBox box = (JCheckBox) src;
			frame.saveProfile.setEnabled( box.isSelected() );
		}
		
		if (src == frame.clearConsole_button)
		{
			frame.console.setText("");
		}
		
	}
}

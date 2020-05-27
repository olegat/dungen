package launcher;



import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MenuListener implements ActionListener
{

	private LaunchFrame frame;
	private ControlsDialog controlsFrame;
	
	public MenuListener (LaunchFrame frame)
	{
		this.frame = frame;
		this.controlsFrame = new ControlsDialog(frame);
		addActionListeners();
	}
	
	private void addActionListeners()
	{
		/*this.frame.file_loadProfile.addActionListener(this);*/
		this.frame.help_controls.addActionListener(this);
	}
	
	@Override
	public void actionPerformed(ActionEvent ae)
	{
		Object src = ae.getSource();
		
		if (src == this.frame.file_loadProfile)
		{
			// TODO
		}
		else if (src == this.frame.help_controls)
		{
			this.controlsFrame.setVisible(true);
		}
	}

}

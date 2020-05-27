package launcher;



import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import javax.swing.JOptionPane;

public class FooterListener implements ActionListener
{
	public LaunchFrame frame;
	
	public FooterListener(LaunchFrame frame)
	{
		this.frame = frame;
		listenToObjects();
	}
	
	private void listenToObjects()
	{
		this.frame.runButton.addActionListener(this);
	}
	
	@Override
	public void actionPerformed(ActionEvent e)
	{
		if (e.getSource() == this.frame.runButton && validate())
		{	
			// Output .dungenprofile File
			FileOutputManager.Export(this.frame);
			FileOutputManager.Export(this.frame, new File("temp.dungenprofile"), false);
			
			// Lock user-input:
			frame.setLock(true);
			
			// Start process:
			ProcessManager pm = ProcessManager.getProcessManager();
			pm.run(this.frame);
			
			// Select the output tab:
			this.frame.tabbedPane.setSelectedComponent( this.frame.tab_output );
		}
	}
	
	private boolean validate()
	{
		// TODO
            File floorFile = new File(this.frame.floorDiffuse.getText().trim());
            if( !floorFile.exists() )
            {
                JOptionPane.showMessageDialog(frame, "Floor diffuse file does not exist", "File missing", JOptionPane.ERROR_MESSAGE);
                return false;
            }
            
            File wallFile = new File(this.frame.wallDiffuse.getText().trim());
            if( !wallFile.exists() )
            {
                JOptionPane.showMessageDialog(frame, "Wall diffuse file does not exist", "File missing", JOptionPane.ERROR_MESSAGE);
                return false;
            }
            
            return true;
	}
}

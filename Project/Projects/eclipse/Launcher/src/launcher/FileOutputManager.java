package launcher;



import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

import javax.swing.JOptionPane;

public class FileOutputManager
{
	/**
	 * 
	 * @param frame
	 * @return false if the launch should be aborted. This occurs when a file exists and
	 *         the user decides not overwrite it.
	 */
	public static boolean Export(LaunchFrame frame)
	{
		// Check if export is required
		if ( ! frame.saveProfile_check.isSelected() ) return true;
		
		// Init file
		File f = new File(frame.saveProfile.getText());
		
		return Export(frame, f);
	}
	
	/**
	 * 
	 * @param frame
	 * @param f File to save to
	 * @return false if the launch should be aborted. This occurs when a file exists and
	 *         the user decides not overwrite it.
	 */
	public static boolean Export(LaunchFrame frame, File f)
	{
		return Export(frame, f, true);
	}
	/**
	 * 
	 * @param frame
	 * @param f File to save to
	 * @param promptOverwrite when true, a confirmation dialog will appear when overwriting a file.
	 * @return false if the launch should be aborted. This occurs when a file exists and
	 *         the user decides not overwrite it.
	 */
	public static boolean Export(LaunchFrame frame, File f, boolean promptOverwrite)
	{
		// Overwrite?
		if (f.exists() && promptOverwrite)
		{
			int selected = JOptionPane.showConfirmDialog(
					frame,
					"Do you want to overwrite\n"+f.getName(),
					"Overwrite?",
					JOptionPane.YES_NO_CANCEL_OPTION,
					JOptionPane.WARNING_MESSAGE);
			
			if (selected != JOptionPane.YES_OPTION) return false;
		}
		else try
		{
			exportProfile(frame, f);
		} 
		catch(Exception $0) 
		{
			frame.appendExceptionStack($0); return false;
		}
		
		return true;
	}
	
	public static void exportProfile(LaunchFrame frame, File f) throws Exception
	{
		BufferedWriter bw = new BufferedWriter(new FileWriter(f));
		
		int randomCount = frame.randomList.getModel().getSize();
		int diggerCount = frame.diggerList.getModel().getSize();
		
		bw.write("RandomCount:"+randomCount);
		bw.write("\n{\n");
		for (int i = 0; i < randomCount; i++) {
			DungenDialog d = (DungenDialog) frame.randomList.getModel().getElementAt(i);
			bw.write(d.getClassRepresentation(1));
		}
		bw.write("}\n");
		
		bw.write("DiggerCount:"+diggerCount);
		bw.write("\n{\n");
		for (int i = 0; i < diggerCount; i++) {
			DungenDialog d = (DungenDialog) frame.diggerList.getModel().getElementAt(i);
			bw.write(d.getClassRepresentation(1));
		}
		bw.write("}\n");
		
		bw.close();
		
		frame.console.append("Profile saved: "+f.getCanonicalPath()+"\n");
	}
}

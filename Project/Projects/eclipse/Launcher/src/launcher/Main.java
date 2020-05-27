package launcher;



import java.awt.Frame;

import javax.swing.ImageIcon;
import javax.swing.UIManager;

import com.apple.eawt.Application;


public class Main 
{
	public static ImageIcon appIcon = new ImageIcon( Main.class.getResource("icon.png") );
	
	public static void main(String[] args)
	{
		lookAndFeelNative();
		LaunchFrame f = new LaunchFrame();
		setIcon(f);
		
		new OutputTabListener(f);
		new FooterListener(f);
		new GraphicsTabListener(f);
		new MenuListener(f);
		f.cbUpdater = new GeneratorTabListener(f);
		
		f.addWindowListener( new LaunchFrameListener() );
		
		f.setVisible(true);
		f.pack();
	}
	
	private static void lookAndFeelNative()
	{
		// This is such baaaaad Java coding :( thank-you Apple.
		if(System.getProperty("os.name").indexOf("Mac")==0) 
		{
			Application.getApplication().setDockIconImage(appIcon.getImage());
			
			// take the menu bar off the jframe
			System.setProperty("apple.laf.useScreenMenuBar", "true");

			// set the name of the application menu item
			System.setProperty("com.apple.mrj.application.apple.menu.about.name", "AppName");
		}  
		{
			try {
				UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
			}
			catch (Exception e) {e.printStackTrace();}
		}
	}
	
	private static void setIcon(Frame f)
	{
		if(System.getProperty("os.name").indexOf("Mac")!=0) 
		{
			f.setIconImage(appIcon.getImage());
		}
	}
}

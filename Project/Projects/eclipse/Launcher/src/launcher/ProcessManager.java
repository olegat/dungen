package launcher;



import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import javax.swing.JTextArea;
import javax.swing.JTextField;

import launcher.GraphicsTabListener.BitMode;
import launcher.GraphicsTabListener.GraphicsMode;

public class ProcessManager extends Thread
{
	private Process dungen;
	private boolean running;
	private LaunchFrame frame;
	private TextBufferer tb;
	
	private static ProcessManager manager = null;
	
	private ProcessManager()
	{
		this.dungen = null;
		this.running = true;
		manager = this;
		
		setName("ProcessManager"+getId());
	}
	
	public static ProcessManager getProcessManager()
	{
		if (manager == null)
		{
			manager = new ProcessManager();
			manager.start();
		}
		return manager;
	}
	
	public void run(LaunchFrame args)
	{
		if (this.dungen != null) return;
		
		// Get args...
		// TODO
		
		try {
			this.frame = args;
			
			String cmd = makeCommand();
			
			Runtime rt = Runtime.getRuntime();
			this.dungen = rt.exec(cmd);
			
			this.frame.console.append(cmd);
			if (this.tb != null) tb.abort();
			this.tb = new TextBufferer(dungen.getInputStream(), frame.console);
			new Thread(this.tb).start();
		}
		catch(Exception e) { this.frame.appendExceptionStack(e); }
	}
	
	private boolean hasValue(JTextField text)
	{
		return !text.getText().trim().isEmpty();
	}
	
	private String makeCommand()
	{
		StringBuffer sb = new StringBuffer("./dungen --profile temp.dungenprofile");
		
		if ( hasValue(this.frame.mazeWidth) )
		{
			sb.append(" -x ");
			sb.append(this.frame.mazeWidth.getText());
		}
		
		if ( hasValue(this.frame.mazeLength) )
		{
			sb.append(" -z ");
			sb.append(this.frame.mazeLength.getText());
		}
		
		if ( hasValue(this.frame.pwd) )
		{
			sb.append(" --pwd ");
			String pwdstr = this.frame.pwd.getText().trim();
			sb.append('\"').append(pwdstr).append('\"');
		}
		
		if ( hasValue(this.frame.floorDiffuse) )
		{
			sb.append(" --floor ");
			String floor = this.frame.floorDiffuse.getText().trim();
			sb.append('\"').append(floor).append('\"');
		}
		
		if ( hasValue(this.frame.wallDiffuse) )
		{
			sb.append(" --wall ");
			String wall = this.frame.wallDiffuse.getText().trim();
			sb.append('\"').append(wall).append('\"');
		}
		
		if ( hasValue(this.frame.ceilingDiffuse) )
		{
			sb.append(" --ceiling ");
			String wall = this.frame.ceilingDiffuse.getText().trim();
			sb.append('\"').append(wall).append('\"');
		}
		
		if ( hasValue(this.frame.seed) )
		{
			sb.append(" --seed ");
			sb.append(this.frame.seed.getText());
		}
		
		if ( this.frame.showGrid.isSelected() )
		{
			sb.append(" --show-grid");
		}
		
		if ( this.frame.showBoundingVolumes.isSelected() )
		{
			sb.append(" --show-bvh");
		}
		
		if ( this.frame.output_path.isSelected() )
		{
			sb.append(" --print-path");
		}
		
		// graphics settings:
		{
			GraphicsMode mode = (GraphicsMode) this.frame.screenRes.getSelectedItem();
			BitMode bits = (BitMode) this.frame.bitFormat.getSelectedItem();
			
			if(mode != null && bits != null) {
				sb.append(" --gfx ").append(mode.w+" ").append(mode.h+" ")
				.append(bits.r+" ").append(bits.g+" ").append(bits.b);
			}
		}
		
		return sb.toString();
	}
	
	public void kill()
	{
		if (dungen != null) dungen.destroy();
	}

	public String getGfxModeOutput() throws IOException
	{
		// Launch program and get its out stream.
		Process process = Runtime.getRuntime().exec("./dungen --gfx-modes");
		InputStream stdout  = process.getInputStream();
		
		// Create buffers.
		BufferedReader reader = new BufferedReader( new InputStreamReader (stdout) );
		StringBuffer   buffer = new StringBuffer();
		
		// Read and buffer string
		String line = reader.readLine();
		while (line != null)
		{
			buffer.append(line).append('\n');
			line = reader.readLine();
		}
		
		// Done :)
		return buffer.toString();
	}
	
	@Override
	public void run() 
	{
		while ( running ) try
		{
			if ( dungen == null ) Thread.sleep(10); // don't hog CPU.
			else {
				int exitval = dungen.waitFor();
				doFinish(exitval);
				dungen = null;
			}
		}
		catch(InterruptedException ex) {}
	}
	
	private synchronized void doFinish(int exitval)
	{
		this.frame.console.append("Process dungen ended.\nExit value: "+exitval+'\n');
		
		this.frame.setLock(false);
	}
	
	private class TextBufferer implements Runnable
	{
		private BufferedReader br;
		private JTextArea text;
		private boolean abort = false;
		
		public TextBufferer(InputStream in, JTextArea out)
		{
			setName("TextBufferer"+getId());
			
			br   = in == null ? null : new BufferedReader( new InputStreamReader(in) );
			text = out;
		}
		
		public void abort()
		{
			abort = true;
		}
		
		@Override
		public void run()
		{
			String line = "";
			while (line != null && !abort) try
			{
				text.append(line+"\n");
				line = br.readLine();
			}
			catch (IOException ex) {
				text.append( ex.getStackTrace().toString() );
				line = null;
			}
		}
	}
}

package launcher;



import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;

public class GraphicsTabListener implements ActionListener
{
	private LaunchFrame frame;
	protected DefaultComboBoxModel gfxModes = new DefaultComboBoxModel();
	
	public GraphicsTabListener(LaunchFrame frame)
	{
		this.frame = frame;
		
		initComboBoxes();
	}
	
	public void initComboBoxes()
	{
		try {
			initComboBoxes( ProcessManager.getProcessManager().getGfxModeOutput() );
		}catch (IOException $0) {}
		
		this.frame.screenRes.setModel(this.gfxModes);
		this.frame.screenRes.addActionListener(this);
		this.frame.screenRes.setSelectedIndex(0);
	}

	private void initComboBoxes(String gfxModes)
	{
		String[] modes = gfxModes.split("\n");
		for (String mode : modes)
			addGfxMode(mode);
	}
	private void addGfxMode(String mode)
	{
		String[] param = mode.split(" ");
		
		int w = Integer.parseInt(param[0]);
		int h = Integer.parseInt(param[1]);
		int r = Integer.parseInt(param[2]);
		int g = Integer.parseInt(param[3]);
		int b = Integer.parseInt(param[4]);
		
		for (int i = 0; i < gfxModes.getSize(); i++)
		{
			// Re-used the same mode but add channel bit-data
			GraphicsMode existingMode = (GraphicsMode) gfxModes.getElementAt(i);
			if (existingMode.w == w && existingMode.h == h) {
				existingMode.bitmodes.addElement(new BitMode(r, g, b));
				return;
			}
		}
		
		// Create a new gfxMode and add it
		GraphicsMode newMode = new GraphicsMode(w, h);
		newMode.bitmodes.addElement(new BitMode(r, g, b));
		gfxModes.addElement(newMode);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		JComboBox src = (JComboBox) e.getSource();
		GraphicsMode mode = (GraphicsMode) src.getSelectedItem();
		this.frame.bitFormat.setModel(mode.bitmodes);
	}
	
	public class BitMode
	{
		public int r,g,b;
		
		public BitMode() {
			this(0, 0, 0);
		}
		public BitMode(int r, int g, int b) {
			this.r = r;
			this.g = g;
			this.b = b;
		}
		
		@Override
		public boolean equals(Object o)
		{
			if ( ! (o instanceof BitMode) ) return false;
			
			BitMode other = (BitMode) o;
			return this.r == other.r && this.g == other.g && this.b == other.b;
		}
		
		@Override
		public String toString()
		{
			if (r == g && g == b) {
				return r +"-bits color channels";
			}
			else {
				return 
				r+"-bit Red / "+
				g+"-bit Green / "+
				b+"-bit Blue";
			}
		}
	}
	public class GraphicsMode
	{
		public int w,h;
		public DefaultComboBoxModel bitmodes;
		
		public GraphicsMode() {
			this(0, 0);
		}
		public GraphicsMode(int w, int h) {
			this.w = w;
			this.h = h;
			this.bitmodes = new DefaultComboBoxModel();
		}
		
		@Override
		public String toString()
		{
			return w +" x "+ h;
		}
	}
}

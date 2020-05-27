package launcher;



import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.ComboBoxModel;
import javax.swing.DefaultComboBoxModel;
import javax.swing.DefaultListModel;
import javax.swing.JComboBox;
import javax.swing.JList;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.ListModel;

public class GeneratorTabListener implements ActionListener, RandomComboBoxUpdater
{
	private LaunchFrame frame;
	
	private JPopupMenu newRandomPopup;
	private JMenuItem newUniform;
	private JMenuItem newRandomTurner;
	
	private JPopupMenu newDiggerPopup;
	private JMenuItem newDFS;
	private JMenuItem newPrim;
	private JMenuItem newKruskal;
	private JMenuItem newBinary;
	private JMenuItem newStartEnd;
	private JMenuItem newDeadEnd;
	private JMenuItem newLoopDigger;
	private JMenuItem newRoomDigger;
	private JMenuItem newWeighedRoomDigger;
	private JMenuItem newWallDecoDigger;
	private JMenuItem newDoorDecoDigger;
	
	private ArrayList<ComboItemRemovedListener> listeners;
	
	public GeneratorTabListener(LaunchFrame frame)
	{
		this.frame = frame;
		
		this.newRandomPopup = new JPopupMenu();
		this.newRandomPopup.add( (newUniform = new JMenuItem("Uniform")) );
		this.newRandomPopup.add( (newRandomTurner = new JMenuItem("Turner")) );
		
		this.newDiggerPopup = new JPopupMenu();
		this.newDiggerPopup.add( (newDFS = new JMenuItem("Depth-first search")) );
		this.newDiggerPopup.add( (newPrim = new JMenuItem("Prim's algorithm")) );
		this.newDiggerPopup.add( (newKruskal = new JMenuItem("Kruskal's algorithm")) );
		this.newDiggerPopup.add( (newBinary = new JMenuItem("BinaryTree maze")) );
		this.newDiggerPopup.addSeparator();
		this.newDiggerPopup.add( (newStartEnd = new JMenuItem("Start/End Digger")) );
		this.newDiggerPopup.add( (newDeadEnd = new JMenuItem("Dead-end remover")) );
		this.newDiggerPopup.add( (newLoopDigger = new JMenuItem("Loop adder")) );
		this.newDiggerPopup.addSeparator();
		this.newDiggerPopup.add( (newRoomDigger = new JMenuItem("Room generator")) );
		this.newDiggerPopup.add( (newWeighedRoomDigger = new JMenuItem("Weighed Room generator")) );
		this.newDiggerPopup.addSeparator();
		this.newDiggerPopup.add( (newWallDecoDigger = new JMenuItem("Wall Decorator")) );
		this.newDiggerPopup.add( (newDoorDecoDigger = new JMenuItem("Door Decorator")) );
		
		listeners = new ArrayList<ComboItemRemovedListener>();
		listenersToFrame();
	}
	
	private void listenersToFrame()
	{
		this.frame.newRandom.addActionListener( this );
		this.frame.newDigger.addActionListener( this );
		this.frame.editRandom.addActionListener( this );
		this.frame.editDigger.addActionListener( this );
		this.frame.removeRandom.addActionListener( this );
		this.frame.removeDigger.addActionListener( this );
		
		this.newUniform.addActionListener( this );
		this.newRandomTurner.addActionListener( this );
		this.newDFS.addActionListener( this );
		this.newPrim.addActionListener( this );
		this.newKruskal.addActionListener( this );
		this.newBinary.addActionListener( this );
		this.newStartEnd.addActionListener( this );
		this.newDeadEnd.addActionListener( this );
		this.newLoopDigger.addActionListener( this );
		this.newRoomDigger.addActionListener( this );
		this.newWeighedRoomDigger.addActionListener( this );
		this.newWallDecoDigger.addActionListener( this );
		this.newDoorDecoDigger.addActionListener( this );
	}
	
	@Override
	public void actionPerformed(ActionEvent ae) 
	{
		Object o = ae.getSource();
		
		if (o == this.frame.newRandom) {
			this.newRandomPopup.show(
					this.frame.newRandom,
					this.frame.newRandom.getX(),
					this.frame.newRandom.getY());
		}
		else if (o == this.frame.newDigger) {
			this.newDiggerPopup.show(
					this.frame.newDigger,
					this.frame.newDigger.getX(),
					this.frame.newDigger.getY());
		}
		else if (o == this.frame.editRandom) {
			doEdit ( this.frame.randomList, this.frame.editRandom );
		}
		else if (o == this.frame.editDigger) {
			doEdit ( this.frame.diggerList, this.frame.editDigger );
		}
		else if (o == this.frame.removeRandom) {
			doRemove( this.frame.randomList );
		}
		else if (o == this.frame.removeDigger) {
			doRemove( this.frame.diggerList );
		}
		else if (o == this.newUniform) {
			doNew ( new UniformDialog(this.frame, this), this.frame.randomList );
		}
		else if (o == this.newRandomTurner) {
			doNew ( new TurnerDialog(this.frame, this), this.frame.randomList );
		}
		else if (o == this.newDFS) { 
			doNew ( new DFSDialog(this.frame, this), this.frame.diggerList );
		}
		else if (o == this.newPrim) { 
			doNew ( new PrimDialog(this.frame, this), this.frame.diggerList );
		}
		else if (o == this.newKruskal) { 
			doNew ( new KruskalDialog(this.frame, this), this.frame.diggerList );
		}
		else if (o == this.newBinary) { 
			doNew ( new BinaryDialog(this.frame, this), this.frame.diggerList );
		}
		else if (o == this.newStartEnd) {
			doNew ( new StartEndDialog(this.frame, this), this.frame.diggerList);
		}
		else if (o == this.newDeadEnd) {
			doNew ( new DeadEndDialog(this.frame, this), this.frame.diggerList);
		}
		else if (o == this.newLoopDigger) {
			doNew ( new LoopDialog(this.frame, this), this.frame.diggerList);
		}
		else if (o == this.newRoomDigger) {
			doNew ( new RoomDialog(this.frame, this), this.frame.diggerList);
		}
		else if (o == this.newWeighedRoomDigger) {
			doNew ( new WeighedRoomDialog(this.frame, this), this.frame.diggerList);
		}
		else if (o == this.newWallDecoDigger) {
			doNew ( new WallDecoDialog(this.frame, this), this.frame.diggerList);
		}
		else if (o == this.newDoorDecoDigger) {
			doNew ( new DoorDecoDialog(this.frame, this), this.frame.diggerList);
		}
	}

	private void doEdit(JList list, Component relativeTo)
	{
		DungenDialog d = (DungenDialog) list.getSelectedValue();
		if (d != null)
		{
			d.setVisible(true);
			d.setLocationRelativeTo(relativeTo);
		}
	}
	
	private void doRemove(JList list)
	{
		int index = list.getSelectedIndex();
		if (index != -1)
		{
			// Remove this item:
			Object selected = list.getSelectedValue();
			DefaultListModel model = (DefaultListModel) list.getModel();
			model.remove(index);
			listeners.remove(selected);
			
			// Inform other listeners:
			for(ComboItemRemovedListener lst : listeners)
			{
				lst.comboItemRemoved(selected);
			}
		}
	}
	
	private void doNew(DungenDialog newDiag, JList list)
	{
		DefaultListModel model = (DefaultListModel) list.getModel();
		model.addElement(newDiag);
		
		if (newDiag instanceof ComboItemRemovedListener)
			listeners.add((ComboItemRemovedListener) newDiag);
		
		newDiag.setVisible(true);
	}
	
	@Override
	public void UpdateRandomI(JComboBox box, Object invoker) { UpdateRandomIorF(0, box, invoker); }

	@Override
	public void UpdateRandomF(JComboBox box, Object invoker) { UpdateRandomIorF(1, box, invoker); }
	
	private void UpdateRandomIorF(int which, JComboBox box, Object invoker)
	{
		Object selected = box.getSelectedItem();
		DefaultComboBoxModel combo = getFreshModel(box);
		
		ListModel list = this.frame.randomList.getModel();
		
		for (int i = 0; i < list.getSize(); i++)
		{
			Object o = list.getElementAt(i);
			if ( ! (o instanceof DungenDialog ) || o == invoker )
				continue;
			
			DungenDialog diag = (DungenDialog) o;
			
			boolean addIt = false;
			     if (which == 0) addIt = diag.isRandomI();
			else if (which == 1) addIt = diag.isRandomF();
			
			if ( addIt )
				combo.addElement( diag );
		}
		
		combo.setSelectedItem( selected );
	}
	

	@Override
	public int getAbsoluteSelectedIndex(JComboBox box) 
	{
		Object selected = box.getSelectedItem();
		ListModel list = frame.randomList.getModel();
		
		for (int i = 0; i < list.getSize(); i++)
		{
			if (list.getElementAt(i) == selected) return i;
		}
		
		return -1;
	}
	
	private DefaultComboBoxModel getFreshModel(JComboBox box)
	{
		ComboBoxModel oldModel = box.getModel();
		if (oldModel instanceof DefaultComboBoxModel) // Reused old model?
		{
			DefaultComboBoxModel model = ((DefaultComboBoxModel) oldModel);
			model.removeAllElements();
			return model;
		}
		else return new DefaultComboBoxModel();// make a new one.
	}
}

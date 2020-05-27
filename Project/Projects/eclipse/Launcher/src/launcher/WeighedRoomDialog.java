package launcher;



import java.awt.Font;
import java.awt.Frame;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JTextField;

@SuppressWarnings("serial")
public class WeighedRoomDialog extends DungenDialog implements ComboItemRemovedListener
{
	protected JTextField maxRoomSize;
	protected JTextField minRoomSize;
	protected JTextField minRoomPos;
	protected JTextField maxRoomPos;
	protected JTextField minNRooms;
	protected JTextField maxNRooms;
	protected JComboBox roomSizeRandom;
	protected JComboBox roomPosRandom;
	protected JComboBox nRoomsRandom;
	protected JTextField onCorridor;
	protected JTextField touchCorridor;
	protected JTextField onRoom;
	public WeighedRoomDialog(Frame owner, RandomComboBoxUpdater updater)
	{
		super(owner, "Weighed Room Digger", "Weighed Room generator", updater);
		GridBagLayout gridBagLayout = (GridBagLayout) center.getLayout();
		gridBagLayout.columnWeights = new double[]{0.0, 1.0, 0.0, 1.0};
		{
			JLabel roomSize_label = new JLabel("Room size");
			roomSize_label.setFont(new Font("Lucida Grande", Font.BOLD, 13));
			GridBagConstraints gbc_roomSize_label = new GridBagConstraints();
			gbc_roomSize_label.ipady = 15;
			gbc_roomSize_label.gridwidth = 4;
			gbc_roomSize_label.insets = new Insets(0, 0, 5, 0);
			gbc_roomSize_label.gridx = 0;
			gbc_roomSize_label.gridy = 0;
			center.add(roomSize_label, gbc_roomSize_label);
		}
		{
			JLabel minRoomSize_label = new JLabel("Minimum");
			GridBagConstraints gbc_minRoomSize_label = new GridBagConstraints();
			gbc_minRoomSize_label.anchor = GridBagConstraints.EAST;
			gbc_minRoomSize_label.insets = new Insets(0, 0, 5, 5);
			gbc_minRoomSize_label.gridx = 0;
			gbc_minRoomSize_label.gridy = 1;
			center.add(minRoomSize_label, gbc_minRoomSize_label);
		}
		{
			this.minRoomSize = new JTextField();
			GridBagConstraints gbc_minRoomSize = new GridBagConstraints();
			gbc_minRoomSize.insets = new Insets(0, 0, 5, 5);
			gbc_minRoomSize.fill = GridBagConstraints.HORIZONTAL;
			gbc_minRoomSize.gridx = 1;
			gbc_minRoomSize.gridy = 1;
			center.add(this.minRoomSize, gbc_minRoomSize);
			this.minRoomSize.setColumns(3);
		}
		{
			JLabel maxRoomSize_label = new JLabel("Maximum");
			GridBagConstraints gbc_maxRoomSize_label = new GridBagConstraints();
			gbc_maxRoomSize_label.anchor = GridBagConstraints.EAST;
			gbc_maxRoomSize_label.insets = new Insets(0, 0, 5, 5);
			gbc_maxRoomSize_label.gridx = 2;
			gbc_maxRoomSize_label.gridy = 1;
			center.add(maxRoomSize_label, gbc_maxRoomSize_label);
		}
		{
			this.maxRoomSize = new JTextField();
			GridBagConstraints gbc_maxRoomSize = new GridBagConstraints();
			gbc_maxRoomSize.insets = new Insets(0, 0, 5, 0);
			gbc_maxRoomSize.fill = GridBagConstraints.HORIZONTAL;
			gbc_maxRoomSize.gridx = 3;
			gbc_maxRoomSize.gridy = 1;
			center.add(this.maxRoomSize, gbc_maxRoomSize);
			this.maxRoomSize.setColumns(3);
		}
		{
			JLabel roomSizeRandomI_label = new JLabel("Random");
			GridBagConstraints gbc_roomSizeRandomI_label = new GridBagConstraints();
			gbc_roomSizeRandomI_label.anchor = GridBagConstraints.EAST;
			gbc_roomSizeRandomI_label.insets = new Insets(0, 0, 5, 5);
			gbc_roomSizeRandomI_label.gridx = 0;
			gbc_roomSizeRandomI_label.gridy = 2;
			center.add(roomSizeRandomI_label, gbc_roomSizeRandomI_label);
		}
		{
			this.roomSizeRandom = new JComboBox();
			GridBagConstraints gbc_roomSizeRandom = new GridBagConstraints();
			gbc_roomSizeRandom.gridwidth = 3;
			gbc_roomSizeRandom.insets = new Insets(0, 0, 5, 0);
			gbc_roomSizeRandom.fill = GridBagConstraints.HORIZONTAL;
			gbc_roomSizeRandom.gridx = 1;
			gbc_roomSizeRandom.gridy = 2;
			center.add(this.roomSizeRandom, gbc_roomSizeRandom);
		}
		{
			JLabel roomPos_label = new JLabel("Room position");
			roomPos_label.setFont(new Font("Lucida Grande", Font.BOLD, 13));
			GridBagConstraints gbc_roomPos_label = new GridBagConstraints();
			gbc_roomPos_label.ipady = 15;
			gbc_roomPos_label.gridwidth = 4;
			gbc_roomPos_label.insets = new Insets(0, 0, 5, 0);
			gbc_roomPos_label.gridx = 0;
			gbc_roomPos_label.gridy = 3;
			center.add(roomPos_label, gbc_roomPos_label);
		}
		{
			JLabel minRoomPos_label = new JLabel("Minimum");
			GridBagConstraints gbc_minRoomPos_label = new GridBagConstraints();
			gbc_minRoomPos_label.anchor = GridBagConstraints.EAST;
			gbc_minRoomPos_label.insets = new Insets(0, 0, 5, 5);
			gbc_minRoomPos_label.gridx = 0;
			gbc_minRoomPos_label.gridy = 4;
			center.add(minRoomPos_label, gbc_minRoomPos_label);
		}
		{
			this.minRoomPos = new JTextField();
			GridBagConstraints gbc_minRoomPos = new GridBagConstraints();
			gbc_minRoomPos.insets = new Insets(0, 0, 5, 5);
			gbc_minRoomPos.fill = GridBagConstraints.HORIZONTAL;
			gbc_minRoomPos.gridx = 1;
			gbc_minRoomPos.gridy = 4;
			center.add(this.minRoomPos, gbc_minRoomPos);
			this.minRoomPos.setColumns(3);
		}
		{
			JLabel maxRoomPos_label = new JLabel("Maximum");
			GridBagConstraints gbc_maxRoomPos_label = new GridBagConstraints();
			gbc_maxRoomPos_label.anchor = GridBagConstraints.EAST;
			gbc_maxRoomPos_label.insets = new Insets(0, 0, 5, 5);
			gbc_maxRoomPos_label.gridx = 2;
			gbc_maxRoomPos_label.gridy = 4;
			center.add(maxRoomPos_label, gbc_maxRoomPos_label);
		}
		{
			this.maxRoomPos = new JTextField();
			GridBagConstraints gbc_maxRoomPos = new GridBagConstraints();
			gbc_maxRoomPos.insets = new Insets(0, 0, 5, 0);
			gbc_maxRoomPos.fill = GridBagConstraints.HORIZONTAL;
			gbc_maxRoomPos.gridx = 3;
			gbc_maxRoomPos.gridy = 4;
			center.add(this.maxRoomPos, gbc_maxRoomPos);
			this.maxRoomPos.setColumns(3);
		}
		{
			JLabel roomPosRandomI_label = new JLabel("Random");
			GridBagConstraints gbc_roomPosRandomI_label = new GridBagConstraints();
			gbc_roomPosRandomI_label.anchor = GridBagConstraints.EAST;
			gbc_roomPosRandomI_label.insets = new Insets(0, 0, 5, 5);
			gbc_roomPosRandomI_label.gridx = 0;
			gbc_roomPosRandomI_label.gridy = 5;
			center.add(roomPosRandomI_label, gbc_roomPosRandomI_label);
		}
		{
			this.roomPosRandom = new JComboBox();
			GridBagConstraints gbc_roomPosRandom = new GridBagConstraints();
			gbc_roomPosRandom.gridwidth = 3;
			gbc_roomPosRandom.insets = new Insets(0, 0, 5, 0);
			gbc_roomPosRandom.fill = GridBagConstraints.HORIZONTAL;
			gbc_roomPosRandom.gridx = 1;
			gbc_roomPosRandom.gridy = 5;
			center.add(this.roomPosRandom, gbc_roomPosRandom);
		}
		{
			JLabel nRooms_label = new JLabel("Number of rooms");
			nRooms_label.setFont(new Font("Lucida Grande", Font.BOLD, 13));
			GridBagConstraints gbc_nRooms_label = new GridBagConstraints();
			gbc_nRooms_label.ipady = 15;
			gbc_nRooms_label.gridwidth = 4;
			gbc_nRooms_label.insets = new Insets(0, 0, 5, 0);
			gbc_nRooms_label.gridx = 0;
			gbc_nRooms_label.gridy = 6;
			center.add(nRooms_label, gbc_nRooms_label);
		}
		{
			JLabel minNRooms_label = new JLabel("Minimum");
			GridBagConstraints gbc_minNRooms_label = new GridBagConstraints();
			gbc_minNRooms_label.anchor = GridBagConstraints.EAST;
			gbc_minNRooms_label.insets = new Insets(0, 0, 5, 5);
			gbc_minNRooms_label.gridx = 0;
			gbc_minNRooms_label.gridy = 7;
			center.add(minNRooms_label, gbc_minNRooms_label);
		}
		{
			this.minNRooms = new JTextField();
			GridBagConstraints gbc_minNRooms = new GridBagConstraints();
			gbc_minNRooms.insets = new Insets(0, 0, 5, 5);
			gbc_minNRooms.fill = GridBagConstraints.HORIZONTAL;
			gbc_minNRooms.gridx = 1;
			gbc_minNRooms.gridy = 7;
			center.add(this.minNRooms, gbc_minNRooms);
			this.minNRooms.setColumns(3);
		}
		{
			JLabel maxNRooms_label = new JLabel("Maximum");
			GridBagConstraints gbc_maxNRooms_label = new GridBagConstraints();
			gbc_maxNRooms_label.anchor = GridBagConstraints.EAST;
			gbc_maxNRooms_label.insets = new Insets(0, 0, 5, 5);
			gbc_maxNRooms_label.gridx = 2;
			gbc_maxNRooms_label.gridy = 7;
			center.add(maxNRooms_label, gbc_maxNRooms_label);
		}
		{
			this.maxNRooms = new JTextField();
			GridBagConstraints gbc_maxNRooms = new GridBagConstraints();
			gbc_maxNRooms.insets = new Insets(0, 0, 5, 0);
			gbc_maxNRooms.fill = GridBagConstraints.HORIZONTAL;
			gbc_maxNRooms.gridx = 3;
			gbc_maxNRooms.gridy = 7;
			center.add(this.maxNRooms, gbc_maxNRooms);
			this.maxNRooms.setColumns(3);
		}
		{
			JLabel nRoomsRandomI_label = new JLabel("Random");
			GridBagConstraints gbc_nRoomsRandomI_label = new GridBagConstraints();
			gbc_nRoomsRandomI_label.anchor = GridBagConstraints.EAST;
			gbc_nRoomsRandomI_label.insets = new Insets(0, 0, 5, 5);
			gbc_nRoomsRandomI_label.gridx = 0;
			gbc_nRoomsRandomI_label.gridy = 8;
			center.add(nRoomsRandomI_label, gbc_nRoomsRandomI_label);
		}
		{
			this.nRoomsRandom = new JComboBox();
			GridBagConstraints gbc_nRoomsRandom = new GridBagConstraints();
			gbc_nRoomsRandom.insets = new Insets(0, 0, 5, 0);
			gbc_nRoomsRandom.gridwidth = 3;
			gbc_nRoomsRandom.fill = GridBagConstraints.HORIZONTAL;
			gbc_nRoomsRandom.gridx = 1;
			gbc_nRoomsRandom.gridy = 8;
			center.add(this.nRoomsRandom, gbc_nRoomsRandom);
		}
		{
			JLabel weights_label = new JLabel("Weights");
			weights_label.setFont(new Font("Lucida Grande", Font.BOLD, 13));
			GridBagConstraints gbc_weights_label = new GridBagConstraints();
			gbc_weights_label.insets = new Insets(0, 0, 5, 0);
			gbc_weights_label.gridwidth = 4;
			gbc_weights_label.gridx = 0;
			gbc_weights_label.gridy = 9;
			center.add(weights_label, gbc_weights_label);
		}
		{
			JLabel lblOnCorridor = new JLabel("OnCorridor");
			GridBagConstraints gbc_lblOnCorridor = new GridBagConstraints();
			gbc_lblOnCorridor.insets = new Insets(0, 0, 5, 5);
			gbc_lblOnCorridor.anchor = GridBagConstraints.EAST;
			gbc_lblOnCorridor.gridx = 0;
			gbc_lblOnCorridor.gridy = 10;
			center.add(lblOnCorridor, gbc_lblOnCorridor);
		}
		{
			this.onCorridor = new JTextField();
			this.onCorridor.setText("3");
			GridBagConstraints gbc_onCorridor = new GridBagConstraints();
			gbc_onCorridor.insets = new Insets(0, 0, 5, 5);
			gbc_onCorridor.fill = GridBagConstraints.HORIZONTAL;
			gbc_onCorridor.gridx = 1;
			gbc_onCorridor.gridy = 10;
			center.add(this.onCorridor, gbc_onCorridor);
			this.onCorridor.setColumns(3);
		}
		{
			JLabel lblTouchescorridor = new JLabel("TouchesCorridor");
			GridBagConstraints gbc_lblTouchescorridor = new GridBagConstraints();
			gbc_lblTouchescorridor.insets = new Insets(0, 0, 5, 5);
			gbc_lblTouchescorridor.anchor = GridBagConstraints.EAST;
			gbc_lblTouchescorridor.gridx = 2;
			gbc_lblTouchescorridor.gridy = 10;
			center.add(lblTouchescorridor, gbc_lblTouchescorridor);
		}
		{
			this.touchCorridor = new JTextField();
			this.touchCorridor.setText("1");
			GridBagConstraints gbc_touchCorridor = new GridBagConstraints();
			gbc_touchCorridor.insets = new Insets(0, 0, 5, 0);
			gbc_touchCorridor.fill = GridBagConstraints.HORIZONTAL;
			gbc_touchCorridor.gridx = 3;
			gbc_touchCorridor.gridy = 10;
			center.add(this.touchCorridor, gbc_touchCorridor);
			this.touchCorridor.setColumns(3);
		}
		{
			JLabel lblOnroom = new JLabel("OnRoom");
			GridBagConstraints gbc_lblOnroom = new GridBagConstraints();
			gbc_lblOnroom.insets = new Insets(0, 0, 0, 5);
			gbc_lblOnroom.anchor = GridBagConstraints.EAST;
			gbc_lblOnroom.gridx = 0;
			gbc_lblOnroom.gridy = 11;
			center.add(lblOnroom, gbc_lblOnroom);
		}
		{
			this.onRoom = new JTextField();
			this.onRoom.setText("100");
			GridBagConstraints gbc_onRoom = new GridBagConstraints();
			gbc_onRoom.insets = new Insets(0, 0, 0, 5);
			gbc_onRoom.fill = GridBagConstraints.HORIZONTAL;
			gbc_onRoom.gridx = 1;
			gbc_onRoom.gridy = 11;
			center.add(this.onRoom, gbc_onRoom);
			this.onRoom.setColumns(3);
		}
	}
	
	@Override
	public String toString()
	{
		return "Weighted-Room-Generator ["
		+minRoomSize.getText()+", "+maxRoomSize.getText()+"] ["
		+minRoomPos.getText() +", "+maxRoomPos.getText() +"] ["
		+minNRooms.getText()  +", "+maxNRooms.getText()  +"]";
	}
	
	@Override
	public String getClassRepresentation(int tabcount)
	{
		String tabs = getTabs(tabcount);
		
		StringBuffer sb = new StringBuffer(tabs);
		sb.append("WeighedRoomDigger\n");
		sb.append(tabs).append("{\n");
		{
			sb.append(tabs).append('\t').append("MinRoomSize:").append(minRoomSize.getText()).append('\n');
			sb.append(tabs).append('\t').append("MaxRoomSize:").append(maxRoomSize.getText()).append('\n');
			sb.append(tabs).append('\t').append("RoomSizeRandomI:").append(roomSizeRandom.getSelectedIndex()).append('\n');
			
			sb.append(tabs).append('\t').append("MinRoomPos:").append(minRoomPos.getText()).append('\n');
			sb.append(tabs).append('\t').append("MaxRoomPos:").append(maxRoomPos.getText()).append('\n');
			sb.append(tabs).append('\t').append("RoomPosRandomI:").append(roomPosRandom.getSelectedIndex()).append('\n');
			
			sb.append(tabs).append('\t').append("MinNRooms:").append(minNRooms.getText()).append('\n');
			sb.append(tabs).append('\t').append("MaxNRooms:").append(maxNRooms.getText()).append('\n');
			sb.append(tabs).append('\t').append("NRoomRandomI:").append(nRoomsRandom.getSelectedIndex()).append('\n');
			
			sb.append(tabs).append('\t').append("PenaltyOnRoom:").append(onRoom.getText()).append('\n');
			sb.append(tabs).append('\t').append("PenaltyOnCorridor:").append(onCorridor.getText()).append('\n');
			sb.append(tabs).append('\t').append("PenaltyTouchingCorridor:").append(touchCorridor.getText()).append('\n');
		}
		sb.append(tabs).append("}\n");
		
		return sb.toString();
	}
	
	@Override
	public void setVisible(boolean v)
	{
		updater.UpdateRandomI( this.roomSizeRandom, this );
		updater.UpdateRandomI( this.roomPosRandom, this );
		updater.UpdateRandomI( this.nRoomsRandom, this );
		super.setVisible(v);
	}

	@Override
	public void comboItemRemoved(Object removed)
	{
		doComboItemRemoved( this.roomSizeRandom, removed );
		doComboItemRemoved( this.roomPosRandom, removed );
		doComboItemRemoved( this.nRoomsRandom, removed );
	}
}

package launcher;



import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.Frame;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class ControlsDialog extends JDialog implements ActionListener {
	protected JPanel footer_panel;
	protected JButton ok_button;
	public ControlsDialog(Frame owner) 
	{
		super(owner, "In-game controls", true);
		
		setTitle("In-game controls");
		{
			this.footer_panel = new JPanel();
			getContentPane().add(this.footer_panel, BorderLayout.SOUTH);
			{
				this.ok_button = new JButton("Got it!");
				this.footer_panel.add(this.ok_button);
			}
		}
		{
			JPanel body_panel = new JPanel();
			getContentPane().add(body_panel, BorderLayout.NORTH);
			{
				JPanel body_grid_panel = new JPanel();
				body_panel.add(body_grid_panel);
				GridBagLayout gbl_body_grid_panel = new GridBagLayout();
				gbl_body_grid_panel.columnWidths = new int[]{0, 0};
				gbl_body_grid_panel.rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
				gbl_body_grid_panel.columnWeights = new double[]{1.0, Double.MIN_VALUE};
				gbl_body_grid_panel.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
				body_grid_panel.setLayout(gbl_body_grid_panel);
				{
					JLabel movexz = new JLabel("Move camera along X-Z plane:");
					movexz.setFont(new Font("Lucida Grande", Font.BOLD, 13));
					GridBagConstraints gbc_movexz = new GridBagConstraints();
					gbc_movexz.anchor = GridBagConstraints.SOUTH;
					gbc_movexz.ipady = 10;
					gbc_movexz.insets = new Insets(0, 0, 5, 0);
					gbc_movexz.gridx = 0;
					gbc_movexz.gridy = 0;
					body_grid_panel.add(movexz, gbc_movexz);
				}
				{
					JLabel wasd = new JLabel("W,A,S,D");
					GridBagConstraints gbc_wasd = new GridBagConstraints();
					gbc_wasd.insets = new Insets(0, 0, 5, 0);
					gbc_wasd.gridx = 0;
					gbc_wasd.gridy = 1;
					body_grid_panel.add(wasd, gbc_wasd);
				}
				{
					JLabel move = new JLabel("Move camera:");
					move.setFont(new Font("Lucida Grande", Font.BOLD, 13));
					GridBagConstraints gbc_move = new GridBagConstraints();
					gbc_move.anchor = GridBagConstraints.SOUTH;
					gbc_move.ipady = 10;
					gbc_move.insets = new Insets(0, 0, 5, 0);
					gbc_move.gridx = 0;
					gbc_move.gridy = 2;
					body_grid_panel.add(move, gbc_move);
				}
				{
					JLabel altwheel = new JLabel("WheelPress+MouseMove");
					GridBagConstraints gbc_altwheel = new GridBagConstraints();
					gbc_altwheel.insets = new Insets(0, 0, 5, 0);
					gbc_altwheel.gridx = 0;
					gbc_altwheel.gridy = 3;
					body_grid_panel.add(altwheel, gbc_altwheel);
				}
				{
					JLabel look = new JLabel("Look around:");
					look.setFont(new Font("Lucida Grande", Font.BOLD, 13));
					GridBagConstraints gbc_look = new GridBagConstraints();
					gbc_look.ipady = 10;
					gbc_look.insets = new Insets(0, 0, 5, 0);
					gbc_look.gridx = 0;
					gbc_look.gridy = 4;
					body_grid_panel.add(look, gbc_look);
				}
				{
					JLabel whellmouse = new JLabel("Alt+WheelPress+MouseMove");
					GridBagConstraints gbc_whellmouse = new GridBagConstraints();
					gbc_whellmouse.insets = new Insets(0, 0, 5, 0);
					gbc_whellmouse.gridx = 0;
					gbc_whellmouse.gridy = 5;
					body_grid_panel.add(whellmouse, gbc_whellmouse);
				}
				{
					JLabel movexz = new JLabel("Toggle Texture / Color:");
					movexz.setFont(new Font("Lucida Grande", Font.BOLD, 13));
					GridBagConstraints gbc_movexz = new GridBagConstraints();
					gbc_movexz.ipady = 10;
					gbc_movexz.insets = new Insets(0, 0, 5, 0);
					gbc_movexz.gridx = 0;
					gbc_movexz.gridy = 6;
					body_grid_panel.add(movexz, gbc_movexz);
				}
				{
					JLabel t = new JLabel("T");
					GridBagConstraints gbc_t = new GridBagConstraints();
					gbc_t.insets = new Insets(0, 0, 5, 0);
					gbc_t.gridx = 0;
					gbc_t.gridy = 7;
					body_grid_panel.add(t, gbc_t);
				}
				{
					JLabel lblToggleGameviewMode = new JLabel("Toggle Game/View Mode");
					lblToggleGameviewMode.setFont(new Font("Lucida Grande", Font.BOLD, 13));
					GridBagConstraints gbc_lblToggleGameviewMode = new GridBagConstraints();
					gbc_lblToggleGameviewMode.insets = new Insets(0, 0, 5, 0);
					gbc_lblToggleGameviewMode.gridx = 0;
					gbc_lblToggleGameviewMode.gridy = 8;
					body_grid_panel.add(lblToggleGameviewMode, gbc_lblToggleGameviewMode);
				}
				{
					JLabel lblR = new JLabel("R");
					GridBagConstraints gbc_lblR = new GridBagConstraints();
					gbc_lblR.insets = new Insets(0, 0, 5, 0);
					gbc_lblR.gridx = 0;
					gbc_lblR.gridy = 9;
					body_grid_panel.add(lblR, gbc_lblR);
				}
				{
					JLabel moveBox = new JLabel("Move test box:");
					moveBox.setFont(new Font("Lucida Grande", Font.BOLD, 13));
					GridBagConstraints gbc_moveBox = new GridBagConstraints();
					gbc_moveBox.ipady = 10;
					gbc_moveBox.insets = new Insets(0, 0, 5, 0);
					gbc_moveBox.gridx = 0;
					gbc_moveBox.gridy = 10;
					body_grid_panel.add(moveBox, gbc_moveBox);
				}
				{
					JLabel gyhj = new JLabel("G,Y,H,J");
					GridBagConstraints gbc_gyhj = new GridBagConstraints();
					gbc_gyhj.insets = new Insets(0, 0, 5, 0);
					gbc_gyhj.gridx = 0;
					gbc_gyhj.gridy = 11;
					body_grid_panel.add(gyhj, gbc_gyhj);
				}
			}
		}
		
		ok_button.addActionListener(this);
	}

	@Override
	public void setVisible(boolean b)
	{
		this.setLocationRelativeTo(this.getOwner());
		this.pack();
		super.setVisible(b);
	}

	@Override
	public void actionPerformed(ActionEvent $) {
		super.setVisible(false);
	}
}

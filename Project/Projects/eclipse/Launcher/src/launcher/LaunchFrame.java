package launcher;



import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;
import javax.swing.SwingConstants;
import javax.swing.WindowConstants;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;

@SuppressWarnings("serial")
public class LaunchFrame extends JFrame {

	protected JPanel contentPane;
	protected JTextField pwd;
	protected JTextField wallDiffuse;
	protected JTextField floorDiffuse;
	protected JPanel tab_graphics;
	protected JPanel tab_output;
	protected JButton newDigger;
	protected JButton editDigger;
	protected JButton removeDigger;
	protected JTextField seed;
	protected JTextArea console;
	protected JButton runButton;
	protected JCheckBox showGrid;
	protected JCheckBox showBoundingVolumes;
	protected JTabbedPane tabbedPane;
	protected JPanel tab_generator;
	protected JScrollPane scrollPane;
	protected JCheckBox output_path;
	protected JTextField mazeWidth;
	protected JTextField mazeLength;
	protected JCheckBox saveProfile_check;
	protected JTextField saveProfile;
	protected JPanel random_button_panel;
	protected JButton newRandom;
	protected JButton editRandom;
	protected JButton removeRandom;
	protected JList randomList;
	protected RandomComboBoxUpdater cbUpdater;
	protected JList diggerList;

	/**
	 * Create the frame.
	 */
	public LaunchFrame() 
	{
		setTitle("Dungeon Generator Launcher");
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		setBounds(100, 100, 639, 500);
		
		this.menuBar = new JMenuBar();
		setJMenuBar(this.menuBar);
		
		/*this.fileMenu = new JMenu("File");
		this.menuBar.add(this.fileMenu);
		
		this.file_loadProfile = new JMenuItem("Load DunGen Profile");
		this.fileMenu.add(this.file_loadProfile);*/
		
		this.helpMenu = new JMenu("Help");
		this.menuBar.add(this.helpMenu);
		
		this.help_controls = new JMenuItem("In-game controls");
		this.helpMenu.add(this.help_controls);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		tabbedPane = new JTabbedPane(SwingConstants.TOP);
		contentPane.add(tabbedPane, BorderLayout.CENTER);
		
		tab_generator = new JPanel();
		this.tab_generator.setToolTipText("Control file input and the generator's behaviour.");
		tabbedPane.addTab("Generator", null, tab_generator, null);
		tab_generator.setLayout(new BorderLayout(0, 0));
		
		JSplitPane generator_splitPane = new JSplitPane();
		tab_generator.add(generator_splitPane);
		
		JPanel generator_general_panel = new JPanel();
		generator_general_panel.setBorder(new TitledBorder(null, "General", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		generator_splitPane.setLeftComponent(generator_general_panel);
		GridBagLayout gbl_generator_general_panel = new GridBagLayout();
		gbl_generator_general_panel.columnWidths = new int[]{0, 0, 0, 0, 0};
		gbl_generator_general_panel.rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gbl_generator_general_panel.columnWeights = new double[]{1.0, 0.0, 0.0, 0.0, 1.0};
		gbl_generator_general_panel.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		generator_general_panel.setLayout(gbl_generator_general_panel);
		
		JLabel mazeWidth_label = new JLabel("Maze Width:");
		GridBagConstraints gbc_mazeWidth_label = new GridBagConstraints();
		gbc_mazeWidth_label.anchor = GridBagConstraints.WEST;
		gbc_mazeWidth_label.insets = new Insets(0, 0, 5, 5);
		gbc_mazeWidth_label.gridx = 0;
		gbc_mazeWidth_label.gridy = 0;
		generator_general_panel.add(mazeWidth_label, gbc_mazeWidth_label);
		
		this.mazeWidth = new JTextField();
		this.mazeWidth.setToolTipText("Number of cells along the X-axis");
		GridBagConstraints gbc_mazeWidth = new GridBagConstraints();
		gbc_mazeWidth.anchor = GridBagConstraints.WEST;
		gbc_mazeWidth.insets = new Insets(0, 0, 5, 5);
		gbc_mazeWidth.gridx = 1;
		gbc_mazeWidth.gridy = 0;
		generator_general_panel.add(this.mazeWidth, gbc_mazeWidth);
		this.mazeWidth.setColumns(3);
		
		JLabel mazeLength_label = new JLabel("Maze Length:");
		GridBagConstraints gbc_mazeLength_label = new GridBagConstraints();
		gbc_mazeLength_label.anchor = GridBagConstraints.WEST;
		gbc_mazeLength_label.insets = new Insets(0, 0, 5, 5);
		gbc_mazeLength_label.gridx = 2;
		gbc_mazeLength_label.gridy = 0;
		generator_general_panel.add(mazeLength_label, gbc_mazeLength_label);
		
		this.mazeLength = new JTextField();
		this.mazeLength.setToolTipText("Number of cells along the Z-axis.");
		GridBagConstraints gbc_mazeLength = new GridBagConstraints();
		gbc_mazeLength.anchor = GridBagConstraints.WEST;
		gbc_mazeLength.insets = new Insets(0, 0, 5, 5);
		gbc_mazeLength.gridx = 3;
		gbc_mazeLength.gridy = 0;
		generator_general_panel.add(this.mazeLength, gbc_mazeLength);
		this.mazeLength.setColumns(3);
		
		JLabel pwd_label = new JLabel("Program Working Directory:");
		GridBagConstraints gbc_pwd_label = new GridBagConstraints();
		gbc_pwd_label.gridwidth = 4;
		gbc_pwd_label.anchor = GridBagConstraints.WEST;
		gbc_pwd_label.insets = new Insets(0, 0, 5, 5);
		gbc_pwd_label.gridx = 0;
		gbc_pwd_label.gridy = 1;
		generator_general_panel.add(pwd_label, gbc_pwd_label);
		
		pwd = new JTextField();
		this.pwd.setToolTipText("Directory used to search for content files.");
		GridBagConstraints gbc_pwd = new GridBagConstraints();
		gbc_pwd.gridwidth = 4;
		gbc_pwd.insets = new Insets(0, 0, 5, 5);
		gbc_pwd.fill = GridBagConstraints.HORIZONTAL;
		gbc_pwd.gridx = 0;
		gbc_pwd.gridy = 2;
		generator_general_panel.add(pwd, gbc_pwd);
		pwd.setColumns(10);
		
		JLabel wallDiffuse_label = new JLabel("Wall Diffuse:");
		GridBagConstraints gbc_wallDiffuse_label = new GridBagConstraints();
		gbc_wallDiffuse_label.gridwidth = 2;
		gbc_wallDiffuse_label.anchor = GridBagConstraints.WEST;
		gbc_wallDiffuse_label.insets = new Insets(0, 0, 5, 5);
		gbc_wallDiffuse_label.gridx = 0;
		gbc_wallDiffuse_label.gridy = 3;
		generator_general_panel.add(wallDiffuse_label, gbc_wallDiffuse_label);
		
		wallDiffuse = new JTextField();
		this.wallDiffuse.setToolTipText("2D texture used on walls (PNG, JPEG, TIFF)");
		GridBagConstraints gbc_wallDiffuse = new GridBagConstraints();
		gbc_wallDiffuse.gridwidth = 4;
		gbc_wallDiffuse.insets = new Insets(0, 0, 5, 5);
		gbc_wallDiffuse.fill = GridBagConstraints.HORIZONTAL;
		gbc_wallDiffuse.gridx = 0;
		gbc_wallDiffuse.gridy = 4;
		generator_general_panel.add(wallDiffuse, gbc_wallDiffuse);
		wallDiffuse.setColumns(10);
		wallDiffuse.setText( "data/diffuse/wall.png" );
		
		JLabel floorDiffuse_label = new JLabel("Floor Diffuse:");
		GridBagConstraints gbc_floorDiffuse_label = new GridBagConstraints();
		gbc_floorDiffuse_label.gridwidth = 2;
		gbc_floorDiffuse_label.anchor = GridBagConstraints.WEST;
		gbc_floorDiffuse_label.insets = new Insets(0, 0, 5, 5);
		gbc_floorDiffuse_label.gridx = 0;
		gbc_floorDiffuse_label.gridy = 5;
		generator_general_panel.add(floorDiffuse_label, gbc_floorDiffuse_label);
		
		floorDiffuse = new JTextField();
		this.floorDiffuse.setToolTipText("2D texture used on floor (PNG, JPEG, TIFF)");
		GridBagConstraints gbc_floorDiffuse = new GridBagConstraints();
		gbc_floorDiffuse.gridwidth = 4;
		gbc_floorDiffuse.insets = new Insets(0, 0, 5, 5);
		gbc_floorDiffuse.fill = GridBagConstraints.HORIZONTAL;
		gbc_floorDiffuse.gridx = 0;
		gbc_floorDiffuse.gridy = 6;
		generator_general_panel.add(floorDiffuse, gbc_floorDiffuse);
		floorDiffuse.setColumns(10);
		floorDiffuse.setText( "data/diffuse/floor.png" );
		
		this.lblCeilingDiffuse = new JLabel("Ceiling Diffuse:");
		GridBagConstraints gbc_lblCeilingDiffuse = new GridBagConstraints();
		gbc_lblCeilingDiffuse.gridwidth = 2;
		gbc_lblCeilingDiffuse.anchor = GridBagConstraints.WEST;
		gbc_lblCeilingDiffuse.insets = new Insets(0, 0, 5, 5);
		gbc_lblCeilingDiffuse.gridx = 0;
		gbc_lblCeilingDiffuse.gridy = 7;
		generator_general_panel.add(this.lblCeilingDiffuse, gbc_lblCeilingDiffuse);
		
		this.ceilingDiffuse = new JTextField();
		this.ceilingDiffuse.setText("data/diffuse/ceiling.png");
		GridBagConstraints gbc_ceilingDiffuse = new GridBagConstraints();
		gbc_ceilingDiffuse.gridwidth = 4;
		gbc_ceilingDiffuse.insets = new Insets(0, 0, 5, 5);
		gbc_ceilingDiffuse.fill = GridBagConstraints.HORIZONTAL;
		gbc_ceilingDiffuse.gridx = 0;
		gbc_ceilingDiffuse.gridy = 8;
		generator_general_panel.add(this.ceilingDiffuse, gbc_ceilingDiffuse);
		this.ceilingDiffuse.setColumns(10);
		
		JLabel seed_label = new JLabel("Seed:");
		GridBagConstraints gbc_seed_label = new GridBagConstraints();
		gbc_seed_label.anchor = GridBagConstraints.WEST;
		gbc_seed_label.insets = new Insets(0, 0, 5, 5);
		gbc_seed_label.gridx = 0;
		gbc_seed_label.gridy = 9;
		generator_general_panel.add(seed_label, gbc_seed_label);
		
		this.seed = new JTextField();
		this.seed.setToolTipText("Random seed used for the Uniform number generator.\nLeave blank to use clock time as the seed.");
		GridBagConstraints gbc_seed = new GridBagConstraints();
		gbc_seed.gridwidth = 3;
		gbc_seed.insets = new Insets(0, 0, 5, 5);
		gbc_seed.fill = GridBagConstraints.HORIZONTAL;
		gbc_seed.gridx = 1;
		gbc_seed.gridy = 9;
		generator_general_panel.add(this.seed, gbc_seed);
		this.seed.setColumns(7);
		
		showGrid = new JCheckBox("Show Grid");
		this.showGrid.setToolTipText("Show a 10x10 grid in the center of\nthe scene.");
		GridBagConstraints gbc_showGrid = new GridBagConstraints();
		gbc_showGrid.anchor = GridBagConstraints.WEST;
		gbc_showGrid.gridwidth = 4;
		gbc_showGrid.insets = new Insets(0, 0, 5, 5);
		gbc_showGrid.gridx = 0;
		gbc_showGrid.gridy = 10;
		generator_general_panel.add(showGrid, gbc_showGrid);
		
		showBoundingVolumes = new JCheckBox("Show bounding volumes");
		this.showBoundingVolumes.setToolTipText("Show the bounding boxes used for\ncollision detection.");
		GridBagConstraints gbc_showBoundingVolumes = new GridBagConstraints();
		gbc_showBoundingVolumes.anchor = GridBagConstraints.WEST;
		gbc_showBoundingVolumes.gridwidth = 4;
		gbc_showBoundingVolumes.insets = new Insets(0, 0, 0, 5);
		gbc_showBoundingVolumes.gridx = 0;
		gbc_showBoundingVolumes.gridy = 11;
		generator_general_panel.add(showBoundingVolumes, gbc_showBoundingVolumes);
		
		JPanel generator_RandomDigger_panel = new JPanel();
		generator_RandomDigger_panel.setBorder(new EmptyBorder(0, 0, 0, 0));
		generator_splitPane.setRightComponent(generator_RandomDigger_panel);
		generator_RandomDigger_panel.setLayout(new BoxLayout(generator_RandomDigger_panel, BoxLayout.Y_AXIS));
		
		JSplitPane generator_splitpane2 = new JSplitPane();
		generator_splitpane2.setOrientation(JSplitPane.VERTICAL_SPLIT);
		generator_RandomDigger_panel.add(generator_splitpane2);
		
		JPanel generator_random_panel = new JPanel();
		generator_splitpane2.setLeftComponent(generator_random_panel);
		generator_random_panel.setBorder(new TitledBorder(null, "Number generators", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		generator_random_panel.setLayout(new BorderLayout(0, 0));
		
		this.random_button_panel = new JPanel();
		generator_random_panel.add(this.random_button_panel, BorderLayout.NORTH);
		this.random_button_panel.setLayout(new BoxLayout(this.random_button_panel, BoxLayout.X_AXIS));
		
		this.newRandom = new JButton("New");
		this.newRandom.setToolTipText("Create a new random number generator.");
		this.random_button_panel.add(this.newRandom);
		
		this.editRandom = new JButton("Edit");
		this.editRandom.setToolTipText("Edit selected number generator.");
		this.random_button_panel.add(this.editRandom);
		
		this.removeRandom = new JButton("Remove");
		this.removeRandom.setToolTipText("Remove selected number generator.");
		this.random_button_panel.add(this.removeRandom);
		
		JScrollPane random_scrollPane = new JScrollPane();
		random_scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		generator_random_panel.add(random_scrollPane, BorderLayout.CENTER);
		
		this.randomList = new JList();
		this.randomList.setVisibleRowCount(3);
		this.randomList.setModel(new DefaultListModel());
		random_scrollPane.setViewportView(this.randomList);
		
		JPanel generator_diggers_panel = new JPanel();
		generator_splitpane2.setRightComponent(generator_diggers_panel);
		generator_diggers_panel.setBorder(new TitledBorder(null, "Diggers", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		generator_diggers_panel.setLayout(new BorderLayout(0, 0));
		
		JPanel digger_button_panel = new JPanel();
		generator_diggers_panel.add(digger_button_panel, BorderLayout.NORTH);
		digger_button_panel.setLayout(new BoxLayout(digger_button_panel, BoxLayout.X_AXIS));
		
		newDigger = new JButton("New");
		this.newDigger.setToolTipText("Create a new digger.");
		digger_button_panel.add(newDigger);
		
		editDigger = new JButton("Edit");
		this.editDigger.setToolTipText("Edit selected digger.");
		this.editDigger.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
			}
		});
		digger_button_panel.add(editDigger);
		
		removeDigger = new JButton("Remove");
		this.removeDigger.setToolTipText("Remove selected digger.");
		digger_button_panel.add(removeDigger);
		
		JScrollPane digger_scrollPane = new JScrollPane();
		digger_scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		generator_diggers_panel.add(digger_scrollPane, BorderLayout.CENTER);
		
		this.diggerList = new JList();
		this.diggerList.setModel(new DefaultListModel());
		this.diggerList.setVisibleRowCount(5);
		digger_scrollPane.setViewportView(this.diggerList);
		
		tab_graphics = new JPanel();
		this.tab_graphics.setToolTipText("Graphics settings and options.");
		tabbedPane.addTab("Graphics", null, tab_graphics, null);
		this.tab_graphics.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
		
		this.panel = new JPanel();
		this.tab_graphics.add(this.panel);
		GridBagLayout gbl_panel = new GridBagLayout();
		gbl_panel.columnWidths = new int[]{0, 0, 0};
		gbl_panel.rowHeights = new int[]{0, 0, 0};
		gbl_panel.columnWeights = new double[]{0.0, 0.0, Double.MIN_VALUE};
		gbl_panel.rowWeights = new double[]{0.0, 0.0, Double.MIN_VALUE};
		this.panel.setLayout(gbl_panel);
		
		JLabel screenRes_label = new JLabel("Screen Resolution");
		GridBagConstraints gbc_screenRes_label = new GridBagConstraints();
		gbc_screenRes_label.anchor = GridBagConstraints.WEST;
		gbc_screenRes_label.insets = new Insets(0, 0, 5, 5);
		gbc_screenRes_label.gridx = 0;
		gbc_screenRes_label.gridy = 0;
		this.panel.add(screenRes_label, gbc_screenRes_label);
		
		this.screenRes = new JComboBox();
		GridBagConstraints gbc_screenRes = new GridBagConstraints();
		gbc_screenRes.anchor = GridBagConstraints.WEST;
		gbc_screenRes.insets = new Insets(0, 0, 5, 0);
		gbc_screenRes.gridx = 1;
		gbc_screenRes.gridy = 0;
		this.panel.add(this.screenRes, gbc_screenRes);
		
		JLabel bitFormat_label = new JLabel("Color Format");
		GridBagConstraints gbc_bitFormat_label = new GridBagConstraints();
		gbc_bitFormat_label.anchor = GridBagConstraints.WEST;
		gbc_bitFormat_label.insets = new Insets(0, 0, 0, 5);
		gbc_bitFormat_label.gridx = 0;
		gbc_bitFormat_label.gridy = 1;
		this.panel.add(bitFormat_label, gbc_bitFormat_label);
		
		this.bitFormat = new JComboBox();
		GridBagConstraints gbc_bitFormat = new GridBagConstraints();
		gbc_bitFormat.fill = GridBagConstraints.HORIZONTAL;
		gbc_bitFormat.gridx = 1;
		gbc_bitFormat.gridy = 1;
		this.panel.add(this.bitFormat, gbc_bitFormat);
		
		tab_output = new JPanel();
		this.tab_output.setToolTipText("Control file and console output.");
		tabbedPane.addTab("Output", null, tab_output, null);
		this.tab_output.setLayout(new BorderLayout(0, 0));
		
		JSplitPane splitPane = new JSplitPane();
		this.tab_output.add(splitPane, BorderLayout.CENTER);
		
		JPanel console_panel = new JPanel();
		console_panel.setBorder(new TitledBorder(null, "Console", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		splitPane.setRightComponent(console_panel);
		console_panel.setLayout(new BorderLayout(0, 0));
		
		this.scrollPane = new JScrollPane();
		this.scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		console_panel.add(this.scrollPane, BorderLayout.CENTER);
		
		console = new JTextArea();
		this.console.setWrapStyleWord(true);
		this.scrollPane.setViewportView(this.console);
		console.setEditable(false);
		
		JPanel consoleControlPanel = new JPanel();
		FlowLayout fl_consoleControlPanel = (FlowLayout) consoleControlPanel.getLayout();
		fl_consoleControlPanel.setVgap(1);
		fl_consoleControlPanel.setHgap(1);
		fl_consoleControlPanel.setAlignment(FlowLayout.LEFT);
		console_panel.add(consoleControlPanel, BorderLayout.SOUTH);
		
		this.clearConsole_button = new JButton("Clear");
		consoleControlPanel.add(this.clearConsole_button);
		
		JPanel output_panel = new JPanel();
		splitPane.setLeftComponent(output_panel);
		GridBagLayout gbl_output_panel = new GridBagLayout();
		gbl_output_panel.columnWidths = new int[]{0, 0, 0};
		gbl_output_panel.rowHeights = new int[]{0, 0, 0, 0, 0, 0};
		gbl_output_panel.columnWeights = new double[]{0.0, 1.0, Double.MIN_VALUE};
		gbl_output_panel.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		output_panel.setLayout(gbl_output_panel);
		
		this.saveProfile_check = new JCheckBox("Save Profile");
		this.saveProfile_check.setToolTipText("Save this current profile into a file\nto re-used later on.");
		GridBagConstraints gbc_saveProfile_check = new GridBagConstraints();
		gbc_saveProfile_check.anchor = GridBagConstraints.WEST;
		gbc_saveProfile_check.gridwidth = 2;
		gbc_saveProfile_check.insets = new Insets(0, 0, 5, 0);
		gbc_saveProfile_check.gridx = 0;
		gbc_saveProfile_check.gridy = 0;
		output_panel.add(this.saveProfile_check, gbc_saveProfile_check);
		
		JLabel saveProfile_label = new JLabel("File:");
		GridBagConstraints gbc_saveProfile_label = new GridBagConstraints();
		gbc_saveProfile_label.insets = new Insets(0, 0, 5, 5);
		gbc_saveProfile_label.anchor = GridBagConstraints.EAST;
		gbc_saveProfile_label.gridx = 0;
		gbc_saveProfile_label.gridy = 1;
		output_panel.add(saveProfile_label, gbc_saveProfile_label);
		
		this.saveProfile = new JTextField();
		this.saveProfile.setEnabled(false);
		this.saveProfile.setText("myprofile.dungenprofile");
		this.saveProfile.setToolTipText("Filepath of output .dungenprofile file.");
		GridBagConstraints gbc_saveProfile = new GridBagConstraints();
		gbc_saveProfile.insets = new Insets(0, 0, 5, 0);
		gbc_saveProfile.fill = GridBagConstraints.HORIZONTAL;
		gbc_saveProfile.gridx = 1;
		gbc_saveProfile.gridy = 1;
		output_panel.add(this.saveProfile, gbc_saveProfile);
		this.saveProfile.setColumns(10);
		
		this.output_path = new JCheckBox("Log search path");
		this.output_path.setToolTipText("If ticked, search diggers will output the order of\nthe path traversed.");
		GridBagConstraints gbc_output_path = new GridBagConstraints();
		gbc_output_path.insets = new Insets(0, 0, 5, 0);
		gbc_output_path.anchor = GridBagConstraints.WEST;
		gbc_output_path.gridwidth = 2;
		gbc_output_path.gridx = 0;
		gbc_output_path.gridy = 3;
		output_panel.add(this.output_path, gbc_output_path);
		
		JPanel footerPanel = new JPanel();
		FlowLayout footer_flowLayout = (FlowLayout) footerPanel.getLayout();
		footer_flowLayout.setVgap(0);
		footer_flowLayout.setHgap(0);
		footer_flowLayout.setAlignment(FlowLayout.RIGHT);
		contentPane.add(footerPanel, BorderLayout.SOUTH);
		
		runButton = new JButton("Run");
		footerPanel.add(runButton);
	}

	public void appendExceptionStack(Exception e)
	{
		StackTraceElement[] stackTraceElements = e.getStackTrace();
		this.console.append(e.getLocalizedMessage() + "\n");
		for(StackTraceElement elem : stackTraceElements) {
			this.console.append( elem.toString() + "\n" );
		}
		this.console.append("\n");
	}
	
	private boolean locked = false;
	protected JButton clearConsole_button;
	protected JPanel panel;
	protected JComboBox screenRes;
	protected JComboBox bitFormat;
	protected JMenuBar menuBar;
	protected JMenu fileMenu;
	protected JMenu helpMenu;
	protected JMenuItem file_loadProfile;
	protected JMenuItem help_controls;
	protected JLabel lblCeilingDiffuse;
	protected JTextField ceilingDiffuse;
	public void setLock(boolean l) {
		locked = l;
		if (locked) lock();
		else      unlock();
	}
	
	private void lock()
	{
		this.runButton.setEnabled(false);
		
		// Disable generator buttons:
		this.mazeWidth.setEnabled(false);
		this.mazeLength.setEnabled(false);
		this.pwd.setEnabled(false);
		this.floorDiffuse.setEnabled(false);
		this.wallDiffuse.setEnabled(false);
		this.ceilingDiffuse.setEnabled(false);
		this.seed.setEnabled(false);
		this.showBoundingVolumes.setEnabled(false);
		this.showGrid.setEnabled(false);
		this.newRandom.setEnabled(false);
		this.editRandom.setEnabled(false);
		this.removeRandom.setEnabled(false);
		this.randomList.setEnabled(false);
		this.newDigger.setEnabled(false);
		this.editDigger.setEnabled(false);
		this.removeDigger.setEnabled(false);
		this.diggerList.setEnabled(false);
		
		// Disable gfx tab:
		this.screenRes.setEnabled(false);
		this.bitFormat.setEnabled(false);
		
		// Disable output tab:
		//this.output_obj.setEnabled(false);
		//this.output_obj_check.setEnabled(false);
		this.output_path.setEnabled(false);
		this.saveProfile.setEnabled(false);
		this.saveProfile_check.setEnabled(false);
	}
	
	private void unlock()
	{
		this.runButton.setEnabled(true);
		
		// Disable generator buttons:
		this.mazeWidth.setEnabled(true);
		this.mazeLength.setEnabled(true);
		this.pwd.setEnabled(true);
		this.floorDiffuse.setEnabled(true);
		this.wallDiffuse.setEnabled(true);
		this.ceilingDiffuse.setEnabled(true);
		this.seed.setEnabled(true);
		this.showBoundingVolumes.setEnabled(true);
		this.showGrid.setEnabled(true);
		this.newRandom.setEnabled(true);
		this.editRandom.setEnabled(true);
		this.removeRandom.setEnabled(true);
		this.randomList.setEnabled(true);
		this.newDigger.setEnabled(true);
		this.editDigger.setEnabled(true);
		this.removeDigger.setEnabled(true);
		this.diggerList.setEnabled(true);
		
		// Disable gfx tab:
		this.screenRes.setEnabled(true);
		this.bitFormat.setEnabled(true);
		
		// Disable output tab:
		//this.output_obj.setEnabled( this.output_obj_check.isSelected() );
		//this.output_obj_check.setEnabled(true);
		this.output_path.setEnabled(true);
		this.saveProfile.setEnabled( this.saveProfile_check.isSelected() );
		this.saveProfile_check.setEnabled(true);
	}
}

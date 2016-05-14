package rbtree;

import java.util.ArrayList;
import java.util.Random;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.GroupLayout;
import static javax.swing.GroupLayout.Alignment.TRAILING;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JEditorPane;
import static javax.swing.LayoutStyle.ComponentPlacement.UNRELATED;
import javax.swing.border.LineBorder;
import java.awt.RenderingHints;
import java.awt.Graphics;
import java.awt.Font;

class TreePanel extends JPanel
{
	private RBTree<Integer, Integer> tree;
	private ArrayList<Integer> keys;
	private Font font;
	private Random ra;
	private boolean validLLRB;

	public TreePanel()
	{
		setPreferredSize(new Dimension(1200, 600));
		setBorder(LineBorder.createGrayLineBorder());
		setBackground(Color.white);
		font = new Font("Courier", Font.PLAIN, 14);
		tree = new RBTree<Integer, Integer>();
		keys = new ArrayList<Integer>();
		ra = new Random();
		validLLRB = tree.testLLRB();
	}

	@Override
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.setFont(font);
		drawTree(g, tree.root(), 600, 15, 600, 15, 300, 60);
		g.drawString(keys.toString(), 10, 540);
		g.drawString("tree.size: "+tree.size(), 10, 560);
		g.drawString("keys.size: "+keys.size(), 10, 580);
		if (!validLLRB || tree.size() != keys.size()) {
			g.setColor(Color.RED);
			g.drawString("Error!!!", 10, 520);
		}
	}

	public void insert(String s)
	{
		Integer x;
		if (keys.size() == 900) {
			return;
		}
		if (s.equals("")) {
			do {
				x = ra.nextInt(900) + 100;
			} while (!tree.insert(x, x));
			keys.add(x);
		} else {
			try {
				x = Integer.parseInt(s);
			} catch (NumberFormatException e) {
				return;
			}
			if (tree.insert(x, x)) {
				keys.add(x);
			}
		}
		validLLRB = tree.testLLRB();
		repaint();
	}

	public void remove(String s)
	{
		if (keys.isEmpty()) {
			return;
		}
		
		int i;
		Integer x;
		if (s.equals("")) {
			i = ra.nextInt(keys.size());
			x = keys.get(i);
		} else {
			x = Integer.parseInt(s);
			i = keys.indexOf(x);
			if (i == -1) {
				return;
			}
		}
		tree.delete(x);
		keys.remove(i);
		validLLRB = tree.testLLRB();
		repaint();
	}

	// require: node != null
	private void drawTree(Graphics g, RBTree<Integer, Integer>.Node node,
							int xp, int yp, int x, int y,
							int detX, int detY)
	{
		if (node == null) {
			return;
		}

		if (node.isRed()) { g.setColor(Color.RED); }
		else { g.setColor(Color.BLACK); }
		g.drawLine(xp, yp, x, y);

		int yc = y + detY, detXc = detX / 2;
		drawTree(g, node.left(), x, y, x-detX, yc, detXc, detY);
		drawTree(g, node.right(), x, y, x+detX, yc, detXc, detY);

		int r = 12;
		g.setColor(Color.WHITE);
		g.fillArc(x-r, y-r, 2*r, 2*r, 0, 360);
		g.setColor(Color.BLACK);
		g.drawArc(x-r, y-r, 2*r, 2*r, 0, 360);
		drawCenteredString(g, node.key().toString(), x, y);
	}

	private void drawCenteredString(Graphics g, String text, int x, int y)
	{
		x = x - g.getFontMetrics(font).stringWidth(text) / 2;
		y = y + 7;
		g.drawString(text, x, y);
	}
}

public class TreeVisual extends JFrame
{
	private JEditorPane inputPane;
	private JButton insertBtn;
	private JButton removeBtn;
	private JButton quitBtn;
	private TreePanel treePanel;

	public TreeVisual()
	{
		inputPane = new JEditorPane();
		insertBtn = new JButton("insert");
		removeBtn = new JButton("remove");
		quitBtn = new JButton("quit");
		treePanel = new TreePanel();
		addActionListeners();
		createLayout();
		setTitle("TreeVisual");
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	private void addActionListeners()
	{
		insertBtn.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent event) {
				treePanel.insert(inputPane.getText());
			}
		});
		removeBtn.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent event) {
				treePanel.remove(inputPane.getText());
			}
		});
		quitBtn.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent event) {
				System.exit(0);
			}
		});
	}

	private void createLayout()
	{
		Container pane = getContentPane();
		GroupLayout gl = new GroupLayout(pane);
		pane.setLayout(gl);

		gl.setAutoCreateContainerGaps(true);
		gl.setAutoCreateGaps(true);

		gl.setVerticalGroup(gl.createSequentialGroup()
			.addComponent(treePanel)
			.addPreferredGap(UNRELATED)
			.addGroup(gl.createParallelGroup()
				.addComponent(inputPane)
				.addComponent(insertBtn)
				.addComponent(removeBtn)
				.addComponent(quitBtn))
		);

		gl.setHorizontalGroup(gl.createParallelGroup(TRAILING)
			.addComponent(treePanel)
			.addGroup(gl.createSequentialGroup()
				.addComponent(inputPane)
				.addComponent(insertBtn)
				.addComponent(removeBtn)
				.addComponent(quitBtn))
		);

		gl.linkSize(inputPane, insertBtn, removeBtn, quitBtn);

		pack();
	}

	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable() {
			@Override
			public void run() {
				TreeVisual ex = new TreeVisual();
				ex.setVisible(true);
			}
		});
	}
}
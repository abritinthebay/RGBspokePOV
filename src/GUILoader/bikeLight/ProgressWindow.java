package bikeLight;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JProgressBar;

public class ProgressWindow extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	JProgressBar pb;
	JButton cb;
	public ProgressWindow() {
		
		super();
		setLayout(null);
		setIconImage(new ImageIcon(BikeLightFrame.class.getResource("/icon.PNG")).getImage());
		pb=new JProgressBar();
		pb.setBounds(50,50,300,30);
		pb.setMaximum(100);
		add(pb);
		cb=new JButton("Cancel");
		cb.setBounds(140,100,120,30);
		add(cb);
		cb.addActionListener(new cancelAL());
		setBounds(160,250,400,200);
		
		setVisible(true);
		
		
		
	}
	
	public class cancelAL implements ActionListener
	{

		public void actionPerformed(ActionEvent arg0) {
			ProgressWindow.this.dispose();
		}
	
	}
	public void updateValue(int val)
	{
		pb.setValue(val);
	}

}

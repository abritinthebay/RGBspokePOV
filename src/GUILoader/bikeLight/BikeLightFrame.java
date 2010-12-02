package bikeLight;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.MediaTracker;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.PixelGrabber;

import java.io.*;


import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;




/**
 * @author Jan Paul Posma
 *
 */
public class BikeLightFrame extends JFrame{

	/**
	 * 
	 */
	public final int nLeds=24;	//number of leds connected to the PIC
	public final int nCir=256;	//number of pixels in a circle
	public final int nFrames=2;
	 private Image m_image=null;   // pointer to original image
	  private int w, h;
	  public JSlider thBar;
	  public JButton openImage;
	  public JButton saveHeader;
	  public JButton comSettings;
	  public JButton sendImage;
	  public Image img=null;
	  public JTextField recData;
	  public JSlider startBar;
	  public JButton switchFrame;
	  public JSlider frameTurns;
	  public JLabel cF,fT;
	private int currentFrame;
	private static final long serialVersionUID = 1L;
	public int[][][] image;
	public int[] pixels;
	public BikeLightFrame() {
		super();
		setTitle("PimpMyBike");
		setIconImage(new ImageIcon(BikeLightFrame.class.getResource("/icon.PNG")).getImage());
		setDefaultLookAndFeelDecorated(false);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		JLabel threshold = new JLabel("Threshold");
		threshold.setBounds(20,15,120,15);
		add(threshold);
		image=new int[nCir+1][nLeds+1][nFrames+1];
		thBar=new JSlider();
		thBar.setMaximum(255);
		thBar.setMinimum(0);
		thBar.setBounds(20,30,120,20);
		add(thBar);
		openImage = new JButton("Open Image");
		openImage.setBounds(20,50,120,20);
		openImage.addActionListener(new openAL());
		add(openImage);
		saveHeader = new JButton("Save Header");
		saveHeader.setBounds(20,80,120,20);
		saveHeader.addActionListener(new saveHeaderAL());
		add(saveHeader);
		comSettings = new JButton("COM settings");
		comSettings.setBounds(20,110,120,20);
		comSettings.addActionListener(new comSettingsAL());
		add(comSettings);
		sendImage = new JButton("Send image");
		sendImage.setBounds(20,140,120,20);
		sendImage.addActionListener(new sendImageAL());
		add(sendImage);
		//Image img;
		recData = new JTextField();
		recData.setBounds(20,170,120,20);
		add(recData);
		cF = new JLabel("Start position: 0");
		cF.setBounds(20,200,120,15);
		add(cF);
		
		startBar=new JSlider();
		startBar.setMaximum(nCir-1);
		startBar.setMinimum(0);
		startBar.addChangeListener(new startBarCl());
		startBar.setBounds(20,215,120,20);
		startBar.setValue(0);
		add(startBar);
		switchFrame = new JButton("Switch Frame");
		switchFrame.setBounds(20,245,120,20);
		switchFrame.addActionListener(new switchFrameAL());
		add(switchFrame);
		fT = new JLabel("Current side: Left");
		fT.setBounds(20,275,120,15);
		add(fT);		
		
		setLayout(null);
		setSize(720,600);
		setVisible(true);
		setResizable(false);
		
	}
	
	
	boolean openPicture()
	{
		JFileChooser fc=new JFileChooser();
		
		String filename=null;
        MediaTracker mt = new MediaTracker(this);
        String[] filefilters={"JPG","GIF","PNG"};
        fc.setFileFilter(new ExampleFileFilter(filefilters,"Supported Filetypes"));
		int fd=fc.showOpenDialog(BikeLightFrame.this);
        if(fd==JFileChooser.APPROVE_OPTION){
            filename=fc.getSelectedFile().getPath();
            repaint();
            m_image=img;
        }
        else
        	return true;
        System.out.println("Opening file: "+filename);
        img = Toolkit.getDefaultToolkit().getImage(filename);
        mt.addImage(img, 0);                
        try
        {
            mt.waitForAll();
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        } 
        
		m_image=img;
        w=m_image.getWidth(this);
        h=m_image.getHeight(this);
        if(w>0)
        {
        	thBar.addChangeListener(new thChange());
        	thBar.setEnabled(true);
        }
        else
        {
        	thBar.setEnabled(false);
        }
        pixels = new int[(w+1)*(h+1)];
        System.out.println(w);
        System.out.println(h);
        PixelGrabber pixelGrabber=new PixelGrabber(m_image, 0,0,w, h, pixels,0 ,w);
        try {
        	pixelGrabber.grabPixels();
		} catch (InterruptedException e) {
            System.err.println("interrupted waiting for pixels!");
           	System.exit(0);
		}
		
		/*
		for(int i=0;i<pixels.length;i++)
		{
			pixels[i]=((pixels[i]&0xFF)+((pixels[i]>>8)&0xFF)+((pixels[i]>>16)&0xFF)/3)&0xFF;
		}
		*/
		
		return false;
	}
	
	public void updatePicture()
	{
		int meanVal=(minVal(pixels)+maxVal(pixels))/2;
		System.out.println("Meanval: "+meanVal);
		for(int i=0;i<nCir;i++)
		{
			for(int j=0;j<nLeds;j++)
			{
				image[i][j][currentFrame] = 
				  ((pixels[rad2ind(i,j,w,h)] & 0xFF) / 64)
				| ((((pixels[rad2ind(i,j,w,h)] >> 8) & 0xFF) / 32) << 2)
				| ((((pixels[rad2ind(i,j,w,h)] >> 16) & 0xFF) / 32) << 5);
			}
		}

		repaint();	
	}
	
	public int minVal(int[] arr)
	{
		int tempVal=255;
		for(int i=0;i<arr.length;i++)
		{
			if(arr[i]<tempVal)tempVal=arr[i];
		}
		System.out.println("Minval: "+tempVal);
		
		return tempVal;
	}
	
	public class thChange implements ChangeListener 
	{
		public void stateChanged(ChangeEvent arg0) 
		{
		      updatePicture();
		}
	}
	
	public class openAL implements ActionListener
	{

		public void actionPerformed(ActionEvent arg0) {
			if (!openPicture())
				updatePicture();
			
		}
	
	}
	
	public class saveHeaderAL implements ActionListener
	{

		public void actionPerformed(ActionEvent arg0) {
			if(saveHeaderFile())System.out.println("Error saving file");
			
		}
	
	}
	
	public class comSettingsAL implements ActionListener
	{

		public void actionPerformed(ActionEvent arg0) {
			
			
		}
	
	}
	
	public class sendImageAL implements ActionListener
	{

		public void actionPerformed(ActionEvent arg0) {
			
		}
	
	}
	
	public class switchFrameAL implements ActionListener
	{

		public void actionPerformed(ActionEvent arg0) {
			
			currentFrame++;
			if (currentFrame >= nFrames)
			{
				currentFrame = 0;
			}
			
			if (currentFrame == 0)
			{
				fT.setText("Current side: Left");
			}
			else
			{
				fT.setText("Current side: Right");
			}
			
			repaint();
		}
	
	}
	public class startBarCl implements ChangeListener
	{

		public void stateChanged(ChangeEvent arg0) {
			repaint();
			cF.setText("Start position: "+Integer.toString(startBar.getValue()));
			startBar.setToolTipText(Integer.toString(startBar.getValue()));
		}
		
	}
	
	public class frameTurnsCl implements ChangeListener
	{

		public void stateChanged(ChangeEvent arg0) {
			repaint();
			
			fT.setText("Turns per frame: "+Integer.toString(frameTurns.getValue()));
			frameTurns.setToolTipText(Integer.toString(frameTurns.getValue()));
		}
		
	}
	
	public int maxVal(int[] arr)
	{
		int tempVal=0;
		for(int i=0;i<arr.length;i++)
		{
			
			if(arr[i]>tempVal)tempVal=arr[i];
		}
		System.out.println("Maxval: "+tempVal);
		
		return tempVal;
	}
	
	public int rad2ind(int cir, int rad, int w, int h)
	{
		int centerx=w/2;
		int centery=h/2;
		int x=centerx+(int)(Math.cos((((double)cir)/nCir)*2*Math.PI)*(0.1*centerx+(((double)rad)/nLeds)*((double)centerx*0.9)));
		int y=centery+(int)(Math.sin((((double)cir)/nCir)*2*Math.PI)*(0.1*centery+(((double)rad)/nLeds)*((double)centery*0.9)));
		return y*w+x;
	}
	
	public void paint(Graphics g)
	{
		super.paint(g);
		double x,y;
		g.setColor (Color.darkGray);
		g.drawLine(150,0,150,600);
		g.setColor( Color.gray);
		g.drawLine(151,0,151,600);
		g.setColor( Color.white);
		g.drawLine(152,0,152,600);
		//g.fillOval (50,50,80,70);
		
		for(double i=0;i<nLeds;i++)
		{
			for(double j=0;j<nCir;j++)
			{
				//if(image[(int)j][(int)i][frameBar.getValue()])
				
				g.setColor(new Color( 
				((image[(int)j][(int)i][currentFrame] >> 5) & 0x07) * 32, 
				((image[(int)j][(int)i][currentFrame] >> 2) & 0x07) * 32, 
				((image[(int)j][(int)i][currentFrame] << 1) & 0x06) * 32
				));
					
				x=(Math.cos((j/nCir)*2*3.14)*(8*i+30))+420;
				y=(Math.sin((j/nCir)*2*3.14)*(8*i+30))+300;
				g.fillOval((int)x,(int)y,7,7);
			}
		}
		
		g.setColor(Color.gray);
		
		if (currentFrame == 0)
		{
			g.drawLine(420, 300, 
				(int)(Math.sin(((double)startBar.getValue()/nCir)*2*3.14)*(8*(nLeds+1)+30))+420, 
				(int)(Math.cos(((double)startBar.getValue()/nCir)*2*3.14)*(8*(nLeds+1)+30))+300);
		}
		else
		{
			g.drawLine(420, 300, 
					(int)-(Math.sin(((double)startBar.getValue()/nCir)*2*3.14)*(8*(nLeds+1)+30))+420, 
					(int)(Math.cos(((double)startBar.getValue()/nCir)*2*3.14)*(8*(nLeds+1)+30))+300);
		}
	}
	
	/**
	 * @param args
	 */
	public boolean saveHeaderFile()
	{
		String filename=null;
		JFileChooser fc=new JFileChooser();
		int address;
		int counter;
		int checksum;
		
		int fd=fc.showSaveDialog(BikeLightFrame.this);
        if(fd==JFileChooser.APPROVE_OPTION){
            filename=fc.getSelectedFile().getPath();
        }
        else
        	return true;
        
        try {
            // Create a PrintStream for writing to the specified
            // file and write the text from the window to that stream.
        	
         File file = new File(filename); 
         PrintWriter out = new PrintWriter(new FileWriter(file));
         
      // Open the file that is the first 
         // command line parameter
         FileInputStream fstream = new FileInputStream("G:\\PimpMyBike\\Software\\PimpMyBike\\bikeLight\\firma.hex");
		
		         // Convert our input stream to a
		         // DataInputStream
		DataInputStream in = new DataInputStream(fstream);
		
		         // Continue to read lines while 
		         // there are still some left to read
		         while (in.available() !=0)
		{
		                 // Print file line to screen
		        	 out.printf("%c", in.read());
		}
		
		in.close();
         
         address = 0x3000;
         counter = -1;
         checksum = 0;
         out.printf(":10%04X00", address);
		 checksum = 0x00 + (address & 0xFF) + ((address >> 8) & 0xFF);
		 address += 0x10;
         
		 int i = 0;
		 int left = startBar.getValue();
		 int right = startBar.getValue();

         while (i<nCir)
         {
        	 for(int k=0;k<nLeds;k++)
        	 {
        		 if (counter >= 0x0F)
        		 {
        			 counter = 0;
		        	 out.printf("%02X\n:10%04X00", (0x100 - (checksum & 0xFF) & 0xFF),
		        			 address);
        			 checksum = 0x00 + (address & 0xFF) + ((address >> 8) & 0xFF);
        			 address += 0x10;
        		 }
        		 else
        		 {
        			 counter++;
        		 }
        		 
        		 out.printf("%02X", image[left][k][0]);
        		 checksum += image[left][k][0];	        	 
        	 }
        	 for(int k=0;k<nLeds;k++)
        	 {
        		 if (counter >= 0x0F)
        		 {
        			 counter = 0;
		        	 out.printf("%02X\n:10%04X00", (0x100 - (checksum & 0xFF) & 0xFF),
		        			 address);
        			 checksum = 0x00 + (address & 0xFF) + ((address >> 8) & 0xFF);
        			 address += 0x10;
        		 }
        		 else
        		 {
        			 counter++;
        		 }
        		 
        		 out.printf("%02X", image[right][k][1]);
        		 checksum += image[right][k][1];	        	 
        	 }
        	 
        	 left++;
        	 right--;
        	 
        	 if (left >= nCir) left = 0;
        	 if (right < 0) right = nCir-1;
        	 
        	 i++;
         }
         
         while (counter < 0x0F)
         {
        	 out.print("00");
        	 counter++;
         }
         
         out.printf("%02X\n", (0x100 - (checksum & 0xFF) & 0xFF));
         
      // Open the file that is the first 
         // command line parameter
         FileInputStream fstream2 = new FileInputStream("G:\\PimpMyBike\\Software\\PimpMyBike\\bikeLight\\firmb.hex");
		
		         // Convert our input stream to a
		         // DataInputStream
		DataInputStream in2 = new DataInputStream(fstream2);
		
		         // Continue to read lines while 
		         // there are still some left to read
		         while (in2.available() !=0)
		{
		                 // Print file line to screen
		        	 out.printf("%c", in2.read());
		}
		
		in.close();
         
         out.close();
      }
      catch (IOException e) {
            // Some error has occured while opening or closing the file.
            // Show an error message.
         System.out.println("Error writing to file");
      }
      
      repaint();
      
        return false;
	}
	
	public int[][] image2ints()
	{
		int[][] tempImageInts=new int[nCir][nFrames];
		for(int k=0;k<nFrames;k++)
		{
			for(int i=0;i<nCir;i++)
	        {
		       	 tempImageInts[i][k]=0;
		       	 for(int j=0;j<nLeds;j++)
		       	 {
		       		//if(image[i][j][k])tempImageInts[i][k]=tempImageInts[i][k]+(1<<j);
		       	 }       	 
	        }
		}
		return tempImageInts;
	}
	
	public static void main(String[] args) 
	{
		new BikeLightFrame();
	}
}

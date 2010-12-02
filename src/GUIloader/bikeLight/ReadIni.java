package bikeLight;

/**
 * Reads the selected comport from comport.ini (eg. DBcomport=COM1)
 */
import java.util.*;
import java.io.*;

import javax.swing.JOptionPane;

class ReadIni {

   

  public String doit() {
	  String tempstring="COM1";
    try{
      Properties p = new Properties();
      p.load(new FileInputStream("comport.ini"));
      tempstring=p.getProperty("DBcomport");
      }
    catch (Exception e) {
    	JOptionPane.showMessageDialog(null,
			    e.toString(),
			    "Ini warning",
			    JOptionPane.WARNING_MESSAGE);
      System.out.println(e);
      }
    	return tempstring;
    }
}
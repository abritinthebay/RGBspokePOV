package bikeLight;

import java.util.*;
import java.io.*;

/**
 * Saves the comport to "comport.ini" (eg. DBcomport=COM2)
 *
 *
 */

class WriteIni {
  public void doit(String comport) {
    try{
      Properties p = new Properties();
      p.put("DBcomport", comport);
      FileOutputStream out = new FileOutputStream("comport.ini");
      p.store(out, "");
      }
    catch (Exception e) {
    	
      System.out.println(e);
      }
    }
}
package fr.enseirb.odroidx;

public class DashManager {
	
	static {
	    System.loadLibrary("dashjni");
	  }
	  
	  public native int openStream(String address);
	  public native int read(byte[] buffer, int size);
}

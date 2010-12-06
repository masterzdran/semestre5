package pt.isel.deetc.ls.report.format;

import java.io.PrintStream;


public abstract class TracFormat<E> implements IFormat {
	private String getDocumentHeader(){
		return "";		
	}
	private String getDocumentFooter(){
		return "";
		
	}
	private String getBodyHeader(){
		return "";
	}
	private String getBodyFooter(){
		return "";
	}
	public void render(PrintStream ps){
		ps.println(getDocumentHeader());
		ps.println(getBodyHeader());
		renderFormat(ps);
		ps.println(getBodyFooter());
		ps.println(getDocumentFooter());
	}
	
	public abstract void renderFormat(PrintStream ps);
}

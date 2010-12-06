package pt.isel.deetc.ls.report.format;

import java.io.PrintStream;


public abstract class HTMLFormat<E> implements IFormat{
	private String getDocumentHeader(){
		return "<HTML>\n";		
	}
	private String getDocumentFooter(){
		return "</HTML>\n";
		
	}
	private String getBodyHeader(){
		return "<BODY>\n";
	}
	private String getBodyFooter(){
		return "</BODY>\n";
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

package pt.isel.deetc.ls.cmd;


import org.junit.Test;

public class GetEventsAllTest {
	@Test
	public void selectAll(){
		GetEventsAll g = new GetEventsAll();
		g.addParameter("layout","table");
		g.addParameter("format","html");
		g.addParameter("output-file","/tmp/geteventsall.html");
		g.run();
	}
}

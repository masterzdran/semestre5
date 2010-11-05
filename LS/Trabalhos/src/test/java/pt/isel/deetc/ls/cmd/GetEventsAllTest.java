package pt.isel.deetc.ls.cmd;


import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

public class GetEventsAllTest {

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
	}

	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}
	@Test
	public void selectAll(){
		GetEventsAll g = new GetEventsAll();
		//g.addParameter("loop", "loop");
		//g.run();
		g.addParameter("layout","table");
		g.addParameter("format","html");
		g.addParameter("output-file","/tmp/geteventsall.html");
		g.run();
	}
}

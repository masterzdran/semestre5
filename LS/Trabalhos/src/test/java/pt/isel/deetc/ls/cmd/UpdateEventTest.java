package pt.isel.deetc.ls.cmd;


import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

public class UpdateEventTest {

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
	public void UpdateEventTest(){
		/*
		 * Possible Options :
		 * - start - data de início do evento. end - data de fim do evento.
		 * - end - duração do evento (end e duration são exclusivos). 
		 * - summary- sumario da descrição do evento. 
		 *  - description - descrição do evento.
		 * - location - localização do evento.		
		 */
		UpdateEvent ue = new UpdateEvent();
		
		ue.addParameter("start","20101030");
		ue.addParameter("event-id","1");
		ue.addParameter("end","20101101");
		ue.addParameter("location","ISEL");
		ue.addParameter("summary","Teste de LS");
		ue.addParameter("description","Teste de LS");
		
		System.out.println("Debug Mode:");
		ue.run();
	}
}

package pt.isel.deetc.ls.model;

import org.junit.Test;


public class EventTest {
	@Test
	public void eventDateTest(){
		LSDate b = new LSDate();
		String duration = "P7W";
		LSDate l = new LSDate(b, duration);
		System.out.println("---> "+b);
		System.out.println("---> "+l);
		
	}

}

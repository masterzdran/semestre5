package pt.isel.deetc.ls.model;

import java.text.ParseException;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.ls.model.Date;

public class DateTest {
	
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
	public void tests() {
		// Construtor por omissao
		Date calDate1 = new Date();
		System.out.println("calDate1="+calDate1.toString());
		
		//Construtor com parametro
		Date calDate2;
		try {
			calDate2 = new Date("20101005060600","3");
			System.out.println("calDate2="+calDate2.toString());
		} catch (ParseException e) {
			System.out.println("Data inv�lida");
		}
	}
}

package pt.isel.deetc.ls.cmd;


import java.util.ArrayList;

import junit.framework.Assert;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.ls.exceptions.InvalidCommandParameterException;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.IRule;

public class ParameterTest {

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

	@Test(expected = InvalidCommandParameterException.class)
	public void parameterSettingAndTestingTest(){
		
		ArrayList<IRule> a1 = new ArrayList<IRule>();
		ArrayList<IRule> a2 = new ArrayList<IRule>();
		
		Parameter p1 = new Parameter("x", "description", a1);
		Parameter p2 = new Parameter("y", "description", a2);
		
		a1.add(ComponentRule.isRequired(p1));
		a1.add(ComponentRule.allowEmpty(p1));
		a1.add(ComponentRule.mutualExclusive(p1, p2));

		a2.add(ComponentRule.isOptional(p1));
		a2.add(ComponentRule.allowNoEmpty(p1));
		a2.add(ComponentRule.mutualExclusive(p1, p2));

		
		
		Assert.assertNotNull(a1);
		Assert.assertNotNull(a2);
		Assert.assertNotNull(p1);
		Assert.assertNotNull(p2);
		
		p1.setValue("teste1");

		p2.setValue("teste2");

		
		Assert.assertTrue(p1.getValue().equals("teste1"));
		Assert.assertTrue(p2.getValue().equals("teste2"));
	}
	
}


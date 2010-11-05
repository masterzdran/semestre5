package pt.isel.deetc.lmp.common.clp;


import java.util.Map;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Assert;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.ls.clp.CommandLineParser;

public class CommandLineParserTest {

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
	public void shouldReturnAnEmptyMapWhenCallingParseWithNullArguments() throws Exception {
		// Arrange
		CommandLineParser clp1 = new CommandLineParser();
		CommandLineParser clp2 = new CommandLineParser();
		
		
		// Act
		Map<String, String> map1 = clp1.parse((String[])null);
		Map<String, String> map2 = clp2.parse((String)null);
				
		// Assert
		Assert.assertTrue(map1.isEmpty());
		Assert.assertTrue(map2.isEmpty());
	}
	
	@Test
	public void defaultConstructedCommandLineParserShouldHaveTwoArgumentsWithValuesForACommandLineWithTwoArgumentsWithValues() throws Exception {
		// Arrange
		CommandLineParser clp = new CommandLineParser();
		
		
		// Act
		Map<String, String> map = clp.parse("-a valuea -b  valueb");
		String[] values = {"-a", " valuea ", " -b", " valueb"}; 
	    Map<String, String> map1 = clp.parse(values);
		
		// Assert
		Assert.assertTrue(map.size() == 2);
		Assert.assertEquals("valuea", map.get("a"));
		Assert.assertEquals("valueb", map.get("b"));
		
		Assert.assertTrue(map1.size() == 2);
		Assert.assertEquals("valuea", map1.get("a"));
		Assert.assertEquals("valueb", map1.get("b"));
	}
	
	@Test
	public void defaultConstructedCommandLineParserShouldHaveTwoArgumentsWithEmptyValuesForACommandLineWithTwoArgumentsWithNoValues() throws Exception {
		// Arrange
		CommandLineParser clp = new CommandLineParser();
				
		// Act
		Map<String, String> map = clp.parse(" -a  -b   ");
		String []values = {"-a ", "-b"}; 
	    Map<String, String> map1 = clp.parse(values);
		
		// Assert
		Assert.assertTrue(map.size() > 0);
		Assert.assertEquals("", map.get("a"));
		Assert.assertEquals("", map.get("b"));
		
		Assert.assertTrue(map1.size() > 0);
		Assert.assertEquals("", map1.get("a"));
	}
	
	@Test
	public void defaultConstructedCommandLineParserShouldHaveZeroArgumentsForACommandLineWithNoValidArguments() throws Exception {
		// Arrange
		CommandLineParser clp = new CommandLineParser();
				
		// Act
		Map<String, String> map = clp.parse("a valuea b  valueb");
		
		// Assert
		Assert.assertNull(map.get("b"));
	}
	
	@Test
	public void customConstructedCommandLineParserShouldHaveTwoArgumentsWithValuesForACommandLineWithTwoArgumentsWithValues() throws Exception {
		// Arrange
		CommandLineParser clp = new CommandLineParser("/", "::");
		
		// Act
		Map<String, String> map = clp.parse("/a ::  valuea /b ::  valueb");
		
		// Assert
		Assert.assertTrue(map.size() != 0);
		Assert.assertEquals("valuea", map.get("a"));
		Assert.assertEquals("valueb",map.get("b"));
	}
	
	@Test
	public void shouldReturnNullValuesForUnexistantArgument() throws Exception {
		// Arrange
		CommandLineParser clp = new CommandLineParser();
		
		// Act
		Map<String, String> map = clp.parse("-a valuea -b");
				
		// Assert
		Assert.assertNotNull(map.get("a"));
		Assert.assertNotNull(map.get("b"));
		Assert.assertNull(map.get("c"));
	}
	
	@Test
	public void shouldSupportMultiWordValues() throws Exception{
	    // Arrange
	    CommandLineParser clp = new CommandLineParser("/"," ");
	    
	    // Act
	    Map<String, String> map = clp.parse(" /a  multi word value  /b   another multi word value");
	    String []values = {" /a"," multi", " word", " value ", " /b", " another multi", " word ", "value "}; 
	    Map<String, String> map1 = clp.parse(values);
	    
	    // Assert
	    Assert.assertEquals("multi word value", map.get("a"));
	    Assert.assertEquals("another multi word value", map.get("b"));
	    
	    Assert.assertEquals("multi word value", map1.get("a"));
	    Assert.assertEquals("another multi word value", map1.get("b"));
	}
	
	@Test
	public void shouldSupportMultiCharPrefixesValues() throws Exception{
	    // Arrange
	    CommandLineParser clp = new CommandLineParser("--","::");
	    
	    // Act
	    Map<String, String> map = clp.parse(" --a  ::valuea --b   :: valueb");
	    
	    // Assert
	    Assert.assertEquals("valuea", map.get("a"));
	    Assert.assertEquals("valueb", map.get("b"));
	}
         /**
         * Bug N. 1
         * Se o array for vazio
         */
        @Test
	public void shouldReturnAnEmptyMapWhenCallingParseWithEmptyArguments() throws Exception {
		// Arrange
		CommandLineParser clp1 = new CommandLineParser();
		CommandLineParser clp2 = new CommandLineParser();


		// Act
                String[] arr1= {""};
                String[] arr2= {"","","",""};
		Map<String, String> map1 = clp1.parse(arr1);
		Map<String, String> map2 = clp2.parse(arr2);

		// Assert
		Assert.assertTrue(map1.isEmpty());
		Assert.assertTrue(map2.isEmpty());
	}
        /**
         * Bug N. 2
         * Se não houver opções válidas não retorna uma EmptyMap
         */
        @Test
	public void defaultConstructedCommandLineParserShouldHaveZeroOptionsForACommandLineWithNoValidOption() throws Exception {
		// Arrange
		CommandLineParser clp = new CommandLineParser();

		// Act
		Map<String, String> map = clp.parse("a valuea b  valueb");

		// Assert
		Assert.assertTrue(map.isEmpty());
	}


}

package pt.isel.deetc.lmp.ls;

import org.junit.Assert;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.lmp.ls.domainModel.Teacher;

public class TeachersAndUcsParserTest {
	static TeachersAndUcsParser _Parser = new TeachersAndUcsParser();
	
	@BeforeClass
	public static void beforeClass() {
	
	}
	
	@Test
	public void shouldBeAbleToParseAteacherLine() {
		// Arrange
		
		// Act
		Teacher t = _Parser.parseTeacherLine("1111|Carlos Manuel Mendes Guedes|d1111@isel.pt");
		
		// Assert
		Assert.assertNotNull(t);
		Assert.assertEquals(1111, t.getNumber());
		Assert.assertEquals("Carlos Manuel Mendes Guedes", t.getName());
		Assert.assertEquals("d1111@isel.pt", t.getEmail());
	}
	
	@Test
	public void shouldTrowInvalidFormatExceptionForInvlidTeacherLine() {
		// Arrange
				
		// Act
		try { 
			Teacher t = _Parser.parseTeacherLine("aaaaa|Carlos Manuel Mendes Guedes|d1111@isel.pt");
		} catch(IllegalArgumentException e ) {
			return;
		}
		Assert.fail();
		// Assert
		
	}
	
}














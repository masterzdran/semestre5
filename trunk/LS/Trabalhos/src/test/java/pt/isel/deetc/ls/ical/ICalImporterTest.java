package pt.isel.deetc.ls.ical;

import org.junit.Test;


public class ICalImporterTest {
	
	@Test
	public void startBuilder() {
		
		String file = "NunoCanceloExportTest2.ics";
		
		ICalImporter ical = new ICalImporter(file);
		
		ical.print(ical.iCalBuilder());
	}

}

/**
 * 
 */
package pt.isel.deetc.ls.cmd;


import org.junit.After;
import org.junit.AfterClass;
import org.junit.Assert;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.ls.model.Calendar;
import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.LSDate;

public class MoveEventTest {

    /**
     * @throws java.lang.Exception
     */
    @BeforeClass
    public static void setUpBeforeClass() throws Exception {
    }

    /**
     * @throws java.lang.Exception
     */
    @AfterClass
    public static void tearDownAfterClass() throws Exception {
    }

    /**
     * @throws java.lang.Exception
     */
    @Before
    public void setUp() throws Exception {
    }

    /**
     * @throws java.lang.Exception
     */
    @After
    public void tearDown() throws Exception {
    }

    @Test
    public void moveEventTest()
    {
	Event event = new Event("Source",new LSDate("20101010"),new LSDate("20101010"));
	Calendar destinationCalendar = new Calendar("Source");
	event.getCalName();
	
	MoveEvent mEvent = new MoveEvent();
	mEvent.addParameter("event-id",String.valueOf(event.getId()));
	mEvent.addParameter("destination-calendar-name",destinationCalendar.getName());
	
	Assert.assertEquals(event.getCalName(),destinationCalendar.getName());
    }
}

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
import pt.isel.deetc.ls.model.LSDate;
import pt.isel.deetc.ls.model.Todo;

public class MoveTodoTest {

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
    public void moveTodoTest()
    {
	Todo todo = new Todo("Source",new LSDate("20101010"),new LSDate("20101010"));
	Calendar destinationCalendar = new Calendar("Source");
	todo.getCalName();
	
	MoveTodo mTodo = new MoveTodo();
	mTodo.addParameter("todo-id",String.valueOf(todo.getId()));
	mTodo.addParameter("destination-calendar-name",destinationCalendar.getName());
	
	Assert.assertEquals(todo.getCalName(),destinationCalendar.getName());
    }
}

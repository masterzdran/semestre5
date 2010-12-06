/**
 * 
 */
package pt.isel.deetc.ls.database;


import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import pt.isel.deetc.ls.model.LSDate;
import pt.isel.deetc.ls.model.Todo;

public class TodoQueryTest {

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
    public void simpleQuery()
    {
	Todo td = new Todo("Teste", new LSDate("20101121"), new LSDate("20101122"));
	td.setDescription("Description Test");
	td.setSummary("Summary Test");
	td.setDonePercent(0.2);
	td.setPriority(3);
	

	System.out.println("----------------------------------------------------------------");
	System.out.println("Todo");
	System.out.println("----------------------------------------------------------------");
	System.out.println(td.toString());
	System.out.println("----------------------------------------------------------------");
	
	int id = td.getId();
	TodoQuery todo = new TodoQuery();
	
	System.out.println("----------------------------------------------------------------");
	System.out.println("Delete");
	System.out.println("----------------------------------------------------------------");
	
	todo.deleteComponentById(id);
	System.out.println(todo.getStatement());
	
	System.out.println("----------------------------------------------------------------");
	System.out.println("Update");
	System.out.println("----------------------------------------------------------------");
	
	todo.updateTodo().setSummary("teste de update").setDescription("teste de update").whereTodoIdIs(id);
	System.out.println(todo.getStatement());
	
	System.out.println("----------------------------------------------------------------");
	System.out.println("Insert");
	System.out.println("----------------------------------------------------------------");
	
	todo.insertTodo(
			id, 
			td.getBeginDate(), td.getEndDate(), 
			1, td.getDescription(), 
			td.getSummary(), 
			td.getState(), 
			td.getDonePercent(), 
			td.getPriority(), 1, 1,1);
	
	System.out.println("----------------------------------------------------------------");
	System.out.println("Select");
	System.out.println("----------------------------------------------------------------");
	
	todo.select().where().calendarNameIs(td.getCalName()).and().beginDateBetween(td.getBeginDate(), td.getEndDate());
	System.out.println(todo.getStatement());
    }

}

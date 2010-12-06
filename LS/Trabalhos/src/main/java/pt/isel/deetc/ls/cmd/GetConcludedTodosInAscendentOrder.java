/**
 * 
 */
package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.database.TodoQuery;
import pt.isel.deetc.ls.mapper.TodoMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.LSDate;
import pt.isel.deetc.ls.model.Todo;

public class GetConcludedTodosInAscendentOrder extends GetTodosAll {

    private static final String _NAME = "get-concluded-todos-in-ascendent-order";
    private static final String _DESCRIPTION = "Show the information of a set of Todo, in ascending order, between a period of time that are concluded";
	
	public GetConcludedTodosInAscendentOrder() {
		super(_NAME, _DESCRIPTION);
		Parameter p1 = new Parameter("start", "start date of the Todo");
		Parameter p2 = new Parameter("end", "end date of the Todo ('end' and 'duration' are both mutually exclusive)");
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowEmpty(p1));
		
		p2.addRule(ComponentRule.isOptional(p2));
		p2.addRule(ComponentRule.allowEmpty(p2));
		
		addParameter(p1);
		addParameter(p2);
	}

	@Override
	public void execute() {
		Todo todo= new Todo("none", new LSDate(getValue("start")), new LSDate(getValue("end")));
		TodoQuery tQuery = new TodoQuery();
				
		((TodoQuery) tQuery.select().
			where().
			beginDateBetween(todo.getBeginDate(), todo.getEndDate()).
			endDateBetween(todo.getBeginDate(), todo.getEndDate())).
			donePercentIs(1.0).inAscendingOrder("end_date");
		
		// TODO - Verify if the query meets all the criteria
		
		TodoMapper t = new TodoMapper();
				
		// Retrieve Todos with the custom select
		Iterable<Todo> collection = t.select(tQuery);
		report(collection);
	}
}

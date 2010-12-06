package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.TodoMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Todo;

public class DeleteTodo extends Command{
	private static final String _NAME = "delete-todo";
	private static final String _DESCRIPTION = "delete ONE Todo given his ID";

	public DeleteTodo() {
		super(_NAME, _DESCRIPTION);
		Parameter p1 = new Parameter("todo-id", "Todo identifier ");
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));
		addParameter(p1);
	}

	@Override
	public void execute() {
		Todo todo= new Todo();
		todo.setId(Integer.parseInt(getValue("todo-id")));
    	TodoMapper t = new TodoMapper();
    	if (t.delete(todo)> 0){
    		System.out.println("Event deleted.");
    	}else{
    		System.out.println("No record was deleted.");
    	}
 	}
}

package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.TodoMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.LSDate;
import pt.isel.deetc.ls.model.Todo;

public class GetTodo extends GetTodosAll {
	private static final String _NAME = "get-todo";
	private static final String _DESCRIPTION = "show the information of ONE Todo given his ID";
	public GetTodo() {
		super(_NAME, _DESCRIPTION);
		Parameter p1 = new Parameter("todo-id", "identificador do evento");
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));
		addParameter(p1);
	}

	@Override
	public void execute() {
		Todo todo= new Todo("none", new LSDate(), new LSDate());
		todo.setId(Integer.parseInt(getValue("todo-id")));
    	TodoMapper e = new TodoMapper();
    	Iterable<Todo> collection = e.selectByID(todo);
    	report(collection);
	}
}

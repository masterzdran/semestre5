package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.TodoMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.LSDate;
import pt.isel.deetc.ls.model.Todo;

public class GetTodosCal extends GetTodosAll {

    private static final String _NAME = "get-todos-cal";
    private static final String _DESCRIPTION = "show the information of ALL Todos of ONE Calendar";

    public GetTodosCal() {
        super(_NAME, _DESCRIPTION);
        Parameter p1  =new Parameter("cal-name", "name of Calendar where the Todo is");
		
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));
		
		addParameter(p1);
    }

    @Override
    public void execute() {
		Todo todo= new Todo(getValue("cal-name"), new LSDate(), new LSDate());
    	TodoMapper t = new TodoMapper();
    	Iterable<Todo> collection = t.selectByCal(todo);
    	report(collection);
    }

}

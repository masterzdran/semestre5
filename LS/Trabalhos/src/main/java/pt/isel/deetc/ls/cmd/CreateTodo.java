package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.mapper.TodoMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Todo;

public class CreateTodo extends Command {

	private static final String _NAME = "create-todo";
	private static final String _DESCRIPTION = "Create one new To-do, in return show his to-do id";

	public CreateTodo() {
		super(_NAME, _DESCRIPTION);
		Parameter p1=new Parameter("cal-name", "name of Calendar where the To-do will be created");
		Parameter p2=new Parameter("summary", "short description of the To-do");
		Parameter p3=new Parameter("description", "long description of the To-do");
		Parameter p4=new Parameter("location", "location of the To-do");
		Parameter p5=new Parameter("donepercent", "percentage of completion of the To-do"); 
		Parameter p6=new Parameter("priority", "priority of To-do");
		
		p1.addRule(ComponentRule.isRequired(p1));
		p1.addRule(ComponentRule.allowNoEmpty(p1));
	
		p2.addRule(ComponentRule.isOptional(p2));
		p2.addRule(ComponentRule.allowEmpty(p2));

		p3.addRule(ComponentRule.isOptional(p3));
		p3.addRule(ComponentRule.allowEmpty(p3));

		p4.addRule(ComponentRule.isOptional(p4));
		p4.addRule(ComponentRule.allowEmpty(p4));	
		
		p5.addRule(ComponentRule.isOptional(p5));
		p5.addRule(ComponentRule.allowEmpty(p5));
		
		p6.addRule(ComponentRule.isOptional(p6));
		p6.addRule(ComponentRule.allowEmpty(p6));
		
		/* Adding the parameters*/
		addParameter(p1);
		addParameter(p2);
		addParameter(p3);
		addParameter(p4);
		addParameter(p5);
		addParameter(p6);
	}
	@Override
	public void execute() {
		Todo todo = new Todo();
		//TODO: fill the todo instance
    	TodoMapper t = new TodoMapper();
    	t.insert(todo);		
	}
}

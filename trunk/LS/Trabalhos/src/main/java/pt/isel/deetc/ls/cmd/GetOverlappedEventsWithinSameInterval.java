/**
 * 
 */
package pt.isel.deetc.ls.cmd;

import pt.isel.deetc.ls.database.EventQuery;
import pt.isel.deetc.ls.mapper.EventMapper;
import pt.isel.deetc.ls.model.ComponentRule;
import pt.isel.deetc.ls.model.Event;
import pt.isel.deetc.ls.model.LSDate;

public class GetOverlappedEventsWithinSameInterval extends GetEventsAll {
    private static final String _NAME = "get-events-overlapped-within-same-interval";
    private static final String _DESCRIPTION = "Show the information of a set of Event between a period of time that are overlapped";
    
    /**
     * @param name
     * @param description
     */
    public GetOverlappedEventsWithinSameInterval() {
	super(_NAME, _DESCRIPTION);
	Parameter p1 = new Parameter("start", "start date of the Event",true);
	Parameter p2 = new Parameter("end", "end date of the Event ('end' and 'duration' are both mutually exclusive)");
	p1.addRule(ComponentRule.isRequired(p1));
	p1.addRule(ComponentRule.allowEmpty(p1));
	
	p2.addRule(ComponentRule.isOptional(p2));
	p2.addRule(ComponentRule.allowEmpty(p2));
	
	addParameter(p1);
	addParameter(p2);
    }

    @Override
    public void execute() {
	Event event= new Event("none", new LSDate(getValue("start")), new LSDate(getValue("end")));
	EventQuery eQuery = new EventQuery();
	// Build criteria query
	String statement = "select * from component " +
			"where " +
				"begin_date >= "+event.getBeginDate()
				+" and " +
				"end_date <= "+event.getEndDate()+" E1 " +
						"inner join ( select * from component " +
							"where " +
								"begin_date >= "+event.getBeginDate()
								+" and " +
								"end_date <= "+event.getEndDate()+") E2 " +
										"on E1.componentID != E2.componentID and (" +
											"E1.end_date >= E2.begin_date " +
											"or " +
											"E1.end_date >= E2.end_date);"; 
	
	// TODO - Verify if the query meets all the criteria
	
	eQuery.select(statement);
	EventMapper e = new EventMapper();
	
	// Retrieve Events with the custom select
       	Iterable<Event> events = e.select(eQuery);
       	report(events);
    }
}

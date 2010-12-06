    create view alarms
    as
        select 
                   a.id,
                   a.atrigger,
                   a.componentID,
                   a.anaction,
                   c.begin_date,
                   c.end_date,
                   c.componentTypeID,
                   e.description as event_description,
                   e.summary as event_summary,
                   e.location,
                    t.description as todo_description,
                   t.summary as todo_summary,
                   t.status,
                   t.donepercent,
                   t.priority
                
       from
                Alarm a, Component c, Event e, Todo t
       where
                a.componentID = e.componentID
                or
                a.componentID = t.componentID

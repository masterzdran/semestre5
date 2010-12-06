    create view events 
    as
        select 
                ca.id as calendar_id, 
                ca.name as calendar_name ,
                c.id as component_id, 
                c.begin_date, 
                c.end_date, 
                e.description,
                e.summary,
                e.location, 
                e.componentID 
        from 
                Event e, Component c, Calendar_Component cc, Calendar ca 
        where 
                e.componentID= c.id and c.id=cc.componentID and cc.calendarID=ca.id

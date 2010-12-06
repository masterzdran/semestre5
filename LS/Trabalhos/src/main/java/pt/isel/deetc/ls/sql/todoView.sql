    create view todos
    as
        select 
                ca.id as calendar_id, 
                ca.name as calendar_name ,
                c.id as component_id, 
                c.begin_date, 
                c.end_date, 
                t.description,
                t.summary,
                t.status,
                t.donepercent, 
                t.priority,
                t.componentID 
        from 
                Todo t, Component c, Calendar_Component cc, Calendar ca 
        where 
                t.componentID= c.id and c.id=cc.componentID and cc.calendarID=ca.id

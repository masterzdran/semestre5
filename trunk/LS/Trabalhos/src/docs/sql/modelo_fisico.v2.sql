create procedure init_database 
as
    -------------------------------------------- Create Tables ------------------------------------------------
    -- Table Calendar
    create table Calendar (
        id int not null,
        name char(50) not null unique,
    );
    -- Table Category
    create table Category (
        id int not null,
        name char(255) not null unique
    );
    -- Table ComponentType
    create table ComponentType (
        id int not null,
        name char(255) not null unique,
        description char(255)
    );
    -- Table Component
    create table Component (
        id int not null,
        begin_date datetime default null,
        end_date datetime default null,
        componentTypeID int not null
    );
    -- Table Event
    create table Event (
        description char(255),
        summary char(255),
        location char(255),
        componentID int not null
    );
    -- Table Todo
    create table Todo (
        description char(255),
        summary char(255),
        status smallint default 0 check (status <= 2),
        donepercent real default 0,
        priority smallint default 0,
        componentID int not null
    );
    -- Table Calendar_Component 
    create table Calendar_Component (
        calendarID int not null,
        componentID int not null
    );
    -- Table Component_Category 
    create table Component_Category (
        categoryID int not null,
        componentID int not null
    ); 
    -- Table Alarm 
    create table Alarm (
        id int not null,
        atrigger datetime default null,
        componentID int not null,
        anaction char(255)
    );
    
    -------------------------------------------- Add Constraints ------------------------------------------------
    -- Table Calendar
    alter table Calendar add constraint pk_Calendar primary key (id); 
    -- Table Category
    alter table Category add constraint pk_Category primary key (id);
    -- Table ComponentType
    alter table ComponentType add constraint pk_ComponentType primary key (id);
    -- Table Component
    alter table Component add constraint pk_Component primary key (id);
    alter table Component add constraint fk_Component foreign key (componentTypeID) references ComponentType(id); 
    -- Table Event
    alter table Event add constraint fk_Event foreign key (componentID) references Component(id);
    -- Table Todo
    alter table Todo add constraint fk_Todo foreign key (componentID) references Component(id);
    -- Table Calendar_Component
    alter table Calendar_Component add constraint fk_Calendar_Component1 foreign key (calendarID) references Calendar (id);
    alter table Calendar_Component add constraint fk_Calendar_Component2 foreign key (componentID) references Component (id);
    -- Table Component_Category
    alter table Component_Category add 	constraint fk_Component_Category1 foreign key (categoryID) references Category (id);
    alter table Component_Category add	constraint fk_Component_Category2 foreign key (componentID) references Component (id);
    -- Table Alarm
    alter table Alarm add constraint pk_Alarm primary key (id);
    alter table Alarm add constraint fk_Alarm1 foreign key (componentID) references Component (id);
    -------------------------------------------- Load Data ------------------------------------------------
    -- Preenchimento da Tabela ComponentType com os tipos de componentes válidos
    insert into ComponentType (id,name,description) values (1,'Event', 'Event description');
    insert into ComponentType (id,name,description) values (2,'Todo',  'Todo description');
    -- Preenchimento da Tabela Category com os tipos de categorias válidos
    insert into Category (id, name) values (1,'Default');
    -------------------------------------------- Views -----------------------------------------
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
    go

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
    go

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
       go
                   
go

create procedure clear_database
as
    -------------------------------------------- Drop Constraints ------------------------------------------------
    -- Table Event
    alter table Event drop constraint fk_Event;
    -- Table Todo
    alter table Todo drop constraint fk_Todo;
    -- Table Alarm
    alter table Alarm drop constraint fk_Alarm1;
    -- Table Calendar_Component
    alter table Calendar_Component drop constraint fk_Calendar_Component1;
    alter table Calendar_Component drop constraint fk_Calendar_Component2;
    -- Table Component_Category
    alter table Component_Category drop constraint fk_Component_Category1;
    alter table Component_Category drop	constraint fk_Component_Category2;
    -- Table Component
    alter table Component drop constraint pk_Component;
    alter table Component drop constraint fk_Component;
    -- Table ComponentType
    alter table ComponentType drop constraint pk_ComponentType;	
    -- Table Category
    alter table Category drop constraint pk_Category;
    -- Table Calendar
    alter table Calendar drop constraint pk_Calendar; 
    -------------------------------------------- Drop Tables ------------------------------------------------
    -- Table Calendar_Component
    if object_id('Calendar_Component') is not null drop table Calendar_Component;
    -- Table Component_Category 
    if object_id('Component_Category') is not null drop table Component_Category;
    -- Table Category
    if object_id('Category') is not null drop table Category;
    -- Table Calendar
    if object_id('Calendar') is not null drop table Calendar;
    -- Table Alarm
    if object_id('Alarm') is not null drop table Alarm; 
   -- Table Component
    if object_id('Component') is not null drop table Component;
    -- Table ComponentType
    if object_id('ComponentType') is not null drop table ComponentType
    -- Table Event 
    if object_id('Event') is not null drop table Event;
    -- Table Todo
    if object_id('Todo') is not null drop table Todo;
 go

-------------------------------------------- Init / Clear Database -----------------------------------------
execute init_database;
execute clear_database;

drop procedure init_database;
drop procedure clear_database;

drop view events;
drop view todos;
drop view alarms;
-------------------------------------------- Miscellaneous ------------------------------------------------
-- Create Calendar
insert into Calendar (id, name) values (1,'ISEL');
-- Create Event
insert into Component (id,begin_date,end_date, componentTypeID) values( 1, getDate(), getDate(), 1);
insert into Event (description, summary, location, componentID) values ( 'aula', 'pratica', 'isel', 1 );
insert into Component_Category (componentID, categoryID) values ( 1, 1);
insert into Calendar_Component (calendarID,componentID) values(1,1);
-- Get Event
select ca.id, ca.name,c.id, c.begin_date, c.end_date,e.description,e.summary,e.location, e.componentID from Event e, Component c,
	Calendar_Component cc, Calendar ca where e.componentID= c.id and c.id=cc.componentID and cc.calendarID=1
-- Create Event Generic Query
insert into Component (id,begin_date,end_date, componentTypeID) values( ?, ?, ?, 1)
insert into Event (description, summary, location, componentID) values ( ?, ?, ?, ? )
insert into Component_Category (componentID, categoryID) values ( ?, 1)
insert into Calendar (id, name) values (?,?)
insert into Calendar_Component (calendarID,componentID) values(?,?)
insert into Alarm (id,componentID) values (1,1);
-- Others
select ca.id, ca.name,c.id, c.begin_date, c.end_date,e.description,e.summary,e.location, e.componentID from Event e, Component c,
	Calendar_Component cc, Calendar ca where e.componentID= c.id and c.id=cc.componentID and cc.calendarID=ca.id

select * from Calendar;
select * from Component;
select * from Todo;
select * from events;
select * from todos;
select * from alarms;

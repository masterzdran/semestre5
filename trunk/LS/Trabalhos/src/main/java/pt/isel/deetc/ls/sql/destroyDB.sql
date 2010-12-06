    -------------------------------------------- Drop Views ------------------------------------------------
    if object_id('events') is not null drop view events;
    if object_id('todos') is not null drop view todos;
    if object_id('alarms') is not null drop view alarms;
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

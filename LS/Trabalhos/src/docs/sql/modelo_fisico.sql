-- --------------------------------------------------------------------------------
-- create database (if not exists)
if db_id('CalendarManager') is null
    create database CalendarManager;
go

-- use database
use CalendarManager	;
-- --------------------------------------------------------------------------------
go
-- Clear Data Model

-- Table Calendar_Component
if object_id('Calendar_Component') is not null
	drop table Calendar_Component;
	
-- Table Component_Category
if object_id('Component_Category') is not null
	drop table Component_Category;


-- Table Category
if object_id('Category') is not null
	drop table Category;
		
;

-- Table Calendar
use CalendarManager;
if object_id('Calendar') is not null
begin
	if object_id('Calendar_Component') is not null
	begin
		alter table Calendar_Component
		drop constraint fk_Calendar_Component1
	end
	drop table Calendar;
end
	
-- Table Component
if object_id('Component') is not null
begin
	if object_id('Event') is not null
	begin
		alter table Event
		drop constraint fk_Event
	end
	if object_id('Calendar_Component') is not null
	begin
		alter table Calendar_Component
		drop constraint fk_Calendar_Component2
	end
	drop table Component;
end
-- Table ComponentType
if object_id('ComponentType') is not null
	drop table ComponentType

-- Table Event
if object_id('Event') is not null
	drop table Event;

-- Table Todo
if object_id('Todo') is not null
	drop table Todo;

-- --------------------------------------------------------------------------------

-- Create Model
go 

-- Table Calendar

create table Calendar (
	id int not null,
	name char(50) not null unique,
	constraint pk_Calendar primary key (id) 
);
-- Table Category
create table Category (
	id int not null,
	name char(255) not null unique,
	constraint pk_Category primary key (id)
);

-- Table ComponentType

create table ComponentType (
	id int not null,
	name char(255) not null unique,
	description char(255),
	constraint pk_ComponentType primary key (id)
);

-- Table Component

create table Component (
	id int not null,
	begin_date datetime not null,
	end_date datetime not null,
	componentTypeID int not null,
	constraint pk_Component primary key (id),
	constraint fk_Component foreign key (componentTypeID) references ComponentType(id) 
);

-- Table Event

create table Event (
	description char(255),
	summary char(255),
	location char(255),
	componentID int not null,
	constraint fk_Event foreign key (componentID) references Component(id)
);

-- Table Todo
create table Todo (
	description char(255),
	summary char(255),
	status smallint default 0 check (status <= 2),
	donepercent real default 0,
	priority smallint default 0,
	componentID int not null,
	constraint fk_Todo foreign key (componentID) references Component(id)
);

-- Table Calendar_Component 

create table Calendar_Component (
	calendarID int not null,
	componentID int not null,
	constraint fk_Calendar_Component1 foreign key (calendarID) references Calendar (id),
	constraint fk_Calendar_Component2 foreign key (componentID) references Component (id)  
);


-- Table Component_Category 

create table Component_Category (
	categoryID int not null,
	componentID int not null,
	constraint fk_Component_Category1 foreign key (categoryID) references Category (id),
	constraint fk_Component_Category2 foreign key (componentID) references Component (id)	
);
go
-- --------------------------------------------------------------------------------

-- Load Data
-- Preenchimento da Tabela ComponentType com os tipos de componentes válidos
insert into ComponentType (id,name,description) values (1,'Event', 'Event description');
insert into ComponentType (id,name,description) values (2,'Todo',  'Todo description');
-- Preenchimento da Tabela Category com os tipos de categorias válidos
insert into Category (id, name) values (1,'Default');

-- --------------------------------------------------------------------------------
-- Create Event
insert into Component (id,begin_date,end_date, componentTypeID) values( ?, ?, ?, 1)
insert into Event (description, summary, location, componentID) values ( ?, ?, ?, ? )
insert into Component_Category (componentID, categoryID) values ( ?, 1)
insert into Calendar (id, name) values (?,?)
insert into Calendar_Component (calendarID,componentID) values(?,?)

-- Get Event
select ca.id, ca.name,c.id, c.begin_date, c.end_date,e.description,e.summary,e.location, e.componentID from Event e, Component c,
	Calendar_Component cc, Calendar ca where e.componentID= c.id and c.id=cc.componentID and cc.calendarID=?
go

-- Create Event Data
insert into Component (id,begin_date,end_date, componentTypeID) values( 1, getDate(), getDate(), 1)
insert into Event (description, summary, location, componentID) values ( 'aula', 'pratica', 'isel', 1 )
insert into Component_Category (componentID, categoryID) values ( 1, 1)

insert into Calendar (id, name) values (1,'ISEL')
insert into Calendar_Component (calendarID,componentID) values(1,1)

select ca.id, ca.name,c.id, c.begin_date, c.end_date,e.description,e.summary,e.location, e.componentID from Event e, Component c,
	Calendar_Component cc, Calendar ca where e.componentID= c.id and c.id=cc.componentID and cc.calendarID=ca.id
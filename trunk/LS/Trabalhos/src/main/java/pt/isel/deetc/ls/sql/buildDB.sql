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

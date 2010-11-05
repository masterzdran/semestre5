package pt.isel.deetc.ls.model;

import java.util.ArrayList;

import pt.isel.deetc.ls.utils.Utils;

public class Calendar {

    private static final String DEFAULT_CALENDAR_NAME = "Empty Name";
    private String _name;
    private int _id;
    private ArrayList<Component> _component;

    public Calendar() {
        this(DEFAULT_CALENDAR_NAME);
    }
    public Calendar(String name){
    	this(name,Utils.getUniqueID());
    }
    
    public Calendar(String name, int id) {
        _name = name;
        _id = id;
        _component = new ArrayList<Component>();
    }

    public boolean addComponent(Component component) {
        return _component.add(component);
    }

    public boolean removeComponet(Component component) {
        return _component.remove(component);
    }

    public ArrayList<Component> getComponent() {
        return _component;
    }

    public int getID(){
    	return _id;
    }
    public String getName() {
        return _name;
    }

    public void setName(String name) {
        this._name = name;
    }
}

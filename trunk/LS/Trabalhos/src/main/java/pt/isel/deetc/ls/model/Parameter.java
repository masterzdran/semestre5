/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package pt.isel.deetc.ls.model;

/**
 *
 * @author nac
 */
public class Parameter {
    private String _name;
    private String _value;

    public Parameter(String name, String value) {
        this._name = name;
        this._value = value;
    }

    public String getName() {
        return _name;
    }

    public void setName(String name) {
        this._name = name;
    }

    public String getValue() {
        return _value;
    }

    public void setValue(String value) {
        this._value = value;
    }


}

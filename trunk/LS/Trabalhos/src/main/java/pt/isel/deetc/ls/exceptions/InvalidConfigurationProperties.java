/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package pt.isel.deetc.ls.exceptions;

/**
 *
 * @author nac
 */
public class InvalidConfigurationProperties extends Exception{
    /**
	 * 
	 */
	private static final long serialVersionUID = -8312166125529239428L;
	String _msg;

    public InvalidConfigurationProperties() {
        this("Invalid properties configuration file.");
    }
    public InvalidConfigurationProperties(String msg) {
        _msg=msg;
    }

    @Override
    public String getMessage(){
        return _msg;
    }
}

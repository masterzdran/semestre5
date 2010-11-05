/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package pt.isel.deetc.ls.exceptions;
public class InvalidCommandParameterException extends RuntimeException{
    /**
	 * 
	 */
	private static final long serialVersionUID = -906221264540873272L;
	String _msg;

    public InvalidCommandParameterException() {
        this("Invalid Command Parameter.");
    }
    public InvalidCommandParameterException(String msg) {
        _msg=msg;
    }

    @Override
    public String getMessage(){
        return _msg;
    }
}

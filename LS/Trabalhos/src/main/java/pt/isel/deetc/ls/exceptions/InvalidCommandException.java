/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package pt.isel.deetc.ls.exceptions;

/**
 *
 * @author nac
 */
public class InvalidCommandException extends Exception{
    /**
	 * 
	 */
	private static final long serialVersionUID = -4514329034515766865L;
	String _msg;

    public InvalidCommandException() {
        this("Invalid Command name.");
    }
    public InvalidCommandException(String msg) {
        _msg="Invalid Command name. "+msg;
    }

    @Override
    public String getMessage(){
        return _msg;
    }
}

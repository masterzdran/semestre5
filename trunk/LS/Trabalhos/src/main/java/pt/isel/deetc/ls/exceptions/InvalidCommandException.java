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
    String _msg;

    public InvalidCommandException() {
        this("Invalid Command Parameter.");
    }
    public InvalidCommandException(String msg) {
        _msg=msg;
    }

    @Override
    public String getMessage(){
        return _msg;
    }
}

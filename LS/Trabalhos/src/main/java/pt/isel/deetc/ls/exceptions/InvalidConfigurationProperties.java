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

package pt.isel.deetc.ls.exceptions;

public class RequiredCommandParameterException extends RuntimeException {
    /**
	 * 
	 */
	private static final long serialVersionUID = -3612339576856573488L;
	String _msg;

    public RequiredCommandParameterException() {
        this("Required Command Paramenter not found.");
    }
    public RequiredCommandParameterException(String msg) {
        _msg=msg;
    }

    @Override
    public String getMessage(){
        return _msg;
    }

}

/*
 * 
 * 31401 - Nuno Cancelo 
 * 31900 - José Guilherme
 * 33595 - Nuno Sousa
 * 
 */
public final class LicConstants {
	/*Input Port*/
	public static final int RxRDY_MASK 			= 0x80;				
	public static final int KEY_VAL_MASK 		= 0x40;
	public static final int KEY_LOCK_MASK		= 0x10; 
	public static final int KEY_DAT_MASK 		= 0x0F;
	
	/*OutPut Port*/
	public static final int ACK_MASK			= 0x10;
	public static final int DOOR_MASK			= 0x20;
	public static final int RxC_MASK 			= 0x02;
	public static final int RxD_MASK 			= 0x01;

	/*AccessControl*/
	public static final String ASK4USER			="Insert Number   ";
	public static final String ASK4PIN			="Insert PIN ---";
	public static final String ASK4NEWPIN		="New PIN ---";
	public static final String CONFIRMNEWPIN	="Confirm PIN ---";
	public static final String OK_MESSAGE		="OK";
	public static final String ERROR_PIN_MESSAGE	="Invalid PIN";
	public static final String[] SALUTATION		={"Good Morning","Good Afternoon","Good Evening"};
	public static final String DOOROPEN			="Door is Open!";
	public static final String CLOSEDOOR		="System Locked!";
	public static final String INVALIDUSER		="Invalid User!";
	public static final String TIMEOUT			="Timeout!";
	public static final String INVALID_KEY		="Pin Mismatch!";
	public static final String MAINTENANCE_MESSAGE="Out off Service";
	public static final int PINPOS				=11;
	public static final int MAXDIGIT			=3;
	public static final int IDNBR				=3;
	public static final int CHECKUSER			=0;
	public static final int CHECKPIN			=1;
	public static final int CHECKNEWPIN			=2;
	public static final int CONFIRMPIN			=3;
	public static final String ERROR_USER_MESSAGE="Invalid User ID";


	/* KitProtocol */
	public static final int CLOCK_MASK 			= 1;
	public static final int HALFCLOCK_MASK 		= CLOCK_MASK / 2;
	public static final int SHIFT_BITS_MASK 	= 1;
	
	
	
	
	/* Keyboard*/
	public static final char[] KEYS 			={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	public static final long WAIT				=200;

	/* LCD */
	public static final int RS_MASK				=	0x40;	    //PIN 4
	public static final int ENABLE_MASK			=	0x80;	    //PIN 8
	public static final int DATA_MASK			=	0x0F;	    //PIN 11-14, DB4-7
	public static final int NIBBLE_SHIFT_MASK	=	4;		    //N. Bits a serem deslocados
	/* ****************** Mascaras Controlo****************** */
	public static final int CLEAR_MASK			=	0x01;		//Clear do Display
	public static final int ENTRY_SET_MASK		=	0x06;		//Clear do Display
	public static final int RETURN_HOME_MASK	=	0x02;		//Set Position 0 on AC(address Counter)
	public static final int CURSOR_ON_MASK  	=	0x0A;		//Cursor Activo
	public static final int CURSOR_OFF_MASK		=	0x0B;		//Cursor InActivo
	public static final int DISPLAY_ON_MASK  	=	0x0C;		//Display Activo
	public static final int DISPLAY_OFF_MASK	=	0x08;		//Display InActivo

	public static final int BLINK_ON_MASK		=	0x09;		//Blink Activo
	public static final int BLINK_OFF_MASK		=	0x08;		//Blink InActivo
	public static final int SHIFT_MASK			=	0x04;		//Move Cursor e Shifta Conteudo (2 nibbles)
	public static final int ADDR_COUNTER_MASK	=	0x80;		//Move Cursor para a Posição
	public static final int DISPLAY_SIZE_MASK	=	16;			//Tamanho do Display
	public static final int VALUE_MASK			=	0x0F;		//Mascara para os Valores a serem escritos

	public static final int MAXTIMERISE			=	350; 	// in miliseconds
	public static final int MAXTIMEFALL			=	400; 	// in miliseconds
	
	/* KIT */
	public static final int SLEEP				=1;
	public static final int STARTMASK			=0xFF;
	public static final int EIGHTBITS			=0xFF;
	/*Maintenance*/
	public static final String configFile		="user.netrc";

	
	/*Main*/
	public static final int MAINSLEEP			= 100;
	/*DB*/
	public static final String FILEPATH 		= "users.txt";
}

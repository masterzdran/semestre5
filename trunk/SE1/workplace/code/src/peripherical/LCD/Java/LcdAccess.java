/*
 * 
 * 31401 - Nuno Cancelo 
 * 31900 - José Guilherme
 * 33595 - Nuno Sousa
 * 
 */

import isel.leic.utils.Time;


public class LcdAccess {
	/*
	 * Os pinos do LCD devem ficar ligados da seguinte forma: Pinos 1, 3 e 5 –
	 * GND (alimentação, R/W e controlo de brilho) Pino 2 – Vcc (alimentação)
	 * Pinos 4 e 6 – bits D6 e D7 do output port do Kit (CS e Enable) Pinos
	 * 11..14 – bits D0..D3 do output port do Kit (Dados)
	 * 
	 * O programa de teste deve começar por escrever “ISEL” centrado na primeira
	 * linha do LCD e “LIC 2009” centrado na segunda. Por cada transição
	 * ascendente detectada em I0 do input port é trocado o texto entre as duas
	 * linhas. Quando a entrada I7 do input port for colocada a GND, o programa
	 * pára escrevendo na primeira linha “transitions=” alinhado à esquerda
	 * seguido do número de transições detectadas em I0. Na segunda linha
	 * aparecerá “Bye” alinhado à esquerda e o cursor na forma de bloco a piscar
	 * deve ficar a seguir ao “Bye”.
	 * --------------------------------------------
	 * ------------------------------------------ RS -> Input -> (DnC) 0 -
	 * Instruction register (for write) Busy flag:address counter (for read) 1 -
	 * Data register (for write and read) R/!W -> Input -> Selects read or
	 * write. 0: Write 1: Read E -> Input -> Starts data read/write DB4 to DB7
	 * -> Input/Output -> Four high order bidirectional tristate data bus pins.
	 * Used for data transfer and receive between the MPU and the HD44780U. DB7
	 * can be used as a busy flag. DB0 to DB3 -> Input/Output -> Four low order
	 * bidirectional tristate data bus pins. Used for data transfer and receive
	 * between the MPU and the HD44780U. These pins are not used during 4-bit
	 * operation.
	 * 
	 * 
	 * 
	 * 
	 * --------------------------------------------------------------------------
	 * ------------ Busy Flag (BF) When the busy flag is 1, the HD44780U is in
	 * the internal operation mode, and the next instruction will not be
	 * accepted. When RS = 0 and R/W = 1 (Table 1), the busy flag is output to
	 * DB7. The next instruction must be written after ensuring that the busy
	 * flag is 0.
	 * 
	 * Address Counter (AC) The address counter (AC) assigns addresses to both
	 * DDRAM and CGRAM. When an address of an instruction is written into the
	 * IR, the address information is sent from the IR to the AC. Selection of
	 * either DDRAM or CGRAM is also determined concurrently by the instruction.
	 * After writing into (reading from) DDRAM or CGRAM, the AC is automatically
	 * incremented by 1 (decremented by 1). The AC contents are then output to
	 * DB0 to DB6 when RS = 0 and R/W = 1 (Table 1).
	 * 
	 * Register Selection RS R/W Operation 0 0 IR write as an internal operation
	 * (display clear, etc.) 0 1 Read busy flag (DB7) and address counter (DB0
	 * to DB6) 1 0 DR write as an internal operation (DR to DDRAM or CGRAM) 1 1
	 * DR read as an internal operation (DDRAM or CGRAM to DR)
	 */

	/* Controlo */
	private static boolean isCentered = false;
	private static boolean isVisible = false;
	private static boolean isBlinking = false;
	private static boolean needRS = false;
	private static int cursorPosition = 0;

	/* ********************************************** */
	/**
	 * Activa o modo de entrada de dados
	 */
	public static void entryModeSet() {
		needRS = false;
		procValue(LicConstants.ENTRY_SET_MASK);
	}
	/**
	 * Activa o mostrador
	 */
	public static void displayControlOn() {
		needRS = false;
		procValue(LicConstants.DISPLAY_ON_MASK | LicConstants.CURSOR_ON_MASK);
	}
	/**
	 * Desactiva o mostrador
	 */
	public static void displayControlOff() {
		needRS = false;
		procValue(LicConstants.DISPLAY_OFF_MASK);
	}
	/**
	 * Desactiva o Blik
	 */
	public static void blinkOff() {
		needRS = false;
		procValue(LicConstants.DISPLAY_ON_MASK | LicConstants.BLINK_OFF_MASK);
	}

	/**
	 * Realiza a sequencia de inicialização para comunicação a 4 bits
	 * */
	public static void init() {
		int intValue3 = 0x03;
		int intValue2 = 0x02;
		int intValue8 = 0x08;
		int intValue28 = 0x28;
		int intValue1 = 0x01;
		int intValue7 = 0x07;

		needRS = false;

		sleep(20);
		writeBits(intValue3);
		sleep(5);
		writeBits(intValue3);
		sleep(1);
		writeBits(intValue3);
		writeBits(intValue2);
		procValue(intValue28);
		procValue(intValue8);
		procValue(intValue1);
		procValue(intValue7);

		entryModeSet();
		displayControlOn();
	}
	private static void sleep(int i){
		Time.sleep(i);
	}
	/**
	 * Apaga todos os acaracteres do display
	 * */
	public static void clear() {
		needRS = false;
		procValue(LicConstants.CLEAR_MASK);
	}

	/**
	 * 
	 * @param line
	 */
	public static void clearLine(int line) {
		posCursor(line, 0);
		for (int i = 0; i < 40; i++)
			write(' ');
		posCursor(line, 0);
	}

	/**
	 * 
	 * @param line
	 * @param col
	 *            Posiciona o cursor na linha (0..1) e coluna (0..15) indicadas
	 */
	public static void posCursor(int line, int col) {
		needRS = false;
		procValue(LicConstants.ADDR_COUNTER_MASK | (0x40 * line + col));
	}

	/**
	 * 
	 * @param visible
	 * @param blinking
	 *            Acerta o tipo de cursor: Visivel ou invisivel; A piscar ou
	 *            constante
	 * 
	 *            Cursor/Blink Control Circuit The cursor/blink control circuit
	 *            generates the cursor or character blinking. The cursor or the
	 *            blinking will appear with the digit located at the display
	 *            data RAM (DDRAM) address set in the address counter (AC).
	 */
	public static void setCursor(boolean visible, boolean blinking) {
		needRS = false;
		write((char) (visible ? LicConstants.CURSOR_ON_MASK
				| (blinking ? LicConstants.BLINK_ON_MASK : LicConstants.BLINK_OFF_MASK)
				: (LicConstants.CURSOR_OFF_MASK | (blinking ? LicConstants.BLINK_ON_MASK : LicConstants.BLINK_OFF_MASK))));
	}

	/**
	 * 
	 * @param c
	 *            Escreve o caracter indicado no local do cursor e o cursor
	 *            avança para a proxima coluna
	 */
	public static void write(char c) {
		needRS = true;
		procValue(c);
	}

	/**
	 * 
	 * @param txt
	 *            Escreve o texto indicado no local do cursor e o cursor avança
	 *            para a coluna seguinte
	 */

	public static void write(String txt) {
		for (int i = 0; i < txt.length(); i++) {
			write(txt.charAt(i));
		}
	}

	/**
	 * 
	 * @param line
	 * @param txt
	 *            Escreve o texto indicado na linha indicada (0 ou 1). O resto
	 *            da linha é texto fica centrado ou alinhado à
	 *            esquerda,dependendo da última chamada a SetCenter()
	 */
	public static void writeLine(int line, String txt) {
		posCursor(line, (isCentered) ? (LicConstants.DISPLAY_SIZE_MASK - txt.length()) / 2
				: 0);
		write(txt);
	}

	/**
	 * 
	 * @param value
	 *            Indica se o texto escrito com writeLine() nas chamadas
	 *            seguintes deve ou não ficar centrado na linha
	 */
	public static void setCenter(boolean value) {
		isCentered = value;
	}

	/**
	 * 
	 * @param s
	 * @param b
	 * @return Recebe uma string e o numero de caracteres a recuar e calcula
	 *         onde vai escrever. Método utilizado para os pedidos do PIN.
	 *         x=Total de Caracteres do LCD (16) y=Total de Caracteres da String
	 *         se centrado pos=(x - y)/2 + (y - b) = (x - y + 2y - 2b)/2 = (x +
	 *         y -2b)/2 se não centrado pos= y - b
	 */
	public static int getPos(String s, int b) {
		int x = LicConstants.DISPLAY_SIZE_MASK;
		int y = s.length();
		return (isCentered) ? (x + y - 2 * b) / 2 : (y - 3);
	}

	/**
	 * 
	 * @param value
	 *            Processa o valor para ser enviado.
	 */
	private static void procValue(int value) {
		writeBits(value >> LicConstants.NIBBLE_SHIFT_MASK);
		writeBits(value);
	}

	/**
	 * 
	 * @param value
	 *            Escreve o valor passado, seguindo o protocolo.
	 */
	private static void writeBits(int value) {
		LcdProtocol.sendBits(needRS ? 1 : 0, value);
	}

	public static void main(String args[]) {
		LcdAccess l = new LcdAccess();
		LcdAccess.writeLine(0, "Teste");
	}

}

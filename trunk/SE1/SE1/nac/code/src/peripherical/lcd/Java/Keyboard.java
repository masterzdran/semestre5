/*
 * 
 * 31401 - Nuno Cancelo 
 * 31900 - José Guilherme
 * 33595 - Nuno Sousa
 * 
 */
public class Keyboard {
	private static char keyPressed = 0;
	private static int time = 1;
	/**
	 * Limpa o Fifo
	 */
	public static void resetFifo() {
		while (Kit.readBit((LicConstants.KEY_VAL_MASK))) {
			ACK();
		}
	}

	/**
	 * // Se uma tecla está premida retorna a tecla: '0'..'9','A'..'F' //
	 * Retorna o valor 0 (zero) se nenhuma tecla está premida.
	 * 
	 * @return
	 */
	public static char pressedKey() {
		setACK();
		Kit.sleep(1);
		if (Kit.readBit((LicConstants.KEY_VAL_MASK))) {
			char key = LicConstants.KEYS[Kit.getBits(LicConstants.KEY_DAT_MASK)];
			ACK();
			return key;
		}

		keyPressed = 0;
		return 0;
	}

	/**
	 * // Se uma tecla foi premida retorna a tecla: '0'..'9','A'..'F' // Retorna
	 * o valor 0 (zero) se nenhuma tecla foi premida. // Retorna o valor 0
	 * (zero) se a tecla premida já foi retornada.
	 * 
	 * @return
	 */
	public static char getKey() {
		char key;
		if (((key = pressedKey()) != 0 )){//&&( key != keyPressed)) {
			keyPressed = key;
			return key;
		}
		return 0;
	}

	/**
	 * // Se uma tecla foi premida retorna a tecla: '0'..'9','A'..'F' // Se
	 * nenhuma tecla foi premida espera durante o tempo indicado // em
	 * milisegundos que seja premida uma tecla. // Retorna o valor 0 (zero) se
	 * não for premida uma tecla durante // o tempo indicado.
	 * 
	 * @param timeout
	 * @return
	 */
	public static char waitKey(long timeout) {
		char k;
		long elapsed = 0;
		long towait = (LicConstants.WAIT > timeout) ? timeout
				: LicConstants.WAIT;
		while (((k = getKey()) == 0) && (elapsed < timeout)) {
			elapsed += towait;
			Kit.sleep(towait);
		}
		return k;
	}
	/**
	 * Retorna acknowledge ao Fifo
	 */
	public static void setACK() {
		Kit.setBits(LicConstants.ACK_MASK);
	}
	/**
	 * Retorna que não tem acknowledge ao Fifo
	 */
	public static void unsetACK() {
		Kit.resetBits(LicConstants.ACK_MASK);
	}

	public static void ACK() {
		unsetACK();
		Kit.sleep(time);
		setACK();
	}

	public static void main(String[] args) {
		resetFifo();
		//setACK();
		while (true) {
			System.out.println(waitKey(2500));
			Kit.sleep(100);
		}
	}

}

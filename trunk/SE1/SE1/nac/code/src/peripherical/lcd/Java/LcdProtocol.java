/*
 * 
 * 31401 - Nuno Cancelo 
 * 31900 - José Guilherme
 * 33595 - Nuno Sousa
 * 
 */

public class LcdProtocol {
	private static final int bits2Shift = 4;

	/**
	 * Cria a sequencia de inicio do Protocolo
	 */
	private static void initProtocol() {
		Kit.setBits(LicConstants.RxC_MASK | LicConstants.RxD_MASK);
		fullDelay();
	}

	/**
	 * Cria sequencia de Start.
	 */
	private static void setStart() {
		Kit.invertBits(LicConstants.RxD_MASK);
		delay();
	}

	/**
	 * Verifica se o Kit está pronto a envia a sequencia de Dados.
	 * 
	 * @return
	 */
	private static boolean isReady() {
		return Kit.readBit(LicConstants.RxRDY_MASK);
	}

	/**
	 * Faz reset à sequencia de dados.
	 */
	private static void resetProtocol() {
		Kit.resetBits(LicConstants.RxC_MASK | LicConstants.RxD_MASK);
		// initProtocol();
	}

	/**
	 * Temporizador que pára o acesso ao Kit.
	 */
	private static void delay() {
		Kit.sleep(LicConstants.HALFCLOCK_MASK);
	}

	/**
	 * Temporizador que pára o acesso ao Kit.
	 */
	private static void fullDelay() {
		Kit.sleep(LicConstants.CLOCK_MASK);
	}

	/**
	 * Envia a sequencia de dados para ser mostrado no LCD.
	 * 
	 * @param rs
	 * @param value
	 */
	public static void sendBits(int rs, int value) {
		initProtocol();
		if (isReady()) {
			setStart();
			sendBit(rs);

			for (int count = bits2Shift; count != 0; count -= 1) {
				sendBit(value);
				value = value >> LicConstants.SHIFT_BITS_MASK;
			}

		} else {
			resetProtocol();
			sendBits(rs, value);
		}
	}

	/**
	 * Envia os dados, segundo o protocolo, pelo Output port.
	 * 
	 * @param value
	 */
	private static void sendBit(int value) {
		Kit.invertBits(LicConstants.RxC_MASK);

		if ((value & LicConstants.RxD_MASK) == 1)
			Kit.setBits(LicConstants.RxD_MASK);
		else
			Kit.resetBits(LicConstants.RxD_MASK);
		delay();
		Kit.setBits(LicConstants.RxC_MASK);
		delay();
	}
}

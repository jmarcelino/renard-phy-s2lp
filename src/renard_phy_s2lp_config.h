/*
 * See "4.7. Crystal oscillator" in S2-LP datasheet for details
 *
 * XTAL frequency can either be in range 24-26MHz or in range 48-52MHz
 * If XTAL frequency is in range 24-26MHz, the digital domain clock divider must be disabled, see (Eq. 1) / (Eq. 2).
 */
#define S2LP_XTAL_FREQ                  50000000
#define DISABLE_CLKDIV                  0

/*
 * Modulation type, see register table in datasheet:
 * --> 0x6 is direct polar mode (used to generate DBPSK) for uplink
 * --> 0x2 is 2-GFSK BT = 2 for downlink
 */
#define UPLINK_MOD_TYPE                 0x6
#define DOWNLINK_MOD_TYPE               0x2

/*
 * Datarate mantissa and exponent values - compute these for your XTAL frequency!
 * See datasheet "5.4.5 Data rate" (Eq. 14) for how to compute these values.
 *
 * For the *uplink* the target "DataRate" value in (Eq. 14) should be *5 times the actual Sigfox data rate*
 * (e.g. 500 for 100bps uplinks, 3000 for 600bps uplinks). This is because every Sigfox symbol consists of 40 byte
 * couples in the TX FIFO and the byte couples are sampled at a rate that is 8 times "DataRate", see datasheet
 * "5.4.1 Direct polar mode".
 *
 * For the *downlink* the target "DataRate" should be the actual Sigfox data rate (e.g. 600 for 600bps).
 *
 * Mind that if XTAL is in range 48-52 MHz, digital domain frequency is divided by 2!
 */
#define UPLINK_100BPS_DATARATE_M        20363
#define UPLINK_100BPS_DATARATE_E        1

#define UPLINK_600BPS_DATARATE_M        63313
#define UPLINK_600BPS_DATARATE_E        3

#define DOWNLINK_DATARATE_M             37543
#define DOWNLINK_DATARATE_E             1

/*
 * Frequency deviation mantissa and exponent values - compute these for your XTAL frequency!
 *
 * For *uplink*: Phase shift setting
 * For DBPSK modulation we want 180° phase shifts, but we can only control the instantaneous frequency of the chip.
 * Since every Sigfox symbol consists of 40 FIFO byte-couples, we can compute the duration of a single byte-couple:
 *
 * --> For 100bps uplink, the byte-couple duration is t_FIFO = 1 / (100bps * 40) = 250.0000us
 * --> For 600bps uplink, the byte-couple duration is t_FIFO = 1 / (600bps * 40) =  41.6666us
 *
 * Thus the required instantaneous frequency shifts for 180° are 0.5 / t_FIFO:
 *
 * --> For 100bps uplink:  2000.0Hz
 * --> For 600bps uplink: 12000.0Hz
 *
 * We use "5.4.3 Direct polar mode" (Eq. 12) to achieve these frequency shifts. In this equation, we set
 * fdev_fifo_sample to +127 (ETSI_FDEV_POS) or -128 (ETSI_FDEV_NEG) so that fdev_fifo_sample / 128 becomes effectively
 * +1 or -1. So we only need to program fdev_programmed = 2000.0Hz / 12000.0Hz according to
 * "5.4.1 Frequency modulation" (Eq. 10).
 *
 * For *downlink*: Frequency deviation setting
 * See "5.4.1 Frequency modulation" (Eq. 10) for how to compute these values.
 * The target frequency deviation should be fdev = 800Hz for Sigfox.
 *
 * For "5.4.1 Frequency modulation" (Eq. 10), note that:
 * --> B = 8 since operating in 868MHz band, see "5.3.1 RF channel frequency settings" (Eq. 8).
 * --> D = 1 for XTAL frequency 24MHz - 26MHz or D = 2 for XTAL frequency 48 - 52 MHz
 */
#define UPLINK_100BPS_FDEV_M            168
#define UPLINK_100BPS_FDEV_E            0

#define UPLINK_600BPS_FDEV_M            247
#define UPLINK_600BPS_FDEV_E            2

#define DOWNLINK_FDEV_M                 67
#define DOWNLINK_FDEV_E                 0

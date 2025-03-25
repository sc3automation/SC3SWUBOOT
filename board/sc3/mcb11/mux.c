// SPDX-License-Identifier: GPL-2.0+
/*
 * mux.c
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 */

#include <common.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mux.h>
#include "board.h"

static struct module_pin_mux mii_1_pin_mux[] = {
	{OFFSET(mii1_col), MODE(0) | RXACTIVE},	/* gmii1_col */
	{OFFSET(mii1_crs), MODE(0) | RXACTIVE},	/* gmii1_crs */
	{OFFSET(mii1_rxerr), MODE(0) | RXACTIVE},	/* gmii1_rxer */
	{OFFSET(mii1_txen), MODE(0)},			/* gmii1_txen */
	{OFFSET(mii1_rxdv), MODE(0) | RXACTIVE},	/* gmii1_rxdv */
	{OFFSET(mii1_txclk), MODE(0) | RXACTIVE},	/* gmii1_txclk */
	{OFFSET(mii1_rxclk), MODE(0) | RXACTIVE},	/* gmii1_rxclk */
	{OFFSET(mii1_txd0), MODE(0)},			/* gmii1_txd0 */
	{OFFSET(mii1_txd1), MODE(0)},			/* gmii1_txd1 */
	{OFFSET(mii1_txd2), MODE(0)},			/* gmii1_txd2 */
	{OFFSET(mii1_txd3), MODE(0)},			/* gmii1_txd3 */
	{OFFSET(mii1_rxd0), MODE(0) | RXACTIVE},	/* gmii1_rxd0 */
	{OFFSET(mii1_rxd1), MODE(0) | RXACTIVE},	/* gmii1_rxd1 */
	{OFFSET(mii1_rxd2), MODE(0) | RXACTIVE},	/* gmii1_rxd2 */
	{OFFSET(mii1_rxd3), MODE(0) | RXACTIVE},	/* gmii1_rxd3 */
	{-1},
};

static struct module_pin_mux mii_pruss1_1_pin_mux[] = {
	{OFFSET(gpmc_a6), MODE(5) | RXACTIVE},	/* pr1_mii_mt1_clk */
	{OFFSET(gpmc_a5), MODE(5)},			/* pr1_mii1_txd0 */
	{OFFSET(gpmc_a4), MODE(5)},			/* pr1_mii1_txd1 */
	{OFFSET(gpmc_a3), MODE(5)},			/* pr1_mii1_txd2 */
	{OFFSET(gpmc_a2), MODE(5)},			/* pr1_mii1_txd3 */
	{OFFSET(gpmc_a11), MODE(5) | RXACTIVE},	/* pr1_mii1_rxd0 */
	{OFFSET(gpmc_a10), MODE(5) | RXACTIVE},	/* pr1_mii1_rxd1 */
	{OFFSET(gpmc_a9), MODE(5) | RXACTIVE},	/* pr1_mii1_rxd2 */
	{OFFSET(gpmc_a8), MODE(5) | RXACTIVE},	/* pr1_mii1_rxd3 */
	{OFFSET(gpmc_a0), MODE(5)},			/* pr1_mii1_txen */
	{OFFSET(gpmc_a7), MODE(5) | RXACTIVE},	/* pr1_mii_mr1_clk */
	{OFFSET(gpmc_a1), MODE(5) | RXACTIVE},	/* pr1_mii1_rxdv */
	{OFFSET(gpmc_wpn), MODE(5) | RXACTIVE},	/* pr1_mii1_rxer */
	{OFFSET(gpio5_13), MODE(5) | RXACTIVE},	/* pr1_mii1_rxlink */
	{OFFSET(gpio5_11), MODE(5) | RXACTIVE},	/* pr1_mii1_crs */
	{OFFSET(gpmc_be1n), MODE(5) | RXACTIVE},	/* pr1_mii1_col */
	{-1},
};

static struct module_pin_mux mii_pruss1_0_pin_mux[] = {
	{OFFSET(lcd_data0), MODE(2) | RXACTIVE},	/* pr1_mii_mt0_clk */	
	{OFFSET(lcd_data5), MODE(2)},			/* pr1_mii0_txd0 */
	{OFFSET(lcd_data4), MODE(2)},			/* pr1_mii0_txd1 */
	{OFFSET(lcd_data3), MODE(2)},			/* pr1_mii0_txd2 */
	{OFFSET(lcd_data2), MODE(2)},			/* pr1_mii0_txd3 */
	{OFFSET(lcd_data11), MODE(5) | RXACTIVE},	/* pr1_mii0_rxd0 */
	{OFFSET(lcd_data10), MODE(5) | RXACTIVE},	/* pr1_mii0_rxd1 */
	{OFFSET(lcd_data9), MODE(5) | RXACTIVE},	/* pr1_mii0_rxd2 */
	{OFFSET(lcd_data8), MODE(5) | RXACTIVE},	/* pr1_mii0_rxd3 */
	{OFFSET(lcd_data1), MODE(2)},			/* pr1_mii0_txen */
	{OFFSET(lcd_data14), MODE(5) | RXACTIVE},	/* pr1_mii_mr0_clk */
	{OFFSET(lcd_data15), MODE(5) | RXACTIVE},	/* pr1_mii0_rxdv */
	{OFFSET(lcd_data13), MODE(5) | RXACTIVE},	/* pr1_mii0_rxer */
	{OFFSET(lcd_data12), MODE(5) | RXACTIVE},	/* pr1_mii0_rxlink */
	{OFFSET(gpio5_10), MODE(5) | RXACTIVE},	/* pr1_mii0_crs */
	{OFFSET(gpio5_8), MODE(5) | RXACTIVE},	/* pr1_mii0_col */
	{-1},
};

static struct module_pin_mux mdio_pin_mux[] = {	
	{OFFSET(gpmc_clk), MODE(0) | PULLUP_EN},	/* PR1_MDIO_MDCLK */
	{OFFSET(xdma_evt_intr0), MODE(0) | RXACTIVE | PULLUP_EN},/* PR1_MDIO_DATA */
	{-1},
};

static struct module_pin_mux mdio2_pin_mux[] = {
	{OFFSET(mdio_clk), MODE(0) | PULLUP_EN},	/* MDIO_CLK */
	{OFFSET(mdio_data), MODE(0) | RXACTIVE | PULLUP_EN},/* MDIO_DATA */
	{-1},
};

static struct module_pin_mux uart0_pin_mux[] = {
	{OFFSET(uart0_rxd), (MODE(0) | PULLUP_EN | RXACTIVE | SLEWCTRL)}, /* uart0_rxd */
	{OFFSET(uart0_txd), (MODE(0) | PULLUDDIS | PULLUP_EN | SLEWCTRL)}, /* uart0_txd */
	{-1},
};

static struct module_pin_mux mmc1_pin_mux[] = {
	{OFFSET(gpmc_csn1), (MODE(2) | PULLUP_EN | RXACTIVE)},  /* MMC1_CLK */
	{OFFSET(gpmc_csn2), (MODE(2) | PULLUP_EN | RXACTIVE)},  /* MMC1_CMD */
	{OFFSET(gpmc_ad8), (MODE(2) | PULLUP_EN | RXACTIVE)}, /* MMC1_DAT0 */
	{OFFSET(gpmc_ad9), (MODE(2) | PULLUP_EN | RXACTIVE)}, /* MMC1_DAT1 */
	{OFFSET(gpmc_ad10), (MODE(2) | PULLUP_EN | RXACTIVE)}, /* MMC1_DAT2 */
	{OFFSET(gpmc_ad11), (MODE(2) | PULLUP_EN | RXACTIVE)}, /* MMC1_DAT3 */
	{OFFSET(gpmc_ad12), (MODE(2) | PULLUP_EN | RXACTIVE)}, /* MMC1_DAT4 */
	{OFFSET(gpmc_ad13), (MODE(2) | PULLUP_EN | RXACTIVE)}, /* MMC1_DAT5 */
	{OFFSET(gpmc_ad14), (MODE(2) | PULLUP_EN | RXACTIVE)}, /* MMC1_DAT6 */
	{OFFSET(gpmc_ad15), (MODE(2) | PULLUP_EN | RXACTIVE)}, /* MMC1_DAT7 */
	{-1},
};

static struct module_pin_mux osc_1_pin_mux[] = {
	{OFFSET(osc1_in), (MODE(0) | PULLUP_EN | RXACTIVE)}, /* OSC1_IN */
	{OFFSET(osc1_out), (MODE(0) | PULLUP_EN)}, /* OSC1_OUT */
	{-1},
};

static struct module_pin_mux osc_2_pin_mux[] = {
	{OFFSET(rsvd2), (MODE(0) | PULLUP_EN | RXACTIVE)}, /* OSC0_IN */ 
	{OFFSET(rsvd3), (MODE(0) | PULLUP_EN)}, /* OSC0_OUT */
	{-1},
};

static struct module_pin_mux qspi_1_pin_mux[] = {	
	{OFFSET(gpmc_csn3), (MODE(2) | PULLUP_EN | RXACTIVE)}, /* QSPI_CLK */
	{OFFSET(gpmc_csn0), (MODE(3) | PULLUP_EN | RXACTIVE)}, /* QSPI_CS0 */
	{OFFSET(gpmc_advn_ale), (MODE(3) | PULLUP_EN | RXACTIVE)}, /* QSPI_D0 */
	{OFFSET(gpmc_oen_ren), (MODE(3) | PULLUP_EN | RXACTIVE)}, /* QSPI_D1 */
	{OFFSET(gpmc_wen), (MODE(3) | PULLUP_EN | RXACTIVE)}, /* QSPI_D2 */
	{OFFSET(gpmc_be0n_cle), (MODE(3) | PULLUP_EN | RXACTIVE)}, /* QSPI_D3 */
	{-1},
};

static struct module_pin_mux rtc_1_pin_mux[] = {
	{OFFSET(rtc_porz), (MODE(0) | RXACTIVE | PULLUDDIS)}, /* RTC_PORz */
	{OFFSET(ext_wakeup0), (MODE(0) | RXACTIVE | PULLUDDIS)}, /* RTC_WAKEUP */
	{OFFSET(pmic_power_en0), (MODE(0) | RXACTIVE | PULLUDDIS)}, /* RTC_PMIC_EN */
	{-1},
};

static struct module_pin_mux i2c0_pin_mux[] = {	
	{OFFSET(i2c0_scl), (MODE(0) | PULLUP_EN | RXACTIVE | SLEWCTRL)},
	{OFFSET(i2c0_sda), (MODE(0) | PULLUP_EN | RXACTIVE | SLEWCTRL)},
	{-1},
};

static struct module_pin_mux gpio0_pin_mux[] = {
	{OFFSET(spi0_d0), (MODE(7) | PULLUP_EN)},	/* GPIO0_3 */
	{OFFSET(spi0_d1), (MODE(7) | PULLUP_EN)},	/* GPIO0_4 */
	{OFFSET(spi0_cs0), (MODE(7) | PULLUP_EN)},	/* GPIO0_5 */
	{OFFSET(ecap0_in_pwm0_out), (MODE(7) | PULLUP_EN)},	/* GPIO0_7 */
	{OFFSET(uart1_ctsn), (MODE(7) | PULLUP_EN)},	/* GPIO0_12 */
	{OFFSET(uart1_rtsn), (MODE(7) | PULLUP_EN)},	/* GPIO0_13 */
	{OFFSET(uart1_rxd), (MODE(7) | PULLUP_EN)},	/* GPIO0_14 */
	{OFFSET(gpmc_wait0), (MODE(7) | PULLUP_EN)},	/* GPIO0_30 */
	{-1},
};

void enable_uart0_pin_mux(void)
{
	configure_module_pin_mux(uart0_pin_mux);
}

void enable_board_pin_mux(void)
{
	configure_module_pin_mux(gpio0_pin_mux);
	configure_module_pin_mux(i2c0_pin_mux);
	configure_module_pin_mux(mdio_pin_mux);
	configure_module_pin_mux(mdio2_pin_mux);		
	configure_module_pin_mux(mii_1_pin_mux);
	configure_module_pin_mux(mii_pruss1_1_pin_mux);
	configure_module_pin_mux(mii_pruss1_0_pin_mux);
	configure_module_pin_mux(mmc1_pin_mux);
	configure_module_pin_mux(osc_1_pin_mux);
	configure_module_pin_mux(osc_2_pin_mux);
	configure_module_pin_mux(qspi_1_pin_mux);
	configure_module_pin_mux(rtc_1_pin_mux);
}

void enable_i2c0_pin_mux(void)
{
	configure_module_pin_mux(i2c0_pin_mux);
}

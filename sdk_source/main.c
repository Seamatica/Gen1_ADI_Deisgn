/***************************************************************************//**
 *   @file   ad9361/src/main.c
 *   @brief  Implementation of Main Function.
 *   @author DBogdan (dragos.bogdan@analog.com)
********************************************************************************
 * Copyright 2013(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include <inttypes.h>
#include "app_config.h"
#include "ad9361_api.h"
#include "parameters.h"
#include "no_os_spi.h"
#include "no_os_gpio.h"
#include "no_os_delay.h"
#ifdef XILINX_PLATFORM
#include <xparameters.h>
#include <xil_cache.h>
#include "xilinx_spi.h"
#include "xilinx_gpio.h"
#include "no_os_irq.h"
#ifdef ALTERA_PLATFORM
#include "altera_spi.h"
#include "altera_gpio.h"
#endif
#endif
#ifdef LINUX_PLATFORM
#include "linux_spi.h"
#include "linux_gpio.h"
#else
#include "xilinx_irq.h"
#endif //LINUX

#include "axi_adc_core.h"
#include "axi_dac_core.h"
#include "axi_dmac.h"
#include "no_os_error.h"

#ifdef IIO_SUPPORT

#include "iio_axi_adc.h"
#include "iio_axi_dac.h"
#include "iio_ad9361.h"
#include "no_os_uart.h"
#include "iio_app.h"

#ifdef XILINX_PLATFORM
#include "xilinx_uart.h"
#include "xil_cache.h"
#endif //XILINX

#if defined LINUX_PLATFORM || defined GENERIC_PLATFORM
static uint8_t in_buff[MAX_SIZE_BASE_ADDR];
static uint8_t out_buff[MAX_SIZE_BASE_ADDR];
#endif

#endif // IIO_SUPPORT

#ifdef DAC_DMA_EXAMPLE
#include <string.h>
#endif

/******************************************************************************/
/************************ Variables Definitions *******************************/
/******************************************************************************/

#if defined(DAC_DMA_EXAMPLE) || defined(IIO_SUPPORT)
uint32_t dac_buffer[DAC_BUFFER_SAMPLES] __attribute__ ((aligned));
#endif
uint16_t adc_buffer[ADC_BUFFER_SAMPLES * ADC_CHANNELS] __attribute__ ((
			aligned));

#define AD9361_ADC_DAC_BYTES_PER_SAMPLE 2

#ifdef XILINX_PLATFORM
struct xil_spi_init_param xil_spi_param_phy_a = {
#ifdef PLATFORM_MB
	.type = SPI_PL,
#else
	.type = SPI_PS,
#endif
	.flags = 0
};

struct xil_spi_init_param xil_spi_param_phy_b = {
#ifdef PLATFORM_MB
	.type = SPI_PL,
#else
	.type = SPI_PS,
#endif
	.flags = 0
};


struct xil_gpio_init_param xil_gpio_param_phy_a = {
#ifdef PLATFORM_MB
	.type = GPIO_PL,
#else
	.type = GPIO_PS,
#endif
	.device_id = GPIO_DEVICE_ID
};

struct xil_gpio_init_param xil_gpio_param_phy_b = {
#ifdef PLATFORM_MB
	.type = GPIO_PL,
#else
	.type = GPIO_PS,
#endif
	.device_id = GPIO_DEVICE_ID
};


#define GPIO_OPS	&xil_gpio_ops
#define SPI_OPS		&xil_spi_ops
#define GPIO_PARAM_PHY_A	&xil_gpio_param_phy_a
#define SPI_PARAM_PHY_A	    &xil_spi_param_phy_a
#define GPIO_PARAM_PHY_B	&xil_gpio_param_phy_b
#define SPI_PARAM_PHY_B	    &xil_spi_param_phy_b
#endif



struct axi_adc_init rx_adc_init_phy_a = {"cf-ad9361-lpc-a", RX_CORE_0_BASEADDR, 4};
struct axi_dac_init tx_dac_init_phy_a = {"cf-ad9361-dds-core-lpc-a", TX_CORE_0_BASEADDR, 4, NULL};

struct axi_dmac_init rx_dmac_init_phy_a = {"rx_dmac_a", CF_AD9361_RX_DMA_0_BASEADDR,
#ifdef DMA_IRQ_ENABLE
	IRQ_ENABLED
#else
	IRQ_DISABLED
#endif
};
struct axi_dmac *rx_dmac_phy_a;

struct axi_dmac_init tx_dmac_init_phy_a = {"tx_dmac_a", CF_AD9361_TX_DMA_0_BASEADDR,
#ifdef DMA_IRQ_ENABLE
	IRQ_ENABLED
#else
	IRQ_DISABLED
#endif
};
struct axi_dmac *tx_dmac_phy_a;

AD9361_InitParam init_param_phy_a = {
	/* Device selection */
	ID_AD9361,	// dev_sel
	/* Reference Clock */
	40000000UL,	//reference_clk_rate
	/* Base Configuration */
	1,		//two_rx_two_tx_mode_enable *** adi,2rx-2tx-mode-enable
	1,		//one_rx_one_tx_mode_use_rx_num *** adi,1rx-1tx-mode-use-rx-num
	2,		//one_rx_one_tx_mode_use_tx_num *** adi,1rx-1tx-mode-use-tx-num
	1,		//frequency_division_duplex_mode_enable *** adi,frequency-division-duplex-mode-enable
	0,		//frequency_division_duplex_independent_mode_enable *** adi,frequency-division-duplex-independent-mode-enable
	0,		//tdd_use_dual_synth_mode_enable *** adi,tdd-use-dual-synth-mode-enable
	0,		//tdd_skip_vco_cal_enable *** adi,tdd-skip-vco-cal-enable
	0,		//tx_fastlock_delay_ns *** adi,tx-fastlock-delay-ns
	0,		//rx_fastlock_delay_ns *** adi,rx-fastlock-delay-ns
	0,		//rx_fastlock_pincontrol_enable *** adi,rx-fastlock-pincontrol-enable
	0,		//tx_fastlock_pincontrol_enable *** adi,tx-fastlock-pincontrol-enable
	0,		//external_rx_lo_enable *** adi,external-rx-lo-enable
	0,		//external_tx_lo_enable *** adi,external-tx-lo-enable
	5,		//dc_offset_tracking_update_event_mask *** adi,dc-offset-tracking-update-event-mask
	6,		//dc_offset_attenuation_high_range *** adi,dc-offset-attenuation-high-range
	5,		//dc_offset_attenuation_low_range *** adi,dc-offset-attenuation-low-range
	0x28,	//dc_offset_count_high_range *** adi,dc-offset-count-high-range
	0x32,	//dc_offset_count_low_range *** adi,dc-offset-count-low-range
	0,		//split_gain_table_mode_enable *** adi,split-gain-table-mode-enable
	MAX_SYNTH_FREF,	//trx_synthesizer_target_fref_overwrite_hz *** adi,trx-synthesizer-target-fref-overwrite-hz
	0,		// qec_tracking_slow_mode_enable *** adi,qec-tracking-slow-mode-enable
	/* ENSM Control */
	0,		//ensm_enable_pin_pulse_mode_enable *** adi,ensm-enable-pin-pulse-mode-enable
	0,		//ensm_enable_txnrx_control_enable *** adi,ensm-enable-txnrx-control-enable
	/* LO Control */
	1090000000UL,	//rx_synthesizer_frequency_hz *** adi,rx-synthesizer-frequency-hz
	2400000000UL,	//tx_synthesizer_frequency_hz *** adi,tx-synthesizer-frequency-hz
	1,				//tx_lo_powerdown_managed_enable *** adi,tx-lo-powerdown-managed-enable
	/* Rate & BW Control */
	{983040000, 245760000, 122880000, 61440000, 30720000, 30720000},// rx_path_clock_frequencies[6] *** adi,rx-path-clock-frequencies
	{983040000, 122880000, 122880000, 61440000, 30720000, 30720000},// tx_path_clock_frequencies[6] *** adi,tx-path-clock-frequencies
	18000000,//rf_rx_bandwidth_hz *** adi,rf-rx-bandwidth-hz
	18000000,//rf_tx_bandwidth_hz *** adi,rf-tx-bandwidth-hz
	/* RF Port Control */
	0,		//rx_rf_port_input_select *** adi,rx-rf-port-input-select
	0,		//tx_rf_port_input_select *** adi,tx-rf-port-input-select
	/* TX Attenuation Control */
	10000,	//tx_attenuation_mdB *** adi,tx-attenuation-mdB
	0,		//update_tx_gain_in_alert_enable *** adi,update-tx-gain-in-alert-enable
	/* Reference Clock Control */
	1,		//xo_disable_use_ext_refclk_enable *** adi,xo-disable-use-ext-refclk-enable
	{8, 5920},	//dcxo_coarse_and_fine_tune[2] *** adi,dcxo-coarse-and-fine-tune
	CLKOUT_DISABLE,	//clk_output_mode_select *** adi,clk-output-mode-select
	/* Gain Control */
	0,		//gc_rx1_mode *** adi,gc-rx1-mode
	0,		//gc_rx2_mode *** adi,gc-rx2-mode
	58,		//gc_adc_large_overload_thresh *** adi,gc-adc-large-overload-thresh
	4,		//gc_adc_ovr_sample_size *** adi,gc-adc-ovr-sample-size
	47,		//gc_adc_small_overload_thresh *** adi,gc-adc-small-overload-thresh
	8192,	//gc_dec_pow_measurement_duration *** adi,gc-dec-pow-measurement-duration
	0,		//gc_dig_gain_enable *** adi,gc-dig-gain-enable
	800,	//gc_lmt_overload_high_thresh *** adi,gc-lmt-overload-high-thresh
	704,	//gc_lmt_overload_low_thresh *** adi,gc-lmt-overload-low-thresh
	24,		//gc_low_power_thresh *** adi,gc-low-power-thresh
	15,		//gc_max_dig_gain *** adi,gc-max-dig-gain
	0,		//gc_use_rx_fir_out_for_dec_pwr_meas_enable *** adi,gc-use-rx-fir-out-for-dec-pwr-meas-enable
	/* Gain MGC Control */
	2,		//mgc_dec_gain_step *** adi,mgc-dec-gain-step
	2,		//mgc_inc_gain_step *** adi,mgc-inc-gain-step
	0,		//mgc_rx1_ctrl_inp_enable *** adi,mgc-rx1-ctrl-inp-enable
	0,		//mgc_rx2_ctrl_inp_enable *** adi,mgc-rx2-ctrl-inp-enable
	0,		//mgc_split_table_ctrl_inp_gain_mode *** adi,mgc-split-table-ctrl-inp-gain-mode
	/* Gain AGC Control */
	10,		//agc_adc_large_overload_exceed_counter *** adi,agc-adc-large-overload-exceed-counter
	2,		//agc_adc_large_overload_inc_steps *** adi,agc-adc-large-overload-inc-steps
	0,		//agc_adc_lmt_small_overload_prevent_gain_inc_enable *** adi,agc-adc-lmt-small-overload-prevent-gain-inc-enable
	10,		//agc_adc_small_overload_exceed_counter *** adi,agc-adc-small-overload-exceed-counter
	4,		//agc_dig_gain_step_size *** adi,agc-dig-gain-step-size
	3,		//agc_dig_saturation_exceed_counter *** adi,agc-dig-saturation-exceed-counter
	1000,	// agc_gain_update_interval_us *** adi,agc-gain-update-interval-us
	0,		//agc_immed_gain_change_if_large_adc_overload_enable *** adi,agc-immed-gain-change-if-large-adc-overload-enable
	0,		//agc_immed_gain_change_if_large_lmt_overload_enable *** adi,agc-immed-gain-change-if-large-lmt-overload-enable
	10,		//agc_inner_thresh_high *** adi,agc-inner-thresh-high
	1,		//agc_inner_thresh_high_dec_steps *** adi,agc-inner-thresh-high-dec-steps
	12,		//agc_inner_thresh_low *** adi,agc-inner-thresh-low
	1,		//agc_inner_thresh_low_inc_steps *** adi,agc-inner-thresh-low-inc-steps
	10,		//agc_lmt_overload_large_exceed_counter *** adi,agc-lmt-overload-large-exceed-counter
	2,		//agc_lmt_overload_large_inc_steps *** adi,agc-lmt-overload-large-inc-steps
	10,		//agc_lmt_overload_small_exceed_counter *** adi,agc-lmt-overload-small-exceed-counter
	5,		//agc_outer_thresh_high *** adi,agc-outer-thresh-high
	2,		//agc_outer_thresh_high_dec_steps *** adi,agc-outer-thresh-high-dec-steps
	18,		//agc_outer_thresh_low *** adi,agc-outer-thresh-low
	2,		//agc_outer_thresh_low_inc_steps *** adi,agc-outer-thresh-low-inc-steps
	1,		//agc_attack_delay_extra_margin_us; *** adi,agc-attack-delay-extra-margin-us
	0,		//agc_sync_for_gain_counter_enable *** adi,agc-sync-for-gain-counter-enable
	/* Fast AGC */
	64,		//fagc_dec_pow_measuremnt_duration ***  adi,fagc-dec-pow-measurement-duration
	260,	//fagc_state_wait_time_ns ***  adi,fagc-state-wait-time-ns
	/* Fast AGC - Low Power */
	0,		//fagc_allow_agc_gain_increase ***  adi,fagc-allow-agc-gain-increase-enable
	5,		//fagc_lp_thresh_increment_time ***  adi,fagc-lp-thresh-increment-time
	1,		//fagc_lp_thresh_increment_steps ***  adi,fagc-lp-thresh-increment-steps
	/* Fast AGC - Lock Level (Lock Level is set via slow AGC inner high threshold) */
	1,		//fagc_lock_level_lmt_gain_increase_en ***  adi,fagc-lock-level-lmt-gain-increase-enable
	5,		//fagc_lock_level_gain_increase_upper_limit ***  adi,fagc-lock-level-gain-increase-upper-limit
	/* Fast AGC - Peak Detectors and Final Settling */
	1,		//fagc_lpf_final_settling_steps ***  adi,fagc-lpf-final-settling-steps
	1,		//fagc_lmt_final_settling_steps ***  adi,fagc-lmt-final-settling-steps
	3,		//fagc_final_overrange_count ***  adi,fagc-final-overrange-count
	/* Fast AGC - Final Power Test */
	0,		//fagc_gain_increase_after_gain_lock_en ***  adi,fagc-gain-increase-after-gain-lock-enable
	/* Fast AGC - Unlocking the Gain */
	0,		//fagc_gain_index_type_after_exit_rx_mode ***  adi,fagc-gain-index-type-after-exit-rx-mode
	1,		//fagc_use_last_lock_level_for_set_gain_en ***  adi,fagc-use-last-lock-level-for-set-gain-enable
	1,		//fagc_rst_gla_stronger_sig_thresh_exceeded_en ***  adi,fagc-rst-gla-stronger-sig-thresh-exceeded-enable
	5,		//fagc_optimized_gain_offset ***  adi,fagc-optimized-gain-offset
	10,		//fagc_rst_gla_stronger_sig_thresh_above_ll ***  adi,fagc-rst-gla-stronger-sig-thresh-above-ll
	1,		//fagc_rst_gla_engergy_lost_sig_thresh_exceeded_en ***  adi,fagc-rst-gla-engergy-lost-sig-thresh-exceeded-enable
	1,		//fagc_rst_gla_engergy_lost_goto_optim_gain_en ***  adi,fagc-rst-gla-engergy-lost-goto-optim-gain-enable
	10,		//fagc_rst_gla_engergy_lost_sig_thresh_below_ll ***  adi,fagc-rst-gla-engergy-lost-sig-thresh-below-ll
	8,		//fagc_energy_lost_stronger_sig_gain_lock_exit_cnt ***  adi,fagc-energy-lost-stronger-sig-gain-lock-exit-cnt
	1,		//fagc_rst_gla_large_adc_overload_en ***  adi,fagc-rst-gla-large-adc-overload-enable
	1,		//fagc_rst_gla_large_lmt_overload_en ***  adi,fagc-rst-gla-large-lmt-overload-enable
	0,		//fagc_rst_gla_en_agc_pulled_high_en ***  adi,fagc-rst-gla-en-agc-pulled-high-enable
	0,		//fagc_rst_gla_if_en_agc_pulled_high_mode ***  adi,fagc-rst-gla-if-en-agc-pulled-high-mode
	64,		//fagc_power_measurement_duration_in_state5 ***  adi,fagc-power-measurement-duration-in-state5
	2,		//fagc_large_overload_inc_steps *** adi,fagc-adc-large-overload-inc-steps
	/* RSSI Control */
	1,		//rssi_delay *** adi,rssi-delay
	1000,	//rssi_duration *** adi,rssi-duration
	3,		//rssi_restart_mode *** adi,rssi-restart-mode
	0,		//rssi_unit_is_rx_samples_enable *** adi,rssi-unit-is-rx-samples-enable
	1,		//rssi_wait *** adi,rssi-wait
	/* Aux ADC Control */
	256,	//aux_adc_decimation *** adi,aux-adc-decimation
	40000000UL,	//aux_adc_rate *** adi,aux-adc-rate
	/* AuxDAC Control */
	1,		//aux_dac_manual_mode_enable ***  adi,aux-dac-manual-mode-enable
	0,		//aux_dac1_default_value_mV ***  adi,aux-dac1-default-value-mV
	0,		//aux_dac1_active_in_rx_enable ***  adi,aux-dac1-active-in-rx-enable
	0,		//aux_dac1_active_in_tx_enable ***  adi,aux-dac1-active-in-tx-enable
	0,		//aux_dac1_active_in_alert_enable ***  adi,aux-dac1-active-in-alert-enable
	0,		//aux_dac1_rx_delay_us ***  adi,aux-dac1-rx-delay-us
	0,		//aux_dac1_tx_delay_us ***  adi,aux-dac1-tx-delay-us
	0,		//aux_dac2_default_value_mV ***  adi,aux-dac2-default-value-mV
	0,		//aux_dac2_active_in_rx_enable ***  adi,aux-dac2-active-in-rx-enable
	0,		//aux_dac2_active_in_tx_enable ***  adi,aux-dac2-active-in-tx-enable
	0,		//aux_dac2_active_in_alert_enable ***  adi,aux-dac2-active-in-alert-enable
	0,		//aux_dac2_rx_delay_us ***  adi,aux-dac2-rx-delay-us
	0,		//aux_dac2_tx_delay_us ***  adi,aux-dac2-tx-delay-us
	/* Temperature Sensor Control */
	256,	//temp_sense_decimation *** adi,temp-sense-decimation
	1000,	//temp_sense_measurement_interval_ms *** adi,temp-sense-measurement-interval-ms
	0xCE,	//temp_sense_offset_signed *** adi,temp-sense-offset-signed
	1,		//temp_sense_periodic_measurement_enable *** adi,temp-sense-periodic-measurement-enable
	/* Control Out Setup */
	0xFF,	//ctrl_outs_enable_mask *** adi,ctrl-outs-enable-mask
	0,		//ctrl_outs_index *** adi,ctrl-outs-index
	/* External LNA Control */
	0,		//elna_settling_delay_ns *** adi,elna-settling-delay-ns
	0,		//elna_gain_mdB *** adi,elna-gain-mdB
	0,		//elna_bypass_loss_mdB *** adi,elna-bypass-loss-mdB
	0,		//elna_rx1_gpo0_control_enable *** adi,elna-rx1-gpo0-control-enable
	0,		//elna_rx2_gpo1_control_enable *** adi,elna-rx2-gpo1-control-enable
	0,		//elna_gaintable_all_index_enable *** adi,elna-gaintable-all-index-enable
	/* Digital Interface Control */
	0,		//digital_interface_tune_skip_mode *** adi,digital-interface-tune-skip-mode
	0,		//digital_interface_tune_fir_disable *** adi,digital-interface-tune-fir-disable
	1,		//pp_tx_swap_enable *** adi,pp-tx-swap-enable
	1,		//pp_rx_swap_enable *** adi,pp-rx-swap-enable
	0,		//tx_channel_swap_enable *** adi,tx-channel-swap-enable
	0,		//rx_channel_swap_enable *** adi,rx-channel-swap-enable
	1,		//rx_frame_pulse_mode_enable *** adi,rx-frame-pulse-mode-enable
	0,		//two_t_two_r_timing_enable *** adi,2t2r-timing-enable
	0,		//invert_data_bus_enable *** adi,invert-data-bus-enable
	0,		//invert_data_clk_enable *** adi,invert-data-clk-enable
	0,		//fdd_alt_word_order_enable *** adi,fdd-alt-word-order-enable
	0,		//invert_rx_frame_enable *** adi,invert-rx-frame-enable
	0,		//fdd_rx_rate_2tx_enable *** adi,fdd-rx-rate-2tx-enable
	0,		//swap_ports_enable *** adi,swap-ports-enable
	0,		//single_data_rate_enable *** adi,single-data-rate-enable
	1,		//lvds_mode_enable *** adi,lvds-mode-enable
	0,		//half_duplex_mode_enable *** adi,half-duplex-mode-enable
	0,		//single_port_mode_enable *** adi,single-port-mode-enable
	1,		//full_port_enable *** adi,full-port-enable
	0,		//full_duplex_swap_bits_enable *** adi,full-duplex-swap-bits-enable
	0,		//delay_rx_data *** adi,delay-rx-data
	0,		//rx_data_clock_delay *** adi,rx-data-clock-delay
	4,		//rx_data_delay *** adi,rx-data-delay
	7,		//tx_fb_clock_delay *** adi,tx-fb-clock-delay
	0,		//tx_data_delay *** adi,tx-data-delay
#ifdef ALTERA_PLATFORM
	300,	//lvds_bias_mV *** adi,lvds-bias-mV
#else
	150,	//lvds_bias_mV *** adi,lvds-bias-mV
#endif
	1,		//lvds_rx_onchip_termination_enable *** adi,lvds-rx-onchip-termination-enable
	1,		//rx1rx2_phase_inversion_en *** adi,rx1-rx2-phase-inversion-enable
	0xFF,	//lvds_invert1_control *** adi,lvds-invert1-control
	0x0F,	//lvds_invert2_control *** adi,lvds-invert2-control
	/* GPO Control */
	0,		//gpo_manual_mode_enable *** adi,gpo-manual-mode-enable
	0,		//gpo_manual_mode_enable_mask *** adi,gpo-manual-mode-enable-mask
	0,		//gpo0_inactive_state_high_enable *** adi,gpo0-inactive-state-high-enable
	0,		//gpo1_inactive_state_high_enable *** adi,gpo1-inactive-state-high-enable
	0,		//gpo2_inactive_state_high_enable *** adi,gpo2-inactive-state-high-enable
	0,		//gpo3_inactive_state_high_enable *** adi,gpo3-inactive-state-high-enable
	0,		//gpo0_slave_rx_enable *** adi,gpo0-slave-rx-enable
	0,		//gpo0_slave_tx_enable *** adi,gpo0-slave-tx-enable
	0,		//gpo1_slave_rx_enable *** adi,gpo1-slave-rx-enable
	0,		//gpo1_slave_tx_enable *** adi,gpo1-slave-tx-enable
	0,		//gpo2_slave_rx_enable *** adi,gpo2-slave-rx-enable
	0,		//gpo2_slave_tx_enable *** adi,gpo2-slave-tx-enable
	0,		//gpo3_slave_rx_enable *** adi,gpo3-slave-rx-enable
	0,		//gpo3_slave_tx_enable *** adi,gpo3-slave-tx-enable
	0,		//gpo0_rx_delay_us *** adi,gpo0-rx-delay-us
	0,		//gpo0_tx_delay_us *** adi,gpo0-tx-delay-us
	0,		//gpo1_rx_delay_us *** adi,gpo1-rx-delay-us
	0,		//gpo1_tx_delay_us *** adi,gpo1-tx-delay-us
	0,		//gpo2_rx_delay_us *** adi,gpo2-rx-delay-us
	0,		//gpo2_tx_delay_us *** adi,gpo2-tx-delay-us
	0,		//gpo3_rx_delay_us *** adi,gpo3-rx-delay-us
	0,		//gpo3_tx_delay_us *** adi,gpo3-tx-delay-us
	/* Tx Monitor Control */
	37000,	//low_high_gain_threshold_mdB *** adi,txmon-low-high-thresh
	0,		//low_gain_dB *** adi,txmon-low-gain
	24,		//high_gain_dB *** adi,txmon-high-gain
	0,		//tx_mon_track_en *** adi,txmon-dc-tracking-enable
	0,		//one_shot_mode_en *** adi,txmon-one-shot-mode-enable
	511,	//tx_mon_delay *** adi,txmon-delay
	8192,	//tx_mon_duration *** adi,txmon-duration
	2,		//tx1_mon_front_end_gain *** adi,txmon-1-front-end-gain
	2,		//tx2_mon_front_end_gain *** adi,txmon-2-front-end-gain
	48,		//tx1_mon_lo_cm *** adi,txmon-1-lo-cm
	48,		//tx2_mon_lo_cm *** adi,txmon-2-lo-cm
	/* GPIO definitions */
	{
		.number = -1,
		.platform_ops = GPIO_OPS,
		.extra = GPIO_PARAM_PHY_A
	},		//gpio_resetb *** reset-gpios
	/* MCS Sync */
	{
		.number = -1,
		.platform_ops = GPIO_OPS,
		.extra = GPIO_PARAM_PHY_A
	},		//gpio_sync *** sync-gpios

	{
		.number = -1,
		.platform_ops = GPIO_OPS,
		.extra = GPIO_PARAM_PHY_A
	},		//gpio_cal_sw1 *** cal-sw1-gpios

	{
		.number = -1,
		.platform_ops = GPIO_OPS,
		.extra = GPIO_PARAM_PHY_A
	},		//gpio_cal_sw2 *** cal-sw2-gpios

	{
		.device_id = SPI_DEVICE_ID,
		.mode = NO_OS_SPI_MODE_1,
		.chip_select = SPI_CS,
		.platform_ops = SPI_OPS,
		.extra = SPI_PARAM_PHY_A
	},

	/* External LO clocks */
	NULL,	//(*ad9361_rfpll_ext_recalc_rate)()
	NULL,	//(*ad9361_rfpll_ext_round_rate)()
	NULL,	//(*ad9361_rfpll_ext_set_rate)()
#ifndef AXI_ADC_NOT_PRESENT
	&rx_adc_init_phy_a,	// *rx_adc_init
	&tx_dac_init_phy_a,   // *tx_dac_init
#endif
};

//---------------------------------------------------phy_b---------------------------------------//

struct axi_adc_init rx_adc_init_phy_b = {"cf-ad9361-lpc-b", RX_CORE_1_BASEADDR, 4};
struct axi_dac_init tx_dac_init_phy_b = {"cf-ad9361-dds-core-lpc-b", TX_CORE_1_BASEADDR, 4, NULL};

struct axi_dmac_init rx_dmac_init_phy_b = {"rx_dmac_b", CF_AD9361_RX_DMA_1_BASEADDR,
#ifdef DMA_IRQ_ENABLE
	IRQ_ENABLED
#else
	IRQ_DISABLED
#endif
};
struct axi_dmac *rx_dmac_phy_b;

struct axi_dmac_init tx_dmac_init_phy_b = {"tx_dmac_b", CF_AD9361_TX_DMA_1_BASEADDR,
#ifdef DMA_IRQ_ENABLE
	IRQ_ENABLED
#else
	IRQ_DISABLED
#endif
};
struct axi_dmac *tx_dmac_phy_b;

AD9361_InitParam init_param_phy_b = {
	/* Device selection */
	ID_AD9361,	// dev_sel
	/* Reference Clock */
	40000000UL,	//reference_clk_rate
	/* Base Configuration */
	1,		//two_rx_two_tx_mode_enable *** adi,2rx-2tx-mode-enable
	1,		//one_rx_one_tx_mode_use_rx_num *** adi,1rx-1tx-mode-use-rx-num
	2,		//one_rx_one_tx_mode_use_tx_num *** adi,1rx-1tx-mode-use-tx-num
	1,		//frequency_division_duplex_mode_enable *** adi,frequency-division-duplex-mode-enable
	0,		//frequency_division_duplex_independent_mode_enable *** adi,frequency-division-duplex-independent-mode-enable
	0,		//tdd_use_dual_synth_mode_enable *** adi,tdd-use-dual-synth-mode-enable
	0,		//tdd_skip_vco_cal_enable *** adi,tdd-skip-vco-cal-enable
	0,		//tx_fastlock_delay_ns *** adi,tx-fastlock-delay-ns
	0,		//rx_fastlock_delay_ns *** adi,rx-fastlock-delay-ns
	0,		//rx_fastlock_pincontrol_enable *** adi,rx-fastlock-pincontrol-enable
	0,		//tx_fastlock_pincontrol_enable *** adi,tx-fastlock-pincontrol-enable
	0,		//external_rx_lo_enable *** adi,external-rx-lo-enable
	0,		//external_tx_lo_enable *** adi,external-tx-lo-enable
	5,		//dc_offset_tracking_update_event_mask *** adi,dc-offset-tracking-update-event-mask
	6,		//dc_offset_attenuation_high_range *** adi,dc-offset-attenuation-high-range
	5,		//dc_offset_attenuation_low_range *** adi,dc-offset-attenuation-low-range
	0x28,	//dc_offset_count_high_range *** adi,dc-offset-count-high-range
	0x32,	//dc_offset_count_low_range *** adi,dc-offset-count-low-range
	0,		//split_gain_table_mode_enable *** adi,split-gain-table-mode-enable
	MAX_SYNTH_FREF,	//trx_synthesizer_target_fref_overwrite_hz *** adi,trx-synthesizer-target-fref-overwrite-hz
	0,		// qec_tracking_slow_mode_enable *** adi,qec-tracking-slow-mode-enable
	/* ENSM Control */
	0,		//ensm_enable_pin_pulse_mode_enable *** adi,ensm-enable-pin-pulse-mode-enable
	0,		//ensm_enable_txnrx_control_enable *** adi,ensm-enable-txnrx-control-enable
	/* LO Control */
	1090000000UL,	//rx_synthesizer_frequency_hz *** adi,rx-synthesizer-frequency-hz
	2400000000UL,	//tx_synthesizer_frequency_hz *** adi,tx-synthesizer-frequency-hz
	1,				//tx_lo_powerdown_managed_enable *** adi,tx-lo-powerdown-managed-enable
	/* Rate & BW Control */
	{983040000, 245760000, 122880000, 61440000, 30720000, 30720000},// rx_path_clock_frequencies[6] *** adi,rx-path-clock-frequencies
	{983040000, 122880000, 122880000, 61440000, 30720000, 30720000},// tx_path_clock_frequencies[6] *** adi,tx-path-clock-frequencies
	18000000,//rf_rx_bandwidth_hz *** adi,rf-rx-bandwidth-hz
	18000000,//rf_tx_bandwidth_hz *** adi,rf-tx-bandwidth-hz
	/* RF Port Control */
	0,		//rx_rf_port_input_select *** adi,rx-rf-port-input-select
	0,		//tx_rf_port_input_select *** adi,tx-rf-port-input-select
	/* TX Attenuation Control */
	10000,	//tx_attenuation_mdB *** adi,tx-attenuation-mdB
	0,		//update_tx_gain_in_alert_enable *** adi,update-tx-gain-in-alert-enable
	/* Reference Clock Control */
	1,		//xo_disable_use_ext_refclk_enable *** adi,xo-disable-use-ext-refclk-enable
	{8, 5920},	//dcxo_coarse_and_fine_tune[2] *** adi,dcxo-coarse-and-fine-tune
	CLKOUT_DISABLE,	//clk_output_mode_select *** adi,clk-output-mode-select
	/* Gain Control */
	0,		//gc_rx1_mode *** adi,gc-rx1-mode
	0,		//gc_rx2_mode *** adi,gc-rx2-mode
	58,		//gc_adc_large_overload_thresh *** adi,gc-adc-large-overload-thresh
	4,		//gc_adc_ovr_sample_size *** adi,gc-adc-ovr-sample-size
	47,		//gc_adc_small_overload_thresh *** adi,gc-adc-small-overload-thresh
	8192,	//gc_dec_pow_measurement_duration *** adi,gc-dec-pow-measurement-duration
	0,		//gc_dig_gain_enable *** adi,gc-dig-gain-enable
	800,	//gc_lmt_overload_high_thresh *** adi,gc-lmt-overload-high-thresh
	704,	//gc_lmt_overload_low_thresh *** adi,gc-lmt-overload-low-thresh
	24,		//gc_low_power_thresh *** adi,gc-low-power-thresh
	15,		//gc_max_dig_gain *** adi,gc-max-dig-gain
	0,		//gc_use_rx_fir_out_for_dec_pwr_meas_enable *** adi,gc-use-rx-fir-out-for-dec-pwr-meas-enable
	/* Gain MGC Control */
	2,		//mgc_dec_gain_step *** adi,mgc-dec-gain-step
	2,		//mgc_inc_gain_step *** adi,mgc-inc-gain-step
	0,		//mgc_rx1_ctrl_inp_enable *** adi,mgc-rx1-ctrl-inp-enable
	0,		//mgc_rx2_ctrl_inp_enable *** adi,mgc-rx2-ctrl-inp-enable
	0,		//mgc_split_table_ctrl_inp_gain_mode *** adi,mgc-split-table-ctrl-inp-gain-mode
	/* Gain AGC Control */
	10,		//agc_adc_large_overload_exceed_counter *** adi,agc-adc-large-overload-exceed-counter
	2,		//agc_adc_large_overload_inc_steps *** adi,agc-adc-large-overload-inc-steps
	0,		//agc_adc_lmt_small_overload_prevent_gain_inc_enable *** adi,agc-adc-lmt-small-overload-prevent-gain-inc-enable
	10,		//agc_adc_small_overload_exceed_counter *** adi,agc-adc-small-overload-exceed-counter
	4,		//agc_dig_gain_step_size *** adi,agc-dig-gain-step-size
	3,		//agc_dig_saturation_exceed_counter *** adi,agc-dig-saturation-exceed-counter
	1000,	// agc_gain_update_interval_us *** adi,agc-gain-update-interval-us
	0,		//agc_immed_gain_change_if_large_adc_overload_enable *** adi,agc-immed-gain-change-if-large-adc-overload-enable
	0,		//agc_immed_gain_change_if_large_lmt_overload_enable *** adi,agc-immed-gain-change-if-large-lmt-overload-enable
	10,		//agc_inner_thresh_high *** adi,agc-inner-thresh-high
	1,		//agc_inner_thresh_high_dec_steps *** adi,agc-inner-thresh-high-dec-steps
	12,		//agc_inner_thresh_low *** adi,agc-inner-thresh-low
	1,		//agc_inner_thresh_low_inc_steps *** adi,agc-inner-thresh-low-inc-steps
	10,		//agc_lmt_overload_large_exceed_counter *** adi,agc-lmt-overload-large-exceed-counter
	2,		//agc_lmt_overload_large_inc_steps *** adi,agc-lmt-overload-large-inc-steps
	10,		//agc_lmt_overload_small_exceed_counter *** adi,agc-lmt-overload-small-exceed-counter
	5,		//agc_outer_thresh_high *** adi,agc-outer-thresh-high
	2,		//agc_outer_thresh_high_dec_steps *** adi,agc-outer-thresh-high-dec-steps
	18,		//agc_outer_thresh_low *** adi,agc-outer-thresh-low
	2,		//agc_outer_thresh_low_inc_steps *** adi,agc-outer-thresh-low-inc-steps
	1,		//agc_attack_delay_extra_margin_us; *** adi,agc-attack-delay-extra-margin-us
	0,		//agc_sync_for_gain_counter_enable *** adi,agc-sync-for-gain-counter-enable
	/* Fast AGC */
	64,		//fagc_dec_pow_measuremnt_duration ***  adi,fagc-dec-pow-measurement-duration
	260,	//fagc_state_wait_time_ns ***  adi,fagc-state-wait-time-ns
	/* Fast AGC - Low Power */
	0,		//fagc_allow_agc_gain_increase ***  adi,fagc-allow-agc-gain-increase-enable
	5,		//fagc_lp_thresh_increment_time ***  adi,fagc-lp-thresh-increment-time
	1,		//fagc_lp_thresh_increment_steps ***  adi,fagc-lp-thresh-increment-steps
	/* Fast AGC - Lock Level (Lock Level is set via slow AGC inner high threshold) */
	1,		//fagc_lock_level_lmt_gain_increase_en ***  adi,fagc-lock-level-lmt-gain-increase-enable
	5,		//fagc_lock_level_gain_increase_upper_limit ***  adi,fagc-lock-level-gain-increase-upper-limit
	/* Fast AGC - Peak Detectors and Final Settling */
	1,		//fagc_lpf_final_settling_steps ***  adi,fagc-lpf-final-settling-steps
	1,		//fagc_lmt_final_settling_steps ***  adi,fagc-lmt-final-settling-steps
	3,		//fagc_final_overrange_count ***  adi,fagc-final-overrange-count
	/* Fast AGC - Final Power Test */
	0,		//fagc_gain_increase_after_gain_lock_en ***  adi,fagc-gain-increase-after-gain-lock-enable
	/* Fast AGC - Unlocking the Gain */
	0,		//fagc_gain_index_type_after_exit_rx_mode ***  adi,fagc-gain-index-type-after-exit-rx-mode
	1,		//fagc_use_last_lock_level_for_set_gain_en ***  adi,fagc-use-last-lock-level-for-set-gain-enable
	1,		//fagc_rst_gla_stronger_sig_thresh_exceeded_en ***  adi,fagc-rst-gla-stronger-sig-thresh-exceeded-enable
	5,		//fagc_optimized_gain_offset ***  adi,fagc-optimized-gain-offset
	10,		//fagc_rst_gla_stronger_sig_thresh_above_ll ***  adi,fagc-rst-gla-stronger-sig-thresh-above-ll
	1,		//fagc_rst_gla_engergy_lost_sig_thresh_exceeded_en ***  adi,fagc-rst-gla-engergy-lost-sig-thresh-exceeded-enable
	1,		//fagc_rst_gla_engergy_lost_goto_optim_gain_en ***  adi,fagc-rst-gla-engergy-lost-goto-optim-gain-enable
	10,		//fagc_rst_gla_engergy_lost_sig_thresh_below_ll ***  adi,fagc-rst-gla-engergy-lost-sig-thresh-below-ll
	8,		//fagc_energy_lost_stronger_sig_gain_lock_exit_cnt ***  adi,fagc-energy-lost-stronger-sig-gain-lock-exit-cnt
	1,		//fagc_rst_gla_large_adc_overload_en ***  adi,fagc-rst-gla-large-adc-overload-enable
	1,		//fagc_rst_gla_large_lmt_overload_en ***  adi,fagc-rst-gla-large-lmt-overload-enable
	0,		//fagc_rst_gla_en_agc_pulled_high_en ***  adi,fagc-rst-gla-en-agc-pulled-high-enable
	0,		//fagc_rst_gla_if_en_agc_pulled_high_mode ***  adi,fagc-rst-gla-if-en-agc-pulled-high-mode
	64,		//fagc_power_measurement_duration_in_state5 ***  adi,fagc-power-measurement-duration-in-state5
	2,		//fagc_large_overload_inc_steps *** adi,fagc-adc-large-overload-inc-steps
	/* RSSI Control */
	1,		//rssi_delay *** adi,rssi-delay
	1000,	//rssi_duration *** adi,rssi-duration
	3,		//rssi_restart_mode *** adi,rssi-restart-mode
	0,		//rssi_unit_is_rx_samples_enable *** adi,rssi-unit-is-rx-samples-enable
	1,		//rssi_wait *** adi,rssi-wait
	/* Aux ADC Control */
	256,	//aux_adc_decimation *** adi,aux-adc-decimation
	40000000UL,	//aux_adc_rate *** adi,aux-adc-rate
	/* AuxDAC Control */
	1,		//aux_dac_manual_mode_enable ***  adi,aux-dac-manual-mode-enable
	0,		//aux_dac1_default_value_mV ***  adi,aux-dac1-default-value-mV
	0,		//aux_dac1_active_in_rx_enable ***  adi,aux-dac1-active-in-rx-enable
	0,		//aux_dac1_active_in_tx_enable ***  adi,aux-dac1-active-in-tx-enable
	0,		//aux_dac1_active_in_alert_enable ***  adi,aux-dac1-active-in-alert-enable
	0,		//aux_dac1_rx_delay_us ***  adi,aux-dac1-rx-delay-us
	0,		//aux_dac1_tx_delay_us ***  adi,aux-dac1-tx-delay-us
	0,		//aux_dac2_default_value_mV ***  adi,aux-dac2-default-value-mV
	0,		//aux_dac2_active_in_rx_enable ***  adi,aux-dac2-active-in-rx-enable
	0,		//aux_dac2_active_in_tx_enable ***  adi,aux-dac2-active-in-tx-enable
	0,		//aux_dac2_active_in_alert_enable ***  adi,aux-dac2-active-in-alert-enable
	0,		//aux_dac2_rx_delay_us ***  adi,aux-dac2-rx-delay-us
	0,		//aux_dac2_tx_delay_us ***  adi,aux-dac2-tx-delay-us
	/* Temperature Sensor Control */
	256,	//temp_sense_decimation *** adi,temp-sense-decimation
	1000,	//temp_sense_measurement_interval_ms *** adi,temp-sense-measurement-interval-ms
	0xCE,	//temp_sense_offset_signed *** adi,temp-sense-offset-signed
	1,		//temp_sense_periodic_measurement_enable *** adi,temp-sense-periodic-measurement-enable
	/* Control Out Setup */
	0xFF,	//ctrl_outs_enable_mask *** adi,ctrl-outs-enable-mask
	0,		//ctrl_outs_index *** adi,ctrl-outs-index
	/* External LNA Control */
	0,		//elna_settling_delay_ns *** adi,elna-settling-delay-ns
	0,		//elna_gain_mdB *** adi,elna-gain-mdB
	0,		//elna_bypass_loss_mdB *** adi,elna-bypass-loss-mdB
	0,		//elna_rx1_gpo0_control_enable *** adi,elna-rx1-gpo0-control-enable
	0,		//elna_rx2_gpo1_control_enable *** adi,elna-rx2-gpo1-control-enable
	0,		//elna_gaintable_all_index_enable *** adi,elna-gaintable-all-index-enable
	/* Digital Interface Control */
	0,		//digital_interface_tune_skip_mode *** adi,digital-interface-tune-skip-mode
	0,		//digital_interface_tune_fir_disable *** adi,digital-interface-tune-fir-disable
	1,		//pp_tx_swap_enable *** adi,pp-tx-swap-enable
	1,		//pp_rx_swap_enable *** adi,pp-rx-swap-enable
	0,		//tx_channel_swap_enable *** adi,tx-channel-swap-enable
	0,		//rx_channel_swap_enable *** adi,rx-channel-swap-enable
	1,		//rx_frame_pulse_mode_enable *** adi,rx-frame-pulse-mode-enable
	0,		//two_t_two_r_timing_enable *** adi,2t2r-timing-enable
	0,		//invert_data_bus_enable *** adi,invert-data-bus-enable
	0,		//invert_data_clk_enable *** adi,invert-data-clk-enable
	0,		//fdd_alt_word_order_enable *** adi,fdd-alt-word-order-enable
	0,		//invert_rx_frame_enable *** adi,invert-rx-frame-enable
	0,		//fdd_rx_rate_2tx_enable *** adi,fdd-rx-rate-2tx-enable
	0,		//swap_ports_enable *** adi,swap-ports-enable
	0,		//single_data_rate_enable *** adi,single-data-rate-enable
	1,		//lvds_mode_enable *** adi,lvds-mode-enable
	0,		//half_duplex_mode_enable *** adi,half-duplex-mode-enable
	0,		//single_port_mode_enable *** adi,single-port-mode-enable
	1,		//full_port_enable *** adi,full-port-enable
	0,		//full_duplex_swap_bits_enable *** adi,full-duplex-swap-bits-enable
	0,		//delay_rx_data *** adi,delay-rx-data
	0,		//rx_data_clock_delay *** adi,rx-data-clock-delay
	2,		//rx_data_delay *** adi,rx-data-delay
	7,		//tx_fb_clock_delay *** adi,tx-fb-clock-delay
	0,		//tx_data_delay *** adi,tx-data-delay
#ifdef ALTERA_PLATFORM
	300,	//lvds_bias_mV *** adi,lvds-bias-mV
#else
	150,	//lvds_bias_mV *** adi,lvds-bias-mV
#endif
	1,		//lvds_rx_onchip_termination_enable *** adi,lvds-rx-onchip-termination-enable
	1,		//rx1rx2_phase_inversion_en *** adi,rx1-rx2-phase-inversion-enable
	0xFF,	//lvds_invert1_control *** adi,lvds-invert1-control
	0x0F,	//lvds_invert2_control *** adi,lvds-invert2-control
	/* GPO Control */
	0,		//gpo_manual_mode_enable *** adi,gpo-manual-mode-enable
	0,		//gpo_manual_mode_enable_mask *** adi,gpo-manual-mode-enable-mask
	0,		//gpo0_inactive_state_high_enable *** adi,gpo0-inactive-state-high-enable
	0,		//gpo1_inactive_state_high_enable *** adi,gpo1-inactive-state-high-enable
	0,		//gpo2_inactive_state_high_enable *** adi,gpo2-inactive-state-high-enable
	0,		//gpo3_inactive_state_high_enable *** adi,gpo3-inactive-state-high-enable
	0,		//gpo0_slave_rx_enable *** adi,gpo0-slave-rx-enable
	0,		//gpo0_slave_tx_enable *** adi,gpo0-slave-tx-enable
	0,		//gpo1_slave_rx_enable *** adi,gpo1-slave-rx-enable
	0,		//gpo1_slave_tx_enable *** adi,gpo1-slave-tx-enable
	0,		//gpo2_slave_rx_enable *** adi,gpo2-slave-rx-enable
	0,		//gpo2_slave_tx_enable *** adi,gpo2-slave-tx-enable
	0,		//gpo3_slave_rx_enable *** adi,gpo3-slave-rx-enable
	0,		//gpo3_slave_tx_enable *** adi,gpo3-slave-tx-enable
	0,		//gpo0_rx_delay_us *** adi,gpo0-rx-delay-us
	0,		//gpo0_tx_delay_us *** adi,gpo0-tx-delay-us
	0,		//gpo1_rx_delay_us *** adi,gpo1-rx-delay-us
	0,		//gpo1_tx_delay_us *** adi,gpo1-tx-delay-us
	0,		//gpo2_rx_delay_us *** adi,gpo2-rx-delay-us
	0,		//gpo2_tx_delay_us *** adi,gpo2-tx-delay-us
	0,		//gpo3_rx_delay_us *** adi,gpo3-rx-delay-us
	0,		//gpo3_tx_delay_us *** adi,gpo3-tx-delay-us
	/* Tx Monitor Control */
	37000,	//low_high_gain_threshold_mdB *** adi,txmon-low-high-thresh
	0,		//low_gain_dB *** adi,txmon-low-gain
	24,		//high_gain_dB *** adi,txmon-high-gain
	0,		//tx_mon_track_en *** adi,txmon-dc-tracking-enable
	0,		//one_shot_mode_en *** adi,txmon-one-shot-mode-enable
	511,	//tx_mon_delay *** adi,txmon-delay
	8192,	//tx_mon_duration *** adi,txmon-duration
	2,		//tx1_mon_front_end_gain *** adi,txmon-1-front-end-gain
	2,		//tx2_mon_front_end_gain *** adi,txmon-2-front-end-gain
	48,		//tx1_mon_lo_cm *** adi,txmon-1-lo-cm
	48,		//tx2_mon_lo_cm *** adi,txmon-2-lo-cm
	/* GPIO definitions */
	{
		.number = -1,
		.platform_ops = GPIO_OPS,
		.extra = GPIO_PARAM_PHY_B
	},		//gpio_resetb *** reset-gpios
	/* MCS Sync */
	{
		.number = -1,
		.platform_ops = GPIO_OPS,
		.extra = GPIO_PARAM_PHY_B
	},		//gpio_sync *** sync-gpios

	{
		.number = -1,
		.platform_ops = GPIO_OPS,
		.extra = GPIO_PARAM_PHY_B
	},		//gpio_cal_sw1 *** cal-sw1-gpios

	{
		.number = -1,
		.platform_ops = GPIO_OPS,
		.extra = GPIO_PARAM_PHY_B
	},		//gpio_cal_sw2 *** cal-sw2-gpios

	{
		.device_id = SPI_DEVICE_ID_1,
		.mode = NO_OS_SPI_MODE_1,
		.chip_select = SPI_CS,
		.platform_ops = SPI_OPS,
		.extra = SPI_PARAM_PHY_B
	},

	/* External LO clocks */
	NULL,	//(*ad9361_rfpll_ext_recalc_rate)()
	NULL,	//(*ad9361_rfpll_ext_round_rate)()
	NULL,	//(*ad9361_rfpll_ext_set_rate)()
#ifndef AXI_ADC_NOT_PRESENT
	&rx_adc_init_phy_b,	// *rx_adc_init
	&tx_dac_init_phy_b,   // *tx_dac_init
#endif
};




AD9361_RXFIRConfig rx_fir_config_phy_a = {	// BPF PASSBAND 3/20 fs to 1/4 fs
	3, // rx
	0, // rx_gain
	1, // rx_dec
	{
		-4, -6, -37, 35, 186, 86, -284, -315,
			107, 219, -4, 271, 558, -307, -1182, -356,
			658, 157, 207, 1648, 790, -2525, -2553, 748,
			865, -476, 3737, 6560, -3583, -14731, -5278, 14819,
			14819, -5278, -14731, -3583, 6560, 3737, -476, 865,
			748, -2553, -2525, 790, 1648, 207, 157, 658,
			-356, -1182, -307, 558, 271, -4, 219, 107,
			-315, -284, 86, 186, 35, -37, -6, -4,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0
		}, // rx_coef[128]
	64, // rx_coef_size
	{0, 0, 0, 0, 0, 0}, //rx_path_clks[6]
	0 // rx_bandwidth
};

AD9361_TXFIRConfig tx_fir_config_phy_a = {	// BPF PASSBAND 3/20 fs to 1/4 fs
	3, // tx
	-6, // tx_gain
	1, // tx_int
	{
		-4, -6, -37, 35, 186, 86, -284, -315,
			107, 219, -4, 271, 558, -307, -1182, -356,
			658, 157, 207, 1648, 790, -2525, -2553, 748,
			865, -476, 3737, 6560, -3583, -14731, -5278, 14819,
			14819, -5278, -14731, -3583, 6560, 3737, -476, 865,
			748, -2553, -2525, 790, 1648, 207, 157, 658,
			-356, -1182, -307, 558, 271, -4, 219, 107,
			-315, -284, 86, 186, 35, -37, -6, -4,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0
		}, // tx_coef[128]
	64, // tx_coef_size
	{0, 0, 0, 0, 0, 0}, // tx_path_clks[6]
	0 // tx_bandwidth
};



AD9361_RXFIRConfig rx_fir_config_phy_b = {	// BPF PASSBAND 3/20 fs to 1/4 fs
	3, // rx
	0, // rx_gain
	1, // rx_dec
	{
		-4, -6, -37, 35, 186, 86, -284, -315,
			107, 219, -4, 271, 558, -307, -1182, -356,
			658, 157, 207, 1648, 790, -2525, -2553, 748,
			865, -476, 3737, 6560, -3583, -14731, -5278, 14819,
			14819, -5278, -14731, -3583, 6560, 3737, -476, 865,
			748, -2553, -2525, 790, 1648, 207, 157, 658,
			-356, -1182, -307, 558, 271, -4, 219, 107,
			-315, -284, 86, 186, 35, -37, -6, -4,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0
		}, // rx_coef[128]
	64, // rx_coef_size
	{0, 0, 0, 0, 0, 0}, //rx_path_clks[6]
	0 // rx_bandwidth
};

AD9361_TXFIRConfig tx_fir_config_phy_b = {	// BPF PASSBAND 3/20 fs to 1/4 fs
	3, // tx
	-6, // tx_gain
	1, // tx_int
	{
		-4, -6, -37, 35, 186, 86, -284, -315,
			107, 219, -4, 271, 558, -307, -1182, -356,
			658, 157, 207, 1648, 790, -2525, -2553, 748,
			865, -476, 3737, 6560, -3583, -14731, -5278, 14819,
			14819, -5278, -14731, -3583, 6560, 3737, -476, 865,
			748, -2553, -2525, 790, 1648, 207, 157, 658,
			-356, -1182, -307, 558, 271, -4, 219, 107,
			-315, -284, 86, 186, 35, -37, -6, -4,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0
		}, // tx_coef[128]
	64, // tx_coef_size
	{0, 0, 0, 0, 0, 0}, // tx_path_clks[6]
	0 // tx_bandwidth
};



struct ad9361_rf_phy *ad9361_phy;
#ifdef FMCOMMS5
struct ad9361_rf_phy *ad9361_phy_b;
#endif


/***************************************************************************//**
 * @brief main
*******************************************************************************/
int main(void)
{
	int32_t status;
#ifdef XILINX_PLATFORM
	Xil_ICacheEnable();
	Xil_DCacheEnable();
	init_param_phy_a.spi_param.extra = &xil_spi_param_phy_a;
	init_param_phy_a.spi_param.platform_ops = &xil_spi_ops;
#endif


	// NOTE: The user has to choose the GPIO numbers according to desired
	// carrier board.
	init_param_phy_a.gpio_resetb.number = GPIO_RESET_PIN;

#ifdef FMCOMMS5
//	init_param_phy_a.gpio_sync.number = GPIO_SYNC_PIN;
//	default_init_param.gpio_cal_sw1.number = GPIO_CAL_SW1_PIN;
//	default_init_param.gpio_cal_sw2.number = GPIO_CAL_SW2_PIN;

#else
	default_init_param.gpio_sync.number = -1;
	default_init_param.gpio_cal_sw1.number = -1;
	default_init_param.gpio_cal_sw2.number = -1;
#endif

	if (AD9364_DEVICE)
		init_param_phy_a.dev_sel = ID_AD9364;
	if (AD9363A_DEVICE)
		init_param_phy_a.dev_sel = ID_AD9363A;



//	//0,6 is a good pair
//	default_init_param.rx_data_clock_delay = 0;
//	default_init_param.rx_data_delay = 6;


	uint8_t rx_reg = 0;
	uint8_t rx_delay = 0;



	ad9361_init(&ad9361_phy, &init_param_phy_a);




	status = axi_dmac_init(&tx_dmac_phy_a, &tx_dmac_init_phy_a);
	if (status < 0) {printf("axi_dmac_init tx a init error: %"PRIi32"\n", status); return status;}
	status = axi_dmac_init(&rx_dmac_phy_a, &rx_dmac_init_phy_a);
	if (status < 0) {printf("axi_dmac_init rx a init error: %"PRIi32"\n", status); return status;}

	rx_reg = ad9361_spi_read(ad9361_phy->spi, 0x006); // RX Data/Clk Delay
	printf("Hardware RX Register (0x006) after phy init: 0x%02X\n", rx_reg);

	rx_delay = ad9361_phy->pdata->port_ctrl.rx_clk_data_delay;
	printf("RX Clock Delay after phy init: %d\n", rx_delay);


	ad9361_set_tx_fir_config(ad9361_phy, tx_fir_config_phy_a);
	ad9361_set_rx_fir_config(ad9361_phy, rx_fir_config_phy_a);


	int gain_db = 20;  // rx1 gain
	int gain_db1 = 20; // rx2 gain
	status = ad9361_set_rx_rf_gain(ad9361_phy, 0, gain_db);
	if(status < 0){printf("Failed to set rx1_rf_gain with error code : %d\n", status);} usleep(2000);
	status = ad9361_set_rx_rf_gain(ad9361_phy, 1, gain_db1);
	if(status < 0){printf("Failed to set rx2_rf_gain with error code : %d\n", status);} usleep(2000);

	ad9361_do_calib(ad9361_phy, RF_DC_CAL, 0);
	ad9361_do_calib(ad9361_phy, RX_QUAD_CAL, 0);
	ad9361_do_calib(ad9361_phy, TX_QUAD_CAL, 0);

	status = ad9361_mcs(ad9361_phy, 0);
	if(status < 0){printf("Failed to do mcs with error code : %d\n", status);} usleep(2000);

	ad9361_tx_mute(ad9361_phy, 0);


	no_os_mdelay(200);

#ifdef FMCOMMS5

	init_param_phy_b.spi_param.extra = &xil_spi_param_phy_b;
	init_param_phy_b.spi_param.platform_ops = &xil_spi_ops;


	init_param_phy_b.gpio_resetb.number = GPIO_RESET_PIN_2;
	init_param_phy_b.gpio_sync.number = -1;
	init_param_phy_b.gpio_cal_sw1.number = -1;
	init_param_phy_b.gpio_cal_sw2.number = -1;


//	//4,0 was a good pair
//	default_init_param.rx_data_clock_delay = 0;
//	default_init_param.rx_data_delay = 2;


	ad9361_init(&ad9361_phy_b, &init_param_phy_b);
	status = axi_dmac_init(&tx_dmac_phy_b, &tx_dmac_init_phy_b);
	if (status < 0) {printf("axi_dmac_init tx b init error: %"PRIi32"\n", status); return status;}
	status = axi_dmac_init(&rx_dmac_phy_b, &rx_dmac_init_phy_b);
	if (status < 0) {printf("axi_dmac_init rx b init error: %"PRIi32"\n", status); return status;}



	rx_reg = ad9361_spi_read(ad9361_phy_b->spi, 0x006); // RX Data/Clk Delay
	printf("Hardware RX Register (0x006) after phy_b init: 0x%02X\n", rx_reg);
	rx_delay = ad9361_phy_b->pdata->port_ctrl.rx_clk_data_delay;
	printf("RX Clock Delay after phy_b init: %d\n", rx_delay);



	ad9361_set_tx_fir_config(ad9361_phy_b, tx_fir_config_phy_b);
	ad9361_set_rx_fir_config(ad9361_phy_b, rx_fir_config_phy_b);



	status = ad9361_set_rx_rf_gain(ad9361_phy_b, 0, gain_db);
	if(status < 0){printf("Failed to set rx1_rf_gain phy_b with error code : %d\n", status);} usleep(2000);
	status = ad9361_set_rx_rf_gain(ad9361_phy_b, 1, gain_db1);
	if(status < 0){printf("Failed to set rx2_rf_gain phy_b with error code : %d\n", status);} usleep(2000);

	ad9361_do_calib(ad9361_phy_b, RF_DC_CAL, 0);
	ad9361_do_calib(ad9361_phy_b, RX_QUAD_CAL, 0);
	ad9361_do_calib(ad9361_phy_b, TX_QUAD_CAL, 0);

	status = ad9361_mcs(ad9361_phy_b, 0);
	if(status < 0){printf("Failed to do mcs phy_b with error code : %d\n", status);} usleep(2000);

	ad9361_tx_mute(ad9361_phy_b, 0);


//	ad9361_dig_tune(ad9361_phy, 61440000, BE_MOREVERBOSE);
//	ad9361_dig_tune(ad9361_phy_b, 61440000, BE_MOREVERBOSE);
//
//
//  status = ad9361_bist_tone(ad9361_phy, BIST_INJ_RX, 0x02, 15, 0x00);
//	status = ad9361_bist_tone(ad9361_phy_b, BIST_INJ_RX, 0x02, 15, 0x00);







#endif









#ifdef FMCOMMS5
//	int32_t status_mcs;
//	status_mcs = ad9361_do_mcs(ad9361_phy, ad9361_phy_b);
//	printf("Status of multi-chip sync: %" PRId32 "\n", status_mcs);
//
//	ad9361_dig_tune(ad9361_phy, 61440000, BE_MOREVERBOSE);
//	ad9361_dig_tune(ad9361_phy_b, 61440000, BE_MOREVERBOSE);
//
//	ad9361_bist_tone(ad9361_phy, BIST_INJ_RX, 0x02, 15, 0x00);
//	ad9361_bist_tone(ad9361_phy_b, BIST_INJ_RX, 0x02, 15, 0x00);
#endif





	printf("Done.\n");
	while(1){}






#ifdef XILINX_PLATFORM
	Xil_DCacheDisable();
	Xil_ICacheDisable();
#endif


	return 0;
}

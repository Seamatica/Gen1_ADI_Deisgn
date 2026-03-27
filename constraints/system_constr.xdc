# constraints
set_property -dict {PACKAGE_PIN AE22 IOSTANDARD LVDS_25} [get_ports ref_clk_p]
set_property -dict {PACKAGE_PIN AF22 IOSTANDARD LVDS_25} [get_ports ref_clk_n]


# ad9361 0
set_property -dict {PACKAGE_PIN AF14 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports rx_clk_in_0_p]
set_property -dict {PACKAGE_PIN AG14 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports rx_clk_in_0_n]
set_property -dict {PACKAGE_PIN AA15 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports rx_frame_in_0_p]
set_property -dict {PACKAGE_PIN AA14 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports rx_frame_in_0_n]

set_property -dict {PACKAGE_PIN AB12 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_0_p[0]}]
set_property -dict {PACKAGE_PIN AC12 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_0_n[0]}]
set_property -dict {PACKAGE_PIN AC14 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_0_p[1]}]
set_property -dict {PACKAGE_PIN AC13 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_0_n[1]}]
set_property -dict {PACKAGE_PIN AD16 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_0_p[2]}]
set_property -dict {PACKAGE_PIN AD15 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_0_n[2]}]
set_property -dict {PACKAGE_PIN AE16 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_0_p[3]}]
set_property -dict {PACKAGE_PIN AE15 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_0_n[3]}]
set_property -dict {PACKAGE_PIN AE18 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_0_p[4]}]
set_property -dict {PACKAGE_PIN AE17 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_0_n[4]}]
set_property -dict {PACKAGE_PIN AF18 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_0_p[5]}]
set_property -dict {PACKAGE_PIN AF17 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_0_n[5]}]

set_property -dict {PACKAGE_PIN AG17 IOSTANDARD LVDS_25} [get_ports tx_clk_out_0_p]
set_property -dict {PACKAGE_PIN AG16 IOSTANDARD LVDS_25} [get_ports tx_clk_out_0_n]
set_property -dict {PACKAGE_PIN AH17 IOSTANDARD LVDS_25} [get_ports tx_frame_out_0_p]
set_property -dict {PACKAGE_PIN AH16 IOSTANDARD LVDS_25} [get_ports tx_frame_out_0_n]
set_property -dict {PACKAGE_PIN AJ14 IOSTANDARD LVDS_25} [get_ports {tx_data_out_0_p[0]}]
set_property -dict {PACKAGE_PIN AJ13 IOSTANDARD LVDS_25} [get_ports {tx_data_out_0_n[0]}]
set_property -dict {PACKAGE_PIN AK13 IOSTANDARD LVDS_25} [get_ports {tx_data_out_0_p[1]}]
set_property -dict {PACKAGE_PIN AK12 IOSTANDARD LVDS_25} [get_ports {tx_data_out_0_n[1]}]
set_property -dict {PACKAGE_PIN AJ15 IOSTANDARD LVDS_25} [get_ports {tx_data_out_0_p[2]}]
set_property -dict {PACKAGE_PIN AK15 IOSTANDARD LVDS_25} [get_ports {tx_data_out_0_n[2]}]
set_property -dict {PACKAGE_PIN AE12 IOSTANDARD LVDS_25} [get_ports {tx_data_out_0_p[3]}]
set_property -dict {PACKAGE_PIN AF12 IOSTANDARD LVDS_25} [get_ports {tx_data_out_0_n[3]}]
set_property -dict {PACKAGE_PIN AH18 IOSTANDARD LVDS_25} [get_ports {tx_data_out_0_p[4]}]
set_property -dict {PACKAGE_PIN AJ18 IOSTANDARD LVDS_25} [get_ports {tx_data_out_0_n[4]}]
set_property -dict {PACKAGE_PIN AJ16 IOSTANDARD LVDS_25} [get_ports {tx_data_out_0_p[5]}]
set_property -dict {PACKAGE_PIN AK16 IOSTANDARD LVDS_25} [get_ports {tx_data_out_0_n[5]}]


set_property -dict {PACKAGE_PIN AB22 IOSTANDARD LVCMOS33} [get_ports mcs_sync]
set_property -dict {PACKAGE_PIN AG19 IOSTANDARD LVCMOS33} [get_ports gpio_resetb_0]
set_property -dict {PACKAGE_PIN AB21 IOSTANDARD LVCMOS33} [get_ports enable_0]
set_property -dict {PACKAGE_PIN Y21 IOSTANDARD LVCMOS33} [get_ports gpio_en_agc_0]

set_property -dict {PACKAGE_PIN AJ20 IOSTANDARD LVCMOS33} [get_ports txnrx_0]

set_property -dict {PACKAGE_PIN AJ24 IOSTANDARD LVCMOS33} [get_ports {gpio_status_0[0]}]
set_property -dict {PACKAGE_PIN AK23 IOSTANDARD LVCMOS33} [get_ports {gpio_status_0[1]}]
set_property -dict {PACKAGE_PIN AJ23 IOSTANDARD LVCMOS33} [get_ports {gpio_status_0[2]}]
set_property -dict {PACKAGE_PIN AH24 IOSTANDARD LVCMOS33} [get_ports {gpio_status_0[3]}]
set_property -dict {PACKAGE_PIN AH23 IOSTANDARD LVCMOS33} [get_ports {gpio_status_0[4]}]
set_property -dict {PACKAGE_PIN AJ21 IOSTANDARD LVCMOS33} [get_ports {gpio_status_0[5]}]
set_property -dict {PACKAGE_PIN AK22 IOSTANDARD LVCMOS33} [get_ports {gpio_status_0[6]}]
set_property -dict {PACKAGE_PIN AK21 IOSTANDARD LVCMOS33} [get_ports {gpio_status_0[7]}]

set_property -dict {PACKAGE_PIN AD24 IOSTANDARD LVCMOS33} [get_ports {gpio_ctl_0[0]}]
set_property -dict {PACKAGE_PIN AF23 IOSTANDARD LVCMOS33} [get_ports {gpio_ctl_0[1]}]
set_property -dict {PACKAGE_PIN AK18 IOSTANDARD LVCMOS33} [get_ports {gpio_ctl_0[2]}]
set_property -dict {PACKAGE_PIN AG24 IOSTANDARD LVCMOS33} [get_ports {gpio_ctl_0[3]}]

# spi 0
set_property PACKAGE_PIN AK17 [get_ports spi_csn_0]
set_property IOSTANDARD LVCMOS33 [get_ports spi_csn_0]
set_property PULLUP true [get_ports spi_csn_0]
set_property -dict {PACKAGE_PIN AK20 IOSTANDARD LVCMOS33} [get_ports spi_clk_0]
set_property -dict {PACKAGE_PIN AH19 IOSTANDARD LVCMOS33} [get_ports spi_mosi_0]
set_property -dict {PACKAGE_PIN W21 IOSTANDARD LVCMOS33} [get_ports spi_miso_0]





# ad9361 1
set_property -dict {PACKAGE_PIN AC28 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports rx_clk_in_1_p]
set_property -dict {PACKAGE_PIN AD28 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports rx_clk_in_1_n]
set_property -dict {PACKAGE_PIN AE25 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports rx_frame_in_1_p]
set_property -dict {PACKAGE_PIN AF25 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports rx_frame_in_1_n]

set_property -dict {PACKAGE_PIN AJ30 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_1_p[0]}]
set_property -dict {PACKAGE_PIN AK30 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_1_n[0]}]
set_property -dict {PACKAGE_PIN AJ28 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_1_p[1]}]
set_property -dict {PACKAGE_PIN AJ29 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_1_n[1]}]
set_property -dict {PACKAGE_PIN AH28 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_1_p[2]}]
set_property -dict {PACKAGE_PIN AH29 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_1_n[2]}]
set_property -dict {PACKAGE_PIN AD30 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_1_p[3]}]
set_property -dict {PACKAGE_PIN AE30 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_1_n[3]}]
set_property -dict {PACKAGE_PIN AF30 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_1_p[4]}]
set_property -dict {PACKAGE_PIN AG30 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_1_n[4]}]
set_property -dict {PACKAGE_PIN AF29 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_1_p[5]}]
set_property -dict {PACKAGE_PIN AG29 IOSTANDARD LVDS_25 DIFF_TERM 1} [get_ports {rx_data_in_1_n[5]}]

set_property -dict {PACKAGE_PIN AE28 IOSTANDARD LVDS_25} [get_ports tx_clk_out_1_p]
set_property -dict {PACKAGE_PIN AF28 IOSTANDARD LVDS_25} [get_ports tx_clk_out_1_n]
set_property -dict {PACKAGE_PIN AC26 IOSTANDARD LVDS_25} [get_ports tx_frame_out_1_p]
set_property -dict {PACKAGE_PIN AD26 IOSTANDARD LVDS_25} [get_ports tx_frame_out_1_n]

set_property -dict {PACKAGE_PIN AB29 IOSTANDARD LVDS_25} [get_ports {tx_data_out_1_p[0]}]
set_property -dict {PACKAGE_PIN AB30 IOSTANDARD LVDS_25} [get_ports {tx_data_out_1_n[0]}]
set_property -dict {PACKAGE_PIN Y26 IOSTANDARD LVDS_25} [get_ports {tx_data_out_1_p[1]}]
set_property -dict {PACKAGE_PIN Y27 IOSTANDARD LVDS_25} [get_ports {tx_data_out_1_n[1]}]
set_property -dict {PACKAGE_PIN AA27 IOSTANDARD LVDS_25} [get_ports {tx_data_out_1_p[2]}]
set_property -dict {PACKAGE_PIN AA28 IOSTANDARD LVDS_25} [get_ports {tx_data_out_1_n[2]}]
set_property -dict {PACKAGE_PIN AB25 IOSTANDARD LVDS_25} [get_ports {tx_data_out_1_p[3]}]
set_property -dict {PACKAGE_PIN AB26 IOSTANDARD LVDS_25} [get_ports {tx_data_out_1_n[3]}]
set_property -dict {PACKAGE_PIN Y28 IOSTANDARD LVDS_25} [get_ports {tx_data_out_1_p[4]}]
set_property -dict {PACKAGE_PIN AA29 IOSTANDARD LVDS_25} [get_ports {tx_data_out_1_n[4]}]
set_property -dict {PACKAGE_PIN Y30 IOSTANDARD LVDS_25} [get_ports {tx_data_out_1_p[5]}]
set_property -dict {PACKAGE_PIN AA30 IOSTANDARD LVDS_25} [get_ports {tx_data_out_1_n[5]}]

set_property -dict {PACKAGE_PIN P25 IOSTANDARD LVCMOS33} [get_ports txnrx_1]
set_property -dict {PACKAGE_PIN T28 IOSTANDARD LVCMOS33} [get_ports gpio_resetb_1]
set_property -dict {PACKAGE_PIN N26 IOSTANDARD LVCMOS33} [get_ports enable_1]
set_property -dict {PACKAGE_PIN T24 IOSTANDARD LVCMOS33} [get_ports gpio_en_agc_1]

set_property -dict {PACKAGE_PIN P30 IOSTANDARD LVCMOS33} [get_ports {gpio_status_1[0]}]
set_property -dict {PACKAGE_PIN R30 IOSTANDARD LVCMOS33} [get_ports {gpio_status_1[1]}]
set_property -dict {PACKAGE_PIN T30 IOSTANDARD LVCMOS33} [get_ports {gpio_status_1[2]}]
set_property -dict {PACKAGE_PIN W29 IOSTANDARD LVCMOS33} [get_ports {gpio_status_1[3]}]
set_property -dict {PACKAGE_PIN W30 IOSTANDARD LVCMOS33} [get_ports {gpio_status_1[4]}]
set_property -dict {PACKAGE_PIN U30 IOSTANDARD LVCMOS33} [get_ports {gpio_status_1[5]}]
set_property -dict {PACKAGE_PIN V27 IOSTANDARD LVCMOS33} [get_ports {gpio_status_1[6]}]
set_property -dict {PACKAGE_PIN V29 IOSTANDARD LVCMOS33} [get_ports {gpio_status_1[7]}]

set_property -dict {PACKAGE_PIN N29 IOSTANDARD LVCMOS33} [get_ports {gpio_ctl_1[0]}]
set_property -dict {PACKAGE_PIN N28 IOSTANDARD LVCMOS33} [get_ports {gpio_ctl_1[1]}]
set_property -dict {PACKAGE_PIN P28 IOSTANDARD LVCMOS33} [get_ports {gpio_ctl_1[2]}]
set_property -dict {PACKAGE_PIN P29 IOSTANDARD LVCMOS33} [get_ports {gpio_ctl_1[3]}]


# spi 1
set_property PACKAGE_PIN T29 [get_ports spi_csn_1]
set_property IOSTANDARD LVCMOS33 [get_ports spi_csn_1]
set_property PULLUP true [get_ports spi_csn_1]
set_property -dict {PACKAGE_PIN R28 IOSTANDARD LVCMOS33} [get_ports spi_clk_1]
set_property -dict {PACKAGE_PIN N27 IOSTANDARD LVCMOS33} [get_ports spi_mosi_1]
set_property -dict {PACKAGE_PIN W28 IOSTANDARD LVCMOS33} [get_ports spi_miso_1]



## gpio bd
## gps m8n
#set_property -dict {PACKAGE_PIN V23  IOSTANDARD LVCMOS33} [get_ports rxd_uart_out]
#set_property -dict {PACKAGE_PIN U24  IOSTANDARD LVCMOS33} [get_ports txd_uart_in]
#set_property -dict {PACKAGE_PIN U22  IOSTANDARD LVCMOS33} [get_ports gps_pps]
#set_property -dict {PACKAGE_PIN V24  IOSTANDARD LVCMOS33} [get_ports pps_led]
## dac 5311
#set_property -dict {PACKAGE_PIN W23  IOSTANDARD LVCMOS33} [get_ports CLK_DAC_SDI]
#set_property -dict {PACKAGE_PIN AJ25 IOSTANDARD LVCMOS33} [get_ports CLK_DAC_CS]
#set_property -dict {PACKAGE_PIN AK25 IOSTANDARD LVCMOS33} [get_ports CLK_DAC_SCLK]
## LED
#set_property -dict {PACKAGE_PIN AA22 IOSTANDARD LVCMOS33} [get_ports pl_led[0]]
#set_property -dict {PACKAGE_PIN AA23 IOSTANDARD LVCMOS33} [get_ports pl_led[1]]



# clocks
create_clock -period 4.000 -name rx_0_clk [get_ports rx_clk_in_0_p]
create_clock -period 4.000 -name rx_1_clk [get_ports rx_clk_in_1_p]
#create_clock -period 4.000 -name ref_clk [get_ports ref_clk_p]
#create_clock -period 25.000 -name ref_clk [get_ports ref_clk_n]

set_clock_groups -asynchronous -group [get_clocks rx_0_clk] -group [get_clocks rx_1_clk]


## Identify the clocks coming out of your two Clocking Wizards
#set mmcm0_clk [get_clocks -of_objects [get_pins -hier -filter {NAME =~ *clk_wiz_0/inst/mmcm_adv_inst/CLKOUT0}]]
#set mmcm1_clk [get_clocks -of_objects [get_pins -hier -filter {NAME =~ *clk_wiz_1/inst/mmcm_adv_inst/CLKOUT0}]]

## Isolate the two SDR interface domains from each other and all Zynq PS clocks
#set_clock_groups -asynchronous \
#    -group [get_clocks $mmcm0_clk] \
#    -group [get_clocks $mmcm1_clk] \
#    -group [get_clocks clk_fpga_0] \
#    -group [get_clocks clk_fpga_1] \
#    -group [get_clocks clk_fpga_2] \
#    -group [get_clocks clk_fpga_3]





create_debug_core u_ila_0 ila
set_property ALL_PROBE_SAME_MU true [get_debug_cores u_ila_0]
set_property ALL_PROBE_SAME_MU_CNT 2 [get_debug_cores u_ila_0]
set_property C_ADV_TRIGGER false [get_debug_cores u_ila_0]
set_property C_DATA_DEPTH 16384 [get_debug_cores u_ila_0]
set_property C_EN_STRG_QUAL true [get_debug_cores u_ila_0]
set_property C_INPUT_PIPE_STAGES 0 [get_debug_cores u_ila_0]
set_property C_TRIGIN_EN false [get_debug_cores u_ila_0]
set_property C_TRIGOUT_EN false [get_debug_cores u_ila_0]
set_property port_width 1 [get_debug_ports u_ila_0/clk]
connect_debug_port u_ila_0/clk [get_nets [list i_system_wrapper/system_i/axi_ad9361_1/inst/i_dev_if/i_clk/clk]]
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe0]
set_property port_width 16 [get_debug_ports u_ila_0/probe0]
connect_debug_port u_ila_0/probe0 [get_nets [list {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[0]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[1]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[2]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[3]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[4]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[5]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[6]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[7]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[8]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[9]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[10]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[11]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[12]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[13]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[14]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q1[15]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe1]
set_property port_width 16 [get_debug_ports u_ila_0/probe1]
connect_debug_port u_ila_0/probe1 [get_nets [list {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[0]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[1]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[2]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[3]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[4]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[5]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[6]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[7]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[8]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[9]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[10]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[11]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[12]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[13]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[14]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i0[15]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe2]
set_property port_width 16 [get_debug_ports u_ila_0/probe2]
connect_debug_port u_ila_0/probe2 [get_nets [list {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[0]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[1]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[2]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[3]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[4]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[5]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[6]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[7]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[8]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[9]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[10]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[11]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[12]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[13]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[14]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_i1[15]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe3]
set_property port_width 16 [get_debug_ports u_ila_0/probe3]
connect_debug_port u_ila_0/probe3 [get_nets [list {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[0]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[1]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[2]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[3]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[4]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[5]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[6]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[7]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[8]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[9]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[10]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[11]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[12]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[13]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[14]} {i_system_wrapper/system_i/axi_ad9361_1_adc_data_q0[15]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe4]
set_property port_width 1 [get_debug_ports u_ila_0/probe4]
connect_debug_port u_ila_0/probe4 [get_nets [list i_system_wrapper/system_i/axi_ad9361_1_adc_valid_i0]]
create_debug_core u_ila_1 ila
set_property ALL_PROBE_SAME_MU true [get_debug_cores u_ila_1]
set_property ALL_PROBE_SAME_MU_CNT 2 [get_debug_cores u_ila_1]
set_property C_ADV_TRIGGER false [get_debug_cores u_ila_1]
set_property C_DATA_DEPTH 16384 [get_debug_cores u_ila_1]
set_property C_EN_STRG_QUAL true [get_debug_cores u_ila_1]
set_property C_INPUT_PIPE_STAGES 0 [get_debug_cores u_ila_1]
set_property C_TRIGIN_EN false [get_debug_cores u_ila_1]
set_property C_TRIGOUT_EN false [get_debug_cores u_ila_1]
set_property port_width 1 [get_debug_ports u_ila_1/clk]
connect_debug_port u_ila_1/clk [get_nets [list i_system_wrapper/system_i/axi_ad9361_0/inst/i_dev_if/i_clk/clk]]
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_1/probe0]
set_property port_width 16 [get_debug_ports u_ila_1/probe0]
connect_debug_port u_ila_1/probe0 [get_nets [list {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[0]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[1]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[2]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[3]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[4]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[5]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[6]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[7]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[8]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[9]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[10]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[11]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[12]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[13]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[14]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q0[15]}]]
create_debug_port u_ila_1 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_1/probe1]
set_property port_width 16 [get_debug_ports u_ila_1/probe1]
connect_debug_port u_ila_1/probe1 [get_nets [list {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[0]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[1]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[2]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[3]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[4]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[5]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[6]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[7]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[8]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[9]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[10]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[11]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[12]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[13]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[14]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i0[15]}]]
create_debug_port u_ila_1 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_1/probe2]
set_property port_width 16 [get_debug_ports u_ila_1/probe2]
connect_debug_port u_ila_1/probe2 [get_nets [list {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[0]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[1]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[2]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[3]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[4]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[5]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[6]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[7]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[8]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[9]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[10]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[11]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[12]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[13]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[14]} {i_system_wrapper/system_i/axi_ad9361_adc_data_i1[15]}]]
create_debug_port u_ila_1 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_1/probe3]
set_property port_width 16 [get_debug_ports u_ila_1/probe3]
connect_debug_port u_ila_1/probe3 [get_nets [list {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[0]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[1]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[2]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[3]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[4]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[5]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[6]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[7]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[8]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[9]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[10]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[11]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[12]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[13]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[14]} {i_system_wrapper/system_i/axi_ad9361_adc_data_q1[15]}]]
create_debug_port u_ila_1 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_1/probe4]
set_property port_width 1 [get_debug_ports u_ila_1/probe4]
connect_debug_port u_ila_1/probe4 [get_nets [list i_system_wrapper/system_i/axi_ad9361_adc_valid_i0]]
create_debug_core u_ila_2 ila
set_property ALL_PROBE_SAME_MU true [get_debug_cores u_ila_2]
set_property ALL_PROBE_SAME_MU_CNT 2 [get_debug_cores u_ila_2]
set_property C_ADV_TRIGGER false [get_debug_cores u_ila_2]
set_property C_DATA_DEPTH 16384 [get_debug_cores u_ila_2]
set_property C_EN_STRG_QUAL true [get_debug_cores u_ila_2]
set_property C_INPUT_PIPE_STAGES 0 [get_debug_cores u_ila_2]
set_property C_TRIGIN_EN false [get_debug_cores u_ila_2]
set_property C_TRIGOUT_EN false [get_debug_cores u_ila_2]
set_property port_width 1 [get_debug_ports u_ila_2/clk]
connect_debug_port u_ila_2/clk [get_nets [list i_system_wrapper/system_i/util_ad9361_divclk1/inst/clk_out]]
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_2/probe0]
set_property port_width 16 [get_debug_ports u_ila_2/probe0]
connect_debug_port u_ila_2/probe0 [get_nets [list {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[0]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[1]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[2]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[3]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[4]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[5]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[6]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[7]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[8]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[9]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[10]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[11]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[12]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[13]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[14]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_3[15]}]]
create_debug_port u_ila_2 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_2/probe1]
set_property port_width 16 [get_debug_ports u_ila_2/probe1]
connect_debug_port u_ila_2/probe1 [get_nets [list {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[0]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[1]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[2]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[3]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[4]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[5]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[6]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[7]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[8]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[9]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[10]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[11]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[12]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[13]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[14]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_1[15]}]]
create_debug_port u_ila_2 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_2/probe2]
set_property port_width 16 [get_debug_ports u_ila_2/probe2]
connect_debug_port u_ila_2/probe2 [get_nets [list {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[0]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[1]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[2]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[3]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[4]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[5]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[6]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[7]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[8]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[9]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[10]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[11]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[12]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[13]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[14]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_0[15]}]]
create_debug_port u_ila_2 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_2/probe3]
set_property port_width 16 [get_debug_ports u_ila_2/probe3]
connect_debug_port u_ila_2/probe3 [get_nets [list {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[0]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[1]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[2]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[3]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[4]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[5]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[6]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[7]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[8]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[9]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[10]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[11]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[12]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[13]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[14]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_1_dout_data_2[15]}]]
create_debug_core u_ila_3 ila
set_property ALL_PROBE_SAME_MU true [get_debug_cores u_ila_3]
set_property ALL_PROBE_SAME_MU_CNT 2 [get_debug_cores u_ila_3]
set_property C_ADV_TRIGGER false [get_debug_cores u_ila_3]
set_property C_DATA_DEPTH 16384 [get_debug_cores u_ila_3]
set_property C_EN_STRG_QUAL true [get_debug_cores u_ila_3]
set_property C_INPUT_PIPE_STAGES 0 [get_debug_cores u_ila_3]
set_property C_TRIGIN_EN false [get_debug_cores u_ila_3]
set_property C_TRIGOUT_EN false [get_debug_cores u_ila_3]
set_property port_width 1 [get_debug_ports u_ila_3/clk]
connect_debug_port u_ila_3/clk [get_nets [list i_system_wrapper/system_i/util_ad9361_divclk/inst/clk_out]]
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_3/probe0]
set_property port_width 16 [get_debug_ports u_ila_3/probe0]
connect_debug_port u_ila_3/probe0 [get_nets [list {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[0]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[1]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[2]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[3]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[4]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[5]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[6]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[7]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[8]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[9]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[10]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[11]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[12]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[13]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[14]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_0[15]}]]
create_debug_port u_ila_3 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_3/probe1]
set_property port_width 16 [get_debug_ports u_ila_3/probe1]
connect_debug_port u_ila_3/probe1 [get_nets [list {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[0]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[1]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[2]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[3]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[4]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[5]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[6]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[7]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[8]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[9]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[10]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[11]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[12]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[13]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[14]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_2[15]}]]
create_debug_port u_ila_3 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_3/probe2]
set_property port_width 16 [get_debug_ports u_ila_3/probe2]
connect_debug_port u_ila_3/probe2 [get_nets [list {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[0]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[1]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[2]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[3]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[4]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[5]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[6]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[7]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[8]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[9]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[10]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[11]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[12]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[13]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[14]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_3[15]}]]
create_debug_port u_ila_3 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_3/probe3]
set_property port_width 16 [get_debug_ports u_ila_3/probe3]
connect_debug_port u_ila_3/probe3 [get_nets [list {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[0]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[1]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[2]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[3]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[4]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[5]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[6]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[7]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[8]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[9]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[10]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[11]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[12]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[13]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[14]} {i_system_wrapper/system_i/util_ad9361_adc_fifo_dout_data_1[15]}]]
set_property C_CLK_INPUT_FREQ_HZ 300000000 [get_debug_cores dbg_hub]
set_property C_ENABLE_CLK_DIVIDER false [get_debug_cores dbg_hub]
set_property C_USER_SCAN_CHAIN 1 [get_debug_cores dbg_hub]
connect_debug_port dbg_hub/clk [get_nets u_ila_3_clk_out]

	/*
	 * The interrupt vector is defined here --- you shouldn't
	 * need to add any interrupt, because they're all defined as weak
	 * symbols by default.
	 */

	.section  .isr_vec, "a", %progbits
isr_vec:
	/* Cortex interrupts */
	.word stack_end
	.word handle_reset
	.word handle_nmi
	.word handle_hardfault
	.word handle_memmanage
	.word handle_busfault
	.word handle_usagefault
	.word 0
	.word 0
	.word 0
	.word 0
	.word handle_svc
	.word handle_debugmon
	.word 0
	.word handle_pendsv
	.word handle_systick

	/* Peripheral interrupts */
	.word handle_wwdg_irq
	.word handle_pvd_avd_irq
	.word handle_tamp_stamp_irq
	.word handle_rtc_wkup_irq
	.word handle_flash_irq
	.word handle_rcc_irq
	.word handle_exti0_irq
	.word handle_exti1_irq
	.word handle_exti2_irq
	.word handle_exti3_irq
	.word handle_exti4_irq
	.word handle_dma1_stream0_irq
	.word handle_dma1_stream1_irq
	.word handle_dma1_stream2_irq
	.word handle_dma1_stream3_irq
	.word handle_dma1_stream4_irq
	.word handle_dma1_stream5_irq
	.word handle_dma1_stream6_irq
	.word handle_adc_irq
	.word handle_fdcan1_it0_irq
	.word handle_fdcan2_it0_irq
	.word handle_fdcan1_it1_irq
	.word handle_fdcan2_it1_irq
	.word handle_exti9_5_irq
	.word handle_tim1_brk_irq
	.word handle_tim1_up_irq
	.word handle_tim1_trg_com_IRQ
	.word handle_tim1_cc_irq
	.word handle_tim2_irq
	.word handle_tim3_irq
	.word handle_tim4_irq
	.word handle_i2c1_ev_irq
	.word handle_i2c1_er_irq
	.word handle_i2c2_ev_irq
	.word handle_i2c2_er_irq
	.word handle_spi1_irq
	.word handle_spi2_irq
	.word handle_usart1_irq
	.word handle_usart2_irq
	.word handle_usart3_irq
	.word handle_exti15_10_irq
	.word handle_rtc_alarm_irq
	.word 0
	.word handle_tim8_brk_tim12_IRQ
	.word handle_tim8_up_tim13_IRQ
	.word handle_tim8_trg_com_TIM14_IRQ
	.word handle_tim8_cc_irq
	.word handle_dma1_stream7_irq
	.word handle_fmc_irq
	.word handle_sdmmc1_irq
	.word handle_tim5_irq
	.word handle_spi3_irq
	.word handle_uart4_irq
	.word handle_uart5_irq
	.word handle_tim6_dac_irq
	.word handle_tim7_irq
	.word handle_dma2_stream0_irq
	.word handle_dma2_stream1_irq
	.word handle_dma2_stream2_irq
	.word handle_dma2_stream3_irq
	.word handle_dma2_stream4_irq
	.word handle_eth_irq
	.word handle_eth_wkup_irq
	.word handle_fdcan_cal_irq
	.word 0
	.word 0
	.word 0
	.word 0
	.word handle_dma2_stream5_irq
	.word handle_dma2_stream6_irq
	.word handle_dma2_stream7_irq
	.word handle_usart6_irq
	.word handle_i2c3_ev_irq
	.word handle_i2c3_er_irq
	.word handle_otg_hs_ep1_OUT_IRQ
	.word handle_otg_hs_ep1_IN_IRQ
	.word handle_otg_hs_wkup_IRQ
	.word handle_otg_hs_irq
	.word handle_dcmi_irq
	.word 0
	.word handle_rng_irq
	.word handle_fpu_irq
	.word handle_uart7_irq
	.word handle_uart8_irq
	.word handle_spi4_irq
	.word handle_spi5_irq
	.word handle_spi6_irq
	.word handle_sai1_irq
	.word handle_ltdc_irq
	.word handle_ltdc_er_irq
	.word handle_dma2d_irq
	.word handle_sai2_irq
	.word handle_quadspi_irq
	.word handle_lptim1_irq
	.word handle_cec_irq
	.word handle_i2c4_ev_irq
	.word handle_i2c4_er_irq
	.word handle_spdif_rx_irq
	.word handle_otg_fs_ep1_OUT_IRQ
	.word handle_otg_fs_ep1_IN_IRQ
	.word handle_otg_fs_wkup_IRQ
	.word handle_otg_fs_irq
	.word handle_dmamux1_ovr_irq
	.word handle_hrtim1_master_irq
	.word handle_hrtim1_tima_irq
	.word handle_hrtim1_timb_irq
	.word handle_hrtim1_timc_irq
	.word handle_hrtim1_timd_irq
	.word handle_hrtim1_time_irq
	.word handle_hrtim1_flt_irq
	.word handle_dfsdm1_flt0_irq
	.word handle_dfsdm1_flt1_irq
	.word handle_dfsdm1_flt2_irq
	.word handle_dfsdm1_flt3_irq
	.word handle_sai3_irq
	.word handle_swpmi1_irq
	.word handle_tim15_irq
	.word handle_tim16_irq
	.word handle_tim17_irq
	.word handle_mdios_wkup_irq
	.word handle_mdios_irq
	.word handle_jpeg_irq
	.word handle_mdma_irq
	.word 0
	.word handle_sdmmc2_irq
	.word handle_hsem1_irq
	.word 0
	.word handle_adc3_irq
	.word handle_dmamux2_ovr_irq
	.word handle_bdma_channel0_irq
	.word handle_bdma_channel1_irq
	.word handle_bdma_channel2_irq
	.word handle_bdma_channel3_irq
	.word handle_bdma_channel4_irq
	.word handle_bdma_channel5_irq
	.word handle_bdma_channel6_irq
	.word handle_bdma_channel7_irq
	.word handle_comp1_irq
	.word handle_lptim2_irq
	.word handle_lptim3_irq
	.word handle_lptim4_irq
	.word handle_lptim5_irq
	.word handle_lpuart1_irq
	.word 0
	.word handle_crs_irq
	.word 0
	.word handle_sai4_irq
	.word 0
	.word 0
	.word handle_wakeup_pin_irq

	/*
	 * default handlers -- if these aren't defined elsewhere,
	 * they'll just infinite loop (so you can boot up gdb and see
	 * what happened).
	 */
	.weak handle_nmi
	.thumb_set handle_nmi, handle_default
	.weak handle_hardfault
	.thumb_set handle_hardfault, handle_default
	.weak handle_memmanage
	.thumb_set handle_memmanage, handle_default
	.weak handle_busfault
	.thumb_set handle_busfault, handle_default
	.weak handle_usagefault
	.thumb_set handle_usagefault, handle_default
	.weak handle_svc
	.thumb_set handle_svc, handle_default
	.weak handle_debugmon
	.thumb_set handle_debugmon, handle_default
	.weak handle_pendsv
	.thumb_set handle_pendsv, handle_default
	.weak handle_systick
	.thumb_set handle_systick, handle_default

	.weak handle_wwdg_irq
	.thumb_set handle_wwdg_irq, handle_default
	.weak handle_pvd_avd_irq
	.thumb_set handle_pvd_avd_irq, handle_default
	.weak handle_tamp_stamp_irq
	.thumb_set handle_tamp_stamp_irq, handle_default
	.weak handle_rtc_wkup_irq
	.thumb_set handle_rtc_wkup_irq, handle_default
	.weak handle_flash_irq
	.thumb_set handle_flash_irq, handle_default
	.weak handle_rcc_irq
	.thumb_set handle_rcc_irq, handle_default
	.weak handle_exti0_irq
	.thumb_set handle_exti0_irq, handle_default
	.weak handle_exti1_irq
	.thumb_set handle_exti1_irq, handle_default
	.weak handle_exti2_irq
	.thumb_set handle_exti2_irq, handle_default
	.weak handle_exti3_irq
	.thumb_set handle_exti3_irq, handle_default
	.weak handle_exti4_irq
	.thumb_set handle_exti4_irq, handle_default
	.weak handle_dma1_stream0_irq
	.thumb_set handle_dma1_stream0_irq, handle_default
	.weak handle_dma1_stream1_irq
	.thumb_set handle_dma1_stream1_irq, handle_default
	.weak handle_dma1_stream2_irq
	.thumb_set handle_dma1_stream2_irq, handle_default
	.weak handle_dma1_stream3_irq
	.thumb_set handle_dma1_stream3_irq, handle_default
	.weak handle_dma1_stream4_irq
	.thumb_set handle_dma1_stream4_irq, handle_default
	.weak handle_dma1_stream5_irq
	.thumb_set handle_dma1_stream5_irq, handle_default
	.weak handle_dma1_stream6_irq
	.thumb_set handle_dma1_stream6_irq, handle_default
	.weak handle_adc_irq
	.thumb_set handle_adc_irq, handle_default
	.weak handle_fdcan1_it0_irq
	.thumb_set handle_fdcan1_it0_irq, handle_default
	.weak handle_fdcan2_it0_irq
	.thumb_set handle_fdcan2_it0_irq, handle_default
	.weak handle_fdcan1_it1_irq
	.thumb_set handle_fdcan1_it1_irq, handle_default
	.weak handle_fdcan2_it1_irq
	.thumb_set handle_fdcan2_it1_irq, handle_default
	.weak handle_exti9_5_irq
	.thumb_set handle_exti9_5_irq, handle_default
	.weak handle_tim1_brk_irq
	.thumb_set handle_tim1_brk_irq, handle_default
	.weak handle_tim1_up_irq
	.thumb_set handle_tim1_up_irq, handle_default
	.weak handle_tim1_trg_com_IRQ
	.thumb_set handle_tim1_trg_com_IRQ, handle_default
	.weak handle_tim1_cc_irq
	.thumb_set handle_tim1_cc_irq, handle_default
	.weak handle_tim2_irq
	.thumb_set handle_tim2_irq, handle_default
	.weak handle_tim3_irq
	.thumb_set handle_tim3_irq, handle_default
	.weak handle_tim4_irq
	.thumb_set handle_tim4_irq, handle_default
	.weak handle_i2c1_ev_irq
	.thumb_set handle_i2c1_ev_irq, handle_default
	.weak handle_i2c1_er_irq
	.thumb_set handle_i2c1_er_irq, handle_default
	.weak handle_i2c2_ev_irq
	.thumb_set handle_i2c2_ev_irq, handle_default
	.weak handle_i2c2_er_irq
	.thumb_set handle_i2c2_er_irq, handle_default
	.weak handle_spi1_irq
	.thumb_set handle_spi1_irq, handle_default
	.weak handle_spi2_irq
	.thumb_set handle_spi2_irq, handle_default
	.weak handle_usart1_irq
	.thumb_set handle_usart1_irq, handle_default
	.weak handle_usart2_irq
	.thumb_set handle_usart2_irq, handle_default
	.weak handle_usart3_irq
	.thumb_set handle_usart3_irq, handle_default
	.weak handle_exti15_10_irq
	.thumb_set handle_exti15_10_irq, handle_default
	.weak handle_rtc_alarm_irq
	.thumb_set handle_rtc_alarm_irq, handle_default
	.weak handle_tim8_brk_tim12_IRQ
	.thumb_set handle_tim8_brk_tim12_IRQ, handle_default
	.weak handle_tim8_up_tim13_IRQ
	.thumb_set handle_tim8_up_tim13_IRQ, handle_default
	.weak handle_tim8_trg_com_TIM14_IRQ
	.thumb_set handle_tim8_trg_com_TIM14_IRQ, handle_default
	.weak handle_tim8_cc_irq
	.thumb_set handle_tim8_cc_irq, handle_default
	.weak handle_dma1_stream7_irq
	.thumb_set handle_dma1_stream7_irq, handle_default
	.weak handle_fmc_irq
	.thumb_set handle_fmc_irq, handle_default
	.weak handle_sdmmc1_irq
	.thumb_set handle_sdmmc1_irq, handle_default
	.weak handle_tim5_irq
	.thumb_set handle_tim5_irq, handle_default
	.weak handle_spi3_irq
	.thumb_set handle_spi3_irq, handle_default
	.weak handle_uart4_irq
	.thumb_set handle_uart4_irq, handle_default
	.weak handle_uart5_irq
	.thumb_set handle_uart5_irq, handle_default
	.weak handle_tim6_dac_irq
	.thumb_set handle_tim6_dac_irq, handle_default
	.weak handle_tim7_irq
	.thumb_set handle_tim7_irq, handle_default
	.weak handle_dma2_stream0_irq
	.thumb_set handle_dma2_stream0_irq, handle_default
	.weak handle_dma2_stream1_irq
	.thumb_set handle_dma2_stream1_irq, handle_default
	.weak handle_dma2_stream2_irq
	.thumb_set handle_dma2_stream2_irq, handle_default
	.weak handle_dma2_stream3_irq
	.thumb_set handle_dma2_stream3_irq, handle_default
	.weak handle_dma2_stream4_irq
	.thumb_set handle_dma2_stream4_irq, handle_default
	.weak handle_eth_irq
	.thumb_set handle_eth_irq, handle_default
	.weak handle_eth_wkup_irq
	.thumb_set handle_eth_wkup_irq, handle_default
	.weak handle_fdcan_cal_irq
	.thumb_set handle_fdcan_cal_irq, handle_default
	.weak handle_dma2_stream5_irq
	.thumb_set handle_dma2_stream5_irq, handle_default
	.weak handle_dma2_stream6_irq
	.thumb_set handle_dma2_stream6_irq, handle_default
	.weak handle_dma2_stream7_irq
	.thumb_set handle_dma2_stream7_irq, handle_default
	.weak handle_usart6_irq
	.thumb_set handle_usart6_irq, handle_default
	.weak handle_i2c3_ev_irq
	.thumb_set handle_i2c3_ev_irq, handle_default
	.weak handle_i2c3_er_irq
	.thumb_set handle_i2c3_er_irq, handle_default
	.weak handle_otg_hs_ep1_OUT_IRQ
	.thumb_set handle_otg_hs_ep1_OUT_IRQ, handle_default
	.weak handle_otg_hs_ep1_IN_IRQ
	.thumb_set handle_otg_hs_ep1_IN_IRQ, handle_default
	.weak handle_otg_hs_wkup_IRQ
	.thumb_set handle_otg_hs_wkup_IRQ, handle_default
	.weak handle_otg_hs_irq
	.thumb_set handle_otg_hs_irq, handle_default
	.weak handle_dcmi_irq
	.thumb_set handle_dcmi_irq, handle_default
	.weak handle_rng_irq
	.thumb_set handle_rng_irq, handle_default
	.weak handle_fpu_irq
	.thumb_set handle_fpu_irq, handle_default
	.weak handle_uart7_irq
	.thumb_set handle_uart7_irq, handle_default
	.weak handle_uart8_irq
	.thumb_set handle_uart8_irq, handle_default
	.weak handle_spi4_irq
	.thumb_set handle_spi4_irq, handle_default
	.weak handle_spi5_irq
	.thumb_set handle_spi5_irq, handle_default
	.weak handle_spi6_irq
	.thumb_set handle_spi6_irq, handle_default
	.weak handle_sai1_irq
	.thumb_set handle_sai1_irq, handle_default
	.weak handle_ltdc_irq
	.thumb_set handle_ltdc_irq, handle_default
	.weak handle_ltdc_er_irq
	.thumb_set handle_ltdc_er_irq, handle_default
	.weak handle_dma2d_irq
	.thumb_set handle_dma2d_irq, handle_default
	.weak handle_sai2_irq
	.thumb_set handle_sai2_irq, handle_default
	.weak handle_quadspi_irq
	.thumb_set handle_quadspi_irq, handle_default
	.weak handle_lptim1_irq
	.thumb_set handle_lptim1_irq, handle_default
	.weak handle_cec_irq
	.thumb_set handle_cec_irq, handle_default
	.weak handle_i2c4_ev_irq
	.thumb_set handle_i2c4_ev_irq, handle_default
	.weak handle_i2c4_er_irq
	.thumb_set handle_i2c4_er_irq, handle_default
	.weak handle_spdif_rx_irq
	.thumb_set handle_spdif_rx_irq, handle_default
	.weak handle_otg_fs_ep1_OUT_IRQ
	.thumb_set handle_otg_fs_ep1_OUT_IRQ, handle_default
	.weak handle_otg_fs_ep1_IN_IRQ
	.thumb_set handle_otg_fs_ep1_IN_IRQ, handle_default
	.weak handle_otg_fs_wkup_IRQ
	.thumb_set handle_otg_fs_wkup_IRQ, handle_default
	.weak handle_otg_fs_irq
	.thumb_set handle_otg_fs_irq, handle_default
	.weak handle_dmamux1_ovr_irq
	.thumb_set handle_dmamux1_ovr_irq, handle_default
	.weak handle_hrtim1_master_irq
	.thumb_set handle_hrtim1_master_irq, handle_default
	.weak handle_hrtim1_tima_irq
	.thumb_set handle_hrtim1_tima_irq, handle_default
	.weak handle_hrtim1_timb_irq
	.thumb_set handle_hrtim1_timb_irq, handle_default
	.weak handle_hrtim1_timc_irq
	.thumb_set handle_hrtim1_timc_irq, handle_default
	.weak handle_hrtim1_timd_irq
	.thumb_set handle_hrtim1_timd_irq, handle_default
	.weak handle_hrtim1_time_irq
	.thumb_set handle_hrtim1_time_irq, handle_default
	.weak handle_hrtim1_flt_irq
	.thumb_set handle_hrtim1_flt_irq, handle_default
	.weak handle_dfsdm1_flt0_irq
	.thumb_set handle_dfsdm1_flt0_irq, handle_default
	.weak handle_dfsdm1_flt1_irq
	.thumb_set handle_dfsdm1_flt1_irq, handle_default
	.weak handle_dfsdm1_flt2_irq
	.thumb_set handle_dfsdm1_flt2_irq, handle_default
	.weak handle_dfsdm1_flt3_irq
	.thumb_set handle_dfsdm1_flt3_irq, handle_default
	.weak handle_sai3_irq
	.thumb_set handle_sai3_irq, handle_default
	.weak handle_swpmi1_irq
	.thumb_set handle_swpmi1_irq, handle_default
	.weak handle_tim15_irq
	.thumb_set handle_tim15_irq, handle_default
	.weak handle_tim16_irq
	.thumb_set handle_tim16_irq, handle_default
	.weak handle_tim17_irq
	.thumb_set handle_tim17_irq, handle_default
	.weak handle_mdios_wkup_irq
	.thumb_set handle_mdios_wkup_irq, handle_default
	.weak handle_mdios_irq
	.thumb_set handle_mdios_irq, handle_default
	.weak handle_jpeg_irq
	.thumb_set handle_jpeg_irq, handle_default
	.weak handle_mdma_irq
	.thumb_set handle_mdma_irq, handle_default
	.weak handle_sdmmc2_irq
	.thumb_set handle_sdmmc2_irq, handle_default
	.weak handle_hsem1_irq
	.thumb_set handle_hsem1_irq, handle_default
	.weak handle_adc3_irq
	.thumb_set handle_adc3_irq, handle_default
	.weak handle_dmamux2_ovr_irq
	.thumb_set handle_dmamux2_ovr_irq, handle_default
	.weak handle_bdma_channel0_irq
	.thumb_set handle_bdma_channel0_irq, handle_default
	.weak handle_bdma_channel1_irq
	.thumb_set handle_bdma_channel1_irq, handle_default
	.weak handle_bdma_channel2_irq
	.thumb_set handle_bdma_channel2_irq, handle_default
	.weak handle_bdma_channel3_irq
	.thumb_set handle_bdma_channel3_irq, handle_default
	.weak handle_bdma_channel4_irq
	.thumb_set handle_bdma_channel4_irq, handle_default
	.weak handle_bdma_channel5_irq
	.thumb_set handle_bdma_channel5_irq, handle_default
	.weak handle_bdma_channel6_irq
	.thumb_set handle_bdma_channel6_irq, handle_default
	.weak handle_bdma_channel7_irq
	.thumb_set handle_bdma_channel7_irq, handle_default
	.weak handle_comp1_irq
	.thumb_set handle_comp1_irq, handle_default
	.weak handle_lptim2_irq
	.thumb_set handle_lptim2_irq, handle_default
	.weak handle_lptim3_irq
	.thumb_set handle_lptim3_irq, handle_default
	.weak handle_lptim4_irq
	.thumb_set handle_lptim4_irq, handle_default
	.weak handle_lptim5_irq
	.thumb_set handle_lptim5_irq, handle_default
	.weak handle_lpuart1_irq
	.thumb_set handle_lpuart1_irq, handle_default
	.weak handle_crs_irq
	.thumb_set handle_crs_irq, handle_default
	.weak handle_sai4_irq
	.thumb_set handle_sai4_irq, handle_default
	.weak handle_wakeup_pin_irq
	.thumb_set handle_wakeup_pin_irq, handle_default

	.text
handle_default:
	b handle_default

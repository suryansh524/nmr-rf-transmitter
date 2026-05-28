#include "driver/rmt.h"

#define PRE_GPIO   22
#define MAIN_GPIO  23

void setup() {

  rmt_config_t cfg;

  cfg.rmt_mode = RMT_MODE_TX;
  cfg.mem_block_num = 1;
  cfg.clk_div = 80;   // 1 µs resolution
  cfg.tx_config.loop_en = false;
  cfg.tx_config.carrier_en = false;
  cfg.tx_config.idle_output_en = true;
  cfg.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;

  // PRE channel
  cfg.channel = RMT_CHANNEL_0;
  cfg.gpio_num = (gpio_num_t)PRE_GPIO;
  rmt_config(&cfg);
  rmt_driver_install(cfg.channel, 0, 0);

  // MAIN channel
  cfg.channel = RMT_CHANNEL_1;
  cfg.gpio_num = (gpio_num_t)MAIN_GPIO;
  rmt_config(&cfg);
  rmt_driver_install(cfg.channel, 0, 0);
}

void loop() {

  uint32_t start_time = micros();  //  track start

  // PRE pulse
  rmt_item32_t preItem[1];
  preItem[0].level0 = 1;
  preItem[0].duration0 = 30;
  preItem[0].level1 = 0;
  preItem[0].duration1 = 0;

  //  MAIN double pulse
  rmt_item32_t mainItem[3];

  mainItem[0].level0 = 0;
  mainItem[0].duration0 = 25;
  mainItem[0].level1 = 1;
  mainItem[0].duration1 = 1;

  mainItem[1].level0 = 0;
  mainItem[1].duration0 = 25;
  mainItem[1].level1 = 1;
  mainItem[1].duration1 = 1;

  mainItem[2].level0 = 0;
  mainItem[2].duration0 = 25;
  mainItem[2].level1 = 0;
  mainItem[2].duration1 = 0;

  //  Start both channels
  rmt_write_items(RMT_CHANNEL_0, preItem, 1, false);
  rmt_write_items(RMT_CHANNEL_1, mainItem, 3, true);

  //  Wait until exactly 1 second has passed
  while (micros() - start_time < 1000000) {
    // precise wait
  }
}

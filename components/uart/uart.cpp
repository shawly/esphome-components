#include "uart.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "esphome/core/application.h"
#include "esphome/core/defines.h"

namespace esphome {
namespace uart {

static const char *const TAG = "uart";

void UARTDevice::check_uart_settings(uint32_t baud_rate, uint8_t stop_bits, UARTParityOptions parity,
                                     uint8_t data_bits, UARTHardwareFlowControl hw_flowctrl) {
  if (this->parent_->get_baud_rate() != baud_rate) {
    ESP_LOGE(TAG, "  Invalid baud_rate: Integration requested baud_rate %u but you have %u!", baud_rate,
             this->parent_->get_baud_rate());
  }
  if (this->parent_->get_stop_bits() != stop_bits) {
    ESP_LOGE(TAG, "  Invalid stop bits: Integration requested stop_bits %u but you have %u!", stop_bits,
             this->parent_->get_stop_bits());
  }
  if (this->parent_->get_data_bits() != data_bits) {
    ESP_LOGE(TAG, "  Invalid number of data bits: Integration requested %u data bits but you have %u!", data_bits,
             this->parent_->get_data_bits());
  }
  if (this->parent_->get_parity() != parity) {
    ESP_LOGE(TAG, "  Invalid parity: Integration requested parity %s but you have %s!",
             LOG_STR_ARG(parity_to_str(parity)), LOG_STR_ARG(parity_to_str(this->parent_->get_parity())));
  }
  if (this->parent_->get_hw_flowctrl() != hw_flowctrl) {
    ESP_LOGE(TAG, "  Invalid hw_flowctrl: Integration requested hw_flowctrl %s but you have %s!",
             LOG_STR_ARG(hw_flowctrl_to_str(hw_flowctrl)), LOG_STR_ARG(hw_flowctrl_to_str(this->parent_->get_hw_flowctrl())));
  }
}

const LogString *parity_to_str(UARTParityOptions parity) {
  switch (parity) {
    case UART_CONFIG_PARITY_NONE:
      return LOG_STR("NONE");
    case UART_CONFIG_PARITY_EVEN:
      return LOG_STR("EVEN");
    case UART_CONFIG_PARITY_ODD:
      return LOG_STR("ODD");
    default:
      return LOG_STR("UNKNOWN");
  }
}

const LogString *hw_flowctrl_to_str(UARTHardwareFlowControl hw_flowctrl) {
  switch (hw_flowctrl) {
    case UART_CONFIG_HW_FLOWCTRL_DISABLE:
      return LOG_STR("DISABLE");
    case UART_CONFIG_HW_FLOWCTRL_CTS:
      return LOG_STR("CTS");
    case UART_CONFIG_HW_FLOWCTRL_RTS:
      return LOG_STR("RTS");
    case UART_CONFIG_HW_FLOWCTRL_CTS_RTS:
      return LOG_STR("CTS_RTS");
    case UART_CONFIG_HW_FLOWCTRL_MAX:
      return LOG_STR("MAX");
    default:
      return LOG_STR("UNKNOWN");
  }
}

}  // namespace uart
}  // namespace esphome

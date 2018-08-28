/*
 * hid.h
 *
 *  Created on: Aug 25, 2018
 *      Author: technix
 */

#ifndef INCLUDE_USB_CDC_H_
#define INCLUDE_USB_CDC_H_

#include <stm32f0xx.h>
#include <usb.h>
#include <usbd_core.h>

usbd_respond cdc_control(usbd_device *dev, usbd_ctlreq *req, usbd_rqc_callback *callback);
void cdc_rx (usbd_device *dev, uint8_t event, uint8_t ep);
void cdc_tx (usbd_device *dev, uint8_t event, uint8_t ep);

#endif /* INCLUDE_USB_CDC_H_ */

/*
 * hid.c
 *
 *  Created on: Aug 25, 2018
 *      Author: technix
 */

#include <stm32f0xx.h>
#include "usb/cdc.h"
#include <usb.h>
#include <usbd_core.h>

#include "usb/usb_descriptor.h"
#include "main.h"

usbd_respond cdc_get_descriptor(usbd_ctlreq *req, void **buf, uint16_t *len)
{
    const uint8_t type = req->wValue >> 8;
    const uint8_t number = req->wValue & 0xFF;
    const struct usb_header_descriptor *descriptor;
    uint16_t length = 0;

    switch (type)
    {
    default:
    	return usbd_fail;
    }

    length = length ?: descriptor->bLength;
    *buf = (void *)descriptor;
    *len = length;
    return usbd_ack;
}

usbd_respond cdc_control(usbd_device *dev, usbd_ctlreq *req, usbd_rqc_callback *callback)
{
	switch (req->bRequest)
	{
	case USB_STD_GET_DESCRIPTOR:
		return cdc_get_descriptor(req, &(dev->status.data_ptr), &(dev->status.data_count));

	default:
		break;
	}

	return usbd_fail;
}

void cdc_rx(usbd_device *dev, uint8_t event, uint8_t ep)
{
//	uint8_t buf[HID_EP_SIZE];
//	int len = usbd_ep_read(dev, ep, buf, HID_EP_SIZE);
//
//	if (len > 0)
//	{
//		for (uint8_t *bp = buf; bp - buf < len; bp++)
//			ring_buffer_putchar(rx_buffer, *bp);
//	}
}

void cdc_tx(usbd_device *dev, uint8_t event, uint8_t ep)
{
//	uint8_t buf[HID_EP_SIZE];
//	int len = 0;
//	for (len = 0; len < HID_EP_SIZE; len++)
//	{
//		int ch = ring_buffer_getchar(tx_buffer);
//		if (ch < 0)
//			break;
//		else
//			buf[len] = ch;
//	}
//
//	usbd_ep_write(dev, ep, buf, len);
}

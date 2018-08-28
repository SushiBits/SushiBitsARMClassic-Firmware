/*
 * usb.c
 *
 *  Created on: Aug 25, 2018
 *      Author: technix
 */

#include "usb/usb.h"
#include <stm32f0xx.h>
#include <usb.h>
#include <usbd_core.h>
#include <stddef.h>
#include "usb/cdc.h"

#include "usb/usb_descriptor.h"

usbd_device usb;
uint32_t usb_buffer[USB_EP0_SIZE];

usbd_respond usb_get_descriptor(usbd_ctlreq *req, void **buf, uint16_t *len);
usbd_respond usb_control(usbd_device *dev, usbd_ctlreq *req, usbd_rqc_callback *callback);
usbd_respond usb_set_configuration(usbd_device *dev, uint8_t configuration);

void usb_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
	RCC->CFGR3 |= RCC_CFGR3_USBSW;
	SYSCFG->CFGR1 |= SYSCFG_CFGR1_PA11_PA12_RMP;

	usbd_init(&usb, &usbd_devfs, USB_EP0_SIZE, usb_buffer, sizeof(usb_buffer));
	usbd_reg_control(&usb, usb_control);
	usbd_reg_descr(&usb, usb_get_descriptor);
	usbd_reg_config(&usb, usb_set_configuration);

	usbd_enable(&usb, true);
	usbd_connect(&usb, true);
	NVIC_EnableIRQ(USB_IRQn);
}

void USB_IRQHandler(void)
{
	usbd_poll(&usb);
}

usbd_respond usb_get_descriptor(usbd_ctlreq *req, void **buf, uint16_t *len)
{
    const uint8_t type = req->wValue >> 8;
    const uint8_t number = req->wValue & 0xFF;
    const struct usb_header_descriptor *descriptor;
    uint16_t length = 0;

    switch (type)
    {
    case USB_DTYPE_DEVICE:
    	descriptor = (struct usb_header_descriptor *)&device_descriptor;
    	break;

    case USB_DTYPE_QUALIFIER:
    	descriptor = (struct usb_header_descriptor *)&qualifier_descriptor;
    	break;

    case USB_DTYPE_CONFIGURATION:
    	descriptor = (struct usb_header_descriptor *)&configuration_descriptor;
    	length = sizeof(configuration_descriptor);
    	break;

    case USB_DTYPE_STRING:
    	if (number < sizeof(string_descriptor) / sizeof(struct usb_string_descriptor *const))
    		descriptor = (struct usb_header_descriptor *)string_descriptor[number];
    	else
    		return usbd_fail;
    	break;

    default:
    	return usbd_fail;
    }

    length = length ?: descriptor->bLength;
    *buf = (void *)descriptor;
    *len = length;
    return usbd_ack;
}

usbd_respond usb_control(usbd_device *dev, usbd_ctlreq *req, usbd_rqc_callback *callback)
{
	switch (req->bmRequestType & USB_REQ_RECIPIENT)
	{
	case USB_REQ_INTERFACE:
		switch (req->wIndex)
		{
		case CDC_IF_INDEX:
			return cdc_control(dev, req, callback);

		default:
			break;
		}
		break;

	default:
		break;
	}
	return usbd_fail;
}

usbd_respond usb_set_configuration(usbd_device *dev, uint8_t configuration)
{
    switch (configuration)
    {
    case 0:
    	usbd_ep_deconfig(dev, COMM_EP);
        usbd_ep_deconfig(dev, CDC_EP_TX);
        usbd_ep_deconfig(dev, CDC_EP_RX);
        usbd_reg_endpoint(dev, CDC_EP_TX, NULL);
        usbd_reg_endpoint(dev, CDC_EP_RX, NULL);
        return usbd_ack;
    case 1:
        /* configuring device */
        usbd_ep_config(dev, CDC_EP_TX, USB_EPTYPE_BULK, CDC_EP_SIZE);
        usbd_ep_config(dev, CDC_EP_RX, USB_EPTYPE_BULK, CDC_EP_SIZE);
        usbd_ep_config(dev, COMM_EP, USB_EPTYPE_INTERRUPT, COMM_EP_SIZE);

        usbd_reg_endpoint(dev, CDC_EP_TX, cdc_tx);
        usbd_reg_endpoint(dev, CDC_EP_RX, cdc_rx);
        usbd_ep_write(dev, CDC_EP_TX, 0, 0);
        return usbd_ack;
    default:
        return usbd_fail;
    }
}

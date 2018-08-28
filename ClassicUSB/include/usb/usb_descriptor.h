/*
 * usb_descriptor.h
 *
 *  Created on: Aug 25, 2018
 *      Author: technix
 */

#ifndef INCLUDE_USB_USB_DESCRIPTOR_H_
#define INCLUDE_USB_USB_DESCRIPTOR_H_

#include <usb_std.h>
#include <usb_cdc.h>

#define USB_VID				0x0002
#define USB_VENDOR_NAME		"SushiBits"
#define USB_PID				0x2103
#define USB_PRODUCT_NAME	"SushiBits ARM Classic"
#define USB_VERSION			VERSION_BCD(1, 0, 0)
#define USB_EP0_SIZE		64

#define COMM_IF_INDEX		0
#define COMM_EP				(USB_EPDIR_OUT | 1)
#define COMM_EP_SIZE		8

#define CDC_IF_INDEX		1
#define CDC_EP_RX			(USB_EPDIR_IN  | 2)
#define CDC_EP_TX			(USB_EPDIR_OUT | 2)
#define CDC_EP_SIZE			64

static const struct usb_device_descriptor device_descriptor =
{
		.bLength = sizeof(struct usb_device_descriptor),
		.bDescriptorType = USB_DTYPE_DEVICE,
		.bcdUSB = VERSION_BCD(2, 0, 0),
		.bDeviceClass = 0xEF,
		.bDeviceSubClass = 0x02,
		.bDeviceProtocol = 0x01,
		.bMaxPacketSize0 = USB_EP0_SIZE,
		.idVendor = USB_VID,
		.idProduct = USB_PID,
		.bcdDevice = USB_VERSION,
		.iManufacturer = 1,
		.iProduct = 2,
		.iSerialNumber = INTSERIALNO_DESCRIPTOR,
		.bNumConfigurations = 1
};

static const struct usb_qualifier_descriptor qualifier_descriptor =
{
		.bLength = sizeof(struct usb_qualifier_descriptor),
		.bDescriptorType = USB_DTYPE_QUALIFIER,
    	.bcdUSB = VERSION_BCD(2, 0, 0),
		.bDeviceClass = 0xEF,
		.bDeviceSubClass = 0x02,
		.bDeviceProtocol = 0x01,
		.bMaxPacketSize0 = USB_EP0_SIZE,
		.bNumConfigurations = 1,
    	.bReserved = 0
};

struct usb_hid_configuration_descriptor
{
	struct usb_config_descriptor config_descriptor;
	struct usb_iad_descriptor iad_descriptor;
	struct usb_interface_descriptor comm_interface_descriptor;
    struct usb_cdc_header_desc cdc_header_descriptor;
    struct usb_cdc_call_mgmt_desc cdc_call_mgmt_descriptor;
    struct usb_cdc_acm_desc cdc_acm_descriptor;
    struct usb_cdc_union_desc cdc_union_descriptor;
    struct usb_endpoint_descriptor comm_endpoint_descriptor[1];
    struct usb_interface_descriptor data_interface_descriptor;
	struct usb_endpoint_descriptor data_endpoint_descriptor[2];
} __attribute__((packed));

static const struct usb_hid_configuration_descriptor configuration_descriptor =
{
		.config_descriptor =
		{
				.bLength = sizeof(struct usb_config_descriptor),
				.bDescriptorType = USB_DTYPE_CONFIGURATION,
				.wTotalLength = sizeof(struct usb_hid_configuration_descriptor),
				.bNumInterfaces = 1,
				.bConfigurationValue = 1,
				.iConfiguration = NO_DESCRIPTOR,
				.bmAttributes = USB_CFG_ATTR_RESERVED | USB_CFG_ATTR_SELFPOWERED,
				.bMaxPower = USB_CFG_POWER_MA(500)
		},
		.iad_descriptor =
		{
				.bLength = sizeof(struct usb_iad_descriptor),
				.bDescriptorType = USB_DTYPE_INTERFASEASSOC,
		    	.bFirstInterface = 0,
				.bInterfaceCount = 2,
				.bFunctionClass = USB_CLASS_CDC,
				.bFunctionSubClass = USB_SUBCLASS_NONE,
				.bFunctionProtocol = USB_PROTO_NONE,
				.iFunction = NO_DESCRIPTOR
		},
		.comm_interface_descriptor =
		{
			    .bLength = sizeof(struct usb_interface_descriptor),
			    .bDescriptorType = USB_DTYPE_INTERFACE,
			    .bInterfaceNumber = COMM_IF_INDEX,
			    .bAlternateSetting = 0,
			    .bNumEndpoints = 2,
			    .bInterfaceClass = USB_CLASS_CDC,
			    .bInterfaceSubClass = USB_CDC_SUBCLASS_ACM,
			    .bInterfaceProtocol = USB_CDC_PROTO_V25TER,
			    .iInterface = NO_DESCRIPTOR
		},
		.cdc_header_descriptor = {
				.bFunctionLength = sizeof(struct usb_cdc_header_desc),
				.bDescriptorType  = USB_DTYPE_CS_INTERFACE,
				.bDescriptorSubType = USB_DTYPE_CDC_HEADER,
				.bcdCDC = VERSION_BCD(1,1,0),
		},
		.cdc_call_mgmt_descriptor = {
				.bFunctionLength = sizeof(struct usb_cdc_call_mgmt_desc),
				.bDescriptorType = USB_DTYPE_CS_INTERFACE,
				.bDescriptorSubType = USB_DTYPE_CDC_CALL_MANAGEMENT,
				.bmCapabilities = 0,
				.bDataInterface = CDC_IF_INDEX,

		},
		.cdc_acm_descriptor = {
				.bFunctionLength = sizeof(struct usb_cdc_acm_desc),
				.bDescriptorType = USB_DTYPE_CS_INTERFACE,
				.bDescriptorSubType = USB_DTYPE_CDC_ACM,
				.bmCapabilities = 0,
		},
		.cdc_union_descriptor = {
				.bFunctionLength = sizeof(struct usb_cdc_union_desc),
				.bDescriptorType = USB_DTYPE_CS_INTERFACE,
				.bDescriptorSubType = USB_DTYPE_CDC_UNION,
				.bMasterInterface0 = COMM_IF_INDEX,
				.bSlaveInterface0 = CDC_IF_INDEX,
		},
		.comm_endpoint_descriptor =
		{
				{
					    .bLength = sizeof(struct usb_endpoint_descriptor),
					    .bDescriptorType = USB_DTYPE_ENDPOINT,
					    .bEndpointAddress = COMM_EP,
					    .bmAttributes = USB_EPTYPE_INTERRUPT,
					    .wMaxPacketSize = COMM_EP_SIZE,
					    .bInterval = 1,
				}
		},
		.data_interface_descriptor =
		{
			    .bLength = sizeof(struct usb_interface_descriptor),
			    .bDescriptorType = USB_DTYPE_INTERFACE,
			    .bInterfaceNumber = CDC_IF_INDEX,
			    .bAlternateSetting = 0,
			    .bNumEndpoints = 2,
			    .bInterfaceClass = USB_CLASS_CDC_DATA,
			    .bInterfaceSubClass = USB_SUBCLASS_NONE,
			    .bInterfaceProtocol = USB_PROTO_NONE,
			    .iInterface = NO_DESCRIPTOR
		},
		.data_endpoint_descriptor =
		{
				{
					    .bLength = sizeof(struct usb_endpoint_descriptor),
					    .bDescriptorType = USB_DTYPE_ENDPOINT,
					    .bEndpointAddress = CDC_EP_TX,
					    .bmAttributes = USB_EPTYPE_BULK,
					    .wMaxPacketSize = CDC_EP_SIZE,
					    .bInterval = 1,
				},
				{
					    .bLength = sizeof(struct usb_endpoint_descriptor),
					    .bDescriptorType = USB_DTYPE_ENDPOINT,
					    .bEndpointAddress = CDC_EP_RX,
					    .bmAttributes = USB_EPTYPE_BULK,
					    .wMaxPacketSize = CDC_EP_SIZE,
					    .bInterval = 1,
				}
		}
};

static const struct usb_string_descriptor array_descriptor = USB_ARRAY_DESC(USB_LANGID_ENG_US);
static const struct usb_string_descriptor vendor_string_descriptor = USB_STRING_DESC(USB_VENDOR_NAME);
static const struct usb_string_descriptor product_string_descriptor = USB_STRING_DESC(USB_PRODUCT_NAME);

static const struct usb_string_descriptor *const string_descriptor[] =
{
		&array_descriptor,
		&vendor_string_descriptor,
		&product_string_descriptor
};

#endif /* INCLUDE_USB_USB_DESCRIPTOR_H_ */

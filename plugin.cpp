/*
 * Fledge south plugin.
 *
 * Copyright (c) 2020 Nex Computers Inc.
 *
 * Released under the Apache 2.0 License
 *
 * Author: Daniel Man
 */
#include <j1939.h>
#include <plugin_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string>
#include <logger.h>
#include <plugin_exception.h>
#include <config_category.h>
#include <version.h>

using namespace std;
using namespace rapidjson;

#define PLUGIN_NAME "J1939"
/**
 * Default configuration
 */
static const char *default_config = QUOTE({
		"plugin" : {
			"description" : "J1939 plugin",
			"type" : "string",
			"default" : PLUGIN_NAME,
			"readonly" : "true"
		},
		"asset" : {
			"description" : "Asset name",
			"type" : "string",
			"default" : "J1939",
			"displayName" : "Asset Name",
			"order" : "1",
			"mandatory" : "true"
		},
		"port" : {
			"description" : "Port of J1939 device",
			"type" : "string",
			"default" : "/dev/ttyUSB0",
			"displayName" : "Port",
			"order" : "2",
			"mandatory" : "true"
		},
		"baud" : {
			"description" : "Baud rate of J1939 device",
			"type" : "integer",
			"default" : "57600",
			"displayName" : "Baud Rate",
			"order" : "3",
			"mandatory" : "true"
		},
		"bits" : {
			"description" : "Number of data bits for J1939",
			"type" : "integer",
			"default" : "8",
			"displayName" : "Number of Data Bits",
			"order" : "4",
			"mandatory" : "true"
		},
		"stopbits" : {
			"description" : "Number of stop bits for J1939",
			"type" : "integer",
			"default" : "1",
			"displayName" : "Number of Stop Bits",
			"order" : "5",
			"mandatory" : "true"
		},
		"parity" : {
			"description" : "Parity to use",
			"type" : "enumeration",
			"default" : "none",
			"options" : ["none", "odd", "even"],
			"displayName" : "Parity",
			"order" : "6",
			"mandatory": "true"
		}
	});
			

/**
 * The J1939 plugin interface
 */
extern "C" {

/**
 * The plugin information structure
 */
static PLUGIN_INFORMATION info = {
	PLUGIN_NAME,		  // Name
	VERSION,		  // Version
	0,			  // Flags
	PLUGIN_TYPE_SOUTH,	  // Type
	"1.0.0",		  // Interface version
	default_config		  // Default configuration
};

/**
 * Return the information about this plugin
 */
PLUGIN_INFORMATION *plugin_info()
{
	return &info;
}

/**
 * Initialize the plugin, called to get the plugin handle
 */
PLUGIN_HANDLE plugin_init(ConfigCategory *config)
{
J1939 *j1939 = new J1939();

	if (config->itemExists("asset"))
	{
		j1939->setAssetName(config->getValue("asset"));
	}
	else
	{
		j1939->setAssetName("J1939");
	}

	return (PLUGIN_HANDLE)j1939;
}

/**
 * Start the Async handling for the plugin
 */
void plugin_start(PLUGIN_HANDLE *handle)
{
}

/**
 * Poll for a plugin reading
 */
Reading plugin_poll(PLUGIN_HANDLE *handle)
{
J1939 *j1939 = (J1939 *)handle;

	return j1939->takeReading();
}

/**
 * Reconfigure the plugin
 */
void plugin_reconfigure(PLUGIN_HANDLE *handle, string& newConfig)
{
ConfigCategory 	config("j1939", newConfig);
J1939		*j1939 = (J1939 *)*handle;

	if (config.itemExists("asset"))
	{
		j1939->setAssetName(config.getValue("asset"));
	}
}

/**
 * Shutdown the plugin
 */
void plugin_shutdown(PLUGIN_HANDLE *handle)
{
J1939 *j1939 = (J1939 *)handle;

	delete j1939;
}
};

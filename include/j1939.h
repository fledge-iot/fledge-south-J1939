#ifndef _J1939_H
#define _J1939_H
/*
 * Fledge south service plugin
 *
 * Copyright (c) 2020 Nex Computers Inc.
 *
 * Release under the Apache 2.0 License
 *
 * Author: Daniel Man
 */
#include <reading.h>

class J1939 {
	public:
		J1939();
		~J1939();
		Reading		takeReading();
	void	setAssetName(const std::string& assetName)
		{
			m_asset_name = assetName;
		}

	private:
		long		m_lastValue;
		std::string	m_asset_name;
};
#endif

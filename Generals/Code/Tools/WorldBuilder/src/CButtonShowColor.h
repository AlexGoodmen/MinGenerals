/*
** MinGenerals(tm)
** Copyright 2025 CommunityRTS
**
** The above copyright notice applies to additions and/or other modifications
** made to this file by CommunityRTS.
**
** This file incorporates original work covered by the following copyright and
** permission notice:
**
**		Command & Conquer Generals(tm)
**		Command & Conquer Generals Zero Hour(tm)
**		Copyright 2025 Electronic Arts Inc.
**
**		This program is free software: you can redistribute it and/or modify
**		it under the terms of the GNU General Public License as published by
**		the Free Software Foundation, either version 3 of the License, or
**		(at your option) any later version.
**
**		This program is distributed in the hope that it will be useful,
**		but WITHOUT ANY WARRANTY; without even the implied warranty of
**		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**		GNU General Public License for more details.
**
**		You should have received a copy of the GNU General Public License
**		along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifndef _H_CBUTTONSHOWCOLOR_
#define _H_CBUTTONSHOWCOLOR_

class CButtonShowColor : public CButton
{
	protected:
		RGBColor m_color;

	public:
		const RGBColor& getColor(void) const { return m_color; }
		void setColor(Int color) { m_color.setFromInt(color); }
		void setColor(const RGBColor& color) { m_color = color; }
		~CButtonShowColor();
		
		
		static COLORREF RGBtoBGR(Int color);
		static Int BGRtoRGB(COLORREF color);


	protected:
		afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP();
};

#endif /* _H_CBUTTONSHOWCOLOR_ */
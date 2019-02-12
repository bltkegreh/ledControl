#pragma once
#include <cstdint>

enum Color
{
	eColorUnknown,
	eColorRed,
	eColorGreen,
	eColorBlue
};

const uint32_t MAX_BLINK_RATE = 5;

struct PrimitiveLed
{
	PrimitiveLed(Color color) : m_color(color)
	{}

	Color    m_color;
	uint32_t m_blinkFrequencyHz = 0;

	bool operator< (PrimitiveLed const &p) const
	{
		return static_cast<uint32_t>(m_color) < static_cast<uint32_t>(p.m_color);
	}
};
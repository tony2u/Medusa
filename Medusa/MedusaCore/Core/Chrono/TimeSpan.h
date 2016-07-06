// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class TimeSpan
{
public:
	using Duration = std::chrono::nanoseconds;

public:
	TimeSpan(Duration val = Duration(0)) :mDuration(val) {}
	TimeSpan(size_t day, size_t hour, size_t minute, size_t second)
		:mDuration(std::chrono::seconds(second + 60 * (minute + 60 * (hour + 24 * day)))) {}

	TimeSpan(const TimeSpan& timeSpan) :mDuration(timeSpan.mDuration) {}
	TimeSpan& operator=(const TimeSpan& timeSpan) { mDuration = timeSpan.mDuration; return *this; }
public:
	void AddSeconds(int val) { mDuration += std::chrono::seconds(val); }
	void AddMinutes(int minutes) { AddSeconds(minutes * 60); }
	void AddHours(int hours) { AddMinutes(hours * 60); }
	void AddDays(int days) { AddHours(days * 24); }
public:
	static int Compare(const TimeSpan& value1, const TimeSpan& value2) { return value1.CompareTo(value2); }
	int CompareTo(const TimeSpan& val) const { return (int)(mDuration - val.mDuration).count(); }
	bool Equals(const TimeSpan& timeSpan) const { return mDuration == timeSpan.mDuration; }
	static bool Equals(const TimeSpan& value1, const TimeSpan& value2) { return value1.mDuration == value2.mDuration; }

	HeapString ToString() const;
	HeapString ToShortString() const;

	HeapString ToTotalSecondsString() const;

public:
	size_t Days() const { return (size_t)TotalDays(); }
	size_t Hours() const { return (size_t)(TotalHours().count() - Days() * 24); }
	size_t Minutes() const { return (size_t)(TotalMinutes().count() - TotalHours().count() * 60); }
	size_t Seconds() const { return (size_t)(TotalSeconds().count() - TotalMinutes().count() * 60); }

	size_t TotalDays() const { return  TotalHours().count() / 24; }
	std::chrono::hours TotalHours() const { return std::chrono::duration_cast<std::chrono::hours>(mDuration); }
	std::chrono::minutes TotalMinutes() const { return std::chrono::duration_cast<std::chrono::minutes>(mDuration); }
	std::chrono::seconds TotalSeconds() const { return std::chrono::duration_cast<std::chrono::seconds>(mDuration); }
	std::chrono::milliseconds TotalMilliseconds() const { return std::chrono::duration_cast<std::chrono::milliseconds>(mDuration); }
	std::chrono::microseconds TotalMicroseconds() const { return std::chrono::duration_cast<std::chrono::microseconds>(mDuration); }
	std::chrono::nanoseconds TotalNanoseconds() const { return mDuration; }

public:
	bool operator==(const TimeSpan& timeSpan)const { return mDuration == timeSpan.mDuration; }
	bool operator>(const TimeSpan& timeSpan)const { return mDuration > timeSpan.mDuration; }
	bool operator<(const TimeSpan& timeSpan)const { return mDuration < timeSpan.mDuration; }
	bool operator>=(const TimeSpan& timeSpan)const { return mDuration >= timeSpan.mDuration; }
	bool operator<=(const TimeSpan& timeSpan)const { return mDuration <= timeSpan.mDuration; }
	bool operator!=(const TimeSpan& timeSpan)const { return mDuration != timeSpan.mDuration; }

public:
	TimeSpan operator-(const TimeSpan& timeSpan)const { return TimeSpan(mDuration - timeSpan.mDuration); }
	TimeSpan operator+(const TimeSpan& timeSpan)const { return TimeSpan(mDuration + timeSpan.mDuration); }

	TimeSpan& operator-=(const TimeSpan& timeSpan) { mDuration -= timeSpan.mDuration; return *this; }
	TimeSpan& operator+=(const TimeSpan& timeSpan) { mDuration += timeSpan.mDuration; return *this; }
private:
	Duration mDuration;	//nano seconds
};
MEDUSA_END;
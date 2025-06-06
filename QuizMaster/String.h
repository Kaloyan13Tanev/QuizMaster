#pragma once
#include <iostream>

class String
{
public:
	static constexpr size_t factor = 2;

	char* data;
	// Size includes '\0'
	size_t size;
	// Capacity includes '\0'
	size_t capacity;

	void free();
	void copyFrom(const String& other);
	void moveFrom(String&& other);
	void resize(size_t newCapacity);

	void setData(const char* data);

	String();
	String(short data);
	String(unsigned short data);
	String(int data);
	String(unsigned int data);
	String(long data);
	String(unsigned long data);
	String(long long data);
	String(unsigned long long data);
	String(const char* data);
	String(const String& other);
	String(String&& other) noexcept;
	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	~String();

	// Len does not include '\0'
	size_t getLen() const;
	// Size includes '\0'
	size_t getSize() const;
	// Capacity includes '\0'
	size_t getCapacity() const;

	const char* c_str() const;
	String toLower() const;
	String& makeLower();
	String toUpper() const;
	String& makeUpper();
	String trimmed() const;
	String& makeTrimmed();
	// Start and end is inclusive [start, end]
	String substr(size_t start, size_t end) const;

	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);

	char& operator[](size_t indx);
	const char& operator[](size_t indx) const;

	String& operator+=(const String& other);
	String& operator+=(char ch);
	friend String operator+(const String& lhs, const String& rhs);
	friend String operator+(const String& lhs, char rhs);
	friend std::ostream& operator<<(std::ostream& os, const String& str);
	friend std::istream& operator>>(std::istream& is, String& str);
	friend bool operator>(const String& lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const String& rhs);
	friend bool operator<(const String& lhs, const String& rhs);
	friend bool operator<=(const String& lhs, const String& rhs);
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
};
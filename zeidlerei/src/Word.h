#pragma once
#include <string>
class Word
{
public:
	Word(const std::string& base);
	~Word();
	std::string getContent() const { return _base; }
	operator std::string() const { return _base; }
	bool operator<(const Word& other) const { return _base < other._base; }
	bool operator==(const Word& other) const { return _base == other._base; }
	bool operator!=(const Word& other) const { return !(*this == other); }

	int calculateEditDistance(const Word& other) const;
private:
	std::string _base;
};


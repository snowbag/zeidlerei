#pragma once
#include <string>
class Word
{
public:
	Word(const std::string& base);
	~Word();
	std::string getContent() const { return _base; }
	operator std::string() const { return _base; }
	bool operator<(const Word& rhs) const { return _base < rhs._base; }
	bool operator==(const Word& rhs) const { return _base == rhs._base; }
private:
	std::string _base;
};


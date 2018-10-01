#pragma once
#include <map>

template <class T>
class Multiset
{
public:
	Multiset() {}
	~Multiset() {}

	void add(const T &element, const unsigned int &count = 1)
	{
		content[element] += count;
	}

	void remove(const T &element, const unsigned int &count = 1)
	{
		content[element] -= count;
		if (content[element] <= 0) {
			content.erase(element);
		}
	}

	void addAll(const Multiset<T> &other)
	{
		for (auto pair : other.content) {
			content[pair.first] += pair.second;
		}
	}


	int operator[](const T &element)
	{
		return content[element];
	}

	bool contains(const T &element) const
	{
		return content.find(element) != content.end();
	}
private:
	std::map<T, unsigned int> content;
};


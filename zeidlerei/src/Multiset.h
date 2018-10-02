#pragma once
#include <map>

template <class T>
class Multiset
{
public:
	void add(const T& element, const unsigned int& count = 1)
	{
		content_[element] += count;
	}

	void remove(const T& element, const unsigned int& count = 1)
	{
		content_[element] -= count;
		if (content_[element] <= 0) {
			content_.erase(element);
		}
	}

	void addAll(const Multiset<T>& other)
	{
		for (auto pair : other.content_) {
			content_[pair.first] += pair.second;
		}
	}

	int operator[](const T& element)
	{
		return content_[element];
	}

	bool contains(const T& element) const
	{
		return content_.find(element) != content_.end();
	}

	void clear() {
		content_.clear();
	}

	auto begin() { return content_.begin(); }
	auto end() { return content_.end(); }
	auto begin() const { return content_.begin(); }
	auto end() const { return content_.end(); }

	bool operator==(const Multiset<T>& rhs) const {
		return content_ == rhs.content_;
	}
private:
	std::map<T, unsigned int> content_;
};


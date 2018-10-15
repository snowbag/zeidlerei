#pragma once
#include <map>

template <class T>
class Multiset
{
public:
	friend std::ostream& operator<< (std::ostream& stream, const Multiset& multiset) {
		for (auto p : multiset)
		{
			stream << "word: " << p.first.getContent() << "; count: " << p.second << "\n";
		}
		return stream;
	}

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

	auto begin() const { return content_.begin(); }
	auto end() const { return content_.end(); }

	bool operator==(const Multiset<T>& other) const {
		return content_ == other.content_;
	}

	bool operator!=(const Multiset<T>& other) const {
		return !(*this == other);
	}

	int size() const {
		int sum = 0;
		std::for_each(content_.begin(), content_.end(), [&](auto pair) {
			sum += pair.second;
		});
		return sum;
	}
private:
	std::map<T, unsigned int> content_;
};


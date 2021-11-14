#pragma once
#include <string>
#include <iostream>
#include <vector>

class FormattedText {
public:
	struct TextRange {
		int start, end;
		bool capitalize;

		bool covers(int position) const {
			return position >= start && position <= end;
		}
		TextRange(int s, int e) : start(s), end(e) {}
	};

	TextRange& get_range(int start, int end) {
		formatting.emplace_back(start, end);
		return *formatting.rbegin();
	}
	friend std::ostream& operator<<(std::ostream& os, const FormattedText& obj) {
		std::string s;
		for (std::size_t i = 0; i < obj.plain_text.length(); ++i) {
			auto c = obj.plain_text[i];
			for (const auto& rng : obj.formatting) {
				if (rng.covers(i) && rng.capitalize) {
					c = std::toupper(c);
				}
			}
			s += c;
		}
		return os << s;
	}

	FormattedText(std::string s) : plain_text(std::move(s)) {}
private:
	std::string plain_text;
	std::vector<TextRange> formatting;
};
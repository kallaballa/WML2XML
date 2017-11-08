#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace b = boost;

using std::string;
using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::map;

struct Tag {
	string name_;
	map<string, string> attributes_;
	vector<Tag*> children_;
	Tag* parent_ = NULL;
};

void encode_xml_attr_key(std::string& data) {
	b::replace_all(data, " ", "_");
	b::replace_all(data, "<", "_");
}

void encode_xml_attr_val(std::string& data) {
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        switch(data[pos]) {
            case '&':  buffer.append("&amp;");       break;
            case '\"': buffer.append("&quot;");      break;
            case '\'': buffer.append("&apos;");      break;
            case '<':  buffer.append("&lt;");        break;
            case '>':  buffer.append("&gt;");        break;
            default:   buffer.append(&data[pos], 1); break;
        }
    }
    data.swap(buffer);
}

void to_xml(Tag& tag) {
	if(tag.name_ == "lua" || tag.name_ == "message")
		return;
	cout << '<' << tag.name_ << ' ';
	string key;
	for(auto& attr : tag.attributes_) {
		encode_xml_attr_val(attr.second);
		key = attr.first;
		encode_xml_attr_key(key);
		if(key == "terrain")
			continue;
		cout << key << "=\"" << attr.second << "\" ";
	}
	cout << '>';
	for(auto& child : tag.children_) {
		to_xml(*child);
	}
	cout << "</" << tag.name_ << '>' << endl;
}

int main(int argc, char* argv[]) {
	string line;
	string name;
	string key;
	string value;

	Tag root = { "replay", {}, {}, NULL};
	Tag* current = &root;
	while(getline(std::cin, line)) {
		b::trim(line);
		if(line.empty() || line.at(0) == '#' || line.at(0) == '<' || line.at(0) == '"'  || line.at(0) == '$')
			continue;

		if(line.at(0) == '[') {
			assert(line.length() > 2);
			assert(line.at(line.length() - 1) == ']');

			if(line.at(1) == '/') {
				assert(line.length() > 3);
				name = line.substr(2, line.length() - 3);
				assert(name == current->name_);
				if(current->parent_ != NULL) {
					current = current->parent_;
				} else {
					break; // root node ended
				}
			} else {
				name = line.substr(1, line.length() - 2);
				Tag* child = new Tag{ name, {}, {}, current};
				current->children_.push_back(child);
				current = child;
			}
		} else {
			size_t ei;
			if(line.length() < 3 || (ei = line.find('=')) == string::npos)
				continue;
			key = line.substr(0, ei);
			value = line.substr(ei + 1);
			if(value.length() > 1) {
				if(value.at(0) == '"' && value.at(value.length() - 1) != '"')
					continue;
				else if((value.at(0) == '"' && value.at(value.length() - 1) == '"'))
					value = value.substr(1, value.length() - 2);
			}
			current->attributes_[key] = value;
		}
	}
	assert(current == &root);
	cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
	to_xml(root);
}

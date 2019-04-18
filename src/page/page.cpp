/**
 * This file contains implementations for methods in the Page class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page/page.h"

using namespace std;


// Ensure PAGE_SIZE is initialized.
const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
  vector<char> input_bytes;
  if (in.peek() == EOF) return nullptr;
  while (in.good() && input_bytes.size() < Page::PAGE_SIZE) {
  	if (in.peek() != EOF) {
  		input_bytes.push_back(in.get()); // Extracts next bit from filestream
  	}
  }
  Page* new_page = new Page(input_bytes);
  return new_page;
}


size_t Page::size() const {
  return bytes.size();
}


bool Page::is_valid_offset(size_t offset) const {
  if (offset <= bytes.size() - 1) return true;
  else return false;
}


char Page::get_byte_at_offset(size_t offset) {
  if(is_valid_offset(offset)) return bytes[offset];
}

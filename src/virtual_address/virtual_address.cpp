/**
 * This file contains implementations for methods in the VirtualAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "virtual_address/virtual_address.h"
#include <bitset>

using namespace std;

size_t bin_to_dec(size_t n) {
	size_t dec = 0; 
    size_t base = 1;  
    
    while (n) { 
    size_t last_digit = n % 10; 
    n = n/10;
    dec += last_digit * base; 
    base = base * 2; 
    }  
	return dec; 
}

string binary_page(size_t n) {
  bitset<10> page_bin(n);
  return page_bin.to_string();
}

string binary_offset(size_t n) {
  bitset<6> offset_bin(n);
  return offset_bin.to_string();
}

VirtualAddress VirtualAddress::from_string(int process_id, string address) {
  string page_string = address.substr(0, PAGE_BITS);
  string offset_string = address.substr(PAGE_BITS, OFFSET_BITS);
  size_t page_input = (size_t)stoi(page_string);
  size_t offset_input = (size_t)stoi(offset_string);
  page_input = bin_to_dec(page_input);
  offset_input = bin_to_dec(offset_input);
  return VirtualAddress(process_id, page_input, offset_input);
}


string VirtualAddress::to_string() const {
  return binary_page(page) + binary_offset(offset);
}


ostream& operator <<(ostream& out, const VirtualAddress& address) {
  out << "PID "<< address.process_id << " @ " << address.to_string() << " [page: " << address.page << "; offset: " << address.offset << "]";
  return out;
}
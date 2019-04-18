/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"
#include <bitset>

using namespace std;

string binary_frame(int n) {
  bitset<10> frame_bin(n);
  return frame_bin.to_string();
}

string binary_offset(int n) {
  bitset<6> offset_bin(n);
  return offset_bin.to_string();
}

string PhysicalAddress::to_string() const {
  return binary_frame(frame) + binary_offset(offset);
}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
  out << address.to_string() << " [frame: " << address.frame << "; offset: " << address.offset << "]";
  return out;
}

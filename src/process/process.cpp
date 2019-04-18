/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"
#include <cmath>

using namespace std;


Process* Process::read_from_input(std::istream& in) {
  vector<Page*> input_pages;
  size_t bytes = 0;
  while (!in.eof()) {
    Page* page = page->read_from_input(in);
    input_pages.push_back(page);
    bytes += page->size();
  }
  Process* process = new Process(bytes, input_pages);
  return process;
}


size_t Process::size() const {
  return num_bytes;
}


bool Process::is_valid_page(size_t index) const {
  if (index <= pages.size() - 1) return true;
  return false;
}


size_t Process::get_rss() const {
  int rss = 0;
  for (int i = 0; i < page_table.rows.size(); i++) {
    if (page_table.rows[i].present) rss++;
  }
  return rss;
}


double Process::get_fault_percent() const {
  float percent;
  if (memory_accesses == 0) percent = 0; // Can't have any faults if there are no accesses *Insert meme here*
  else percent = 100 * (float)page_faults / (float)memory_accesses;
  return round(percent);
}

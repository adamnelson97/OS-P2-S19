/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"

using namespace std;


size_t PageTable::get_present_page_count() const {
  size_t count = 0;
  for (int i = 0; i < rows.size(); i++) { if (rows[i].present) count++; }
  return count;
}


size_t PageTable::get_oldest_page() const {
  size_t index = 0;
  // Get oldest present row
  Row oldest;
  for (int i = 0; i < rows.size(); i++) {
    if (rows[i].present) {
      oldest = rows[i];
    }
    break;
  }
  for (int i = 0; i < rows.size(); i++) {
  	if (rows[i].present && rows[i].loaded_at < oldest.loaded_at) {
  		index = i;
  		oldest = rows[i];
  	}
  }
  return index;
}


size_t PageTable::get_least_recently_used_page() const {
  size_t index = 0;
  Row recent = rows[0]; // Initial row for comparisons
  for (int i = 0; i < rows.size(); i++) {
  	if (rows[i].present && (rows[i].last_accessed_at < recent.last_accessed_at)) {
  		index = i;
  		recent = rows[i];
  	}
  }
  return index;
}
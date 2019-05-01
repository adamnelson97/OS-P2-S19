/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"
#include <iostream>

using namespace std;

void Simulation::run() {
  for(size_t i = 0; i < vir_mem_accesses.size(); i++) {
    perform_memory_access(vir_mem_accesses[i], i);
  }
  cout << "DONE!" << endl;
  cout << "STRATEGY: " << flush;
  if (flags.strategy == ReplacementStrategy::LRU) cout << "LRU\n" << endl;
  else cout << "FIFO\n" << endl;
  
  int accesses = 0;
  int page_faults = 0;
  int used_frames = 0;
  
  for (size_t j = 0; j < NUM_FRAMES; j++) {
  	if (main_memory[j].contents) used_frames++;
  }
  for (size_t k = 0; k < prcs_table.size(); k++) {
  	cout << "PROCESS " << prcs_table[k]->process_id 
  	<< "\tACCESSES: " << prcs_table[k]->memory_accesses 
  	<< "\tPAGE FAULTS: " << prcs_table[k]->page_faults 
  	<< "\tFAULT RATE: " << prcs_table[k]->get_fault_percent() 
  	<< "\tRSS: " << prcs_table[k]->get_rss() 
    << "\tPROC. SIZE: " << prcs_table[k]->size() << endl;
  }
  for (size_t l = 0; l < prcs_table.size(); l++) {
  	page_faults += prcs_table[l]->page_faults;
  }
  for (size_t m = 0; m < prcs_table.size(); m++) {
  	accesses += prcs_table[m]->memory_accesses;
  }
  
  cout << "\nTotal memory accesses: " << accesses << endl;
  cout << "Total page faults: " << page_faults << endl;
  cout << "Free frames remaining: " << NUM_FRAMES - used_frames << endl;
}

char Simulation::perform_memory_access(const VirtualAddress& address, size_t time) {
  size_t frame_process = 0;
  for (size_t i = 0; i < prcs_table.size(); i++) {
  	if (prcs_table[i]->process_id == address.process_id) {
  	  frame_process = i;
  	}
  }
  size_t frame = prcs_table[frame_process]->page_table.rows[address.page].frame;
  PhysicalAddress p_address(frame, address.offset);
  prcs_table[frame_process]->memory_accesses++;
  if (prcs_table[frame_process]->page_table.rows[address.page].present) {
    if (flags.verbose) {
      cout << "  -> IN MEMORY" << endl;
    }
  }
  else handle_page_fault(prcs_table[frame_process], address.page);
  if (flags.verbose) {
	cout << address << endl;	
  	cout << "  -> physical address " << p_address << endl;
  	cout << "  -> RSS: " << prcs_table[frame_process]->get_rss() << endl;
  }
  if (main_memory[frame].contents->is_valid_offset(p_address.offset)) {
  	return main_memory[frame].contents->get_byte_at_offset(p_address.offset);
  }
  else {
    cout << "SIMULATION Segmentation Fault" << endl;
    exit(EXIT_FAILURE);
  }
}

void Simulation::handle_page_fault(Process*& process, size_t page) {
  if (flags.verbose) {
    cout << "  -> PAGE FAULT" << endl;
  }

  size_t frame = 0;
  size_t replacement_frame;

  if (available_frames > 0 && process->get_rss() < (size_t)flags.max_frames) {
    available_frames--;
    frame = frame_index;
    frame_index++;
  } else {
    if (flags.strategy == ReplacementStrategy::LRU) {
      replacement_frame = process->page_table.get_least_recently_used_page();
    } else {
      replacement_frame = process->page_table.get_oldest_page();
    }
    process->page_table.rows[replacement_frame].present = false;
    frame = process->page_table.rows[replacement_frame].frame;
  }

  process->page_faults++;
  process->page_table.rows[page].frame = frame;
  process->page_table.rows[page].present = true;
  process->page_table.rows[page].loaded_at = process->memory_accesses;
}
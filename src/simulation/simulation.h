/**
 * This file contains the definition of the Simulation class.
 *
 * You're free to modify this class however you see fit. Add new methods to help
 * keep your code modular.
 */

#pragma once
#include "process/process.h"
#include "frame/frame.h"
#include "page_table/page_table.h"
#include "flag_parser/flag_parser.h"
#include "physical_address/physical_address.h"
#include "virtual_address/virtual_address.h"
#include <cstdlib>
#include <vector>

using namespace std;

/**
 * Class responsible for running the memory simulation.
 */
class Simulation {
// PUBLIC CONSTANTS
public:
  /**
   * The maximum number of frames in the simulated system (512).
   */
  static const size_t NUM_FRAMES = 1 << 9;
  FlagOptions flags;
  vector<Process*> prcs_table;
  vector<VirtualAddress> vir_mem_accesses;
  Frame main_memory[NUM_FRAMES];
  Simulation(FlagOptions flags, vector<Process*> prcs_table, vector<VirtualAddress> vir_mem_accesses, Frame* main_memory)
  : flags(flags),prcs_table(prcs_table),vir_mem_accesses(vir_mem_accesses) {
    for (size_t i = 0; i < NUM_FRAMES; i++){
      this->main_memory[i] = main_memory[i];
    }
  }
// PUBLIC API METHODS
public:

  /**
   * Runs the simulation.
   */
  void run();
// PRIVATE METHODS
private:

  /**
   * Performs a memory access for the given virtual address, translating it to
   * a physical address and loading the page into memory if needed. Returns the
   * byte at the given address.
   */
  char perform_memory_access(const VirtualAddress& address, size_t time);

  /**
   * Handles a page fault, attempting to load the given page for the given
   * process into memory.
   */
  void handle_page_fault(Process*& process, size_t page, size_t frame, size_t time);


// INSTANCE VARIABLES
private:
};
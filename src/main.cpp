/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
 */

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "simulation/simulation.h"
#include "flag_parser/flag_parser.h"

using namespace std;

void read_input_files(ifstream &in, vector<int>& PID_vec, vector<Process*>& process_vec, 
  vector<VirtualAddress>& vir_mem_accesses, Frame* main_memory, size_t max_frames);

/**
 * The main entry point to the simulation.
 */
int main(int argc, char** argv) {
  Frame main_memory[Simulation::NUM_FRAMES];
  vector<int> PID_vec;
  vector<Process*> process_vec;
  vector<VirtualAddress> vir_mem_accesses;
  FlagOptions flags;
  if (parse_flags(argc, argv, flags)) {
    ifstream in(flags.filename);
    read_input_files(in, PID_vec, process_vec, vir_mem_accesses, main_memory, flags.max_frames);
    Simulation sim(flags,process_vec,vir_mem_accesses,main_memory);
    cout << "\nRunning simulation...\n" << endl;
    sim.run();
    return EXIT_SUCCESS;
  }
  else {
    return EXIT_FAILURE;
  }
}

void read_input_files(ifstream &in, vector<int>& PID_vec, vector<Process*>& process_vec, 
  vector<VirtualAddress>& vir_mem_accesses, Frame* main_memory, size_t max_frames) {

  int num_proc;
  in >> num_proc;
  vector<string> proc_file_vec;
  for (int i = 0; i < num_proc; i++) {
    int process_id;
    string process_file;
    in >> process_id;
    PID_vec.push_back(process_id);
    in >> process_file;
    proc_file_vec.push_back(process_file);
  }
  for (int i = 0; i < num_proc; i++) {
    ifstream process_in(proc_file_vec[i]);
    Process* process = Process::read_from_input(process_in);
    process->process_id = PID_vec[i];
    process_vec.push_back(process);
  }
  for (int i = 0; i < num_proc; i++) {
    for (int j = 0; j < max_frames; j++) {
      j += i*max_frames;
      Frame frame;
      frame.set_page(process_vec[i], j);
      main_memory[j] = frame;
      for(int k = 0; k < process_vec[i]->page_table.rows.size(); k++) {
        process_vec[i]->page_table.rows[k].frame = j;
      }
      j -= i*max_frames;
    }
  }
  while (!in.eof()) {
    int process_id;
    string binary;
    in >> process_id >> binary;
    if (binary.empty()) break;
    cout << "Process " << process_id << " accesses " << binary << endl;
    VirtualAddress virt = VirtualAddress::from_string(process_id, binary);
    vir_mem_accesses.push_back(virt);
  }
}
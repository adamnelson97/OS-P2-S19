/**
 * This file contains implementations for methods in the flag_parser.h file.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "flag_parser/flag_parser.h"
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;


void print_usage() {
  cout <<
      "Usage: mem-sim [options] filename\n"
      "\n"
      "Options:\n"
      "  -v, --verbose\n"
      "      Output information about every memory access.\n"
      "\n"
      "  -s, --strategy (FIFO | LRU)\n"
      "      The replacement strategy to use. One of FIFO or LRU.\n"
      "\n"
      "  -f, --max-frames <positive integer>\n"
      "      The maximum number of frames a process may be allocated.\n"
      "\n"
      "  -h --help\n"
      "      Display a help message about these flags and exit\n"
      "\n";
}

bool is_number(const std::string &s) {
  bool all_valid = true;
  for (int i = 0; i < s.size(); i++) {
    if (!isdigit(s[i])) {
      all_valid = false;
      break;
    }
  }
  return !s.empty() && all_valid;
}

bool parse_flags(int argc, char** argv, FlagOptions& flags) {
  if (argc == 1) return false; // No filename specified

  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) flags.verbose = true;
    
    else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--strategy") == 0) {
      if (i + 1 == argc) return false; // s flag is last argument in command, no strategy specified
      else if (strcmp(argv[i + 1], "FIFO") == 0) flags.strategy = ReplacementStrategy::FIFO;
      else if (strcmp(argv[i + 1], "LRU") == 0) flags.strategy = ReplacementStrategy::LRU;
      else return false; // Strategy specified is not valid
    }
    
    else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--max-frames") == 0) {
      if (i + 1 == argc) return false; // No integer specified
      else {
        if (is_number(argv[i + 1])) {
          flags.max_frames = stoi(argv[i + 1]);
          if (flags.max_frames == 0) return false; // Breaks simulation
        }
        else return false;
      }
    }

    else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      print_usage();
      return false;
    }

    else flags.filename = argv[i];
  }

  return true; // All flags processed correctly and are valid.
}
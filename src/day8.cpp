#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Operation { kNop = 0, kAcc = 1, kJmp = 2 };

struct Instruction {
  Operation op;
  int val;
};

vector<Instruction> instructions;

void LoadInput() {
  fstream file("../input/day8.txt", ios::in);
  string line;
  string sop, sval;

  while (getline(file, line)) {
    Instruction ins;

    sop = line.substr(0, 3);
    sval = line.substr(4, line.size());

    ins.op = sop == "acc"   ? Operation::kAcc
             : sop == "jmp" ? Operation::kJmp
                            : Operation::kNop;
    ins.val = stoi(sval);

    instructions.push_back(ins);
  }

  file.close();
}

int RunInstruction(int &accumulator, const int &index) {
  if (index < instructions.size()) {
    switch (instructions[index].op) {
    case kJmp:
      return index + instructions[index].val;
      break;
    case kAcc:
      accumulator += instructions[index].val;
    case kNop:
      return index + 1;
    }
  }

  return -1;
}

tuple<int, int, bool> RunProgram() {
  vector<bool> completed_instructions(instructions.size());

  int accumulator = 0;
  int index = 0;

  do {
    if (!completed_instructions[index]) {
      completed_instructions[index] = true;

      index = RunInstruction(accumulator, index);
    } else {
      return make_tuple(index, accumulator, false);
    }
  } while (index != -1);

  return make_tuple(index, accumulator, true);
}

int main() {
  LoadInput();

  int mod_index = -1;
  tuple<int, int, bool> result;

  auto swap = [&] (const int &i) -> bool {
    switch (instructions[i].op) {
      case kJmp:
        instructions[i].op = Operation::kNop;
        break;
      case kNop:
        instructions[i].op = Operation::kJmp;
        break;
      case kAcc:
        return false;
    }

    return true;
  };

  auto swap_next = [&] (const int &i) {
    for (int j = i + 1; j < instructions.size(); j++) {
      if (swap(j)) {
        mod_index = j;
        break;
      }
    }
  };

  do {
    result = RunProgram();

    swap(mod_index);
    swap_next(mod_index);
  } while (!get<2>(result));

  cout << get<1>(result) << endl;
}

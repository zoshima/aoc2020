#include <fstream>
#include <iostream>
#include <numeric>
#include <stack>
#include <vector>

using namespace std;

void ApplyOperator(long& lop, const char& op, const long& rop) {
  switch (op) {
    case '+':
      lop += rop;
      break;
    case '*':
      lop *= rop;
      break;
    default:
      break;
  }
}

int main() {
  ifstream file{"../input/day18.txt"};  // end with nl
  vector<long> results;
  stack<char> scp_operators;
  stack<long> scp_operands;

  char c;

  auto add_scope = [&]() {
    scp_operators.push('+');
    scp_operands.push(0);
  };

  auto pop_scope = [&]() {
    scp_operators.pop();
    scp_operands.pop();
  };

  add_scope();

  while (file >> noskipws >> c) {
    switch (c) {
      case '+':
      case '*':
        scp_operators.top() = c;
        break;
      case '(':
        add_scope();
        break;
      case ')': {
        long val = scp_operands.top();

        pop_scope();

        ApplyOperator(scp_operands.top(), scp_operators.top(), val);
        break;
      }
      case '\n': {
        long val = scp_operands.top();

        results.push_back(val);

        pop_scope();
        add_scope();
        break;
      }
      case ' ':
        break;
      default:
        ApplyOperator(scp_operands.top(), scp_operators.top(), c - '0');
        break;
    }
  }

  long sum = accumulate(results.begin(), results.end(), 0L);

  cout << sum << endl;
}
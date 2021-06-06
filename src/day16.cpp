#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

struct Range {
  int start;
  int end;
};

using Ticket = vector<int>;
using RangePair = pair<Range, Range>;

const regex range_pattern("^.+:\\ (\\d+)-(\\d+) or (\\d+)-(\\d+)");

Ticket my_ticket;
vector<Ticket> nearby_tickets;
vector<RangePair> ranges;

Ticket GetTicket(const string &s) {
  istringstream ss(s);
  string st;
  Ticket t;

  while (getline(ss, st, ',')) {
    t.push_back(stoi(st));
  }

  return t;
}

void LoadInput() {
  ifstream file("../input/day16.txt");
  string line;
  smatch sm;

  while (getline(file, line) && line.size()) {
    regex_search(line, sm, range_pattern);

    ranges.push_back({{stoi(sm[1]), stoi(sm[2])}, {stoi(sm[3]), stoi(sm[4])}});
  }

  getline(file, line); // "your ticket:"
  getline(file, line);

  my_ticket = GetTicket(line);

  getline(file, line);
  getline(file, line); // "nearby tickets:"

  while (getline(file, line)) {
    nearby_tickets.push_back(GetTicket(line));
  }
}

const bool Includes(const Range &range, const int num) {
  for (int i = range.start; i <= range.end; ++i) {
    if (i == num) {
      return true;
    }
  }

  return false;
}

int main() {
  LoadInput();

  vector<int> invalid_values;

  for (const auto &ticket : nearby_tickets) {
    for (const int &i : ticket) {
      bool is_valid = false;

      for (const RangePair &rp : ranges) {
        if (Includes(rp.first, i) || Includes(rp.second, i)) {
          is_valid = true;
          break;
        }
      }

      if (!is_valid) {
        invalid_values.push_back(i);
      }
    }
  }

  cout << accumulate(invalid_values.begin(), invalid_values.end(), 0) << endl;
}

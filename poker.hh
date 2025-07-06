#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace euler_poker {

using Card = std::pair<int, char>;
using Hand = std::vector<Card>;
using ScoreResult = std::pair<bool, std::vector<int>>;
using ScoreFunc = std::function<ScoreResult(const Hand&)>;
using ScorePair = std::pair<std::string, ScoreFunc>;
using ScoreInfo = std::tuple<int, std::string, std::vector<int>>;

const std::map<char, int> values = {{'2', 2},  {'3', 3},  {'4', 4}, {'5', 5},  {'6', 6},
                                    {'7', 7},  {'8', 8},  {'9', 9}, {'T', 10}, {'J', 11},
                                    {'Q', 12}, {'K', 13}, {'A', 14}};

Hand parse_hand(const std::vector<std::string>& cards);
std::vector<int> discarded(const Hand& hand, const std::vector<int>& skips);
ScoreResult high_card(const Hand& hand);
std::map<int, int> count_ranks(const Hand& hand);
std::map<char, int> count_suits(const Hand& hand);
template <typename T>
int max_rank(const T& c);
ScoreResult one_pair(const Hand& hand);
ScoreResult two_pairs(const Hand& hand);
ScoreResult three_of_a_kind(const Hand& hand);
ScoreResult full_house(const Hand& hand);
bool consecutive(const Hand& hand);
ScoreResult straight(const Hand& hand);
ScoreResult flush(const Hand& hand);
ScoreResult straight_flush(const Hand& hand);
ScoreResult royal_flush(const Hand& hand);
ScoreResult four_of_a_kind(const Hand& hand);
ScoreInfo best_score(const Hand& hand);
int winner(const Hand& p1, const Hand& p2);

// Implementation

Hand parse_hand(const std::vector<std::string>& cards) {
  Hand hand;
  for (const auto& cs : cards) {
    char rank = cs[0];
    char suit = cs[1];
    hand.emplace_back(values.at(rank), suit);
  }
  std::sort(hand.begin(), hand.end());
  return hand;
}

std::vector<int> discarded(const Hand& hand, const std::vector<int>& skips) {
  std::vector<int> result = skips;
  for (auto it = hand.rbegin(); it != hand.rend(); ++it) {
    int rank = it->first;
    if (std::find(skips.begin(), skips.end(), rank) == skips.end()) {
      result.push_back(rank);
    }
  }
  return result;
}

ScoreResult high_card(const Hand& hand) { return {true, discarded(hand, {})}; }

std::map<int, int> count_ranks(const Hand& hand) {
  std::map<int, int> c;
  for (const auto& [rank, suit] : hand) {
    c[rank]++;
  }
  return c;
}

std::map<char, int> count_suits(const Hand& hand) {
  std::map<char, int> c;
  for (const auto& [rank, suit] : hand) {
    c[suit]++;
  }
  return c;
}

template <typename T>
int max_rank(const T& c) {
  if (c.empty()) return 0;
  return std::max_element(c.begin(), c.end(),
                          [](auto& a, auto& b) { return a.second < b.second; })
      ->second;
}

ScoreResult one_pair(const Hand& hand) {
  auto c = count_ranks(hand);
  if (max_rank(c) != 2) {
    return {false, {}};
  }
  std::vector<int> ranks;
  for (auto& [k, v] : c) {
    if (v == 2) {
      ranks.push_back(k);
    }
  }
  if (ranks.size() != 1) {
    return {false, {}};
  }
  return {true, discarded(hand, {ranks[0]})};
}

ScoreResult two_pairs(const Hand& hand) {
  auto c = count_ranks(hand);
  if (max_rank(c) != 2) return {false, {}};
  std::vector<int> ranks;
  for (auto& [k, v] : c)
    if (v == 2) ranks.push_back(k);
  if (ranks.size() != 2) return {false, {}};
  int r1 = std::max(ranks[0], ranks[1]);
  int r2 = std::min(ranks[0], ranks[1]);
  return {true, discarded(hand, {r1, r2})};
}

ScoreResult three_of_a_kind(const Hand& hand) {
  auto c = count_ranks(hand);
  if (max_rank(c) != 3) return {false, {}};
  if (std::any_of(c.begin(), c.end(), [](auto& p) { return p.second == 2; })) return {false, {}};
  std::vector<int> ranks;
  for (auto& [k, v] : c)
    if (v == 3) ranks.push_back(k);
  return {true, discarded(hand, ranks)};
}

ScoreResult full_house(const Hand& hand) {
  auto c = count_ranks(hand);
  bool has3 = std::any_of(c.begin(), c.end(), [](auto& p) { return p.second == 3; });
  bool has2 = std::any_of(c.begin(), c.end(), [](auto& p) { return p.second == 2; });
  if (!has3 || !has2) return {false, {}};
  int big = 0, small = 0;
  for (auto& [k, v] : c)
    if (v == 3) big = k;
  for (auto& [k, v] : c)
    if (v == 2) small = k;
  return {true, discarded(hand, {big, small})};
}

bool consecutive(const Hand& hand) {
  for (size_t i = 1; i < hand.size(); ++i)
    if (hand[i].first != hand[i - 1].first + 1) return false;
  return true;
}

ScoreResult straight(const Hand& hand) {
  if (!consecutive(hand)) return {false, {}};
  std::vector<int> r;
  for (auto it = hand.rbegin(); it != hand.rend(); ++it) r.push_back(it->first);
  return {true, r};
}

ScoreResult flush(const Hand& hand) {
  auto c = count_suits(hand);
  if (max_rank(c) != 5) return {false, {}};
  std::vector<int> r;
  for (auto it = hand.rbegin(); it != hand.rend(); ++it) r.push_back(it->first);
  return {true, r};
}

ScoreResult straight_flush(const Hand& hand) {
  auto s = straight(hand);
  if (!s.first) return {false, {}};
  auto f = flush(hand);
  if (!f.first) return {false, {}};
  return s;
}

ScoreResult royal_flush(const Hand& hand) {
  if (!consecutive(hand)) return {false, {}};
  auto c_suit = count_suits(hand);
  if (max_rank(c_suit) != 5) return {false, {}};
  if (hand[0].first != 10) return {false, {}};
  std::vector<int> r;
  for (auto it = hand.rbegin(); it != hand.rend(); ++it) r.push_back(it->first);
  return {true, r};
}

ScoreResult four_of_a_kind(const Hand& hand) {
  auto c = count_ranks(hand);
  if (max_rank(c) != 4) return {false, {}};
  std::vector<int> ranks;
  for (auto& [k, v] : c)
    if (v == 4) ranks.push_back(k);
  return {true, discarded(hand, ranks)};
}

const std::vector<ScorePair> scores = {
    {"royal_flush", royal_flush},
    {"straight_flush", straight_flush},
    {"four_of_a_kind", four_of_a_kind},
    {"full_house", full_house},
    {"flush", flush},
    {"straight", straight},
    {"three_of_a_kind", three_of_a_kind},
    {"two_pairs", two_pairs},
    {"one_pair", one_pair},
    {"high_card", high_card},
};

ScoreInfo best_score(const Hand& hand) {
  for (size_t i = 0; i < scores.size(); ++i) {
    const auto& [name, func] = scores[i];
    auto [res, val] = func(hand);
    if (res) {
      return {static_cast<int>(scores.size() - i), name, val};
    }
  }
  return {0, "none", {}};
}

int winner(const Hand& p1, const Hand& p2) {
  auto [s1, n1, v1] = best_score(p1);
  auto [s2, n2, v2] = best_score(p2);
  if (std::tie(s1, v1) > std::tie(s2, v2))
    return 1;
  else
    return 2;
}

}  // namespace euler_poker

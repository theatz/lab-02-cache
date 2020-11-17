//
// Created by theatz on 16.11.2020.
//

#ifndef LAB_02_CACHE_INVESTIGATOR_HPP
#define LAB_02_CACHE_INVESTIGATOR_HPP
#include <iostream>
#include <vector>
#include <chrono>

struct Investigation{
  std::string type;
  uint32_t number;
  double time;
};

class Investigator {
public:
  Investigator(uint32_t L1, uint32_t L3);
  ~Investigator();
  void WarmupDirect(uint32_t* array, uint32_t size);
  void WarmupReverse(uint32_t* array, uint32_t size);
  void WarmupRandom(uint32_t* array, uint32_t size);
  uint32_t* CreateArray(uint32_t size);
  void DirectTest();
  void ReverseTest();
  void RandomTest();
  void ClearOutput();
  void Graf();
private:
  std::vector<struct Investigation> _result;
  std::vector<uint32_t> _mas;
};

#endif  // LAB_02_CACHE_INVESTIGATOR_HPP

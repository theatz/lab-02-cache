//Copyright 2020 theatz
//
// Created by theatz on 16.11.2020.
//
#include "Investigator.hpp"

Investigator::Investigator(uint32_t L1, uint32_t L3){
  uint32_t current = L1 / 2;
  while (current < 3 * L3 / 2) {
    _mas.push_back(current * 256);
    current *= 2;
  }
  _mas.push_back(3 * L3 * 128);
  DirectTest();
  ReverseTest();
  RandomTest();
  ClearOutput();
  //Graf();
}

Investigator::~Investigator() {
}

void Investigator::DirectTest() {
  uint32_t* array = nullptr;
  uint32_t ArraySize = _mas.size();
  uint32_t TestCount = 1000;
  uint32_t current = 0;
  uint32_t ArrayLength = 0;
  ArraySize += ArrayLength;
  current += current;
  int64_t EntireTime = 0;
  struct Investigation NewInvestigation;

  for (uint32_t i = 0; i < ArraySize; ++i) {
    ArrayLength = _mas[i];
    array = CreateArray(ArrayLength);
    WarmupDirect(array, ArrayLength);
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t j = 0; j < TestCount; ++j) {
      for (uint32_t k = 0; k < ArrayLength; k += 16) current = array[k];
      }

    auto finish = std::chrono::high_resolution_clock::now();
    EntireTime =
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
            .count();
    NewInvestigation.number = i;
    NewInvestigation.time = static_cast<double>(EntireTime) / 1000.0;
    NewInvestigation.type = "Direct";
    _result.push_back(NewInvestigation);
    delete[] array;
  }
}

void Investigator::ReverseTest() {
  uint32_t* array = nullptr;
  uint32_t ArraySize = _mas.size();
  uint32_t TestCount = 1000;
  uint32_t current = 0;
  uint32_t ArrayLength = 0;
  ArraySize += ArrayLength;
  current += current;
  int64_t EntireTime = 0;
  struct Investigation NewInvestigation;

  for (uint32_t i = 0; i < ArraySize; ++i) {
    ArrayLength = _mas[i];
    array = CreateArray(ArrayLength);
    WarmupReverse(array, ArrayLength);
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t j = 0; j < TestCount; ++j) {
      for (uint32_t k = ArrayLength; k > 0; k -= 16) current = array[k];
    }

    auto finish = std::chrono::high_resolution_clock::now();
    EntireTime =
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
            .count();
    NewInvestigation.number = i;
    NewInvestigation.time = static_cast<double>(EntireTime) / 1000.0;
    NewInvestigation.type = "Reverse";
    _result.push_back(NewInvestigation);
    delete[] array;
  }
}

uint32_t RandomNumber(uint32_t lower, uint32_t upper){
  return lower + random() % (upper - lower + 1);
}

void Investigator::RandomTest() {
  uint32_t* array = nullptr;
  uint32_t ArraySize = _mas.size();
  uint32_t TestCount = 1000;
  uint32_t current = 0;
  uint32_t ArrayLength = 0;
  ArraySize += ArrayLength;
  current += current;
  int64_t EntireTime = 0;
  struct Investigation NewInvestigation;

  for (uint32_t i = 0; i < ArraySize; ++i) {
    ArrayLength = _mas[i];
    array = CreateArray(ArrayLength);
    WarmupRandom(array, ArrayLength);
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t j = 0; j < TestCount; ++j) {
      for (uint32_t k = 0; k < ArrayLength / 16; ++k)
        current = array[RandomNumber(0, ArrayLength - 1)];
    }

    auto finish = std::chrono::high_resolution_clock::now();
    EntireTime =
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
            .count();
    NewInvestigation.number = i;
    NewInvestigation.time = static_cast<double>(EntireTime) / 1000.0;
    NewInvestigation.type = "Random";
    _result.push_back(NewInvestigation);
    delete[] array;
  }
}

uint32_t* Investigator::CreateArray(uint32_t size) {
  uint32_t* array = new uint32_t[size];
  return array;
}

void Investigator::WarmupDirect(uint32_t* array, uint32_t size) {
  uint32_t current = 0;
  current += current;
  for (uint32_t i = 0; i < size; i += 16)
    current = array[i];
}

void Investigator::WarmupReverse(uint32_t* array, uint32_t size) {
  uint32_t current = 0;
  current += current;
  for (uint32_t i = size; i == 0 ; i -= 16)
    current = array[i];
}

void Investigator::WarmupRandom(uint32_t* array, uint32_t size) {
  for (uint32_t i = size; i > 0 ; i -= 16)
    array[RandomNumber(0, size - 1)] = 0;
}

void Investigator::ClearOutput() {
  std::string Out = "";
  uint32_t NumberOfWays = _result.size()/_mas.size();
  for (uint32_t j = 0; j < NumberOfWays; ++j) {
    Out += "investigation:\n";
    Out += " travel_variant: ";
    Out += _result[j*_result.size()/NumberOfWays].type;
    Out += "\n experiments\n";
    for (uint32_t i = (_result.size() / NumberOfWays) * j;
         i < (_result.size() / NumberOfWays) * (j + 1); ++i) {
      Out += "- experiment:\n";
      Out += "  number: ";
      Out += std::to_string(_result[i].number + 1);
      Out += "\n  input_data:\n   buffer_size: ";
      Out += std::to_string(_mas[i % _mas.size()] / 256);
      Out += " Kib\n";
      Out += "  results:\n   duration: ";
      Out += std::to_string(_result[i].time);
      Out += " ms\n";
    }
  }
  std::cout << Out;
}
void Investigator::Graf() {
  //uint32_t NumberOfWays = _result.size()/_mas.size();
  std::string Coord = "";
  for (auto i : _result) {
    Coord += "(";
    Coord += std::to_string(_mas[i.number] / 256);
    Coord += ";";
    Coord += std::to_string(i.time);
    Coord += ")";
  }
  std::cout << Coord << std::endl;
}

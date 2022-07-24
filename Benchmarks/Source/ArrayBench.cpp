

// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#include <benchmark/benchmark.h>

#include <SharperC/Array.hpp>

#define ARRAY_SIZE 1000000
#define BENCH_ITERATIONS 10

void RawArray(int* data, intn count) {
  for (int i = 0; i < count; ++i) {
    ++data[i];
  }
}

void EnumerateArray(IEnumerator<int>* enumerator) {
  while (enumerator->MoveNext()) {
    ++enumerator->Current();
  }
}

void EnumerateVectorForeach(std::vector<int>& vector) {
  for (auto& x : vector) {
    ++x;
  }
}

void EnumerateVectorFor(std::vector<int>& vector) {
  for (int i = 0; i < vector.size(); ++i) {
    ++vector[i];
  }
}

void EnumerateVectorForIt(std::vector<int>& vector) {
  auto end = vector.end();
  for (auto it = vector.begin(); it != end; ++it) {
    ++*it;
  }
}

void Increment(int& x) { ++x; }

void EnumerateVectorAlgor(std::vector<int>& vector) {
  std::for_each(vector.begin(), vector.end(), Increment);
}

void VectorForeachBenchmark(benchmark::State& state) {
  auto vec = std::vector<int>(ARRAY_SIZE);
  for (auto _ : state) {
    EnumerateVectorForeach(vec);
  }
}

void VectorForBenchmark(benchmark::State& state) {
  auto vec = std::vector<int>(ARRAY_SIZE);
  for (auto _ : state) {
    EnumerateVectorFor(vec);
  }
}

void VectorForItBenchmark(benchmark::State& state) {
  auto vec = std::vector<int>(ARRAY_SIZE);
  for (auto _ : state) {
    EnumerateVectorForIt(vec);
  }
}

void VectorAlgorBenchmark(benchmark::State& state) {
  auto vec = std::vector<int>(ARRAY_SIZE);
  for (auto _ : state) {
    EnumerateVectorAlgor(vec);
  }
}

void ArrayForBenchmark(benchmark::State& state) {
  auto array = Array<int>::New(ARRAY_SIZE);
  for (auto _ : state) {
    RawArray(array->Data(), array->Size());
  }
}

void ArrayEnumeratorBenchmark(benchmark::State& state) {
  auto array = Array<int>::New(ARRAY_SIZE);
  auto enumerator = array->GetEnumerator();
  auto pEnumerator = enumerator.operator->();

  for (auto _ : state) {
    EnumerateArray(pEnumerator);
    enumerator->Reset();
  }
}

BENCHMARK(VectorForeachBenchmark)
    ->Name("Vector Foreach")
    ->Iterations(BENCH_ITERATIONS);
BENCHMARK(VectorForBenchmark)->Name("Vector For")->Iterations(BENCH_ITERATIONS);
BENCHMARK(VectorForItBenchmark)
    ->Name("Vector For Iterator")
    ->Iterations(BENCH_ITERATIONS);
BENCHMARK(VectorAlgorBenchmark)
    ->Name("Vector Algorithm")
    ->Iterations(BENCH_ITERATIONS);
BENCHMARK(ArrayForBenchmark)->Name("Array For")->Iterations(BENCH_ITERATIONS);
BENCHMARK(ArrayEnumeratorBenchmark)
    ->Name("Array Enumerator")
    ->Iterations(BENCH_ITERATIONS);
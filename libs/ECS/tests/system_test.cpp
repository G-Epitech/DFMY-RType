/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.cpp
*/

#include <gtest/gtest.h>

#include "registry.hpp"
#include "system_abstract.hpp"

using namespace rtype::sdk::ECS;

TEST(SystemTests, CreateBasicSystem) {
  class BasicSystem : public ASystem<int> {
   public:
    BasicSystem() = default;
    void Run(Registry *r, sparse_array<int> &nb) override {
      (void) r;
      (void) nb;
    }
  };
  Registry registry;
  registry.RegisterComponent<int>();
  registry.AddSystem<BasicSystem>();
  registry.RunSystems();
}

TEST(SystemTests, CreateMultipleSystem) {
  class IntSystem : public ASystem<int> {
   public:
    IntSystem() = default;
    void Run(Registry *r, sparse_array<int> &nb) override {
      (void) r;
      (void) nb;
    }
  };
  class FloatSystem : public ASystem<float> {
   public:
    FloatSystem() = default;
    void Run(Registry *r, sparse_array<float> &nb) override {
      (void) r;
      (void) nb;
    }
  };
  Registry registry;
  registry.RegisterComponent<int>();
  registry.RegisterComponent<float>();
  registry.AddSystem<IntSystem>();
  registry.AddSystem<FloatSystem>();
  registry.RunSystems();
}

TEST(SystemTests, CreateMultipleSystemWithSameComponent) {
  class IntSystem : public ASystem<int> {
   public:
    IntSystem() = default;
    void Run(Registry *r, sparse_array<int> &nb) override {
      (void) r;
      (void) nb;
    }
  };
  class FloatSystem : public ASystem<int> {
   public:
    FloatSystem() = default;
    void Run(Registry *r, sparse_array<int> &nb) override {
      (void) r;
      (void) nb;
    }
  };
  Registry registry;
  registry.RegisterComponent<int>();
  registry.AddSystem<IntSystem>();
  registry.AddSystem<FloatSystem>();
  registry.RunSystems();
}

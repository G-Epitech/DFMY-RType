/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry.cpp
*/

#include <gtest/gtest.h>

#include "registry.hpp"
#include "system_abstract.hpp"
#include "tools/zipper.hpp"

using namespace zygarde;

TEST(SystemTests, CreateBasicSystem) {
  class BasicSystem : public ASystem<int> {
   public:
    BasicSystem() = default;

    void Run(std::shared_ptr<Registry> r, zipper<sparse_array<int>::ptr> components) override {
      (void) r;
      for (auto &&[nb] : components) {
        (void) nb;
      }
      const auto beg = components.begin();
      const auto end = components.end();
      for (auto it = beg; it != end; ++it) {
        auto &&[index, values] = ~it;
        auto &&[nb] = values;
        (void) nb;
      }
    }
  };
  const auto registry = Registry::create();
  registry->RegisterComponent<int>();
  registry->AddSystem<BasicSystem>();
  const auto entity = registry->SpawnEntity();
  registry->AddComponent<int>(entity, 1);
  registry->RunSystems();
}

TEST(SystemTests, CreateMultipleSystem) {
  class IntSystem : public ASystem<int> {
   public:
    IntSystem() = default;

    void Run(std::shared_ptr<Registry> r, zipper<sparse_array<int>::ptr> components) override {
      (void) r;
      (void) components;
    }
  };
  class FloatSystem : public ASystem<float, int> {
   public:
    FloatSystem() = default;

    void Run(std::shared_ptr<Registry> r,
             zipper<sparse_array<float>::ptr, sparse_array<int>::ptr> components) override {
      (void) r;
      for (auto &&[f, i] : components) {
        (void) f;
        (void) i;
      }
    }
  };
  const auto registry = Registry::create();
  registry->RegisterComponent<int>();
  registry->RegisterComponent<float>();
  registry->AddSystem<IntSystem>();
  registry->AddSystem<FloatSystem>();
  auto entity = registry->SpawnEntity();
  registry->AddComponent<float>(entity, 1.0f);
  registry->AddComponent<int>(entity, 1);
  auto entity2 = registry->SpawnEntity();
  registry->AddComponent<int>(entity2, 2);
  auto entity3 = registry->SpawnEntity();
  registry->AddComponent<int>(entity3, 3);
  registry->AddComponent<float>(entity3, 3.0f);
  registry->RunSystems();
}

TEST(SystemTests, CreateMultipleSystemWithSameComponent) {
  class IntSystem : public ASystem<int> {
   public:
    IntSystem() = default;

    void Run(std::shared_ptr<Registry> r, zipper<sparse_array<int>::ptr> components) override {
      (void) r;
      (void) components;
    }
  };
  class FloatSystem : public ASystem<int> {
   public:
    FloatSystem() = default;

    void Run(std::shared_ptr<Registry> r, zipper<sparse_array<int>::ptr> components) override {
      (void) r;
      (void) components;
    }
  };
  const auto registry = Registry::create();
  registry->RegisterComponent<int>();
  registry->AddSystem<IntSystem>();
  registry->AddSystem<FloatSystem>();
  registry->RunSystems();
}

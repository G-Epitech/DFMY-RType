/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry->cpp
*/

#include "registry.hpp"

#include <gtest/gtest.h>

using namespace zygarde;

TEST(RegistryTests, CreateEmptyRegistry) {
  auto registry = Registry::Create();
}

TEST(RegistryTests, SpawnEntity) {
  auto registry = Registry::Create();
  const auto entity = registry->SpawnEntity();
  const auto id = static_cast<std::size_t>(entity);
  ASSERT_EQ(id, 0);
}

TEST(RegistryTests, AddComponent) {
  auto registry = Registry::Create();
  registry->RegisterComponent<int>();
  const auto entity = registry->SpawnEntity();
  registry->AddComponent<int>(entity, 42);
  auto component = registry->GetComponents<int>();
  const auto &value = (*component)[static_cast<std::size_t>(entity)];
  ASSERT_EQ(value, 42);
}

TEST(RegistryTests, RemoveComponent) {
  auto registry = Registry::Create();
  registry->RegisterComponent<int>();
  const auto entity = registry->SpawnEntity();
  registry->AddComponent<int>(entity, 42);
  registry->RemoveComponent<int>(entity);
  auto component = registry->GetComponents<int>();
  const auto &value = (*component)[static_cast<std::size_t>(entity)];
  ASSERT_EQ(value, std::nullopt);
}

TEST(RegistryTests, AddMultipleComponents) {
  auto registry = Registry::Create();
  registry->RegisterComponent<int>();
  registry->RegisterComponent<float>();
  const auto entity = registry->SpawnEntity();
  registry->AddComponent<int>(entity, 42);
  registry->AddComponent<float>(entity, 42.0f);
  auto intComponent = registry->GetComponents<int>();
  auto floatComponent = registry->GetComponents<float>();
  const auto &intValue = (*intComponent)[static_cast<std::size_t>(entity)];
  const auto &floatValue = (*floatComponent)[static_cast<std::size_t>(entity)];
  ASSERT_EQ(intValue, 42);
  ASSERT_EQ(floatValue, 42.0f);
}

TEST(RegistryTests, AddMultipleEntities) {
  auto registry = Registry::Create();
  registry->RegisterComponent<int>();
  const auto entity = registry->SpawnEntity();
  const auto entity2 = registry->SpawnEntity();
  const auto entity3 = registry->SpawnEntity();
  const auto entity4 = registry->SpawnEntity();
  registry->AddComponent<int>(entity, 42);
  registry->AddComponent<int>(entity2, 43);
  registry->AddComponent<int>(entity3, 44);
  registry->AddComponent<int>(entity4, 45);
  registry->RemoveComponent<int>(entity);
  auto component = registry->GetComponents<int>();
  const auto &value = (*component)[static_cast<std::size_t>(entity)];
  ASSERT_EQ(value, std::nullopt);
}

TEST(RegistryTests, AddMultipleEntitiesMultipleComponents) {
  auto registry = Registry::Create();
  registry->RegisterComponent<int>();
  registry->RegisterComponent<float>();
  const auto entity = registry->SpawnEntity();
  const auto entity2 = registry->SpawnEntity();
  const auto entity3 = registry->SpawnEntity();
  const auto entity4 = registry->SpawnEntity();
  registry->AddComponent<int>(entity, 42);
  registry->AddComponent<float>(entity, 42.0f);
  registry->AddComponent<int>(entity2, 43);
  registry->AddComponent<float>(entity2, 43.0f);
  registry->AddComponent<int>(entity3, 44);
  registry->AddComponent<float>(entity3, 44.0f);
  registry->AddComponent<int>(entity4, 45);
  registry->AddComponent<float>(entity4, 45.0f);
  registry->RemoveComponent<int>(entity);
  registry->RemoveComponent<float>(entity);
  auto intComponent = registry->GetComponents<int>();
  auto floatComponent = registry->GetComponents<float>();
  const auto &intValue = (*intComponent)[static_cast<std::size_t>(entity)];
  const auto &floatValue = (*floatComponent)[static_cast<std::size_t>(entity)];
  ASSERT_EQ(intValue, std::nullopt);
  ASSERT_EQ(floatValue, std::nullopt);
}

TEST(RegistryTests, AddMultipleEntitiesAndRemoveSomeAndCreateNewOnes) {
  auto registry = Registry::Create();
  registry->RegisterComponent<int>();
  const auto entity = registry->SpawnEntity();
  const auto entity2 = registry->SpawnEntity();
  const auto entity3 = registry->SpawnEntity();
  const auto entity4 = registry->SpawnEntity();
  registry->AddComponent<int>(entity, 42);
  registry->AddComponent<int>(entity2, 43);
  registry->AddComponent<int>(entity3, 44);
  registry->AddComponent<int>(entity4, 45);
  registry->KillEntity(entity);
  registry->KillEntity(entity4);
  const auto entity5 = registry->SpawnEntity();
  const auto entity6 = registry->SpawnEntity();
  const auto entity7 = registry->SpawnEntity();
  const auto entity8 = registry->SpawnEntity();
  registry->AddComponent<int>(entity5, 46);
  registry->AddComponent<int>(entity6, 47);
  registry->AddComponent<int>(entity7, 48);
  registry->AddComponent<int>(entity8, 49);
  auto component = registry->GetComponents<int>();
  const auto &value = (*component)[static_cast<std::size_t>(entity)];
  const auto &value2 = (*component)[static_cast<std::size_t>(entity2)];
  const auto &value3 = (*component)[static_cast<std::size_t>(entity3)];
  const auto &value4 = (*component)[static_cast<std::size_t>(entity4)];
  ASSERT_EQ(value, 47);
  ASSERT_EQ(value2, 43);
  ASSERT_EQ(value3, 44);
  ASSERT_EQ(value4, 46);
}

TEST(RegisterTests, EntityFromIndex) {
  auto registry = Registry::Create();
  const auto entity = registry->SpawnEntity();
  const auto entity2 = registry->SpawnEntity();
  const auto entity3 = registry->SpawnEntity();
  const auto entity4 = registry->SpawnEntity();

  const auto entityFromIndex = registry->EntityFromIndex(0);
  const auto entityFromIndex2 = registry->EntityFromIndex(1);
  const auto entityFromIndex3 = registry->EntityFromIndex(2);
  const auto entityFromIndex4 = registry->EntityFromIndex(3);

  ASSERT_EQ(static_cast<std::size_t>(entity), static_cast<std::size_t>(entityFromIndex));
  ASSERT_EQ(static_cast<std::size_t>(entity2), static_cast<std::size_t>(entityFromIndex2));
  ASSERT_EQ(static_cast<std::size_t>(entity3), static_cast<std::size_t>(entityFromIndex3));
  ASSERT_EQ(static_cast<std::size_t>(entity4), static_cast<std::size_t>(entityFromIndex4));
}

TEST(RegisterTests, EntityFromIndexOutOfRange) {
  const auto registry = Registry::Create();
  ASSERT_THROW(registry->EntityFromIndex(0), Registry::Exception);
}

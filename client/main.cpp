/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include <iostream>
#include <libs/ECS/src/registry.hpp>
#include <libs/ECS/src/system_abstract.hpp>

struct position {
  float x;
  float y;
};

struct velocity {
  float vx;
  float vy;
};

struct drawable {
  bool hidden;
};

struct controllable {
  bool up;
  bool down;
  bool left;
  bool right;
};

class LoggingSystem final : public ASystem<position, velocity> {
 public:
  explicit LoggingSystem(const int nb) { std::cout << nb << std::endl; }

  void Run(Registry* r, sparse_array<position>& positions,
           sparse_array<velocity>& velocities) override {
    for (size_t i = 0; i < positions.size(); ++i) {
      const auto& [x, y] = positions[i].value();
      std::cout << i << ": Position = { " << x << ", " << y << " }" << std::endl;
    }
    const auto e = r->SpawnEntity();
    r->AddComponent(e, position{10.0f, 20.0f});
  }
};

int main() {
  rtype::sdk::ECS::Registry registry;

  registry.RegisterComponent<position>();
  registry.RegisterComponent<velocity>();
  registry.RegisterComponent<drawable>();
  registry.RegisterComponent<controllable>();

  const auto entity = registry.SpawnEntity();

  registry.AddComponent<position>(entity, {10.0f, 20.0f});
  registry.AddComponent<velocity>(entity, {1.0f, 2.0f});
  registry.AddComponent<drawable>(entity, {false});
  registry.AddComponent<controllable>(entity, {false, false, false, false});

  registry.AddSystem<LoggingSystem>(4);

  registry.RunSystems();

  return 0;
}

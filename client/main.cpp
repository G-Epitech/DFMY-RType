/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include <iostream>

#include "app/app.hpp"
#include "libs/ECS/src/registry.hpp"

using namespace rtype::client;
using namespace rtype::sdk::ECS;

struct position {
  float x;
  float y;
};

struct velocity {
  float vx;
  float vy;
};

struct drawable {
  sf::RectangleShape shape;
};

struct controllable {
  bool up;
  bool down;
  bool left;
  bool right;
};

void logging_system(registry& r, const sparse_array<position>& positions,
                    const sparse_array<velocity>& velocities) {
  for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
    if (positions[i] && velocities[i]) {
      const auto& [x, y] = positions[i].value();
      const auto& [vx, vy] = velocities[i].value();
      std::cerr << i << ": Position = { " << x << ", " << y << " }, Velocity = { " << vx << ", "
                << vy << " }\n";
    }
  }
}

int main() {
  /*App app;
  app.run();*/
  registry reg;

  reg.register_component<position>();
  reg.register_component<velocity>();
  reg.register_component<drawable>();
  reg.register_component<controllable>();

  reg.add_system<position, velocity>(logging_system);

  Entity e1 = reg.spawn_entity();

  position pos1 = {100.0f, 150.0f};
  velocity vel1 = {0.5f, 0.5f};
  drawable draw1;
  draw1.shape.setSize(sf::Vector2f(50, 50));
  draw1.shape.setFillColor(sf::Color::Green);
  controllable ctrl1 = {false, true, false, false};

  reg.add_component<position>(e1, std::move(pos1));
  reg.add_component<velocity>(e1, std::move(vel1));
  reg.add_component<drawable>(e1, std::move(draw1));
  reg.add_component<controllable>(e1, std::move(ctrl1));

  reg.remove_component<controllable>(e1);

  controllable new_ctrl = {true, false, true, false};
  reg.add_component<controllable>(e1, std::move(new_ctrl));

  auto& pos_component = reg.get_components<position>();
  auto& vel_component = reg.get_components<velocity>();
  auto& draw_component = reg.get_components<drawable>();
  auto& ctrl_component = reg.get_components<controllable>();

  if (static_cast<size_t>(e1) < pos_component.size()) {
    const position& pos = pos_component[static_cast<size_t>(e1)].value();
    std::cout << "Entity " << static_cast<size_t>(e1) << " Position: (" << pos.x << ", " << pos.y
              << ")\n";
  }

  if (static_cast<size_t>(e1) < vel_component.size()) {
    const velocity& vel = vel_component[static_cast<size_t>(e1)].value();
    std::cout << "Entity " << static_cast<size_t>(e1) << " Velocity: (" << vel.vx << ", " << vel.vy
              << ")\n";
  }

  if (static_cast<size_t>(e1) < draw_component.size()) {
    const drawable& draw = draw_component[static_cast<size_t>(e1)].value();
    std::cout << "Entity " << static_cast<size_t>(e1) << " Drawable: Shape Size ("
              << draw.shape.getSize().x << ", " << draw.shape.getSize().y << ")\n";
  }

  if (static_cast<size_t>(e1) < ctrl_component.size()) {
    const controllable& ctrl = ctrl_component[static_cast<size_t>(e1)].value();
    std::cout << "Entity " << static_cast<size_t>(e1) << " Controllable: (Up: " << ctrl.up
              << ", Down: " << ctrl.down << ", Left: " << ctrl.left << ", Right: " << ctrl.right
              << ")\n";
  }

  return 0;
}

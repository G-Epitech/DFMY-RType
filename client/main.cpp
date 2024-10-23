/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "libs/mew/src/app/app.hpp"
#include "libs/mew/src/app/builder.hpp"
#include "libs/mew/src/scenes/scene_interface.hpp"

class MyServiceB;

class MyScene final : public mew::scenes::IScene {
 public:
  MyScene() = default;
  ~MyScene() final = default;

  void OnCreate() override { std::cout << "MyScene created" << std::endl; }

  void Update(zygarde::utils::Timer::Nanoseconds deltaTime) override {
  }

  void OnDestroy() override { std::cout << "MyScene destroyed" << std::endl; }

  void OnActivate() override { std::cout << "MyScene activated" << std::endl; }

  void OnDeactivate() override { std::cout << "MyScene deactivated" << std::endl; }

 private:
  mew::app::DependenciesHandler::Ptr dependencies_handler_;
};

using namespace mew::app;

#if (defined(_WIN32) && !defined(DEBUG))
  #include <windows.h>
  #define MAIN \
    WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
  #define MAIN main()
#endif

class MyServiceA {
 public:
  MyServiceA() = default;
  ~MyServiceA() = default;

  void Update() {
    std::cout << this << std::endl;
  }
};

class MyServiceB {
 public:
  explicit MyServiceB(const DependenciesHandler::Ptr& dependencies_handler) {
    auto e = dependencies_handler->GetOrThrow<MyServiceA>();
    e->Update();
  }
  ~MyServiceB() = default;

  void Update() { std::cout << this << std::endl; }
};

int MAIN {
  auto builder = AppBuilder();
  auto app = builder
                 .WithWindowProperties({
                     .title = "R-Type",
                     .videoMode = {1920, 1080},
                     .style = sf::Style::Default,
                     .contextSettings = sf::ContextSettings(),
                     .frameLimit = 60,
                     .iconPath = "assets/icons/R-Type.png",
                 })
                 .WithService<MyServiceA>()
                 .WithService<MyServiceB>()
                 .Build();

  app.scenesManager->RegisterScene<MyScene>();
  app.scenesManager->GoToScene<MyScene>();
  app.services->GetOrThrow<MyServiceB>();
  return app.Run();
}

/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_abstract.cpp
*/

#include "scene_base.hpp"

#include <utility>

#include "libs/mew/src/sets/events/events.hpp"

using namespace mew::scenes;
using namespace mew::managers;
using namespace mew::sets;
using namespace porygon;

SceneBase::SceneBase(DependenciesHandler::Ptr services) : services_(std::move(services)) {
  defaultManagers_ = {.window = services->GetOrThrow<WindowManager>(),
                      .scenes = services->GetOrThrow<ScenesManager>(),
                      .sound = services->GetOrThrow<SoundManager>(),
                      .resources = services->GetOrThrow<ResourcesManager>()};
  InitializeRegistry();
}

void SceneBase::Update(DeltaTime delta_time) {
  registry_->RunSystems();
}

void SceneBase::OnCreate() {}

void SceneBase::OnDestroy() {}

void SceneBase::OnActivate() {}

void SceneBase::OnDeactivate() {}

void SceneBase::InitializeRegistry() {
  registry_ = zygarde::Registry::Create();
  RegisterDefaultComponents();
  AddDefaultSystems();
}

void SceneBase::AddDefaultSystems() {
  registry_->AddSystem<drawable::DrawableSystem>(defaultManagers_.window,
                                                 defaultManagers_.resources);
  registry_->AddSystem<events::MousePressEventSystem>(defaultManagers_.window);
  registry_->AddSystem<events::MouseReleaseEventSystem>(defaultManagers_.window);
  registry_->AddSystem<events::MouseScrollEventSystem>(defaultManagers_.window);
  registry_->AddSystem<events::MouseMoveEventSystem>(defaultManagers_.window);
  registry_->AddSystem<events::KeyPressEventSystem>(defaultManagers_.window);
  registry_->AddSystem<events::KeyReleaseEventSystem>(defaultManagers_.window);
}

void SceneBase::RegisterDefaultComponents() {
  registry_->RegisterComponent<drawable::Drawable>();
  registry_->RegisterComponent<events::OnMousePressed>();
  registry_->RegisterComponent<events::OnMouseReleased>();
  registry_->RegisterComponent<events::OnMouseScrolled>();
  registry_->RegisterComponent<events::OnMouseMoved>();
  registry_->RegisterComponent<events::OnKeyPressed>();
  registry_->RegisterComponent<events::OnKeyReleased>();
}

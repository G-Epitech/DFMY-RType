/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_abstract.cpp
*/

#include "scene_base.hpp"

#include <utility>

#include "libs/mew/src/sets/events/events.hpp"
#include "libs/zygarde/src/core/components/components.hpp"

using namespace mew::scenes;
using namespace mew::managers;
using namespace mew::sets;
using namespace porygon;
namespace zyc = zygarde::core;

SceneBase::SceneBase(DependenciesHandler::Ptr services) : services_(std::move(services)) {
  managers_ = {.window = services_->GetOrThrow<WindowManager>(),
               .scenes = services_->GetOrThrow<ScenesManager>(),
               .sound = services_->GetOrThrow<SoundManager>(),
               .resources = services_->GetOrThrow<ResourcesManager>()};
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
  registry_->AddSystem<drawable::DrawableSystem>(managers_.window, managers_.resources);
  registry_->AddSystem<events::MousePressEventSystem>(managers_.window);
  registry_->AddSystem<events::MouseReleaseEventSystem>(managers_.window);
  registry_->AddSystem<events::MouseScrollEventSystem>(managers_.window);
  registry_->AddSystem<events::MouseMoveEventSystem>(managers_.window);
  registry_->AddSystem<events::KeyPressEventSystem>(managers_.window);
  registry_->AddSystem<events::KeyReleaseEventSystem>(managers_.window);
}

void SceneBase::RegisterDefaultComponents() {
  registry_->RegisterComponent<drawable::Drawable>();
  registry_->RegisterComponent<zyc::components::Position>();
  registry_->RegisterComponent<events::OnMousePressed>();
  registry_->RegisterComponent<events::OnMouseReleased>();
  registry_->RegisterComponent<events::OnMouseScrolled>();
  registry_->RegisterComponent<events::OnMouseMoved>();
  registry_->RegisterComponent<events::OnKeyPressed>();
  registry_->RegisterComponent<events::OnKeyReleased>();
}

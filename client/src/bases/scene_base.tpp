/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_abstract.cpp
*/

using namespace rtype::client;
using namespace zygarde;

template <typename ContextType>
SceneBase<ContextType>::SceneBase(const ContextType &context) : context_(context) {
  registry_ = Registry::create();
  resourcesManager_ = ResourcesManager::Create();
}

template <typename ContextType>
void SceneBase<ContextType>::Update(utils::DeltaTime delta_time) {
  registry_->RunSystems();
}

template <typename ContextType>
void SceneBase<ContextType>::OnCreate() {}

template <typename ContextType>
void SceneBase<ContextType>::OnDestroy() {}

template <typename ContextType>
void SceneBase<ContextType>::OnActivate() {}

template <typename ContextType>
void SceneBase<ContextType>::OnDeactivate() {}

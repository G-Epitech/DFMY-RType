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
}

template <typename ContextType>
void SceneBase<ContextType>::Draw() {}

template <typename ContextType>
void SceneBase<ContextType>::Update(utils::DeltaTime delta_time) {}

template <typename ContextType>
void SceneBase<ContextType>::OnCreate() {}

template <typename ContextType>
void SceneBase<ContextType>::OnDestroy() {}

template <typename ContextType>
void SceneBase<ContextType>::OnActivate() {}

template <typename ContextType>
void SceneBase<ContextType>::OnDeactivate() {}

/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_abstract.cpp
*/

#include "scene_base.hpp"

using namespace rtype::client;

SceneBase::SceneBase(const GlobalContext &global_context) : globalContext_(global_context) {}

void SceneBase::Draw() {}

void SceneBase::Update(utils::DeltaTime delta_time) {}

void SceneBase::OnCreate() {}

void SceneBase::OnDestroy() {}

void SceneBase::OnActivate() {}

void SceneBase::OnDeactivate() {}

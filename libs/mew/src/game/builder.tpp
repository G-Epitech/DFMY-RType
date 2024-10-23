/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** factory.cpp
*/

namespace mew::game {
template <typename T, typename... Args>
GameBuilder &GameBuilder::WithService(Args &&...args) {
  services_->Add<T>(std::forward<Args>(args)...);
  return *this;
}

template <typename T>
GameBuilder &GameBuilder::WithServiceInstance(std::shared_ptr<T> instance) {
  services_->AddInstance<T>(instance);
  return *this;
}

}  // namespace mew::game

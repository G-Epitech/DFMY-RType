/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** factory.cpp
*/

namespace mew::app {
template <typename T, typename... Args>
AppBuilder &AppBuilder::WithService(Args &&...args) {
  services_->Add<T>(std::forward<Args>(args)...);
  return *this;
}

template <typename T>
AppBuilder &AppBuilder::WithServiceInstance(std::shared_ptr<T> instance) {
  services_->AddInstance<T>(instance);
  return *this;
}

}  // namespace mew::app

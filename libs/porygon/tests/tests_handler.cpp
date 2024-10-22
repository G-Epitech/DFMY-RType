/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** tests_handler.cpp
*/

#include <gtest/gtest.h>

#include <utility>

#include "libs/porygon/src/handler.hpp"

using namespace porygon;

class DependenciesHandlerTests : public ::testing::Test {
 public:
  class ServiceWithDeps {
   public:
    explicit ServiceWithDeps(DependenciesHandler::Ptr handler) : handler_{std::move(handler)} {}
    std::shared_ptr<DependenciesHandler> GetHandler() { return handler_; }

   private:
    std::shared_ptr<DependenciesHandler> handler_;
  };

  class ServiceWithoutDeps {
   public:
    ServiceWithoutDeps() = default;
  };
};

TEST_F(DependenciesHandlerTests, CreateDependenciesHandler) {
    auto handler = DependenciesHandler::Create();
    ASSERT_NE(handler, nullptr);
}

TEST_F(DependenciesHandlerTests, GetSharedDependenciesHandler) {
    auto handler = DependenciesHandler::Create();
    auto shared = handler->GetShared();
    ASSERT_NE(shared, nullptr);
    ASSERT_EQ(shared, handler);
}

TEST_F(DependenciesHandlerTests, SingleMakeWithDependencies) {
    auto handler = DependenciesHandler::Create();
    auto svc = handler->MakeWithDependencies<ServiceWithDeps>();

    ASSERT_EQ(svc.GetHandler(), handler);
}

TEST_F(DependenciesHandlerTests, SingleMakeWithoutDependencies) {
    auto handler = DependenciesHandler::Create();

    ASSERT_NO_THROW(handler->MakeWithDependencies<ServiceWithoutDeps>());
}

TEST_F(DependenciesHandlerTests, MakeSharedWithDependencies) {
    auto handler = DependenciesHandler::Create();
    auto svc = handler->MakeSharedWithDependencies<ServiceWithDeps>();

    ASSERT_NE(svc, nullptr);
    ASSERT_EQ(svc->GetHandler(), handler);
}

TEST_F(DependenciesHandlerTests, PersistentInstance) {
    auto handler = DependenciesHandler::Create();
    handler->Add<ServiceWithDeps>();

    auto ref1 = handler->Get<ServiceWithDeps>();
    auto ref2 = handler->Get<ServiceWithDeps>();
    ASSERT_EQ(ref1, ref2);
    ASSERT_NE(ref1, nullptr);
}

TEST_F(DependenciesHandlerTests, AddInstance) {
    auto handler = DependenciesHandler::Create();
    auto instance = std::make_shared<ServiceWithDeps>(handler);
    handler->AddInstance(instance);

    auto svc = handler->Get<ServiceWithDeps>();
    ASSERT_EQ(svc, instance);
}

TEST_F(DependenciesHandlerTests, Add) {
    auto handler = DependenciesHandler::Create();
    handler->Add<ServiceWithDeps>();

    auto svc = handler->Get<ServiceWithDeps>();
    ASSERT_NE(svc, nullptr);
    ASSERT_EQ(svc->GetHandler(), handler);
}

TEST_F(DependenciesHandlerTests, GetOrThrowNonExistent) {
    auto handler = DependenciesHandler::Create();
    ASSERT_THROW(handler->GetOrThrow<ServiceWithDeps>(), std::runtime_error);
}

TEST_F(DependenciesHandlerTests, GetOrThrowExistent) {
    auto handler = DependenciesHandler::Create();
    handler->Add<ServiceWithDeps>();

    ASSERT_NO_THROW(handler->GetOrThrow<ServiceWithDeps>());
}

TEST_F(DependenciesHandlerTests, Get) {
    auto handler = DependenciesHandler::Create();
    auto instance = std::make_shared<ServiceWithDeps>(handler);
    handler->AddInstance(instance);

    auto svc = handler->Get<ServiceWithDeps>();
    ASSERT_EQ(svc, instance);
}

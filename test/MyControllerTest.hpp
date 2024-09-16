#ifndef MY_CONTROLLER_TEST
#define MY_CONTROLLER_TEST

#include "oatpp-test/UnitTest.hpp"

class MyControllerTest : public oatpp::test::UnitTest
{
public:

  MyControllerTest() : UnitTest("TEST[MyControllerTest]") {}
  void onRun() override;
};

#endif
#include "MyControllerTest.hpp"
#include "constants/LogFlag.hpp"

void runTests() {
  OATPP_RUN_TEST(MyControllerTest);
}

int main() {
  oatpp::Environment::init();

  runTests();

  OATPP_LOGi(APP_NAME, "objectCounts = {}", oatpp::Environment::getObjectsCount());
  OATPP_LOGi(APP_NAME, "objectCreated = {}", oatpp::Environment::getObjectsCreated())

  OATPP_ASSERT(oatpp::Environment::getObjectsCount() == 0);

  oatpp::Environment::destroy();
}
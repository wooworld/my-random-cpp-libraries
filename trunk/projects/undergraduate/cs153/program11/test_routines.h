//////////////////////////////////////////////////////////////////////
/// @file void test_routines.cpp
/// @author Gary Steelman, CS153-B
/// @brief Tests for classes
//////////////////////////////////////////////////////////////////////

#ifndef TEST_ROUTINES_H
#define TEST_ROUTINES_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>
#include <ctime>
#include <cstdlib>
#include "priority_queue.h"
#include "exception.h"

class Test_routines : public CPPUNIT_NS::TestFixture {

  private:
  
    CPPUNIT_TEST_SUITE(Test_routines);
      CPPUNIT_TEST(test_push);
      CPPUNIT_TEST(test_pop);
    CPPUNIT_TEST_SUITE_END();
    
  protected:
  
    void test_push();
    void test_pop();
    void test_search();
  
};

#endif

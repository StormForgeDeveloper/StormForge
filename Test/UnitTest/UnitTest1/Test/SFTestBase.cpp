// TestApp.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFTestBase.h"
#include "Service/SFService.h"




// --gtest_catch_exceptions=0 to disable exception catch
//	--gtest_filter = ThreadTest.EntityTaskManager --gtest_catch_exceptions=0

//./foo_test --gtest_filter=* Also runs everything, due to the single match-everything * value.
//./foo_test --gtest_filter=FooTest.* Runs everything in test case FooTest.
//./foo_test --gtest_filter=*Null*:*Constructor* Runs any test whose full name contains either "Null" or "Constructor".
//./foo_test --gtest_filter=-*DeathTest.* Runs all non-death tests.
//./foo_test --gtest_filter=FooTest.*-FooTest.Bar Runs everything in test case FooTest except 


void MyTestBase::SetUp()
{
}

// TearDown() is invoked immediately after a test finishes.  Here we
void MyTestBase::TearDown()
{
	StopAllThread();

	SF::Service::LogModule->Flush();

}




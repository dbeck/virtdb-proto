#include "value_type_test.hh"
#include <list>
#include <set>
#include <deque>
#include <vector>
#include <limits>

using namespace virtdb::test;
using namespace virtdb::interface;

TEST_F(ValueTypeTest, TestString)
{
  typedef std::string val_t;
  typedef uint32_t    other_t;
  
  // get without set
  EXPECT_EQ(this->get<val_t>(99,"empty"), "empty");
  
  // size without set
  EXPECT_EQ(this->size<val_t>(), 0);
  
  // setting the values
  std::vector<val_t> values{"apple","peach","lemon"};
  this->set(values.begin(), values.end());

  // size after set
  EXPECT_EQ(this->size<val_t>(), values.size());
  
  // size of wrong type
  EXPECT_EQ(this->size<other_t>(), 0);
  
  // non-existant
  EXPECT_EQ(this->get<val_t>(8,"foo"),"foo");
  
  // real values
  EXPECT_EQ(this->get<val_t>(0,"foo"),"apple");
  EXPECT_EQ(this->get<val_t>(1,"foo"),"peach");
  EXPECT_EQ(this->get<val_t>(2,"foo"),"lemon");
  
  // real values, wrong type
  EXPECT_EQ(this->get<other_t>(0,99),99);
  EXPECT_EQ(this->get<other_t>(1,99),99);
  EXPECT_EQ(this->get<other_t>(2,99),99);
}

TEST_F(ValueTypeTest, TestI32)
{
  typedef int32_t      val_t;
  typedef std::string  other_t;
  
  // get without set
  EXPECT_EQ(this->get<val_t>(0,-1), -1);

  // size without set
  EXPECT_EQ(this->size<val_t>(), 0);
  
  // setting the values
  std::set<val_t> values{1,3,-5,6};
  this->set(values.begin(), values.end());
  
  // size after set
  EXPECT_EQ(this->size<val_t>(), values.size());
  
  // size of wrong type
  EXPECT_EQ(this->size<other_t>(), 0);
  
  // non-existant
  EXPECT_EQ(this->get<val_t>(8,-3),-3);
  
  // real values
  EXPECT_EQ(this->get<val_t>(0,-9),-5);
  EXPECT_EQ(this->get<val_t>(1,-9),1);
  EXPECT_EQ(this->get<val_t>(2,-9),3);
  EXPECT_EQ(this->get<val_t>(3,-9),6);
  
  // real values, wrong type
  EXPECT_EQ(this->get<other_t>(0,"empty"),"empty");
  EXPECT_EQ(this->get<other_t>(1,"empty"),"empty");
  EXPECT_EQ(this->get<other_t>(2,"empty"),"empty");
  EXPECT_EQ(this->get<other_t>(3,"empty"),"empty");
}

TEST_F(ValueTypeTest, TestI64)
{
  typedef int64_t    val_t;
  typedef double     other_t;
  
  // get without set
  EXPECT_EQ(this->get<val_t>(0,-1), -1);
  
  // size without set
  EXPECT_EQ(this->size<val_t>(), 0);
  
  // setting the values
  std::list<val_t> values{-6,9,-123};
  this->set(values.begin(), values.end());

  // size after set
  EXPECT_EQ(this->size<val_t>(), values.size());
  
  // size of wrong type
  EXPECT_EQ(this->size<other_t>(), 0);

  // non-existant
  EXPECT_EQ(this->get<val_t>(8,-3),-3);
  
  // real values
  EXPECT_EQ(this->get<val_t>(0,-9),-6);
  EXPECT_EQ(this->get<val_t>(1,-9),9);
  EXPECT_EQ(this->get<val_t>(2,-9),-123);
  
  // real values, wrong type
  EXPECT_EQ(this->get<other_t>(0,1.134),1.134);
  EXPECT_EQ(this->get<other_t>(1,1.134),1.134);
  EXPECT_EQ(this->get<other_t>(2,1.134),1.134);
}

TEST_F(ValueTypeTest, TestU32)
{
  typedef uint32_t   val_t;
  typedef bool       other_t;
  
  // get without set
  EXPECT_EQ(this->get<val_t>(0,999), 999);
  
  // size without set
  EXPECT_EQ(this->size<val_t>(), 0);
  
  // setting the values
  std::deque<val_t> values{98,32,11};
  this->set(values.begin(), values.end());
  
  // size after set
  EXPECT_EQ(this->size<val_t>(), values.size());
  
  // size of wrong type
  EXPECT_EQ(this->size<other_t>(), 0);
  
  // non-existant
  EXPECT_EQ(this->get<val_t>(8,33),33);
  
  // real values
  EXPECT_EQ(this->get<val_t>(0,19),98);
  EXPECT_EQ(this->get<val_t>(1,19),32);
  EXPECT_EQ(this->get<val_t>(2,19),11);
  
  // real values, wrong type
  EXPECT_EQ(this->get<other_t>(0,false),false);
  EXPECT_EQ(this->get<other_t>(1,false),false);
  EXPECT_EQ(this->get<other_t>(2,false),false);
}

TEST_F(ValueTypeTest, TestU64)
{
  typedef uint64_t  val_t;
  typedef float     other_t;
  
  static const other_t zero = 0.0;
  
  // get without set
  EXPECT_EQ(this->get<val_t>(0,22), 22);
  
  // size without set
  EXPECT_EQ(this->size<val_t>(), 0);
  
  // setting the values
  std::vector<val_t> values{2,66,89,123};
  this->set(values.begin(), values.end());
  
  // size after set
  EXPECT_EQ(this->size<val_t>(), values.size());
  
  // size of wrong type
  EXPECT_EQ(this->size<other_t>(), 0);
  
  // non-existant
  EXPECT_EQ(this->get<val_t>(8,33),33);
  
  // real values
  EXPECT_EQ(this->get<val_t>(0,1),2);
  EXPECT_EQ(this->get<val_t>(1,1),66);
  EXPECT_EQ(this->get<val_t>(2,1),89);
  EXPECT_EQ(this->get<val_t>(3,1),123);
  
  // real values, wrong type
  EXPECT_FLOAT_EQ(this->get<other_t>(0,zero),zero);
  EXPECT_FLOAT_EQ(this->get<other_t>(1,zero),zero);
  EXPECT_FLOAT_EQ(this->get<other_t>(2,zero),zero);
  EXPECT_FLOAT_EQ(this->get<other_t>(3,zero),zero);
}

TEST_F(ValueTypeTest, TestDouble)
{
  typedef double    val_t;
  typedef uint64_t  other_t;
  
  static const val_t zero = 0.0;
  
  // get without set
  EXPECT_DOUBLE_EQ(this->get<val_t>(0,zero), zero);
  
  // size without set
  EXPECT_EQ(this->size<val_t>(), 0);
  
  // setting the values
  std::set<val_t> values{1.34,999.876,123.765};
  this->set(values.begin(), values.end());
  
  // size after set
  EXPECT_DOUBLE_EQ(this->size<val_t>(), values.size());
  
  // size of wrong type
  EXPECT_EQ(this->size<other_t>(), 0);
  
  // non-existant
  EXPECT_DOUBLE_EQ(this->get<val_t>(8,zero),zero);
  
  // real values
  EXPECT_DOUBLE_EQ(this->get<val_t>(0,zero),1.34);
  EXPECT_DOUBLE_EQ(this->get<val_t>(1,zero),123.765);
  EXPECT_DOUBLE_EQ(this->get<val_t>(2,zero),999.876);
  
  // real values, wrong type
  EXPECT_EQ(this->get<other_t>(0,0),0);
  EXPECT_EQ(this->get<other_t>(1,0),0);
  EXPECT_EQ(this->get<other_t>(2,0),0);
}

TEST_F(ValueTypeTest, TestFloat)
{
  typedef float        val_t;
  typedef std::string  other_t;
  
  static const val_t zero = 0.0;

  // get without set
  EXPECT_FLOAT_EQ(this->get<val_t>(0,9.9), 9.9);
  
  // size without set
  EXPECT_EQ(this->size<val_t>(), 0);
  
  // setting the values
  std::list<val_t> values{13.4,111.23,998.23};
  this->set(values.begin(), values.end());
  
  // size after set
  EXPECT_FLOAT_EQ(this->size<val_t>(), values.size());
  
  // size of wrong type
  EXPECT_EQ(this->size<other_t>(), 0);
  
  // non-existant
  EXPECT_FLOAT_EQ(this->get<val_t>(8,zero),zero);
  
  // real values
  EXPECT_FLOAT_EQ(this->get<val_t>(0,zero),13.4);
  EXPECT_FLOAT_EQ(this->get<val_t>(1,zero),111.23);
  EXPECT_FLOAT_EQ(this->get<val_t>(2,zero),998.23);
  
  // real values, wrong type
  EXPECT_EQ(this->get<other_t>(0,"0"),"0");
  EXPECT_EQ(this->get<other_t>(1,"0"),"0");
  EXPECT_EQ(this->get<other_t>(2,"0"),"0");
}

TEST_F(ValueTypeTest, TestBool)
{
  typedef bool     val_t;
  typedef int32_t  other_t;
  
  // get without set
  EXPECT_EQ(this->get<val_t>(0,false), false);
  
  // size without set
  EXPECT_EQ(this->size<val_t>(), 0);

  // setting the values
  std::deque<val_t> values{true, false, false, true};
  this->set(values.begin(), values.end());
  
  // size after set
  EXPECT_EQ(this->size<val_t>(), values.size());
  
  // size of wrong type
  EXPECT_EQ(this->size<other_t>(), 0);
  
  // non-existant
  EXPECT_EQ(this->get<val_t>(8,true),true);
  
  // real values
  EXPECT_EQ(this->get<val_t>(0,false),true);
  EXPECT_EQ(this->get<val_t>(1,true),false);
  EXPECT_EQ(this->get<val_t>(2,true),false);
  EXPECT_EQ(this->get<val_t>(3,false),true);
  
  // real values, wrong type
  EXPECT_EQ(this->get<other_t>(0,-1),-1);
  EXPECT_EQ(this->get<other_t>(1,-1),-1);
  EXPECT_EQ(this->get<other_t>(2,-1),-1);
  EXPECT_EQ(this->get<other_t>(3,-1),-1);
}

TEST_F(ValueTypeTest, TestNulls)
{
  // value default to non null
  EXPECT_EQ(this->is_null(0), false);

  // setting a null value
  this->set_null<std::string>(2,true);

  // getting from the base class
  EXPECT_EQ(this->is_null(2), true);
  
  // getting from the templated child of a different type
  EXPECT_EQ(this->is_null<double>(2), true);

  // getting the other values
  EXPECT_EQ(this->is_null(0), false);
  EXPECT_EQ(this->is_null(1), false);
  
  // non-existant values are still non-null
  EXPECT_EQ(this->is_null(111), false);
}

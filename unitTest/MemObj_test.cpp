/*
 * MemObj_test.cpp
 *  Module     :
 *  Description:
 *  Input      :
 *  Output     :
 *  Created on : 13-Jan-2018
 *  Author     : pratik
 *  License     :
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 3 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */

#include <limits.h>
#include "gtest/gtest.h"

#include "basedef.h"
#include "memObj.h"

namespace
{

  class MemObj_test : public ::testing::Test
  {
  public:
    Linear::MemObj<double> *obj;
    std::vector<double> values;
    const U_INT size= 2;
  protected:
    MemObj_test () :
        obj (nullptr)
    {
      for (unsigned int i = 0; i < size; ++i)
        {
          values.push_back (i);
        }
      obj = new Linear::MemObj<double> (size, values);
    }

    virtual
    ~MemObj_test ()
    {
      delete obj;
//      std::cout << "matrix destroyed" << std::endl;
    }
  };

  TEST_F (MemObj_test,constructor)
  {
    Linear::MemObj<double> m;
    EXPECT_EQ(0 , m.getSize());
    EXPECT_EQ(Linear::InvalidObject , m.getState());
    Linear::MemObj<double> m2(2);
    EXPECT_EQ(2 , m2.getSize());
    EXPECT_EQ(Linear::ValidObject , m2.getState());
    std::vector<double> returnValues = obj->getValues ();
    EXPECT_TRUE(values == returnValues);
  }

  TEST_F(MemObj_test, destructor)
  {

    std::vector<double> values;
    for (unsigned int i = 0; i < size; ++i)
            {
              values.push_back (i);
            }
    Linear::MemObj<double> *ptr = new Linear::MemObj<double> (size, values);
    delete ptr;
  }
}



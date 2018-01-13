/*
 * matrix_operations_test.cpp
 *  Module     :
 *  Description:
 *  Input      :
 *  Output     :
 *  Created on : 18-Nov-2017
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
#include "matrix.h"

namespace
{
  template<typename DataType>
    void
    printMatrix (Linear::Matrix<DataType>& mx)
    {
      /*
       * Geting values in vector getValues
       */
      std::vector<DataType> matValues = mx.getValues ();
      std::cout << "Matrix values" << std::endl;
      std::copy (matValues.begin (), matValues.end (),
                 std::ostream_iterator<DataType> (std::cout, "\n"));
    }
  class Matrix_test : public ::testing::Test
  {
  public:
    Linear::Matrix<double> *mat; //(ROWS, COLUMNS, values);
    std::vector<double> values;
    const U_INT ROWS = 2;
    const U_INT COLUMNS = 2;
  protected:
    Matrix_test () :
        mat (nullptr)
    {
      for (unsigned int i = 0; i < ROWS * COLUMNS; ++i)
        {
          values.push_back (i);
        }
      mat = new Linear::Matrix<double> (ROWS, COLUMNS, values);
    }

    virtual
    ~Matrix_test ()
    {
      delete mat;
    }
  };

  TEST_F (Matrix_test,constructor)
  {
    Linear::Matrix<double> m;
    EXPECT_EQ(0 , m.getRow());
    EXPECT_EQ(0 , m.getcolumn());
    EXPECT_EQ(Linear::InvalidObject , m.getState());
    Linear::Matrix<double> m2(2,2);
    EXPECT_EQ(2 , m2.getRow());
    EXPECT_EQ(2 , m2.getcolumn());
    EXPECT_EQ(Linear::ValidObject , m2.getState());
    std::vector<double> returnValues = mat->getValues ();
    EXPECT_TRUE(values == returnValues);
  }
  // to retrieve values
  TEST_F (Matrix_test,getValues)
  {
    std::vector<double> returnValues = mat->getValues ();
    EXPECT_TRUE(values == returnValues);
  }

  // to update
  TEST_F (Matrix_test, initFromVector)
  {
    ++values[0];
    ++values[3];
    mat->initFromVector (values);

    std::vector<double> returnValues = mat->getValues ();
    ASSERT_TRUE(values == returnValues);
  }

  TEST_F (Matrix_test, addition)
  {
    Linear::Matrix<double> m1 (ROWS, COLUMNS, values);
    // updated values for m2
    ++values[0];
    ++values[3];
    Linear::Matrix<double> m2 (ROWS, COLUMNS, values);
    // done addition
    Linear::Matrix<double> m3 (m1 + m2);
    std::vector<double> result = m3.getValues ();
    std::vector<double> m1V = m1.getValues ();
    std::vector<double> m2V = m2.getValues ();
    for (unsigned int i = 0; i < ROWS * COLUMNS; ++i)
      {
        EXPECT_DOUBLE_EQ(result[i], (m1V[i] + m2V[i]));
      }
  }

  TEST_F (Matrix_test, subtraction)
  {
    Linear::Matrix<double> m1 (ROWS, COLUMNS, values);
    // updated values for m2
    ++values[0];
    ++values[3];
    Linear::Matrix<double> m2 (ROWS, COLUMNS, values);
    // done addition
    Linear::Matrix<double> m3 (m1 - m2);
    std::vector<double> result = m3.getValues ();
    std::vector<double> m1V = m1.getValues ();
    std::vector<double> m2V = m2.getValues ();
    for (unsigned int i = 0; i < ROWS * COLUMNS; ++i)
      {
        EXPECT_DOUBLE_EQ(result[i], (m1V[i] - m2V[i]));
      }
  }

  TEST_F (Matrix_test, scalarProduct)
  {
    (*mat) (3);
    std::vector<double> result = mat->getValues ();

    for (unsigned int i = 0; i < ROWS * COLUMNS; ++i)
      {
        EXPECT_DOUBLE_EQ(result[i], 3 * values[i]);
      }
  }

  TEST_F (Matrix_test, crossProduct)
  {
    /*
     |0 1| X |0 1|  = |2 3|
     |2 3|   |2 3|    |6 11|
     */

    Linear::Matrix<double> m1 (ROWS, COLUMNS, values);
    std::vector<double> values = m1.getValues ();
    Linear::Matrix<double> cross = (m1 * (*mat));
    std::vector<double> result = cross.getValues ();
    std::vector<double> expectedVal =
      { 2, 3, 6, 11 };
    for (unsigned int i = 0; i < ROWS * COLUMNS; ++i)
      {
        EXPECT_DOUBLE_EQ(result[i], expectedVal[i]);
      }
  }

  TEST_F (Matrix_test, equality)
  {
    Linear::Matrix<double> m1 (ROWS, COLUMNS, values);
    //m1 is initialized with same vector that of mat. both should be equal
    EXPECT_TRUE(*mat == m1);
  }
}


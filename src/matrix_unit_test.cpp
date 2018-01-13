/*
 *  matrix_unit_test.cpp
 *  Module     : unit test for linear algebra library
 *  Description: source testing LinAlg library
 *  Created on : 11-Nov-2017
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
#include <iostream>
#include <iterator>
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include "matrix.h"
#include "vector.h"

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

#define ROWS 2
#define COLUMNS 2
#if 0
void
getValues (Linear::Matrix<double>& mx)
{
  /*
   * Geting values in vector getValues
   */
  std::cout << "mx" << std::endl;
  printMatrix (mx);
}

Linear::Matrix<double>
updateMatrix (std::vector<double>& values)
{
  // changing values
  ++values[0];
  ++(values[3]);
  Linear::Matrix<double> mx2 (ROWS, COLUMNS, values);
  std::cout << "mx2" << std::endl;
  printMatrix (mx2);
  return mx2;
}

void
addition (Linear::Matrix<double>& mx2, Linear::Matrix<double>& mx,
          Linear::Matrix<double>& mx3)
{
  /*
   * == operator
   */
  if (mx2 == mx)
    std::cout << "Matrices are equal" << std::endl;
  else
    std::cout << "Matrices are not equal" << std::endl;

  std::cout << "mx3 = mx3 + mx2" << std::endl;
  printMatrix (mx3);
}

Linear::Matrix<double>
subtraction (Linear::Matrix<double>& mx3, Linear::Matrix<double>& mx2)
{
  /*
   * - operator
   */
  Linear::Matrix<double> mx4 (mx3 - mx2);
  std::cout << "mx4 = mx3 - mx2" << std::endl;
  printMatrix (mx4);
  Linear::Matrix<double> mx5 (mx2 - mx3);
  std::cout << "mx5 = mx2 - mx3" << std::endl;
  printMatrix (mx5);
  return mx4;
}

void
scalarProduct (Linear::Matrix<double> mx4)
{
  /*
   *  scalar operator
   */
  mx4 (2);
  std::cout << "mx4(2) \n";
  printMatrix (mx4);
}
#endif

int
main (int argc, char* atgv[])
{
#if 0
    {
      /*
       * creating matrix
       *  constructing using vector
       */
      std::vector<double> values;
      std::vector<double> values2;
      for (unsigned int i = 0; i < ROWS*COLUMNS; ++i)
        {
//          for (unsigned int j = 0; j < COLUMNS; ++j)
//            {
//              std::cout << "i + j : \t" << i + j << std::endl;
              values.push_back (1);
              values2.push_back (1);
//            }
        }
      Linear::Matrix<double> mx (ROWS, COLUMNS, values);
      /*
       * Geting values in vector getValues
       */
      getValues (mx);
      // changing values
      Linear::Matrix<double> mx2 = updateMatrix (values);
      /*
       * + operator and copy constructor
       */
      Linear::Matrix<double> mx3 (mx + mx2);
      /*
       * == operator
       */
      addition (mx2, mx, mx3);
      /*
       * - operator
       */
      Linear::Matrix<double> mx4 = subtraction (mx3, mx2);
      /*
       * Cross product
       */

      printMatrix (mx);
      Linear::Matrix<double> m4Cr (COLUMNS, ROWS, values2);
      Linear::Matrix<double> cross ( mx * m4Cr);
      std::cout << "Cross product" << std::endl;
      printMatrix (cross);
      /*
       *  scalar operator
       */
      scalarProduct (mx4);
    }
#endif
  return 0;
}

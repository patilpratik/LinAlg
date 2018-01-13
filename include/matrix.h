/*
 * matrix.h
 *  Module     : Matrix
 *  Description: It is a container for matrix data, encapsulating matrix operations along
 *  Input      : 1) row : row count
 *               2) col : column count
 *               3) values : data values of the matrix
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

#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <cstring>
#include <functional>
#include "basedef.h"
#include "memObj.h"
namespace Linear
{
  // Todo Need to optimize for performance.
  // Todo const ness of the functions

  /*
   * Matrix class will handle up to 2 dimentional matrices.
   * It will support following operations
   *  1) Addition +
   *  2) subtraction -
   *  3) DOT product ()
   *  4) Cross product *
   */

  template<typename DataType>
    class Matrix
    {
    public:
      /*
       * Constructs an empty matrix if no row/column specified
       */
      Matrix (U_INT row = 0, U_INT column = 0);

      /*
       * Constructs Matrix from the vectors
       */
      Matrix (U_INT row, U_INT column, std::vector<DataType> values);
      /*
       * Constructs Matrix from the buffer
       */
      Matrix (U_INT row, U_INT column, DataType* values);
      /*
       * get rows
       */
      U_INT
      getRow ()
      {
        return _rows;
      }
      /*
       * get rows
       */
      U_INT
      getcolumn ()
      {
        return _columns;
      }
      /*
       * get status
       */
      U_INT
      getState ()
      {
        return memObj->getState();
      }
      /*
       * Copy Constructor
       */
      Matrix (const Matrix& mat);

      virtual
      ~Matrix ();
      /*
       * Adds two matrices
       */
      Matrix
      operator + (const Matrix& mat);

      /*
       * Subtracts two matrices
       */
      Matrix
      operator - (const Matrix& mat);

      /*
       * Scalar multiplication
       */
      void
      operator () (const DataType scalar);

      /*
       * DOT product of 2 matrices
       */

      /*
       * cross product of 2 matrices
       */
      DataType
      partialProduct (U_INT row, U_INT col, Matrix<DataType> mat);
      Matrix
      operator * (const Matrix<DataType> mat);

      /*
       * Compares if matrices are equal
       */
      bool
      operator == (const Matrix& mat);
      /*
       * Returns matrix values from in form of vector
       */
      std::vector<DataType>
      getValues ();
      /*
       * Initializes matrix from a vector.
       * Precondition : matrix is initialized with the sufficient memory.
       *  Not to be exposed to out of the class
       */
      void
      initFromVector (std::vector<DataType> values);
    private:

      /*
       * Allocates memory.
       */
      bool
      allocateMemory ();

      /*
       *  Loop through matrix
       */
      //template<typename functor>
      void
      for_all_elems (std::function<void
      (U_INT i, U_INT j)> fn)
      {
        for (U_INT i = 0; i < _rows; ++i)
          {
            for (U_INT j = 0; j < _columns; ++j)
              {
                fn (i, j);
              }
          }
      }
      void
      for_all_elems (std::function<void
      (DataType value)> fn)
      {
        for (U_INT i = 0; i < _rows; ++i)
          {
            for (U_INT j = 0; j < _columns; ++j)
              {
                fn (memObj->_memSpace[i * _rows + j]);
              }
          }
      }
      /*
       * number of rows in the matrix
       */
      U_INT _rows;

      /*
       * number of columns in the matrix
       */
      U_INT _columns;

      /*
       * Holds dynamically allocated memory for Matrix
       */

      MemObj<DataType> * memObj;
    };

  template<typename DataType>
    bool
    Matrix<DataType>::allocateMemory ()
    {
      memObj->allocateMemory (_rows * _columns);
    }

  // Constructing empty matrix if row and column are zero.
  template<typename DataType>
    Matrix<DataType>::Matrix (U_INT row, U_INT column) :
        _rows (row), _columns (column), memObj(new MemObj<DataType>(_rows*_columns))
    {
    }

  // Constructing matrix from the vector
  template<typename DataType>
    Matrix<DataType>::Matrix (U_INT row, U_INT col, std::vector<DataType> value) :
        _rows (row), _columns (col), memObj(new MemObj<DataType>(_rows*_columns))
    {
      if (ValidObject == memObj->getState())
        initFromVector (value);
    }
  // Constructing matrix from the buffer
  template<typename DataType>
    Matrix<DataType>::Matrix (U_INT row, U_INT col, DataType* value) :
        _rows (row), _columns (col), memObj(new MemObj<DataType>(_rows*_columns))
    {
      if (ValidObject == memObj->getState())
        {
          // copy data from mat to current only if memory allocation is successful.
          if (nullptr != memObj->_memSpace)
            memcpy (memObj->_memSpace, value, _rows * _columns * sizeof(DataType));
        }
    }

  // Copy constructor
  template<typename DataType>
    Matrix<DataType>::Matrix (const Matrix& mat) :
        _rows (mat._rows), _columns (mat._columns), memObj(new MemObj<DataType> (*(mat.memObj)))
    {
    }

  template<typename DataType>
    void
    Matrix<DataType>::initFromVector (std::vector<DataType> values)
    {
      memObj->initFromVector(values);
    }
  template<typename DataType>
    std::vector<DataType>
    Matrix<DataType>::getValues ()
    {
      std::vector<DataType> values;
      for_all_elems ([this, &values] (DataType value)
        {
          values.push_back(value);
        });
      return values;
    }

  template<typename DataType>
    Matrix<DataType>::~Matrix ()
    {
      if (nullptr != memObj)
        {
          delete memObj;
          memObj = nullptr;
        }
    }

  /************************ Matrix operations ***************************/

  ///
  /// Adds tow matrices
  ///
  template<typename DataType>
    Matrix<DataType>
    Matrix<DataType>::operator + (const Matrix& mat)
    {
      Matrix result (_rows, _columns);
      if ((_rows == mat._rows) && (_columns == mat._columns))
        {
          for_all_elems ([this,&result,&mat] (U_INT i, U_INT j)
            {
              result.memObj->_memSpace[i * _rows + j] = memObj->_memSpace[i * _rows + j]
              + mat.memObj->_memSpace[i * _rows + j];
            });
        }
      return result;
    }

  ///
  /// subtracts tow matrices
  ///
  template<typename DataType>
    Matrix<DataType>
    Matrix<DataType>::operator - (const Matrix& mat)
    {
      Matrix result (_rows, _columns);
      if ((_rows == mat._rows) && (_columns == mat._columns))
        {
          for_all_elems ([this,&result, &mat] (U_INT i, U_INT j)
            {
              result.memObj->_memSpace[i * _rows + j] = memObj->_memSpace[i * _rows + j]
              - mat.memObj->_memSpace[i * _rows + j];
            });
        }
      return result;
    }

  ///
  /// scalar multiplication with const
  ///
  template<typename DataType>
    void
    Matrix<DataType>::operator () (const DataType scalar)
    {
      for_all_elems ([this,&scalar] (U_INT i, U_INT j)
        {
          memObj->_memSpace[i*_rows+j] *= scalar;
        });
//      return *this;
    }

  template<typename DataType>
    DataType
    Matrix<DataType>::partialProduct (U_INT row, U_INT col,
                                      Matrix<DataType> mat)
    {
      DataType value = 0;
      for (U_INT i = 0; i < _columns; ++i)
        {
          value += memObj->_memSpace[row * _columns + i]
              * mat.memObj->_memSpace[i * mat._columns + col];
        }
      return value;
    }

  ///
  /// Cross product of tow matrices
  ///
  template<typename DataType>
    Matrix<DataType>
    Matrix<DataType>::operator * (const Matrix<DataType> mat)
    {
      if (_columns == mat._rows)
        {
          Matrix<DataType> result (_rows, mat._columns);
          for_all_elems (
              [this,&mat,&result](U_INT i, U_INT j)
                {
                  result.memObj->_memSpace[i * result._columns + j] = partialProduct (i, j, mat);
                });
          return result;
        }
      throw DimentionMissmatch; // dimention missmatch
    }

  ///
  /// equality of tow matrices
  ///
  template<typename DataType>
    bool
    Matrix<DataType>::operator == (const Matrix& mat)
    {
      bool retVal (true);
      if ((_rows == mat._rows) && (_columns == mat._columns))
        {
          // check if all values are same
          for (U_INT i = 0; retVal && (i < _rows); ++i)
            {
              for (U_INT j = 0; retVal && (j < _columns); ++j)
                {
                  if (memObj->_memSpace[i * _rows + j] != mat.memObj->_memSpace[i * _rows + j])
                    {
                      retVal = false;
                      break;
                    }
                }
            }
        }
      return retVal;
    }

} /* namespace Linear */

#endif /* MATRIX_H_ */

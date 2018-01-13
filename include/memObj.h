/*
 * MemObj.h
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

#ifndef INCLUDE_MEMOBJ_H_
#define INCLUDE_MEMOBJ_H_

#include <vector>
#include <cstring>
#include <functional>
#include "basedef.h"

namespace Linear
{

  template<typename DataType>
  class MemObj
  {
  public:
    /*
     * Allocate memory block
     */
    bool allocateMemory(U_INT size);
    /*
     * get state of the object
     */
    bool getState() { return _state;}
    /*
     * get size of the object
     */
    U_INT getSize() { return _size;}
    /*
     * get values in std::vector form
     */
    std::vector<DataType> getValues();
    /*
     * initialize object from memory
     */
    void initFromVector(std::vector<DataType> values);
    /*
     * construct obj of given size
     */
    MemObj(U_INT size =0);
    /*
     * Construct and initialize obj from std::vector
     */
    MemObj(U_INT size, std::vector<DataType> values);
    /*
     * Copy constructor
     */
    MemObj(const MemObj & obj);
    /*
     * Assignment operator
     */
    void operator = (MemObj& m);

    virtual
          ~MemObj ();
    /*
     * Holds dynamically allocated memory for Vector
     */
    DataType * _memSpace;
    /*
     * State indicator
     */
    U_INT _state;
    /*
     * size
     */
    U_INT _size;
  private :
    /*
     * Invalidate object and free its memory.
     */
      void invalidateObj ();
    };

  template<typename DataType>
    void
    MemObj<DataType>::invalidateObj ()
    {
      if (ValidObject == _state)
        {
//          std::cout << "Memspace deleted" << std::endl;
          delete[] _memSpace;
          _state = InvalidObject;
        }
    }

  template<typename DataType>
    void
    MemObj<DataType>::operator = ( MemObj & m)
    {
      invalidateObj ();
       if(allocateMemory(m.getSize()))
         {
          // copy data from m to current only if memory allocation is successful.
             memcpy (_memSpace, m._memSpace,_size * sizeof(DataType));
         }
    }
  template<typename DataType>
    std::vector<DataType>
   MemObj<DataType>::getValues ()
    {
      std::vector<DataType> values;
      for( U_INT i = 0 ; i < _size; ++i)
        {
          values.push_back(_memSpace[i]);
        };
      return values;
    }

  template<typename DataType>
  MemObj<DataType>::MemObj(U_INT size ):_memSpace(nullptr), _size(size)
  {
    allocateMemory(_size);
  }
  template<typename DataType>
  MemObj<DataType>::MemObj(U_INT size, std::vector<DataType> values ):_memSpace(nullptr), _size(size)
  {
    if(allocateMemory(_size))
      memcpy (_memSpace, values.data(),_size * sizeof(DataType));
  }

  template<typename DataType>
  MemObj<DataType>::MemObj(const MemObj & obj): _memSpace(nullptr)
  {
    if(allocateMemory(obj._size))
      memcpy (_memSpace, obj._memSpace,_size * sizeof(DataType));
    else
      throw InvalidObject;
  }

  template <typename DataType>
  void
  MemObj<DataType>::initFromVector(std::vector<DataType> values)
  {
      invalidateObj ();
    if(allocateMemory(values.size()))
      memcpy (_memSpace, values.data(),_size * sizeof(DataType));
  }

  template<typename DataType>
    bool
    MemObj<DataType>::allocateMemory (U_INT size)
    {
      _state = InvalidObject; // unallocated
      if ((0 != size))
        {
//          std::cout << "Memspace allocated" << std::endl;
          _memSpace = new DataType[size] ();
          _state = ValidObject; // allocated
          _size = size;
          return true;
        }
      return false;
    }
  template<typename DataType>
  MemObj<DataType>::~MemObj ()
    {
      if (nullptr != _memSpace)
        {
//          std::cout << "Memspace deleted" << std::endl;
          delete[] _memSpace;
          _memSpace = nullptr;
        }
    }
}

#endif /* INCLUDE_MEMOBJ_H_ */

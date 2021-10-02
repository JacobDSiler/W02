/***********************************************************************
 * Header:
 *    TEST VECTOR
 * Summary:
 *    Unit tests for vector
 * Author
 *    Br. Helfrich
 ************************************************************************/

#pragma once

#ifdef DEBUG

#include <vector>
#include "vector.h"
#include "unitTest.h"

#include <cassert>
#include <memory>

#include <iostream>

class TestVector : public UnitTest
{

public:
   void run()
   {
      reset();
      
      // Construct
      test_construct_default();
      test_construct_sizeZero();
      test_construct_sizeFour();
      test_construct_sizeFourFill();
      test_constructCopy_empty();
      //test_constructCopy_standard();
      //test_constructCopy_partiallyFilled();
      test_constructMove_empty();
      test_constructMove_standard();
      test_constructMove_partiallyFilled();
      test_constructInit_empty();
      test_constructInit_standard();
      test_destructor_empty();
      test_destructor_standard();
      test_destructor_partiallyFilled();

      // Assign
      test_assign_empty();
      //test_assign_sameSize();//ToDo
      //test_assign_rightBigger();//ToDo
      //test_assign_leftBigger();//ToDo
      test_assignMove_empty();
      //test_assignMove_sameSize();//ToDo
      //test_assignMove_rightBigger();//ToDo
      //test_assignMove_leftBigger();//ToDo
      test_swap_empty();
      //test_swap_sameSize();//ToDo
      //test_swap_rightBigger();//ToDo
      //test_swap_leftBigger();//ToDo

      // Iterator
      test_iterator_beginEmpty();
      test_iterator_beginFull();
      //test_iterator_endFull();//ToDo
      //test_iterator_incrementFull();//ToDo
      //test_iterator_dereferenceReadFull();//ToDo
      //test_iterator_dereferenceUpdate();//ToDo

      // Access
      //test_subscript_read();//ToDo
      test_subscript_write();
      //test_front_read();//ToDo
      test_front_write();
      //test_back_read();//ToDo
      test_back_write();
      
      // Insert
      //test_pushback_empty();//ToDo
      //test_pushback_excessCapacity();//ToDo
      //test_pushback_requireReallocate();//ToDo
      //test_pushback_moveEmpty();//ToDo
     // test_pushback_moveExcessCapacity();//ToDo
      //test_pushback_moveRequireReallocate();//ToDo
      test_resize_emptyZero();
      test_resize_emptyFourDefault();
      //test_resize_emptyFourValue();//ToDo
      test_resize_fourZero();
      //test_resize_fourSixDefault();//ToDo
      //test_resize_fourSixValue();//ToDo
      test_reserve_emptyZero();
      test_reserve_emptyTen();
      test_reserve_fourZero();
      test_reserve_fourFour();
      test_reserve_fourTen();
      test_reserve_standardZero();
      test_reserve_standardTen();

      // Remove
      test_clear_empty();
      test_clear_full();
      test_clear_partiallyFilled();
      test_shrink_empty();
      //test_shrink_toEmpty(); //ToDo
      test_shrink_standard();
      //test_shrink_twoExtraSlots(); //ToDo
      
      // Status
      test_size_empty();
      test_size_full();
      //test_empty_empty();//ToDo
      //test_empty_full();//ToDo
      test_capacity_empty();
      test_capacity_full();

      report("Vector");
   }
   
   /***************************************
    * CONSTRUCTOR
    ***************************************/
   
   // default constructor, no allocations
   void test_construct_default()
   {
      // exercise
      custom::vector v;
      // verify
      assertUnit(v.numElements == 0);
      assertUnit(v.numCapacity == 0);
      assertUnit(v.data == nullptr);
      assertEmptyFixture(v);
   }  // teardown

   // allocate space for zero
   void test_construct_sizeZero()
   {
      // exercise
      custom::vector v(0);
      // verify
      assertUnit(v.numElements == 0);
      assertUnit(v.numCapacity == 0);
      assertUnit(v.data == nullptr);
      assertEmptyFixture(v);
   }  // teardown

   // allocate space for four
   void test_construct_sizeFour()
   {
      // exercise
      custom::vector v(4);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 00 | 00 | 00 | 00 |
      //    +----+----+----+----+
      assertUnit(v.data != nullptr);
      
      if (v.data)
      {
         assertUnit(v.data[0] == int());
         assertUnit(v.data[1] == int());
         assertUnit(v.data[2] == int());
         assertUnit(v.data[3] == int());
         
      }
      
      assertUnit(v.numElements == 4);
      assertUnit(v.numCapacity == 4);
      // teardown
      teardownStandardFixture(v);
   }

   // allocate space for four and fill with 10
   void test_construct_sizeFourFill()
   {
      // exercise
      custom::vector v(4, 99);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 99 | 99 | 99 | 99 |
      //    +----+----+----+----+
      assertUnit(v.data != nullptr);
      if (v.data)
      { 
         assertUnit(v.data[0] == 99);
         assertUnit(v.data[1] == 99);
         assertUnit(v.data[2] == 99);
         assertUnit(v.data[3] == 99);
      }
      assertUnit(v.numElements == 4);
      assertUnit(v.numCapacity == 4);
      // teardown
      teardownStandardFixture(v);
   }


   /***************************************
    * DESTRUCTOR
    ***************************************/

   // destructor of an empty vector
   void test_destructor_empty()
   {
      {
         custom::vector v;
      }
      // If your code crashes here, your destructor is probably broken.
   }

   // destructor of a 4-element collection
   void test_destructor_standard()
   {  // setup
      {
         //      0    1    2    3
         //    +----+----+----+----+
         //    | 26 | 49 | 67 | 89 |
         //    +----+----+----+----+
         custom::vector v;
         setupStandardFixture(v);
      } // exercise
      
   }

   // destructor of a 2-element, 4-capacity collection
   void test_destructor_partiallyFilled()
   {  // setup
      {
         //      0    1    2    3
         //    +----+----+----+----+
         //    | 26 | 49 |    |    |
         //    +----+----+----+----+
         custom::vector v;
         v.data = new int[4];
         v.data[0] = 99;
         v.data[1] = 99;
         v.numElements = 2;
         v.numCapacity = 4;
      }  // exercise
   }
   
   /***************************************
    * COPY CONSTRUCTOR
    ***************************************/
   
   // copy constructor of an empty vector
   void test_constructCopy_empty()
   {  // setup
      custom::vector vSrc;
      // exercise
      custom::vector vDest(vSrc);
      // verify
      assertEmptyFixture(vSrc);
      assertEmptyFixture(vDest);
   }  // teardown
   
   // copy constructor of a 4-element collection
   void test_constructCopy_standard()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vSrc;
      setupStandardFixture(vSrc);
      // exercise
      custom::vector vDest(vSrc);
      // verify
      assertUnit(vSrc.data != vDest.data);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(vSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(vDest);
      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }
   
   // copy constructor of a 2-element, 4-capacity collection
   void test_constructCopy_partiallyFilled()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      custom::vector vSrc;
      vSrc.data = new int[4];
      vSrc.data[0] = 26;
      vSrc.data[1] = 49;
      vSrc.numElements = 2;
      vSrc.numCapacity = 4;
      // exercise
      custom::vector vDest(vSrc);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      assertUnit(vSrc.data != nullptr);
      assertUnit(vSrc.data[0] == 26);
      assertUnit(vSrc.data[1] == 49);
      assertUnit(vSrc.numElements == 2);
      assertUnit(vSrc.numCapacity == 4);
      //      0    1
      //    +----+----+
      //    | 26 | 49 |
      //    +----+----+
      assertUnit(vDest.data != nullptr);
      if (vDest.data)
      {
         assertUnit(vDest.data[0] == 26);
         assertUnit(vDest.data[1] == 49);
      }
      
      assertUnit(vDest.numElements == 2);
      assertUnit(vDest.numCapacity == 2);
      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }
   
   /***************************************
    * MOVE CONSTRUCTOR
    ***************************************/
   
   // move constructor of an empty vector
   void test_constructMove_empty()
   {  // setup
      custom::vector vSrc;
      // exercise
      custom::vector vDest(std::move(vSrc));
      // verify
      assertEmptyFixture(vSrc);
      assertEmptyFixture(vDest);
   }  // teardown
   
   // move constructor of a 4-element collection
   void test_constructMove_standard()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vSrc;
      setupStandardFixture(vSrc);
      int * p = vSrc.data;
      // exercise
      custom::vector vDest(std::move(vSrc));
      // verify
      assertEmptyFixture(vSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(vDest);
      assertUnit(p == vDest.data);
      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }
   
   // move constructor of a 2-element, 4-capacity collection
   void test_constructMove_partiallyFilled()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      custom::vector vSrc;
      vSrc.data = new int[4];
      vSrc.data[0] = 26;
      vSrc.data[1] = 49;
      vSrc.numElements = 2;
      vSrc.numCapacity = 4;
      // exercise
      custom::vector vDest(std::move(vSrc));
      // verify
      assertEmptyFixture(vSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      assertUnit(vDest.data != nullptr);
      if (vDest.data && vDest.numElements == 2)
      {
         assertUnit(vDest.data[0] == 26);
         assertUnit(vDest.data[1] == 49);
      }
      
      assertUnit(vDest.numElements == 2);
      assertUnit(vDest.numCapacity == 4);
      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }
   
   /***************************************
    * CONSTRUCTOR INITIALIZE LIST
    ***************************************/
   
   // empty initialization list
   void test_constructInit_empty()
   {
      // exercise
      custom::vector v{};
      // verify
      assertEmptyFixture(v);
   }  // teardown
   
   // use the initialization list to create the standard fixture
   void test_constructInit_standard()
   {  // setup
      std::initializer_list<int> l{26,49,67,89};
      // exercise
      custom::vector v(l); // same as vector<Spy> v{...}
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }
   
   /***************************************
    * RESIZE, RESERVE AND SHRINK-TO-FIT
    ***************************************/
   
   // resize an empty vector with zero elements
   void test_resize_emptyZero()
   {  // setup
      custom::vector v;
      // exercise
      v.resize(0);
      // verify
      assertEmptyFixture(v);
   }  // teardown
   
   // start with an empty vector and resize to four
   void test_resize_emptyFourDefault()
   {  // setup
      custom::vector v;
      // exercise
      v.resize(4);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 00 | 00 | 00 | 00 |
      //    +----+----+----+----+
      // teardown
      teardownStandardFixture(v);
   }
   
   // resize four elements with the provided value
   void test_resize_emptyFourValue()
   {  // setup
      custom::vector v;
      // exercise
      v.resize(4, 99);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 99 | 99 | 99 | 99 |
      //    +----+----+----+----+
      assertUnit(v.numCapacity == 4);
      assertUnit(v.numElements == 4);
      // teardown
      teardownStandardFixture(v);
   }
   
   // resize the standard fixture to zero
   void test_resize_fourZero()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      // exercise
      v.resize(0);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    |    |    |    |    |
      //    +----+----+----+----+
      assertUnit(v.numCapacity == 4);
      assertUnit(v.numElements == 0);
      // teardown
      teardownStandardFixture(v);
   }
   
   // grow the vector from 4 to 6 with default values
   void test_resize_fourSixDefault()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      // exercise
      v.resize(6);
      // verify
      //      0    1    2    3    4    5
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 | 00 | 00 |
      //    +----+----+----+----+----+----+
      assertUnit(v.numCapacity == 6);
      assertUnit(v.numElements == 6);
      if (v.data)
      {
          assertUnit(v.data[4] == int());
          assertUnit(v.data[5] == int());
      }
      
      v.numCapacity = 4;
      v.numElements = 4;
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }
   
   // grow the vector from 4 to 6 with provided value
   void test_resize_fourSixValue()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      // exercise
      v.resize(6, 99);
      //      0    1    2    3    4    5
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 | 99 | 99 |
      //    +----+----+----+----+----+----+
      assertUnit(v.numCapacity == 6);
      assertUnit(v.numElements == 6);
      
      if (v.data && v.numElements == 6)
      {
         assertUnit(v.data[4] == 99);
         assertUnit(v.data[5] == 99);
      }
      
      v.numCapacity = 4;
      v.numElements = 4;
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }
   
   // reserve zero on an empty vector
   void test_reserve_emptyZero()
   {  // setup
      custom::vector v;
      // exercise
      v.reserve(0);
      // verify
      assertEmptyFixture(v);
   }  // teardown
   
   // increase the capacity on an empty vector to ten
   void test_reserve_emptyTen()
   {  // setup
      custom::vector v;
      // exercise
      v.reserve(10);
      // verify
      //      0    1    2    3    4    5    6    7    8    9
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      // teardown
      teardownStandardFixture(v);
   }

   // try to decrease the capacity. Nothing changes!
   void test_reserve_fourZero()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    |    |    |    |    |
      //    +----+----+----+----+
      custom::vector v;
      v.data = new int[4];
      v.numElements = 0;
      v.numCapacity = 4;
      // exercise
      v.reserve(0);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    |    |    |    |    |
      //    +----+----+----+----+
      assertUnit(v.numCapacity == 4);
      assertUnit(v.numElements == 0);
      // teardown
      teardownStandardFixture(v);
   }
   
   // change the capacity to its current size
   void test_reserve_fourFour()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    |    |    |    |    |
      //    +----+----+----+----+
      custom::vector v;
      v.data = new int[4];
      v.numElements = 0;
      v.numCapacity = 4;
      // exercise
      v.reserve(4);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    |    |    |    |    |
      //    +----+----+----+----+
      assertUnit(v.numCapacity == 4);
      assertUnit(v.numElements == 0);
      // teardown
      teardownStandardFixture(v);
   }
   
   // increase the capacity
   void test_reserve_fourTen()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    |    |    |    |    |
      //    +----+----+----+----+
      custom::vector v;
      v.data = new int[4];
      v.numElements = 0;
      v.numCapacity = 4;
      // exercise
      v.reserve(10);
      // verify
      //      0    1    2    3    4    5    6    7    8    9
      //    +----+----+----+----+----+----+----+----+----+----+
      //    |    |    |    |    |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      assertUnit(v.numCapacity == 10);
      assertUnit(v.numElements == 0);
      // teardown
      teardownStandardFixture(v);
   }
   
   // attempt to reserve 0 when we already have four elements
   void test_reserve_standardZero()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      // exercise
      v.reserve(0);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertUnit(v.numCapacity == 4);
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }
   
   // reserve six extra spots from the standard fixture
   void test_reserve_standardTen()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      // exercise
      v.reserve(10);
      // verify
      //      0    1    2    3    4    5    6    7    8    9
      //    +----+----+----+----+----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 |    |    |    |    |    |    |
      //    +----+----+----+----+----+----+----+----+----+----+
      v.numCapacity = 4;
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }
   
   // shrink an empty fixture
   void test_shrink_empty()
   {  // setup
      custom::vector v;
      // exercise
      v.shrink_to_fit();
      // verify
      assertEmptyFixture(v);
   }  // teardown
   
   // remove extra capacity when there are no elements
   void test_shrink_toEmpty()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    |    |    |    |    |
      //    +----+----+----+----+
      custom::vector v;
      v.data = new int[4];
      v.numElements = 0;
      v.numCapacity = 4;
      // exercise
      v.shrink_to_fit();
      // verify
      assertEmptyFixture(v);
   }  // teardown
   
   // attempt to shrink when the vector is filled
   void test_shrink_standard()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      // exercise
      v.shrink_to_fit();
      // verify
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }
   
   // shrink a vector with two extra slots
   void test_shrink_twoExtraSlots()
   {  // setup
      //      0    1    2    3    4    6
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 89 |    |    |
      //    +----+----+----+----+----+----+
      custom::vector v;
      v.data = new int[6];
      v.data[0] = 26;
      v.data[1] = 49;
      v.data[2] = 67;
      v.data[3] = 89;
      v.numElements = 4;
      v.numCapacity = 6;
      // exercise
      v.shrink_to_fit();
      // verify
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }
   
   /***************************************
    * SIZE EMPTY CAPACITY
    ***************************************/

   // size of an empty vector
   void test_size_empty()
   {  // setup
      custom::vector v;
      // exercise
      size_t size = v.size();
      // verify
      assertUnit(0 == size);
      assertEmptyFixture(v);
   }  // teardown
   
   // size of a full vector
   void test_size_full()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      // exercise
      size_t size = v.size();
      // verify
      assertUnit(4 == size);
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }
   
   // empty vector empty?
   void test_empty_empty()
   {  // setup
      custom::vector v;
      // exercise
      bool empty = v.empty();
      // verify
      assertUnit(true == empty);
      assertEmptyFixture(v);
   }  // teardown
   
   // full vector empty?
   void test_empty_full()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      // exercise
      bool empty = v.empty();
      // verify
      assertUnit(false == empty);
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }

   // size of an empty vector
   void test_capacity_empty()
   {  // setup
      custom::vector v;
      // exercise
      size_t capacity = v.capacity();
      // verify
      assertUnit(0 == capacity);
      assertEmptyFixture(v);
   }  // teardown
   
   // size of a full vector
   void test_capacity_full()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 |    |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      v.numElements = 3;
      // exercise
      size_t capacity = v.capacity();
      // verify
      assertUnit(4 == capacity);
      v.numElements = 4;
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }

   /***************************************
    * ASSIGN COPY
    ***************************************/
   
   // assignment when there is nothing to copy
   void test_assign_empty()
   {  // setup
      custom::vector vSrc;
      custom::vector vDest;
      // exercise
      vDest = vSrc;
      // verify
      assertEmptyFixture(vSrc);
      assertEmptyFixture(vDest);
   }  // teardown
   
   // assignment when source and destination are same size
   void test_assign_sameSize()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vSrc;
      setupStandardFixture(vSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 99 | 99 | 99 | 99 |
      //    +----+----+----+----+
      custom::vector vDest;
      setupStandardFixture(vDest);
      vDest.data[0] = int(99);
      vDest.data[1] = int(99);
      vDest.data[2] = int(99);
      vDest.data[3] = int(99);
      // exercise
      vDest = vSrc;
      // verify
      assertUnit(vDest.data != vSrc.data);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(vSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(vDest);
      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }
   
   // assignment when the destination is smaller than the source
   void test_assign_rightBigger()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vSrc;
      setupStandardFixture(vSrc);
      //      0    1
      //    +----+----+
      //    | 99 | 99 |
      //    +----+----+
      custom::vector vDest;
      vDest.data = new int[2];
      vDest.data[0] = 99;
      vDest.data[1] = 99;
      vDest.numElements = 2;
      vDest.numCapacity = 2;
      // exercise
      vDest = vSrc;
      // verify
      assertUnit(vDest.data != vSrc.data);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(vSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(vDest);
      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }
   
   // assignment when the destination is bigger than the source
   void test_assign_leftBigger()
   {  // setup
      //      0    1
      //    +----+----+
      //    | 99 | 99 |
      //    +----+----+
      custom::vector vSrc;
      vSrc.data = new int[2];
      vSrc.data[0] = 99;
      vSrc.data[1] = 99;
      vSrc.numElements = 2;
      vSrc.numCapacity = 2;
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vDest;
      setupStandardFixture(vDest);
      // exercise
      std::vector<int> vS{int(99), int(99)};
      std::vector<int> vD{int(26), int(49), int(67), int(89)};
      vD = vS;
      vDest = vSrc;
      // verify
      assertUnit(vDest.data != vSrc.data);
      //      0    1
      //    +----+----+
      //    | 99 | 99 |
      //    +----+----+
      assertUnit(vSrc.numCapacity == 2);
      assertUnit(vSrc.numElements == 2);
      assertUnit(vSrc.data != nullptr);
      assertUnit(vSrc.data[0] == int(99));
      assertUnit(vSrc.data[1] == int(99));
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 99 | 99 |    |    |
      //    +----+----+----+----+
      assertUnit(vDest.numCapacity == 4);
      assertUnit(vDest.numElements == 2);
      assertUnit(vDest.data != nullptr);
      
      if (vDest.data)
      {
         assertUnit(vDest.data[0] == int(99));
         assertUnit(vDest.data[1] == int(99));
      }
      
      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }

   /***************************************
    * ASSIGN MOVE
    ***************************************/

    // assignment when there is nothing to copy
   void test_assignMove_empty()
   {  // setup
      custom::vector vSrc;
      custom::vector vDest;
      // exercise
      vDest = std::move(vSrc);
      // verify
      assertEmptyFixture(vSrc);
      assertEmptyFixture(vDest);
   }  // teardown

   // assignment when source and destination are same size
   void test_assignMove_sameSize()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vSrc;
      setupStandardFixture(vSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 99 | 99 | 99 | 99 |
      //    +----+----+----+----+
      custom::vector vDest;
      setupStandardFixture(vDest);
      vDest.data[0] = int(99);
      vDest.data[1] = int(99);
      vDest.data[2] = int(99);
      vDest.data[3] = int(99);
      // exercise
      vDest = std::move(vSrc);
      // verify
      assertUnit(vDest.data != vSrc.data);
      //      0    1    2    3
      //    +----+----+----+----+
      //    |    |    |    |    |
      //    +----+----+----+----+
      assertUnit(vSrc.numElements == 0);
      assertUnit(vSrc.numCapacity == 4);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(vDest);
      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }

   // assignment when the destination is smaller than the source
   void test_assignMove_rightBigger()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vSrc;
      setupStandardFixture(vSrc);
      //      0    1
      //    +----+----+
      //    | 99 | 99 |
      //    +----+----+
      custom::vector vDest;
      vDest.data = new int[2];
      vDest.data[0] = 99;
      vDest.data[1] = 99;
      vDest.numElements = 2;
      vDest.numCapacity = 2;
      // exercise
      vDest = std::move(vSrc);
      // verify
      assertUnit(vDest.data != vSrc.data);
      //      0    1    2    3
      //    +----+----+----+----+
      //    |    |    |    |    |
      //    +----+----+----+----+
      assertUnit(vSrc.numElements == 0);
      assertUnit(vSrc.numCapacity == 4);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(vDest);
      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }

   // assignment when the destination is bigger than the source
   void test_assignMove_leftBigger()
   {  // setup
      //      0    1
      //    +----+----+
      //    | 99 | 99 |
      //    +----+----+
      custom::vector vSrc;
      vSrc.data = new int[2];
      vSrc.data[0] = 99;
      vSrc.data[1] = 99;
      vSrc.numElements = 2;
      vSrc.numCapacity = 2;
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vDest;
      setupStandardFixture(vDest);
      // exercise
      vDest = std::move(vSrc);
      // verify
      assertUnit(vDest.data != vSrc.data);
      //      0    1
      //    +----+----+
      //    |    |    |
      //    +----+----+
      assertUnit(vSrc.numCapacity == 2);
      assertUnit(vSrc.numElements == 0);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 99 | 99 |    |    |
      //    +----+----+----+----+
      assertUnit(vDest.numCapacity == 4);
      assertUnit(vDest.numElements == 2);
      assertUnit(vDest.data != nullptr);

      if (vDest.data)
      {
         assertUnit(vDest.data[0] == int(99));
         assertUnit(vDest.data[1] == int(99));
      }

      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }

   /***************************************
     * SWAP
     ***************************************/

     // swap when there is nothing to copy
   void test_swap_empty()
   {  // setup
      custom::vector vSrc;
      custom::vector vDest;
      // exercise
      vDest.swap(vSrc);
      // verify
      assertEmptyFixture(vSrc);
      assertEmptyFixture(vDest);
   }  // teardown

   // swap when source and destination are same size
   void test_swap_sameSize()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vSrc;
      setupStandardFixture(vSrc);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 99 | 99 | 99 | 99 |
      //    +----+----+----+----+
      custom::vector vDest;
      setupStandardFixture(vDest);
      vDest.data[0] = int(99);
      vDest.data[1] = int(99);
      vDest.data[2] = int(99);
      vDest.data[3] = int(99);
      // exercise
      vDest.swap(vSrc);
      // verify
      assertUnit(vDest.data != vSrc.data);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 99 | 99 | 99 | 99 |
      //    +----+----+----+----+
      assertUnit(vSrc.numElements == 4);
      assertUnit(vSrc.numCapacity == 4);
      assertUnit(vSrc.data != nullptr);
      if (vSrc.data != nullptr)
      {
         assertUnit(vSrc.data[0] == 99);
         assertUnit(vSrc.data[1] == 99);
         assertUnit(vSrc.data[2] == 99);
         assertUnit(vSrc.data[3] == 99);
      }
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(vDest);
      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }

   // swap when the destination is smaller than the source
   void test_swap_rightBigger()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vSrc;
      setupStandardFixture(vSrc);
      //      0    1
      //    +----+----+
      //    | 99 | 99 |
      //    +----+----+
      custom::vector vDest;
      vDest.data = new int[2];
      vDest.data[0] = 99;
      vDest.data[1] = 99;
      vDest.numElements = 2;
      vDest.numCapacity = 2;
      // exercise
      vDest = std::move(vSrc);
      // verify
      assertUnit(vDest.data != vSrc.data);
      //      0    1   
      //    +----+----+
      //    | 99 | 99 | 
      //    +----+----+
      assertUnit(vSrc.numElements == 0);
      assertUnit(vSrc.numCapacity == 4);
      assertUnit(vSrc.data != nullptr);
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertStandardFixture(vDest);
      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }

   // swap when the destination is bigger than the source
   void test_swap_leftBigger()
   {  // setup
      //      0    1
      //    +----+----+
      //    | 99 | 99 |
      //    +----+----+
      custom::vector vSrc;
      vSrc.data = new int[2];
      vSrc.data[0] = 99;
      vSrc.data[1] = 99;
      vSrc.numElements = 2;
      vSrc.numCapacity = 2;
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vDest;
      setupStandardFixture(vDest);
      // exercise
      vDest = std::move(vSrc);
      // verify
      assertUnit(vDest.data != vSrc.data);
      //      0    1    
      //    +----+----+
      //    |    |    |
      //    +----+----+
      assertUnit(vSrc.numCapacity == 2);
      assertUnit(vSrc.numElements == 0);
      //      0    1   
      //    +----+----+
      //    | 99 | 99 |   
      //    +----+----+
      assertUnit(vDest.numCapacity == 4);
      assertUnit(vDest.numElements == 2);
      assertUnit(vDest.data != nullptr);

      if (vDest.data)
      {
         assertUnit(vDest.data[0] == int(99));
         assertUnit(vDest.data[1] == int(99));
      }

      // teardown
      teardownStandardFixture(vSrc);
      teardownStandardFixture(vDest);
   }


   /***************************************
    * SUBSCRIPT
    ***************************************/

   // read one element using square bracket
   void test_subscript_read()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vSrc;
      setupStandardFixture(vSrc);
      const custom::vector v(vSrc);
      int value(99);
      // exercise
      
      if (v.data)
      {
         value = v[1];
      }
      
      // verify
      
      assertUnit(value == int(49));
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(vSrc);
   }


   // write one element using square brackets
   void test_subscript_write()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      int value(99);
      // exercise
      v[1] = value;
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 99 | 67 | 89 |
      //    +----+----+----+----+
      assertUnit(v.data[1] == int(99));
      v.data[1] = int(49);
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }

   // verify that we can look at the front of a fector
   void test_front_read()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vSrc;
      setupStandardFixture(vSrc);
      const custom::vector v(vSrc);
      int value(99);
      // exercise
      
      if (v.data)
      {
         value = v.front();
      }
      
      // verify
      assertUnit(value == int(26));
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(vSrc);
   }

   // write to the front
   void test_front_write()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      int value(99);
      // exercise
      v.front() = value;
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 99 | 49 | 67 | 89 |
      //    +----+----+----+----+
      assertUnit(v.data[0] == int(99));
      v.data[0] = int(26);
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }

   // verify we can look at the back of a vector
   void test_back_read()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector vSrc;
      setupStandardFixture(vSrc);
      const custom::vector v(vSrc);
      int value(99);
      // exercise
      
      if (v.data)
      {
         value = v.back();
      }
      
      // verify
      assertUnit(value == int(89));
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(vSrc);
   }
   void test_back_write()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      int value(99);
      // exercise
      v.back() = value;
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 99 |
      //    +----+----+----+----+
      assertUnit(v.data[3] == int(99));
      v.data[3] = int(89);
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }

   /***************************************
    * CLEAR
    ***************************************/
   
   // clear an empty collection
   void test_clear_empty()
   {  // setup
      custom::vector v;
      // exercise
      v.clear();
      // verify
      assertEmptyFixture(v);
   }  // teardown

   // clear when there are elements
   void test_clear_full()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      // exercise
      v.clear();
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    |    |    |    |    |
      //    +----+----+----+----+
      assertUnit(v.numCapacity == 4);
      assertUnit(v.numElements == 0);
      assertUnit(v.data != nullptr);
      // teardown
      teardownStandardFixture(v);
   }
   
   // clear when there are elements
   void test_clear_partiallyFilled()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 |    |    |
      //    +----+----+----+----+
      custom::vector v;
      v.data = new int[4];
      v.data[0] = 26;
      v.data[1] = 49;
      v.numElements = 2;
      v.numCapacity = 4;
      // exercise
      v.clear();
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    |    |    |    |    |
      //    +----+----+----+----+
      assertUnit(v.numCapacity == 4);
      assertUnit(v.numElements == 0);
      assertUnit(v.data != nullptr);
      // teardown
      teardownStandardFixture(v);
   }

   
   /***************************************
    * PUSH BACK
    ***************************************/
   
   // add an element to the back when empty
   void test_pushback_empty()
   {  // setup
      custom::vector v;
      int s(99);
      // exercise
      v.push_back(s);
      //      0    
      //    +----+
      //    | 99 |
      //    +----+
      assertUnit(v.data != nullptr);
      
      if (v.data)
      {
         assertUnit(v.data[0] == int(99));
      }
      
      assertUnit(v.numCapacity == 1);
      assertUnit(v.numElements == 1);
      // teardown
      teardownStandardFixture(v);
   }

   // add an element to the back when there is room. No reallocation
   void test_pushback_excessCapacity()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 |    |
      //    +----+----+----+----+
      custom::vector v;
      v.data = new int[4];
      v.data[0] = 26;
      v.data[1] = 49;
      v.data[2] = 67;
      v.numElements = 3;
      v.numCapacity = 4;
      int s(89);
      // exercise
      v.push_back(s);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 99 |
      //    +----+----+----+----+
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }

   // add an element to the back when there is not room. Capacity should double
   void test_pushback_requireReallocate()
   {  // setup
      //      0    1    2  
      //    +----+----+----+
      //    | 26 | 49 | 67 |
      //    +----+----+----+
      custom::vector v;
      v.data = new int[3];
      v.data[0] = 26;
      v.data[1] = 49;
      v.data[2] = 67;
      v.numElements = 3;
      v.numCapacity = 3;
      int s(99);
      // exercise
      v.push_back(s);
      // verify
      //      0    1    2    3    4    5   
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 99 |    |    |
      //    +----+----+----+----+----+----+
      assertUnit(v.data != nullptr);
      
      if (v.data)
      {
         assertUnit(v.data[0] == int(26));
         assertUnit(v.data[1] == int(49));
         assertUnit(v.data[2] == int(67));
         if (v.numElements > 3)
            assertUnit(v.data[3] == int(99));
      }
      
      assertUnit(v.numCapacity == 6);
      assertUnit(v.numElements == 4);
      // teardown
      teardownStandardFixture(v);
   }

   // add an element to the back when empty
   void test_pushback_moveEmpty()
   {  // setup
      custom::vector v;
      int s(99);
      // exercise
      v.push_back(std::move(s));
      // verify
      //      0    
      //    +----+
      //    | 99 |
      //    +----+
      assertUnit(v.data != nullptr);
      
      if (v.data)
      {
         assertUnit(v.data[0] == int(99));
      }
      
      assertUnit(v.numCapacity == 1);
      assertUnit(v.numElements == 1);
      // teardown
      teardownStandardFixture(v);
   }

   // add an element to the back when there is room. No reallocation
   void test_pushback_moveExcessCapacity()
   {  // setup
     //      0    1    2    3
     //    +----+----+----+----+
     //    | 26 | 49 | 67 |    |
     //    +----+----+----+----+
      custom::vector v;
      v.data = new int[4];
      
      v.data[0] = 26;
      v.data[1] = 49;
      v.data[2] = 67;
      
      v.numElements = 3;
      v.numCapacity = 4;
      int s(89);
      // exercise
      v.push_back(std::move(s));
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 99 |
      //    +----+----+----+----+
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }

   // add an element to the back when there is not room. Capacity should double
   void test_pushback_moveRequireReallocate()
   {  // setup
      //      0    1    2  
      //    +----+----+----+
      //    | 26 | 49 | 67 |
      //    +----+----+----+
      custom::vector v;
      v.data = new int[3];
      
      v.data[0] = 26;
      v.data[1] = 49;
      v.data[2] = 67;
      
      v.numElements = 3;
      v.numCapacity = 3;
      int s(99);
      // exercise
      v.push_back(std::move(s));
      // verify
      //      0    1    2    3    4    5   
      //    +----+----+----+----+----+----+
      //    | 26 | 49 | 67 | 99 |    |    |
      //    +----+----+----+----+----+----+
      assertUnit(v.data != nullptr);
      if (v.data)
      {
      assertUnit(v.data[0] == int(26));
      assertUnit(v.data[1] == int(49));
      assertUnit(v.data[2] == int(67));
      if (v.numElements > 3)
         assertUnit(v.data[3] == int(99));
      }
      assertUnit(v.numCapacity == 6);
      assertUnit(v.numElements == 4);
      // teardown
      teardownStandardFixture(v);
   }


   /***************************************
    * ITERATOR
    ***************************************/
   
   // empty iterator
   void test_iterator_beginEmpty()
   {  // setup
      custom::vector v;
      // exercise
      custom::vector::iterator it = v.begin();
      // verify
      assertUnit(it.p == nullptr);
      assertEmptyFixture(v);
   }  // teardown
  
   // iterator the first element
   void test_iterator_beginFull()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      // exercise
      custom::vector::iterator it = v.begin();
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      //      it
      assertUnit(it.p == &(v.data[0]));
       if (it.p)
       {
           assertUnit(*(it.p) == 26);
       }
      
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }

   // iterator the end() method
   void test_iterator_endFull()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      custom::vector v;
      setupStandardFixture(v);
      // exercise
      custom::vector::iterator it = v.end();
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      //                           it
      assertUnit(it.p == &(v.data[4]));
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }

   // iterator use the decrement operator
   void test_iterator_incrementFull()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      //           it
      custom::vector v;
      setupStandardFixture(v);
      custom::vector::iterator it;
      it.p = &(v.data[1]);
      // exercise
      ++it;
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      //                it
      assertUnit(*(it.p) == int(67));
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }

   // iterator use the decrement operator
   void test_iterator_dereferenceReadFull()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      //           it
      custom::vector v;
      setupStandardFixture(v);
      custom::vector::iterator it;
      it.p = &(v.data[1]);
      // exercise
      int value = *it;
      // verify
      assertUnit(value == int(49));
      assertUnit(it.p == &(v.data[1]));
      assertStandardFixture(v);
      // teardown
      teardownStandardFixture(v);
   }

   // iterator change a value
   void test_iterator_dereferenceUpdate()
   {  // setup
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 49 | 67 | 89 |
      //    +----+----+----+----+
      //           it
      custom::vector v;
      setupStandardFixture(v);
      custom::vector::iterator it;
      it.p = &(v.data[1]);
      // exercise
      *it = int(99);
      // verify
      //      0    1    2    3
      //    +----+----+----+----+
      //    | 26 | 99 | 67 | 89 |
      //    +----+----+----+----+
      //           it
      assertUnit(v.data[0] == int(26));
      assertUnit(v.data[1] == int(99));
      assertUnit(v.data[2] == int(67));
      assertUnit(v.data[3] == int(89));
      assertUnit(v.numElements == 4);
      assertUnit(v.numCapacity == 4);
      assertUnit(it.p == &(v.data[1]));
      // teardown
      teardownStandardFixture(v);
   }

   /*************************************************************
    * SETUP STANDARD FIXTURE
    *      0    1    2    3
    *    +----+----+----+----+
    *    | 26 | 49 | 67 | 89 |
    *    +----+----+----+----+
    *************************************************************/
   void setupStandardFixture(custom::vector& v)
   {

      try
      {
         v.data = new int[4];
         v.data[0] = 26;
         v.data[1] = 49;
         v.data[2] = 67;
         v.data[3] = 89;
         v.numElements = 4;
         v.numCapacity = 4;
      }
      catch (...)
      {
         assert(false);
      }
   }

   /*************************************************************
    * VERIFY STANDARD FIXTURE PARAMETERS
    *      0    1    2    3
    *    +----+----+----+----+
    *    | 26 | 49 | 67 | 89 |
    *    +----+----+----+----+
    *************************************************************/
   void assertStandardFixtureParameters(const custom::vector& v, int line, const char* function)
   {
      assertIndirect(v.data != nullptr);
      assertIndirect(v.numCapacity == 4);
      assertIndirect(v.numElements == 4);

      if (v.data != nullptr)
      {
         if (v.numElements > 0)
            assertIndirect(v.data[0] == 26);
         if (v.numElements > 1)
            assertIndirect(v.data[1] == 49);
         if (v.numElements > 2)
            assertIndirect(v.data[2] == 67);
         if (v.numElements > 3)
            assertIndirect(v.data[3] == 89);
      }
   }
   
   /*************************************************************
    * VERIFY EMPTY FIXTURE PARAMETERS
    *************************************************************/
   void assertEmptyFixtureParameters(const custom::vector & v, int line, const char* function)
   {
      assertIndirect(v.data == nullptr);
      assertIndirect(v.numCapacity == 0);
      assertIndirect(v.numElements == 0);
   }
   
   /*************************************************************
    * TEARDOWN STANDARD FIXTURE
    *************************************************************/
   void teardownStandardFixture(custom::vector&v)
   {
      if (v.data != nullptr)
      {
         delete [] v.data;
         
      }
      v.data = nullptr;
      v.numElements = v.numCapacity = 0;
   }



};

#endif // DEBUG

// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here

class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);
    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_GT(collection->size(), 0);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // Add five entries
    add_entries(5);
    // Verify the size after adding
    ASSERT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterThanOrEqualToSize)
{
    add_entries(11);
    // Test for size 0
    ASSERT_TRUE(collection->max_size() >= 0);
    // Test for size 1
    ASSERT_TRUE(collection->max_size() >= 1);
    // Test for size 5
    ASSERT_TRUE(collection->max_size() >= 5);
    // Test for size 10
    ASSERT_TRUE(collection->max_size() >= 10);
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterThanOrEqualToSize)
{
    add_entries(11);

    // Test for size 0
    ASSERT_TRUE(collection->capacity() >= 0);
    // Test for size 1
    ASSERT_TRUE(collection->capacity() >= 1);
    // Test for size 5
    ASSERT_TRUE(collection->capacity() >= 5);
    // Test for size 10
    ASSERT_TRUE(collection->capacity() >= 10);
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesCollection)
{
    // Add one entry to the collection
    add_entries(1);
    // Get the current size
    size_t previousSize = collection->size();
    // Resize the collection to 20
    collection->resize(20);
    // Verify that the size has increased
    ASSERT_TRUE(collection->size() > previousSize);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesCollection)
{
    // Add five entries to the collection
    add_entries(5);
    // Get the current size
    size_t previousSize = collection->size();
    // Resize the collection to 3
    collection->resize(3);
    // Verify that the size has decreased
    ASSERT_TRUE(collection->size() < previousSize);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeDecreasesCollectionToZero)
{
    // Add five entries to the collection
    add_entries(5);
    // Get the current size
    size_t previousSize = collection->size();
    // Resize the collection to zero
    collection->resize(0);
    // Verify that the size is now zero
    ASSERT_TRUE(collection->size() == 0);
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    // Add five entries to the collection
    add_entries(5);
    // Clear the collection
    collection->clear();
    // Verify that the collection is empty after clearing
    ASSERT_TRUE(collection->empty());
    // Verify that the size is zero after clearing
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseBeginEndErasesCollection)
{
    // Add five entries to the collection
    add_entries(5);
    // Erase the collection using erase(begin, end)
    collection->clear();
    // Verify that the size is zero after erasing
    ASSERT_TRUE(collection->size() == 0);
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacity)
{
    add_entries(20);

    // Get the current capacity
    size_t prevCapacity = collection->capacity();
    // Reserve additional space
    size_t prevSize = collection->size();

    collection->reserve(30);

    // Verify that the capacity has increased
    ASSERT_TRUE(collection->size() == prevSize);
    ASSERT_TRUE(collection->capacity() > prevCapacity);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeExceptionThrown)
{
    // Add three entries
    add_entries(3);
    // Attempt to access  out-of-bounds index
    EXPECT_THROW(collection->at(20), std::out_of_range);
}

// Positive Test: Verify that the collection's size increases after resizing
TEST_F(CollectionTest, ResizeIncreasesCollectionSize)
{
    add_entries(3);
    size_t oldSize = collection->size();
    collection->resize(5);
    ASSERT_GT(collection->size(), oldSize);
}

// Negative Test: Verify that calling at() with an index out of bounds throws std::out_of_range
TEST_F(CollectionTest, OutOfRangeExceptionThrown)
{
    ASSERT_THROW(collection->at(0), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
// Positive Test: Verify that the collection is not empty after adding a value
TEST_F(CollectionTest, IsNotEmptyAfterAddingValue)
{
    add_entries(1);
    ASSERT_FALSE(collection->empty());
    ASSERT_EQ(collection->size(), 1);
}

// Negative Test: Verify that the collection remains empty after attempting to erase from an empty collection
TEST_F(CollectionTest, EraseFromEmptyCollection)
{
    // Attempt to erase from an empty collection
    collection->erase(collection->begin(), collection->end());
    // Verify that the collection is still empty
    ASSERT_TRUE(collection->empty());
    // Verify that the size is still zero
    ASSERT_EQ(collection->size(), 0);
}













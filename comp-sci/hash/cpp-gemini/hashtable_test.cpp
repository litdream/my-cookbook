#include "gtest/gtest.h"
#include "hashtable.hpp"

// Test fixture for HashTable
template <typename Key, typename Value>
class HashTableTest : public ::testing::Test {
protected:
    HashTable<Key, Value> ht;
    HashTableTest() : ht(10) {}
};

// Specialization for string keys and string values
using MyHashTableTest = HashTableTest<std::string, std::string>;

TEST_F(MyHashTableTest, PutAndGet) {
    ht.put("hello", "world");
    ASSERT_EQ(ht.get("hello"), "world");

    ht.put("foo", "bar");
    ASSERT_EQ(ht.get("foo"), "bar");
}

TEST_F(MyHashTableTest, UpdateExistingKey) {
    ht.put("test", "initial");
    ASSERT_EQ(ht.get("test"), "initial");

    ht.put("test", "updated");
    ASSERT_EQ(ht.get("test"), "updated");
}

TEST_F(MyHashTableTest, KeyNotFoundGet) {
    ASSERT_THROW(ht.get("nonexistent"), std::out_of_range);
}

TEST_F(MyHashTableTest, RemoveKey) {
    ht.put("removeme", "value");
    ASSERT_EQ(ht.get("removeme"), "value");

    ht.remove("removeme");
    ASSERT_THROW(ht.get("removeme"), std::out_of_range);
}

TEST_F(MyHashTableTest, RemoveNonExistentKey) {
    ASSERT_THROW(ht.remove("nonexistent"), std::out_of_range);
}

TEST_F(MyHashTableTest, OperatorSquareBracketsPutAndGet) {
    ht["key1"] = "value1";
    ASSERT_EQ(ht["key1"], "value1");

    ht["key2"] = "value2";
    ASSERT_EQ(ht["key2"], "value2");

    // Update using operator[]
    ht["key1"] = "newValue1";
    ASSERT_EQ(ht["key1"], "newValue1");
}

TEST_F(MyHashTableTest, OperatorSquareBracketsGetNonExistentKey) {
    // Accessing a non-existent key via operator[] inserts it with a default-constructed value
    // For std::string, this means an empty string.
    std::string value = ht["newkey"];
    ASSERT_EQ(value, "");
    ASSERT_EQ(ht.get("newkey"), "");
}

// Test with different key and value types (e.g., int to int)
class IntIntHashTableTest : public HashTableTest<int, int> {};

TEST_F(IntIntHashTableTest, PutAndGetInts) {
    ht.put(1, 100);
    ASSERT_EQ(ht.get(1), 100);

    ht[2] = 200;
    ASSERT_EQ(ht[2], 200);

    ht.remove(1);
    ASSERT_THROW(ht.get(1), std::out_of_range);
}

TEST_F(IntIntHashTableTest, GetNonExistentIntKey) {
    ASSERT_THROW(ht.get(999), std::out_of_range);
}

TEST_F(IntIntHashTableTest, OperatorSquareBracketsGetNonExistentIntKey) {
    // Accessing a non-existent int key via operator[] inserts it with 0
    int value = ht[123];
    ASSERT_EQ(value, 0);
    ASSERT_EQ(ht.get(123), 0);
}

// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

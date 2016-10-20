// -------------------------------------
// projects/allocator/TestAllocator1.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------------------

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "gtest/gtest.h"

#include "Allocator.h"

// --------------
// TestAllocator1
// --------------

template <typename A>
struct TestAllocator1 : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A             allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::size_type  size_type;
    typedef typename A::pointer    pointer;};

typedef testing::Types<
            std::allocator<char>,
            std::allocator<int>,
            std::allocator<double>,
            my_allocator<char,   100>,
            my_allocator<int,    100>,
            my_allocator<double, 120>>
        my_types_1;

TYPED_TEST_CASE(TestAllocator1, my_types_1);

TYPED_TEST(TestAllocator1, test_1) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 1;
    const value_type     v = 2;
    const pointer        p = x.allocate(s);
    if (p != nullptr) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);}}

TYPED_TEST(TestAllocator1, test_10) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type  x;
    const size_type       s = 10;
    const value_type      v = 2;
    const pointer         b = x.allocate(s);
    if (b != nullptr) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}}

TYPED_TEST(TestAllocator1, test_4) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 4;
    const pointer        p1 = x.allocate(s);
    const pointer        p2 = x.allocate(s);
    const pointer        p3 = x.allocate(s);

    if (p1 != nullptr) {
        x.destroy(p1);
        x.deallocate(p1, s);}
    if (p3 != nullptr) {
        x.destroy(p3);
        x.deallocate(p3, s);}
    if (p2 != nullptr) {
        x.destroy(p2);
        x.deallocate(p2, s);}}

TYPED_TEST(TestAllocator1, test_9) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type  x;
    const size_type       s = 9;
    const value_type      v = 4;
    const pointer         b = x.allocate(s);
    if (b != nullptr) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}}

TYPED_TEST(TestAllocator1, test_3) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 3;
    const pointer        p1 = x.allocate(s);
    const pointer        p2 = x.allocate(s);
    const pointer        p3 = x.allocate(s);

    if (p2 != nullptr) {
        x.destroy(p2);
        x.deallocate(p2, s);}
    if (p1 != nullptr) {
        x.destroy(p1);
        x.deallocate(p1, s);}
    if (p3 != nullptr) {
        x.destroy(p3);
        x.deallocate(p3, s);}}

TYPED_TEST(TestAllocator1, test_7) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type  x;
    const size_type       s = 7;
    const value_type      v = 1;
    const pointer         b = x.allocate(s);
    if (b != nullptr) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}}

// --------------
// TestAllocator2
// --------------

TEST(TestAllocator2, const_index) {
    const my_allocator<int, 100> x;
    ASSERT_EQ(x[0], 92);}

TEST(TestAllocator2, index) {
    my_allocator<int, 100> x;
    ASSERT_EQ(x[0], 92);}

TEST(TestAllocator2, const_index_2) {
    const my_allocator<double, 50> x;
    ASSERT_EQ(x[0], 42);}

TEST(TestAllocator2, index_2) {
    my_allocator<double, 50> x;
    ASSERT_EQ(x[0], 42);}

TEST(TestAllocator2, const_index_3) {
    const my_allocator<char, 77> x;
    ASSERT_EQ(x[0], 69);}

TEST(TestAllocator2, index_3) {
    my_allocator<char, 77> x;
    ASSERT_EQ(x[0], 69);}

TEST(TestAllocator2, const_index_4) {
    const my_allocator<double, 17> x;
    ASSERT_EQ(x[0], 9);}

TEST(TestAllocator2, index_4) {
    my_allocator<double, 17> x;
    ASSERT_EQ(x[0], 9);}

TEST(TestAllocator2, const_index_5) {
    const my_allocator<char, 9> x;
    ASSERT_EQ(x[0], 1);}

TEST(TestAllocator2, index_5) {
    my_allocator<char, 9> x;
    ASSERT_EQ(x[0], 1);}

TEST(TestAllocator2, const_index_6) {
    try {
        const my_allocator<int, 9> x;
        // Should never get here. Call above should have thrown an exception
        ASSERT_EQ(true, false);}
    catch (...) {
        // Doesn't matter, as long as threw an exception then ok
        ASSERT_NO_THROW();}}

TEST(TestAllocator2, index_6) {
    try {
        my_allocator<int, 9> x;
        // Should never get here. Call above should have thrown an exception
        ASSERT_EQ(true, false);}
    catch (...) {
        // Doesn't matter, as long as threw an exception then ok
        ASSERT_NO_THROW();}}



TEST(TestAllocator2, const_index_7) {
    try {
        const my_allocator<double, 1> x;
        // Should never get here. Call above should have thrown an exception
        ASSERT_EQ(true, false);}
    catch (...) {
        // Doesn't matter, as long as threw an exception then ok
        ASSERT_NO_THROW();}}

TEST(TestAllocator2, index_7) {
    try {
        my_allocator<double, 1> x;
        // Should never get here. Call above should have thrown an exception
        ASSERT_EQ(true, false);}
    catch (...) {
        // Doesn't matter, as long as threw an exception then ok
        ASSERT_NO_THROW();}}



TEST(TestAllocator2, const_index_8) {
    try {
        const my_allocator<char, 8> x;
        // Should never get here. Call above should have thrown an exception
        ASSERT_EQ(true, false);}
    catch (...) {
        // Doesn't matter, as long as threw an exception then ok
        ASSERT_NO_THROW();}}

TEST(TestAllocator2, index_8) {
    try {
        my_allocator<char, 8> x;
        // Should never get here. Call above should have thrown an exception
        ASSERT_EQ(true, false);}
    catch (...) {
        // Doesn't matter, as long as threw an exception then ok
        ASSERT_NO_THROW();}}


TEST(TestAllocator2, const_index_9) {
    try {
        const my_allocator<int, 2> x;
        // Should never get here. Call above should have thrown an exception
        ASSERT_EQ(true, false);}
    catch (...) {
        // Doesn't matter, as long as threw an exception then ok
        ASSERT_NO_THROW();}}

TEST(TestAllocator2, index_9) {
    try {
        my_allocator<int, 2> x;
        // Should never get here. Call above should have thrown an exception
        ASSERT_EQ(true, false);}
    catch (...) {
        // Doesn't matter, as long as threw an exception then ok
        ASSERT_NO_THROW();}}

// --------------
// TestAllocator3
// --------------

template <typename A>
struct TestAllocator3 : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A             allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::size_type  size_type;
    typedef typename A::pointer    pointer;};

typedef testing::Types<
            my_allocator<char,   250>,
            my_allocator<int,    250>,
            my_allocator<double, 250>>
        my_types_2;

TYPED_TEST_CASE(TestAllocator3, my_types_2);

TYPED_TEST(TestAllocator3, test_1) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 1;
    const value_type     v = 2;
    const pointer        p1 = x.allocate(s);
    const pointer        p2 = x.allocate(s);
    const pointer        p3 = x.allocate(s);
    const pointer        p4 = x.allocate(s);
    const pointer        p5 = x.allocate(s);
    const pointer        p6 = x.allocate(s);

    if (p5 != nullptr) {
        x.destroy(p5);
        x.deallocate(p5, s);}
    if (p3 != nullptr) {
        x.destroy(p3);
        x.deallocate(p3, s);}
    if (p2 != nullptr) {
        x.destroy(p2);
        x.deallocate(p2, s);}
    if (p4 != nullptr) {
        x.destroy(p4);
        x.deallocate(p4, s);}
    if (p6 != nullptr) {
        x.destroy(p6);
        x.deallocate(p6, s);}
    if (p1 != nullptr) {
        x.destroy(p1);
        x.deallocate(p1, s);}}

TYPED_TEST(TestAllocator3, test_10) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 10;
    const value_type     v = 2;
    const pointer        b = x.allocate(s);
    if (b != nullptr) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}}

TYPED_TEST(TestAllocator3, test_4) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 4;
    const value_type     v = 2;
    const pointer        p1 = x.allocate(s);
    const pointer        p2 = x.allocate(s);
    const pointer        p3 = x.allocate(s);
    const pointer        p4 = x.allocate(s);
    const pointer        p5 = x.allocate(s);
    const pointer        p6 = x.allocate(s);

    if (p2 != nullptr) {
        x.destroy(p2);
        x.deallocate(p2, s);}
    if (p3 != nullptr) {
        x.destroy(p3);
        x.deallocate(p3, s);}
    if (p6 != nullptr) {
        x.destroy(p6);
        x.deallocate(p6, s);}
    if (p4 != nullptr) {
        x.destroy(p4);
        x.deallocate(p4, s);}
    if (p1 != nullptr) {
        x.destroy(p1);
        x.deallocate(p1, s);}
    if (p5 != nullptr) {
        x.destroy(p5);
        x.deallocate(p5, s);}}

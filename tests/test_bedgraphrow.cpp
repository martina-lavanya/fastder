//
// Unit tests for BedGraphRow class
//

#include "BedGraphRow.h"
#include <gtest/gtest.h>

TEST(BedGraphRowTest, ConstructorCalculatesLength)
{
    BedGraphRow row("chr1", 100, 200, 2.5);
    EXPECT_EQ(row.chrom, "chr1");
    EXPECT_EQ(row.start, 100);
    EXPECT_EQ(row.end, 200);
    EXPECT_EQ(row.coverage, 2.5);
    EXPECT_EQ(row.length, 100);
    EXPECT_EQ(row.total_reads, 0);
}

TEST(BedGraphRowTest, NormalizeCoverageToCPM)
{
    BedGraphRow row("chr1", 100, 200, 1000.0);
    uint64_t library_size = 10000000; // 10 million
    row.normalize(library_size);
    
    // Expected: (1000 / 10000000) * 1e6 = 100 CPM
    EXPECT_DOUBLE_EQ(row.coverage, 100.0);
}

TEST(BedGraphRowTest, NormalizeWithDifferentLibrarySize)
{
    BedGraphRow row("chr2", 500, 1000, 500.0);
    uint64_t library_size = 5000000; // 5 million
    row.normalize(library_size);
    
    // Expected: (500 / 5000000) * 1e6 = 100 CPM
    EXPECT_DOUBLE_EQ(row.coverage, 100.0);
}

TEST(BedGraphRowTest, DefaultConstructor)
{
    BedGraphRow row;
    // Just verify it doesn't crash and string is initialized
    EXPECT_EQ(row.chrom, "");
}

TEST(BedGraphRowTest, LengthCalculationDifferentSizes)
{
    BedGraphRow row1("chr1", 0, 100, 1.0);
    EXPECT_EQ(row1.length, 100);
    
    BedGraphRow row2("chr2", 1000, 5000, 1.0);
    EXPECT_EQ(row2.length, 4000);
    
    BedGraphRow row3("chr3", 50, 51, 1.0);
    EXPECT_EQ(row3.length, 1);
}

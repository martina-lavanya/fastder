//
// Unit tests for SJRow class
//

#include "SJRow.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(SJRowTest, ConstructorInitializesValues)
{
    SJRow row("chr1", 1000, 2000, 1000, '+', true, "GT", "AG", "1", "1");
    EXPECT_EQ(row.chrom, "chr1");
    EXPECT_EQ(row.start, 1000);
    EXPECT_EQ(row.end, 2000);
    EXPECT_EQ(row.length, 1000);
    EXPECT_TRUE(row.strand);
    EXPECT_TRUE(row.annotated);
    EXPECT_EQ(row.left_motif, "GT");
    EXPECT_EQ(row.right_motif, "AG");
}

TEST(SJRowTest, ConstructorWithNegativeStrand)
{
    SJRow row("chr2", 500, 1500, 1000, '-', false, "CT", "AC", "0", "0");
    EXPECT_EQ(row.chrom, "chr2");
    EXPECT_EQ(row.start, 500);
    EXPECT_EQ(row.end, 1500);
    EXPECT_FALSE(row.strand);
    EXPECT_FALSE(row.annotated);
}

TEST(SJRowTest, StreamInputOperator)
{
    std::istringstream iss("chr3 100 200 100 + 1 GT AG 1 1");
    SJRow row;
    iss >> row;
    
    EXPECT_EQ(row.chrom, "chr3");
    EXPECT_EQ(row.start, 100);
    EXPECT_EQ(row.end, 200);
    EXPECT_EQ(row.length, 100);
    EXPECT_TRUE(row.strand);
    EXPECT_TRUE(row.annotated);
    EXPECT_EQ(row.left_motif, "GT");
    EXPECT_EQ(row.right_motif, "AG");
}

TEST(SJRowTest, StreamOutputOperator)
{
    SJRow row("chr4", 300, 400, 100, '+', true, "GT", "AG", "1", "1");
    std::ostringstream oss;
    oss << row;
    
    std::string expected = "chr4\t300\t400\t100\t1\t1\tGT\tAG\t1\t1";
    EXPECT_EQ(oss.str(), expected);
}

TEST(SJRowTest, DefaultConstructor)
{
    SJRow row;
    // Just verify it doesn't crash
    EXPECT_EQ(row.chrom, "");
}

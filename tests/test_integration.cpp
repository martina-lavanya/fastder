//
// Integration test for Averager and related functionality
//

#include "Averager.h"
#include "BedGraphRow.h"
#include "Integrator.h"
#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

TEST(AveragerIntegrationTest, ComputeMeanCoverageBasic)
{
    // Create sample per-base coverage data
    std::vector<std::unordered_map<std::string, std::vector<double>>> all_coverages;
    
    // Sample 1
    std::unordered_map<std::string, std::vector<double>> sample1;
    sample1["chr1"] = {1.0, 2.0, 3.0, 4.0, 5.0};
    all_coverages.push_back(sample1);
    
    // Sample 2
    std::unordered_map<std::string, std::vector<double>> sample2;
    sample2["chr1"] = {2.0, 2.0, 2.0, 2.0, 2.0};
    all_coverages.push_back(sample2);
    
    Averager averager;
    averager.compute_mean_coverage(all_coverages);
    
    // Check that mean coverage was computed
    ASSERT_TRUE(averager.mean_coverage.find("chr1") != averager.mean_coverage.end());
    EXPECT_EQ(averager.mean_coverage["chr1"].size(), 5);
    
    // Check mean values (1+2)/2=1.5, (2+2)/2=2.0, (3+2)/2=2.5, (4+2)/2=3.0, (5+2)/2=3.5
    EXPECT_DOUBLE_EQ(averager.mean_coverage["chr1"][0], 1.5);
    EXPECT_DOUBLE_EQ(averager.mean_coverage["chr1"][1], 2.0);
    EXPECT_DOUBLE_EQ(averager.mean_coverage["chr1"][2], 2.5);
    EXPECT_DOUBLE_EQ(averager.mean_coverage["chr1"][3], 3.0);
    EXPECT_DOUBLE_EQ(averager.mean_coverage["chr1"][4], 3.5);
}

TEST(AveragerIntegrationTest, FindExpressedRegions)
{
    // Create sample per-base coverage data
    std::vector<std::unordered_map<std::string, std::vector<double>>> all_coverages;
    
    // Sample 1 with regions of high and low coverage
    std::unordered_map<std::string, std::vector<double>> sample1;
    // Create a pattern: 10 bases of high coverage, 10 bases of low coverage, 10 bases of high coverage
    std::vector<double> coverage_pattern;
    for (int i = 0; i < 10; i++) coverage_pattern.push_back(5.0); // high
    for (int i = 0; i < 10; i++) coverage_pattern.push_back(0.1); // low
    for (int i = 0; i < 10; i++) coverage_pattern.push_back(4.0); // high
    sample1["chr1"] = coverage_pattern;
    all_coverages.push_back(sample1);
    
    Averager averager;
    averager.compute_mean_coverage(all_coverages);
    averager.find_ERs(1.0, 5); // threshold=1.0, min_length=5
    
    // Should find two expressed regions (the two high coverage regions)
    ASSERT_TRUE(averager.expressed_regions.find("chr1") != averager.expressed_regions.end());
    EXPECT_GT(averager.expressed_regions["chr1"].size(), 0);
}

TEST(IntegratorIntegrationTest, WithinThreshold)
{
    Integrator integrator;
    
    // Test double threshold
    EXPECT_TRUE(integrator.within_threshold(1.0, 1.05));
    EXPECT_TRUE(integrator.within_threshold(1.0, 0.95));
    EXPECT_FALSE(integrator.within_threshold(1.0, 1.5));
    
    // Test uint64_t threshold
    EXPECT_TRUE(integrator.within_threshold(static_cast<uint64_t>(100), static_cast<uint64_t>(103)));
    EXPECT_TRUE(integrator.within_threshold(static_cast<uint64_t>(100), static_cast<uint64_t>(97)));
    EXPECT_FALSE(integrator.within_threshold(static_cast<uint64_t>(100), static_cast<uint64_t>(110)));
}

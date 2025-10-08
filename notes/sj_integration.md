# SPLICE JUNCTION INTEGRATION


1. wget https://duffel.rail.bio/recount3/human/data_sources/gtex/junctions/IN/BRAIN/gtex.junctions.BRAIN.ALL.MM.gz && gunzip 

2. group MM data by sample, store as dictionary-like file where sample is key and perhaps a vector of BedGraphRow is value
3. think about how to fill MM after creating RR file. also, there is an error with rr, none of the annotations are being correctly read

4. afterwards first iterate over chromosome 19 and simultaneously over the MM file grouped by the sample (mm['2931]) -> increase index of mm
when the position of the current sj has been passed
5. check if a sj matches the end of an ER -> if yes, check if there is a next ER that matches end of sj -> if yes and similar coverage, stitch together
as one gene. 

later: also consider closeby ERs that have similar coverage even if sj is not included


# TODO from 08.10
1. consider making std::vector<std::vector<double>> all_per_base_coverages; an unordered_map
instead, where the keys are the chromosomes and each chromosome has a vector of per-base coverages

std::vector<std::unordered_map<std::string, std::vector<double>> all_per_base_coverages;

2. implement chromosome sanity checks whenever calling compute_per_base_coverage on a bin of BedGraph
3. probably combine parser and averager to Preprocessor? currently i am storing all bedgraphs and all per base coverage twice!!
is it perhaps more efficient anyway? normalize is per-sample, so should be called in parser loop
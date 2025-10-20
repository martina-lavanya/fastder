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

std::vector<std::unordered_map<std::string, std::vector<double>>> all_per_base_coverages;

2. implement chromosome sanity checks whenever calling compute_per_base_coverage on a bin of BedGraph
3. probably combine parser and averager to Preprocessor? currently i am storing all bedgraphs and all per base coverage twice!!
is it perhaps more efficient anyway? normalize is per-sample, so should be called in parser loop


read_mm takes about 2-3 min to run!


# Algorithm
1. parse files: 
	MM file has splice junctions + occurrence count for each sample
	RR file uses the sj_id as an index and is a vector of SJRows
	Bedgraph file as a vector of BedGraphRows for each sample -> matrix of BedGraphRow vectors

	-> what to do about chromosome info? only problematic for per sample coverage, bedgraphrows have the chromosome info integrated

2. iterate over each sample's Bedgraphrow before moving on to the next sample and compute 
	1) library size
	2) per base coverages of the sample as a dictionary with key = chromosome, value = vector of doubles --> NO, this is unnecessary, the ER border will never be within a bin anyway since a bin has uniform counts...

3. normalize sample_per_base coverages BEFORE adding to all_per_base_coverages



# Questions:
- do I need sample_id information for all_bedgraphs? why iterate over samples in integrate_sj.cpp?? why do i need to organize the MM matrix by sample id?
	- get mean coverage vector across all samples with compute_avg_coverage(all_bedgraphs) -> assuming that the samples are already grouped meaningfully (e.g. by age, sex, disease, tissue etc.)
	- with find_ERs(), the cutoff of 0.25 is applied to the mean expression vector to keep only the expressed regions (ERs) -> this is done to the mean coverage vector
	=> I need to extract the MM entries for all samples that are used!

	# update 20.10: 
	- then iterate over each sample and find the stitched_regions (i.e. full genes rather than exons) for this sample -> why exactly over each samples if I'm working with the mean expression vector anyway? I think I just need to iterate over the
		1) expressed regions
		2) splice junctions
	simultaneously and see if they line up in terms of counts and bp positions
	- sample imformation is already lost when I compute the mean coverage vector! 




# integration of rail_id

- parse https://duffel.rail.bio/recount3/mouse/data_sources/sra/junctions/73/SRP150473/sra.junctions.SRP150473.ALL.ID.gz file to map rail_id to id used in MM file 
	rail_id is ordered by size, so smallest rail_id corresponds to MM id 1
	16802 <--> 0
	20089887 <--> 2931

- find mapping from rail_id to external_id (which is also the file name!) --> rail_id is unique across the whole recount3 dataset
- add sample_id to the BedGraphRow object

# TODOS from 15.10
- work on line 145 of Parser.cpp to implement the cumulative sum of sj_id -> count
- check it
- then continue with normalize question and confirm again that per_base_pair_coverage is not needed!

# Notes 20.10

- I have two mm objcts:
	1. rail_id_to_mm_id (which stores the mapping of e.g. rail_id 169404 to mm_id 2931) 
	2. all_mm_sj_counts (which stores the cumulative count of each splice junction across all samples that are 
	PRESENT in the dataset)
	--> should it be a map or an unordered map?
		-> need fast lookups of all_mm_sj_counts[sj_id] += count
		->

- for the exon stitching using the splice junctions, I want to iterate over the sj_ids in sequence of their mm_ids (since a smaller mm_id corresponds to a smaller chromosomal position)
	-> luckily smaller mm_ids correspond to smaller rail_ids



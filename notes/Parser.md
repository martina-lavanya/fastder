## Overview of Parser Class

# member variables

std::string path;
std::vector<std::vector<BedGraphRow>> all_bedgraphs; //TODO maybe change to unordered map with key = sample id, value = bedgraph of the sample?

// store RR info for each splice junctions
std::vector<SJRow> rr_all_sj;

//TODO use uint64_t instead for the sj_id
std::unordered_map<unsigned int, unsigned int> mm_sj_counts; // <sj_id, count> map of sj occurring in samples part of the user input

std::vector<std::pair<unsigned int, std::string>> rail_id_to_ext_id; // <rail_id, external_id> for all samples in the dataset

std::vector<std::pair<unsigned int, unsigned int>> rail_id_to_mm_id; // <rail_id, mm_id> mapping



# Algorithm
1) iterate over directory 
	- parse bigwig url list and fill rail_id_to_ext_id (to get rank of rail_id)
	- compile list of bedgraph files
2) sort rail_id_to_ext_id by rail_id
3) use list of bedgraph files to fill rail_id_to_mm_id (based on rail_id rank in rail_id_to_ext_id)
4) iterate over directory a second time
	- parse RR file into rr_all_sj (all splice junctions with their full information)
	- parse MM file into mm_sj_counts (counts per splice junction across all samples that the user provides)
	- parse BedGraph file and add to all_bedgraphs and count library size of the current sample
5) after parsing each BedGraph file, normalize by library size




# TODOs (starting 20.10)


- should rail_id_to_ext_id and rail_if_to_mm_id be maps rather than vectors of pairs? -> probably, since I only ever perform a lookup of ext_id (rail_id_to_ext_id[i].second) and
	- issue is that bedgraph_files only contains the file name with the external_id, which is a string so an (ordered) map won't work
	- unordered map with key = external_id is inconvenient because the map has to be sorted by rail_id afterwards
	- unordered map with key = rail_id is inconvenient because I look up by external_id
	--> check if unordered map full iteration is faster than vector full iteration (but probably hash map is slower because memory is not contiguous?)


- check if unsigned long long is needed anywhere else

# IMPORTANT TODO: should all_per_base_coverage be computed in Parser class anyway? yes, it saves an iteration...
## Bump Hunting Algorithm Design

# Derfinder Paper (https://academic.oup.com/nar/article/45/2/e9/2953306)
Algorithm:
1. calculate expressed regions (ERs) across the set of observed samples
2. compute per-base-pair average across all samples (adjusted by library size) --> gives a vector of mean expression across the genome
3. average-cutoff is applied to mean expression (i.e. mean base coverage) -> an expressed region is a contiguous set of bases that has a gene expression above the mean expression cutoff, where the mean expression is calculated over all samples using an F-statistic model
4. count number of reads that overlap with an expressed region --> in the paper, they use "bumphunter" from another paper --> The DERs can be annotated to their nearest gene or known feature using bumphunter 

F-statistic model:
- fit an intercept-only null model (just the mean expression? or what is the intercept?) and an alternative model which accounts for tissue differences with different coefficients
- calculate the F-statistic for each base or for each ER (depending on the approach)
- determine differential expression using a Bonferroni-adjusted P-value cutoff of 0.05

- they used the nearest exon coverage to model intronic regions

Using limma (15,16) functions lmFit, ebayes we fit an
intercept-only null model and an alternative model with co-
efficients for tissue differences. For each ER we calculated a
F-statistic and determined whether it was differentially ex-
pressed by tissue using a Bonferroni adjusted P-value cutoff
of 0.05

other takeaways from reread of the derfinder paper:

# PyBumpHunter: 2023 paper with bump hunting algorithm
https://scipost.org/SciPostPhysCodeb.15/pdf
- algorithm that searches for a deviation in a binned distribution (histogram)
- sliding window approach with variable width (e.g. between length 1 and 5)
--> I could also set a min and max width depending on common gene lengths


BigWig -> BedGraph conversion using kenutils (bigWigToBedGraph input.bw output.bedGraph)

for per-base coverage:

awk '{for(i=$2;i<$3;i++) print $1"\t"i"\t"i+1"\t"$4}' notes/example.bedGraph > perbase.bedGraph

	--> how can i normalize the coverage and for what criteria?

created virtual environment in conda called "mls_project" (conda activate mls_project) for python code

iterate over the entire chromosome (for each bp, we have a "value")

# Information about the recount3 datasets:
	- 	for the GTEx BRAIN dataset, there are 2931 samples of 54 tissue sites of ca. 1000 individuals
	- junction and bigWig coverage summaries are compiled with STAR (annotation-free)
	- for the splice junction files (MM and RR), all junctions that appeared in at least 5% of run accessions were considered
	16 % of all identified SJ in humans are not part of any tested annotation!! (so novel splice sites!)
		- in the paper, they also differentiate between SJ where either donor or acceptor are part of annotations, both are part of annotations (but not associated with each other) or none are part of annotations
		- cassette exon = splicing event where an intervening exon between two others can be either included or skipped --> same thing as exon skipping
		--> they found that the more cell-type specific a splicing event is, the less likely it is to be annotated
	- Megadepth is used to output .bigwig files with coverage
		- Megadepth is an efficient, C++ - based implementation that can convert the STAR output (BAM file) into a bigwig file with the coverage of each base or can re-quantify coverage over multiple (?) .bigwig files (https://github.com/ChristopherWilks/megadepth)
	- **recount3 outputs one bigWig file per sample containing its per-base coverage**
## Q: how do we get to the .bigWig file over all 2931 samples that is shown on the recount3 studyfinder? or is this .bigwig file somehow per sample anyway??? 
	No! The .bigwig file was downloaded from the URL for this sample, it is not aggregated!!

# Preprocessing
	- normalization? per-base coverage normalized to reads per million. this data is likely not normalized
	- note that for different sample sizes (e.g. sample 1 has total 40 mio reads, sample 2 has total 80 mio reads), we need to normalize to a common number of reads (e.g. 40 mio, so divide each read number of sample 2 by 2) 
	- mean coverage across samples (of the exact same tissue) --> compute mean bigwig across samples (avg coverage per base)
		--> use an f-statistic model to account for group differences (e.g. healthy / disease, brain developmental stage etc.)?

# Hyperparameters
	- decide on a minimal length that an expressed region needds to have to be considered (and not just noise or artifacts) --> derfinder uses 9bp
	- decide on a cutoff (which is compared with the mean coverage across samples, as calculated above)


# Algorithm
	- remove bases with very low coverage right away by applying a cutoff value to the mean coverage vector (across samples)
	- idea: iterate over the entire genome (perhaps still in .bed compressed version, so not a separate row for each nt but one entry for each window with the same length)
		1. check if the value for this window is close to the current bump (find an acceptable range)
		2. if yes, add to current bump, else start new bump?
		-> immediately discard all bumps that are shorter than e.g. 10bp

		(note that the shortest protein-coding human gene is 189 bp according to https://pmc.ncbi.nlm.nih.gov/articles/PMC6549324/ and the shortest exon is 2 bp, humans have a few micro-exons as seen in https://pmc.ncbi.nlm.nih.gov/articles/PMC403649/
			no human (and possibly of any species) introns shorter than 30 bp

	- how do I choose which transcript is likely expressed? just count how many DERs align with each transcript version and choose by majority vote?


Ideas:
1. calculating deviation by taking the p-value of the observed counts within the window and the mean counts (of the mean expression vector) --> choose the most significant bump (with the lowest p-value)
	- issue: since gene expression profiles dip quite rapidly (from 0 counts to 100 counts from one to the next bp), the most significant bump may not be that hard to identify
	note that depending on the site, the cutoff can be more or less clean cut
		not-so-clean: https://genome.ucsc.edu/cgi-bin/hgTracks?db=hg38&lastVirtModeType=default&lastVirtModeExtraState=&virtModeType=default&virtMode=0&nonVirtPosition=&position=chr1%3A160037400%2D160037600&hgsid=3165714530_UK0JAgDpH119ju1HV7IOFvAtcbIn
		super-clean: https://genome.ucsc.edu/cgi-bin/hgTracks?db=hg38&lastVirtModeType=default&lastVirtModeExtraState=&virtModeType=default&virtMode=0&nonVirtPosition=&position=chr1%3A160042400%2D160043000&hgsid=3165714530_UK0JAgDpH119ju1HV7IOFvAtcbIn

megadepth: computing coverage for genomic regions from the recount3 bigWig
files 


## data formatting of recount3:
The coverage summaries provided in recount3 are stored as tab delimited matrices in
GZip compressed flat files. Rows are genes or exons, and columns are samples. 

Coverage is stored as raw per-base counts summed over the relevant annotation interval (gene or
exon). 

Junction files follow the Market Matrix format [64] which represents the junction
coverage matrix as a sparse list of matrix coordinates for those cells which are non-0. The
non-0 values represent the raw count of split reads supporting a given junction. Per-base
coverage values are stored in bigWigs, one bigWig file per sample.

bigWigToBedGraph — converts a bigWig file to ASCII bedGraph format 
# --> I am assuming without any normalization or scaling applied


# TODO: 
1. understand how the per-base coverage files were made in recount3 --> so far, no mean computation


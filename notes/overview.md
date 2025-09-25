### PROJECT OVERVIEW

## BACKGROUND
developing a method for reference-free RNA-seq quantification starting from (genome) coverage files

- what does reference-free mean? it means that we do map to the genome using STAR (an ultrafast RNA-seq aligner that maps directly to the genome with the maximum mappable prefix strategy), but we don't use **annotations** of the genome (i.e. which exon or gene is where). we first identify differentially expressed regions based on the genome coverage files and then we compare these to genome annotations



Resources [1] and [2] are the most relevant for understanding the problem
> [1] https://nar.oxfordjournals.org/content/early/2016/09/29/nar.gkw852
	- problem: in DGEA, there can be incorrect or incomplete gene annotation --> could affect downstream modelling of the nr of reads
# Old approaches (https://academic.oup.com/biostatistics/article/15/3/413/223630, original DER analysis)
1. # Annotate-then-identify
	- count reads that overlap with known genes or exons (they count as one read for this gene, where each gene or exon is defined by start and end coordinates)
	- normalize for depth and library size
	- then tests for differential expression 
	--> cannot detect DE in new or mis-annotated regions
2. # Assemble-then-identify
	- reconstruct the transcriptome by aligning with the reference genome (like in 1) but the result is a set of transcript models 
	--> can discover new transcripts, alternative splicing and isoforms
	- can identify expression per transcript (e.g. TPM)
	--> problems are ambiguity and computation
# DER: identify-then-annotate
- DER (differentially expressed regions): first identifies regions that show differential expression signal and then annotates these regions using previously annotated genomic features
	- advantages: agnostic to annotation --> can identify differential expression signal if 
		1. a feature is slightly mis-annotated or where the read mappings do not quite match up with the feature's annotation
		2. differential expression exists in regions that do not overlap annotated features (novel transcript)
- process: 
	1. align reads to genome -> create a count per nt position matrix (dimension bases x samples)
	2. fit linear regression to test for differences between groups --> get a test statistic for each base
	3. group the nt positions with similar signals into DERs using HMMs (this approach was then discarded in the new derfinder)
	4. test regions for statistical significance
	5. annotate to see if a DER overlaps with a known exon, intron or neither (intragenic) --> also reports any combination of these three options

# Extension of derfinder package (this paper)
- more efficient: original derfinder is computationally heavy if each base is tested
	- here, **bump hunting** is used to find clusters of contiguous bases (= bumps) with an elevated signal (instead of individual bases)
	- produces a region-level expression matrix (e.g. gene counts but without annotation)
	# Q: isn't this also more robust to sequencing errors? 
	yes, it reduces noise too

- algorithm:
	Single base-level approach: 
	1. calculate the average coverage for each base (over all samples) and adjust it by library size if needed
	2. apply cutoff to each base rather than to an entire ER
	3. calculate F-statistics for each base --> then identify DERs via bump hunting

	ER approach
	1. calculate the average coverage for each base (over all samples) and adjust it by library size if needed --> gives a vector of mean coverage per base (= average number of reads per base pair)
	2. use a cutoff value (e.g. at least a mean of 0.25 reads is required for a base to become a candidate region) --> important: this cutoff is directly applied to the mean coverage vector
		i. a candidate ER is any contiguous set of bases > 9 bp that passes this cutoff **(per base or on average across the region??)**
	3. then summarize the base-level coverage per sample in a matrix (DERs x samples) 

> [2] https://pmc.ncbi.nlm.nih.gov/articles/PMC8042062/
# Idea: single-cell analysis when high-quality gene annotation is not available
- TAR-based workflow (transcriptionally active regions)
1. use a HMM (groHMM) to separate the genome into transcribed and untranscribed regions based on read coverage
2. take the TARs and classify them into annotated and unannotated TARs (aTARs and uTARs, depending on if the overlap with existing gene annotations)
3. generate a single-cell expression matrix of TARs
4. then apply single-cell analysis like clustering, PCA/UMAP --> then test for differential expression of TARs between clusters
5. test differentially expressed uTARs for sequence homology (alignment with BLAST)
--> if they match to any known transcripts, it could imply new isoforms or missing annotations
--> if they don't match, they could be new genes


> [3] https://genomebiology.biomedcentral.com/articles/10.1186/s13059-021-02533-6

# General: provides a large RNA-sequencing dataset that was processed in different ways

recount3 consists of five types of data summaries — Quality Control (QC), gene-level quantification, exon-level quantification, junction counts, and per-base coverages — packaged into tables with associated metadata and organized at the study level. 

    gene files: one count matrix per annotation
    exon files: one count matrix per annotation
    3 exon-exon junction files: the sparse count matrix data in Matrix Market (MM) format, the small list of sample identifiers (IDs), and the exon-exon junctions coordinate information (RR file)


--> probably need the per-base coverages

Idea is to use the coverage bigwig for annotation-agnostic bump hunting and gene expression analysis


Note that we have access to coverage files (meaning, aligned RNA-seq runs) for almost all GEO/SRA at [3]
---> GEO and SRA are public repositories where RNA-seq data is stored
		GEO: processed expression data (expression matrices etc.)
		SRA: sequence read archive (e.g. far FASTQ files, unaligned)
Aim: speed up [1-2] by processing [3]'s outputs to detect the "bumps" or expressed regions.



## RESOURCES 
- STAR paper: Particularly important to be aware of the SJ files (and have a general idea of novel splicing detection)
https://pubmed.ncbi.nlm.nih.gov/23104886/
	- an ultrafast RNA-seq aligner that maps directly to the genome with the maximum mappable prefix strategy (MMP is the longest substring of a read starting in position i that matches to at least one place in the genome) --> find all of the maximal exact pieces and stitch them together
	- detects splice junctions efficiently (also novel ones)
	- produces outputs that include aligned reads (BAM) and splice junction files

		- https://github.com/alexdobin/STAR/blob/master/doc/STARmanual.pdf

		# Q: what are SJ files? 
		sites where introns were removed from pre-mRNA --> a splice junction is the joining place of two exons in mRNA
		- novel splice junctions = junctions that are not present in the annotation
			**Detection method: 2-pass mapping**
			1. run STAR normally -> will map all that can be mapped and output all junctions (novel and known)
			2. take all junctions and add them to a set of annotated junctions
			3. run STAR again but using the updated annotation --> allows much more reads to be mapped to those novel junctions

	- coordinate formats: BED, wiggle, bigwig 
		- https://genome.ucsc.edu/goldenpath/help/bedgraph.html (coordinate formats)
			1. BED --> describe genome intervals
				chromA  chromStartA  chromEndA  dataValueA
				chr19	49302000	49302300 	-1.0
			2. bigwig -> store continuous-valued RNA-seq coverage (compressed version of wig)
		--> bed files (only peak location), bigwig files have continuous signal
		- https://genome-blog.gi.ucsc.edu/blog/2016/12/12/the-ucsc-genome-browser-coordinate-counting-systems/
		(counting framework)

		1. 0-start, half-open (0-based)
		used in BED files -> the start position is counted from 0, but the interval includes bases up to end-1 (like a for loop in python)

			example for 1 base: chr1 127140000 127140001 (the one base is at position 127,140,001)

		2. 1-start, fully-closed
		used in the UCSC Genome Browser web interface
		chr1:127140001-127140001 (start and end position are inclusive)

		# Conversion rules:
			0-based to 1-based: add 1 to the start positon
			1-based to 0-based: subtract 1 from the start (end stays the same)

	- https://rna.recount.bio/ 
		paper and data. We're mostly going to use their bigWigs and SJ files

		Overview:
			- rail_id: id created by the monorail system
			- external_id: original sample identifier
				GTEX-1117F → donor ID (person or organism)
				3226 → tissue (brain, liver etc)
				SM-5N9CT → sequencing sample ID (e.g. library or sequencing protocol)
				.1 → version (if a sample is processed more than once)


### RNA-SEQ REFRESHER

# RNA-seq workflow: 

	RNA extraction, RNA fragmentation, cDNA generation, library amplification, and sequencing on an NGS platform to get strings of continuous sequence data in “reads”.
1. extract mRNA and remove rRNA
2. fragment into small reads
3. convert to cDNA (can either maintain the strand info, so sense or antisense, or not --> depends if we want to know which DNA strand that the RNA originated from)
	Stranded (also called directional) RNA-seq first accomplished this by using a modified dUTP nucleotides in place of dTTPs for second-strand cDNA synthesis (Parkhomchuk 2009). This allows for the second strand to be removed by digestion via uracil-N-glycosylase prior to PCR amplification.

	sequencing adapters are added to the ends 
4. amplify with PCR
5. next-generation sequencing with Illumina 
	single-end (only sequence from forward adapter) or paired-end (sequence from both ends)
6. output as a FASTQ format -> a txt file with the raw sequence and score


# Data Analysis pipeline: 
- input: the FASTQ files

1. Map or assemble: align FASTQ files using a reference genome OR de novo assembly (without a reference genome)
	# alignment to reference genome
	outputs alignment files
	# reference-free mapping: 
	assemble short reads into larger contigs based on areas of sequence overlap
		--> difficult because of sequencing errors, coverage gaps and splicing variants
- depth = number of reads that cover a specific region

2. quality control: check FASTQ raw reads with FASTQC
	understand the quality of reads and analysis as well as normalization (RPKM, TPM) and counting (for example, to characterize coverage and number of genes). The purpose of quality control checks of raw reads is to detect PCR bias, contamination, sequencing errors, and other artifacts. These quality checks look for GC content, adapters, number of reads/fragments (k-mers), and duplicate reads. 

3. transcript quantification:
important to normalize read counts first (e.g. transcripts per million TPM, which adjusts for read number and gene length)

	# differencial gene expression analysis 
	see if a gene is expressed more or less compared to normalized read counts (e.g. with EdgeR by Robinson)

	# splicing analysis
	identify splice variants of a gene

good summary: https://www.bio-rad.com/en-ch/applications-technologies/rna-seq-workflow?ID=Q106ZUWDLBV5

## OTHER CONCEPTS

# Matrix Market Exchange Format
only has as many entries as the matrix has non-zero entries

a real 5x5 general sparse matrix.

             1    0      0       6      0     
             0   10.5    0       0      0     
             0    0    .015      0      0     
             0  250.5    0     -280    33.32  
             0    0      0       0     12     


MM format
  5  5  8
    1     1   1.000e+00
    2     2   1.050e+01
    3     3   1.500e-02
    1     4   6.000e+00
    4     2   2.505e+02
    4     4  -2.800e+02
    4     5   3.332e+01
    5     5   1.200e+01

## MEETING NOTES
polyA recon, most data is exploring the 3' --> we don't normally have the first exon in the datasets

mRNA: does the mRNA contain introns or not
	can have pre-spliced or partially splice mRNA depending on the dataset
scRNA seq: people don't sequence full cell, instead only nuclei are sequenced but there are lots of introns of course

--> these things should be fixed with library prep 
	depends on the source


what do we get from rna seq
	- cannot align spliced mrna if splice site is not annotated 


	depending on ref genome the coordinates mean somethng different


STAR is splicing aware

GTFs tell us for each gene which is the transcripts and exons --> aim is to find all splicing events in all humans
	- note that one gene can have multiple transcripts thanks to alternative splicing
	- there are waves of people using gencode, refseq, phantom etc as reference
	- people started comparing the references and they do not match
	- CHESS combines all these references

	junction tables:
		- will have annontated, then say rs, gencode, ph which means that this junction is in all three references

- STAR can also discover unannotated junctions
	- more reads per site means more likely there is a junction

# Question: how do i report the spliced intron, do i say coverage 10 for 10 reads or 0 since it was spliced (if the surrounding exons had 10 reads)?

another evaluation method:
	- gtf: 
	- compare coverage to gene annotation by gtfs
	- discuss ways of making the quantification more sensible of expressed unannotated introns

	we are not discussing variants it's too much

harvard collected all sra data from mouse and human and align everything to give coverage 
	- show that some splice sites are not annotated even though they have been sequenced enough(cumulative nr of junctions)
	- Fig 3: some junctions are less explored in certan cell types
	- if some junction is diff. expr. in a specific cell type it is likely not annotated


kentutils encode-dcc to convert bed <-> bigwig



annotation to select:

	gencode as less genes
	fantom has more genes
	refseq is tradition
	ercc artificial mrna added as a control to RNA seq


	gencode:
		we care about junctions rr and mm

	sparse matrix: gene x cell

		very low detection of genes, so don't store as matrix
		instead have a file with 
		file 1 			file 2

		row1 actin 		col1 celltype1
		row2 tubulin	col2 celltype 2

		1 1 10 (row 1 col 2 has value of 10)
		--> only store data for positions that are filled 



chromosome is ercc
start-end is quite short (short intron, but there can also be long introns)
strand, doesn't mean they are on same strand

humans have preferred sequence (= motif) at start and end of exon
	can see if these motifs are annotated

	if the annotation is in cH38 (chess version 38) that is a great sign


rail_id (use other dataset from monorail to know which it corresponds to)
	can look up chr start and end position in the ucsc genome browser
		not very thick line is an intron

		i thinkkk external id has the highest granularity in the table (compared to e.g. rail id)

	download bigwig, then use the dcc tools from above to convert to bed graph

	bed hack: for coverage profiles, the genome is binned into windows and then they count overlap of reads
	
	in monorail, they create window as long as it's needed (variable length)


which dataset to start with:
	- not cancer
	- human stem cell, not too large

GTEx --> tried to sequence every cell type in human, maybe take stem cells from GTEx, any cell type should work since all healthy

parallelization?
	- splicing events across chromosomes which cannot be taken into consideration for this project


# Questions
1. Use the MM and RR files
	- RR files provide an overview of all exon-exon junction coordinate info (as identified by STAR?)
	- MM files provide a count matrix of each junction coverage
how am I meant to use bump hunting for this since a splice junction is one specific location and not a sequence of base pairs like a gene? I thought that the idea was to quantify differential gene expression by finding regions with higher or lower signal (bumps) --> speed up the algorithm of derfinder and TAR-based workflow by implementing it in C++
--> how does this connect to the splice junction annotation?

The idea is to include sj files in the bump hunting itself (to aid the finding of junctions)
 

2. There are no per base coverage files 
	--> no, but the bigwig files can be "binned" to contain per-base information

perhaps let user parametrize how significant it should be

bigwig not strand specific, but the other data is!

use the sj to integrate intron info --> the idea is not to identify splice junction sites with the coverage bigwig files



bigwig can have per nucleotide resolution
	- 

## IMPORTANT DECISIONS
1. how many reads do i need so that a region can be highly expressed rather than just noise (e.g. with 10 reads) --> also relative to total nr of reads or total coverage

2. is novel annotation more likely to be an error or more interesting
		- perhaps opt-in to use annotation and focus more on novelsplice sites or not

3. reference genome also has contigs --> better to use normal chromosomes only, keep y chromosome or not

4. what cutoff to choose?

5. what is the impact of the lack of strand specificity in the .bigwig files? 

6. should i use different thresholds for different regions? --> yes, that is why i have to use the mean base coverage as comparison base!

7. decide what counting system i want to use to indicate base positions

8. think about the integration of the sj files

9. do i use the y chromosome and ERCC?


Notes 12.9: look at bigwig file in 1 bp resolution -> how? start thinking about algorithm and how to integrate the sj junction files.

# Names
fastder
dEXpress, DExpress, D-Express
# Questions about derfinder paper:
1. how does the ER approach differ? I think they use the sum of coverage across each region and calculate differential expression based on that
2. is the average-coverage cutoff applied base-wise (each base in an ER must have an average coverage of 5 reads) or per region (ER must have an average coverage of 5 reads across the whole region, more robust)


# Meeting 17.9. with Izaskun

1. should I aim for a single base-level or expressed region approach? I think single base-level approach, since C++ is faster and single base will be more precise.

gene dependent

consider prior exon to see how high signal

many are polyA

chromatin accessibility puts some non-contiguous genes in an open chromatin state and they are co expressed


polymerases sometimes transcribe in the opposite direction, so tss could have some nt before or after

2. to practice, how many samples should i use to compute the mean expression vector?




3. should my approach only group bases that exceed the threshold for the F-statistic, or should I also have a tolerance (e.g. if one base is 
below the threshold but the next 5 are above again, I will still count it)?



might have drops sometimes depending on cell type



4. have you got any inputs regarding the calculation of the significance level of a bp? For instance, derfinder uses F-statistic and edgeR used a likelihood ratio test (for more complex setups)



first normalize by reads!

check kentutils if there is a way 

could be that nuclei and not cells are sequenced or genomic verdreckt

use gtf first to sample some introns to learn base-line signal

5. where do i find info about the sample metadata (gender, age, brain region)?

	reads shorter or longer,

6. what is my ground truth?

diseases with knocked out spliceosome where all introns are expressed


similarity of expressed regions

try out with one chromosome, chr19 works well
-> have different levels of expression


CNV will affect normalization
it will be hard to consider chr-level expression differences

# 17.9.25 TODOs for next time

1. check metadata of brain samples and choose a few with similar groups (age, sex, brain region) --DONE

2. check for library size and normalize (perhaps do this in python?), select chr19 --DONE

3. choose some samples and compute their average expression --DONE

4. then implement a sliding window that iterates over chromosome 19 and tries to find differentially expressed regions
	use a cutoff of 5 reads for now --CURRENTLY WORKING ON THIS


5. compare to visualization or genome uscs browser to validate results? or directly map them to annotations?

6. how do i use splice junction files?

remember to clone git repo and to download the files via wget onto the server directly if possible 
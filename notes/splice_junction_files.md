## Notes about the GTEx brain junctions RR file
--> this is across all samples!
chromosome	start	end		length	strand	annotated	left_motif	right_motif	left_annotated																					right_annotated
chr1			12698	13203		506			+				0					GT					AG					aC19,gC19,gC24,gC25,gC26,gC29,gC33,kG19,kG38,sG19,sG38	0
chr1			12698	13220		523			+				1					GT					AG					aC19,gC19,gC24,gC25,gC26,gC29,gC33,kG19,kG38,sG19,sG38 	aC19,cH38,gC19
chr1			12698	13224		527			+				0					GT					AG					aC19,gC19,gC24,gC25,gC26,gC29,gC33,kG19,kG38,sG19,sG38	gC19


describes the chromosome, bp position, annotation


# strand: 

   1. + means that the splice junction is on the forward (sense, 5' -> 3') strand of the reference genome (so, the DNA!)
   2. - means that the splice junction is on the reverse (antisense, 3' -> 5') strand of the reference genome (so, the DNA!)

	remember: RNA polymerase always synthesizes RNA in the 5′ → 3′ direction, but it can use **either** DNA strand as the template.


# annotation
- both donor and acceptor have to be annotated
	- annotated = 0: the splice junction does not appear in the reference gene models
	- left_annotated and right_annotated:  the donor site (left) or acceptor site (right) matches known exon boundaries in many references of gC (GENCODE version xx)

	remember:
	- Donor Site (5′ splice site): This site marks the beginning of an intron and the end of the preceding exon. The most common donor site sequence is GT (GU in pre-mRNA). 
	- Acceptor Site (3′ splice site): This site marks the end of an intron and the beginning of the following exon

	so if the left site is annotated but the right is not, this means that we have 

	--------- xxxxx xxxxxxx -------
	exon 1    i1     i2     exon 2

	where either i1 + i2 was the known intron and spliced out before exon 2 (known site) or i1 was the known intron and i2 belonged to exon 2 in the reference annotation

Note: ERCCs (the External RNA Controls Consortium spike-ins) are often added to RNA-seq experiments as artificial control RNAs



# MM file

%%MatrixMarket matrix coordinate integer general
%------------------------------------
9484210	2931	699368828 
	1	2887	1
	1	2068	2
	2	2085	1
	3	1251	1
	3	2064	2
	4	2085	1
	5	2356	1
	6	2065	1

--> 9484210	rows (nr of splice junctions) --> but one splice junction can be on multiple rows if it is mapped by reads of multiple samples
--> 2931 columns (nr of samples)
--> 699368828 (nonzero entries), nr of rows!!
--> third row: how many reads mapped across the junction in sample x

# linking MM and RR
for splice junction id 1, in sample 2887, there was 1 read that mapped to it, and in sample 2068, there were 2 reads that mapped to it

how to map RR files (exon-exon junction coords) to MM files (occurrence of each junction in the 2931 samples)
	--> the RR file has exactly 9484210 junctions, which is also the number of junctions (but not rows) in the market matrix (MM) file!


# meaning of SJ
- contain info about start, end, length of a splice junction 
  - so is a splice junction also informing about the length of the spliced region (intron, cassette exon)
  --> start = first base of the intron, end = last base of the intron

**Integration ideas**
- I know for which samples a splice junction (with its exact coordinates) has nonzero coverage (= reads mapping to it) - what do i do with this info?
    - either i could remove all DERs that map to a splice junction or a region between a splice junction
    - or perhaps the aim is to find expressed introns?
    - or to annotate intronic and exonic regions? what about intergenic regions (not even in pre-mRNA)? UTRs?
  can we assume that an intron is surrounded by exons, so the regions before and after the intron are likely exons? 
    - to verify that a DER is actually in an exonic region -> stronger support for the DER?


# ideal ground truth data

1. per-bp coverage file for each chr, normalized to counts per million bp
2. contiguous regions with above-threshold expression with their coordinates + ground-truth annotation of exon, intron
3. classify a DER as expressed exon, expressed intron or intergenic?

perhaps write algorithm which performs lookup in array where each bp position is classified as intron or exon
-> is it more efficient to lookup the start & end via binary search or just index lookup where each bp is one vector element?

let's say binary search:
	- example region start 112, end 145, avg coverage 1.2
	- check if start-end is fully intronic, fully exonic or overlaps with both
			maybe create struct with start, end, type = EXON INTRON INTRAGENIC COMBO for each splice junction in the RR file

			what about annotation vs no annotation, and how it's annotated?



			maybe say that if the region partially or fully overlaps with an intron (i.e. lies between the start and end of the intronic site), then i can check if this splice junction is annotated, i.e. a known intron, or unannotated

			do i want to add a trust score (i.e. how many or which annotations it's part of, like cH38 has more weight than others)



			is the assumption that the sj files actually tell me what splicing occurred in this sample? so should i group by sample to get a list of all sj per sample? and then, what do i do with this info?

					--> assume that all ERs that fall into SJ regions are actually expressed introns (if the SJ was previously annotated) or even intragenic regions (if the SJ was not previously annotated)?

					--> then compare to ensembl database to check what they actually match to? how do i combine this info, e.g. if an ER (partially) overlaps with a SJ (i.e. an intron) but the annotation says it's an exon, do i assume it's a cassette exon? a wrong annotation?

					--> OR assign 3 scores based on SJ files, 0: exon, 1: known SJ, 2: novel SJ, the splice sites could be stored in a struct with start, end, boolean annotated and ordered by start --> binary search to match ER to start coordinate

					--> then compare to annotation, and check what it overlaps with (exon, intron, intragenic)


					IMPORTANT: just because something was spliced, it doesn't necessarily have to be an intron, could also be an exon that can be skipped (= cassette exon)



					COMET C++-oriented



can input different gffs to the gffcompare tool

	build some sort of tree of cell

	build metric of how similar two gtfs are -> if they are more similar, then they have similar gene expression


	up to 64 cores for parallelization

	parallelize the different chromosomes but remember that other organisms have more chromosomes!